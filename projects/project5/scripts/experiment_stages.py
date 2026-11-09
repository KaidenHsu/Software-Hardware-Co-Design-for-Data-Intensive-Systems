"""Kernel stages: preserve the oracle, build the harness, simulate, and extract ROI traffic."""
import collections
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import shlex
import subprocess
import sys

# Log numbers follow execution order; CLI stage names remain unchanged.
LOG_FILES = {
    'check': '0_check_tools.log',
    'baseline': '1_check_correctness.log',
    'generate': '2_snapshot_gem5_sources.log',
    'build': '3_compile_workload.log',
    'gem5': '4_simulate_gem5.log',
    'trace': '5_extract_roi_trace.log',
    'replay': '6_replay_req_equiv_ramulator_trace.log',
    'payload': '7_replay_byte_equiv_ramulator_trace.log',
    'report': '8_generate_report.log',
}


def stage_log_file(logs, stage):
    """Resolve a stage's consolidated log file beneath the selected log root."""
    return logs / LOG_FILES[stage]


# Packet command classes exported to Ramulator's simpler load/store vocabulary.
READ_CMDS = frozenset(('ReadReq','ReadExReq','ReadCleanReq','ReadSharedReq',
                       'LoadLockedReq','LockedRMWReadReq','SoftPFReq','SoftPFExReq','HardPFReq'))
WRITE_CMDS = frozenset(('WriteReq','WriteLineReq','WritebackDirty','WritebackClean',
                        'WriteClean','StoreCondReq','LockedRMWWriteReq'))

# Keep command announcements outside stage-output redirection.
COMMAND_STREAM = sys.stdout

# Shared validation, command execution, and protobuf decoding helpers.
def sha256(path):
    """Return the SHA-256 hex digest used to identify a file by its contents."""
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def check(ok,msg):
    """Raise a framework validation error when the required condition is false."""
    if not ok: raise RuntimeError('W8_KERNEL_PREFLIGHT_FAILED: '+msg)


def append_command_header(stream, command):
    """Append a command header, separating blocks with exactly three blank lines."""
    # Binary offsets let run() return just this command's block, even with Unicode.
    stream.seek(0, os.SEEK_END)
    end = stream.tell()
    while end:
        stream.seek(end - 1)
        if stream.read(1) not in (b'\n', b'\r'):
            break
        end -= 1
    stream.truncate(end)
    stream.seek(end)
    if end:
        stream.write(b'\n\n\n\n')
    start = stream.tell()
    stream.write(('$ ' + command + '\n\n').encode('utf8'))
    stream.flush()
    return start


def run(args, log, cwd=None, timeout=None, env=None):
    """Append combined command output and return only this command's captured block."""
    args = list(map(str, args))
    command = shlex.join(args)
    print(command, file=COMMAND_STREAM, flush=True)
    # Stage diagnostics use another append handle to this file. Flush before the
    # subprocess so Python buffering cannot move diagnostics past command output.
    sys.stdout.flush()
    sys.stderr.flush()
    log.parent.mkdir(parents=True, exist_ok=True)
    with log.open('a+b') as stream:
        start = append_command_header(stream, command)
        try:
            cp = subprocess.run(args, cwd=cwd, env=env, stdout=stream,
                                stderr=subprocess.STDOUT, timeout=timeout, check=False)
        except (OSError, subprocess.TimeoutExpired) as exc:
            stream.write(('\n' + str(exc) + '\n').encode('utf8'))
            stream.flush()
            raise RuntimeError(f'W8_KERNEL_RUN_FAILED: {args[0]} see {log}: {exc}') from exc
        stream.flush()
        stream.seek(start)
        block = stream.read().decode('utf8', errors='replace')

    if cp.returncode:
        raise RuntimeError(f'W8_KERNEL_RUN_FAILED: {args[0]} see {log}')
    return block


def find_gem5_root(arg):
    """Resolve an explicit or conventional gem5 installation containing gem5.opt."""
    if arg: return Path(arg).expanduser().resolve()
    for p in (Path.home()/'gem5',Path.home()/'tools/week8/gem5'):
        if (p/'build/X86/gem5.opt').is_file():return p.resolve()
    raise RuntimeError('cannot find installed gem5 (expected ~/gem5 or ~/tools/week8/gem5)')


def parse_memcmd_enum(path):
    # --- Find the Command enum in the installed gem5 packet.hh. ---
    # re.S allows the enum body to span multiple lines.
    """Read gem5 Command enum values and return the numeric-ID-to-name mapping."""
    text=path.read_text()
    match=re.search(r'\benum\s+Command\s*\{(.*?)\}',text,re.S)
    check(match is not None, 'MemCmd enum absent in installed gem5 source')

    # Strip block and line comments before splitting enum members at commas.
    body=re.sub(r'/\*.*?\*/','',match.group(1),flags=re.S)
    body=re.sub(r'//[^\n]*','',body)

    # Track name -> value while parsing, including references to earlier members.
    # Start at -1 so the first implicit C++ enum value becomes zero.
    names={};v=-1
    for chunk in body.split(','):
        chunk=chunk.strip()
        if not chunk:continue

        # Separate an optional explicit assignment, such as Name = Earlier + 1.
        name,eq,expr=chunk.partition('=');name=name.strip()
        check(re.fullmatch(r'[A-Za-z_]\w*',name) is not None,f'bad enum member {name}')

        if eq:
            # Support a decimal integer or earlier name, optionally +/- an integer.
            # Reject other expressions rather than silently guessing command IDs.
            mm=re.fullmatch(r'\s*([A-Za-z_]\w*|\d+)\s*(?:([+-])\s*(\d+))?\s*',expr)
            check(mm is not None,f'unsupported enum expression {expr}')
            base=int(mm.group(1)) if mm.group(1).isdigit() else names.get(mm.group(1))
            check(base is not None,'unknown enum reference '+expr)
            v=base+((1 if mm.group(2)=='+' else -1)*int(mm.group(3)) if mm.group(2) else 0)
        # Without an assignment, C++ increments the previous member value.
        else:v+=1
        names[name]=v

    # Confirm the expected baseline numbering before using this mapping on packets.
    check(names.get('ReadReq')==1 and names.get('WriteReq')==4,'unexpected gem5 MemCmd numbering')

    # Trace packets store numeric IDs, so return the inverse: value -> name.
    return {v:k for k,v in names.items()}


def extract_roi_packets(gem5root,trace,roi,output):
    # --- Load the decoder and command vocabulary from the installed gem5. ---
    # Respect old pre-generated protobuf classes from installed gem5 v25.1.
    """Write ROI-filtered LD/ST records from a protobuf trace and return audit metadata."""
    os.environ['PROTOCOL_BUFFERS_PYTHON_IMPLEMENTATION']='python'
    sys.path.insert(0,str(gem5root/'util'))
    import packet_pb2, protolib
    id_to_name=parse_memcmd_enum(gem5root/'src/mem/packet.hh')

    # --- Load and validate the half-open measurement interval [start, end). ---
    window=json.loads(roi.read_text())
    start=int(window['roi_start_tick']);end=int(window['roi_end_tick'])
    check(0<=start<end,'invalid gem5 ROI ticks')

    # Keep all ROI command counts, skipped commands, and exported packet sizes.
    # Also account for packets outside the ROI and bytes represented by LD/ST.
    counts=collections.Counter();skipped=collections.Counter(); sizes=collections.Counter()
    outside_before=outside_after=inside=reads=writes=0
    rbytes=wbytes=0;first_t=last_t=None

    # --- Decode the binary protobuf stream and write a plain-text replay trace. ---
    inf=protolib.openFileRd(str(trace))
    try:
        # Validate the file signature and decode its header (including tick frequency).
        check(inf.read(4)==b'gem5','invalid gem5 protobuf magic')
        head=packet_pb2.PacketHeader()
        check(protolib.decodeMessage(inf,head),'invalid protobuf header')

        # Reuse one message object as decodeMessage reads each successive packet.
        pkt=packet_pb2.Packet()
        with output.open('w',encoding='ascii') as f:
            while protolib.decodeMessage(inf,pkt):
                # Select by request timestamp; end itself is excluded from the ROI.
                tick=int(pkt.tick)
                if tick<start:outside_before+=1;continue
                if tick>=end:outside_after+=1;continue
                inside+=1

                # Translate numeric command IDs and classify requests as LD or ST.
                # Unknown/non-replayable commands are counted for validation below.
                cmd=id_to_name.get(int(pkt.cmd),f'UNKNOWN_{int(pkt.cmd)}')
                counts[cmd]+=1
                if cmd in READ_CMDS:op='LD'
                elif cmd in WRITE_CMDS:op='ST'
                else:skipped[cmd]+=1;continue

                # Preserve size accounting separately: the replay text contains only
                # operation and address, with no original size or timestamp.
                addr=int(pkt.addr);size=int(pkt.size)
                check(addr>=0 and size>0, 'invalid gem5 packet address/size')
                sizes[str(size)]+=1
                f.write(f'{op} 0x{addr:x}\n')

                # Count exported requests/bytes and retain their first/last timestamps.
                if op=='LD':reads+=1;rbytes+=size
                else:writes+=1;wbytes+=size
                first_t=tick if first_t is None else first_t
                last_t=tick
    # Close the input even if decoding, validation, or output writing fails.
    finally:inf.close()

    # --- Audit traffic volume and ensure every ROI packet is accounted for. ---
    # The 256-record minimum is a framework workload check, not a protobuf limit.
    check(reads>0 and reads+writes>=256,
          f'ROI yielded too few post-L2 data packets: reads={reads} writes={writes}; inspect marker window')
    check(inside==reads+writes+sum(skipped.values()),'ROI command-count conservation failure')

    # CleanEvict can be omitted; any other skipped class requires explicit review.
    unexpected={k:v for k,v in skipped.items() if k!='CleanEvict'}
    check(not unexpected, 'unclassified post-L2 ROI commands require manual review: '+repr(unexpected))

    # Expect initialization and post-ROI traffic in this whole-program recording.
    check(outside_before>0 and outside_after>0,
          f'expected setup and post-ROI memory traffic; before={outside_before} after={outside_after}')

    # --- Return evidence for kernel_trace_manifest.json, saved by the caller. ---
    # The header supplies ticks/second; hashing ties this metadata to the text trace.
    result={
      'roi_start_tick':start,'roi_end_tick':end,'roi_ticks':end-start,
      'tick_frequency_hz':int(head.tick_freq),
      'roi_seconds_in_gem5':(end-start)/int(head.tick_freq),
      'whole_trace_packets_before_roi':outside_before,
      'whole_trace_packets_after_roi':outside_after,
      'packets_within_roi':inside,
      'read':reads,'write':writes,'output_records':reads+writes,
      'classified_read_bytes':rbytes,'classified_write_bytes':wbytes,
      'command_histogram':dict(counts),'skipped_commands':dict(skipped),
      'size_histogram_bytes':dict(sizes),
      'first_accepted_tick':first_t,'last_accepted_tick':last_t,
      'trace_sha256':sha256(output),
      'interpretation':['ROI selected by gem5 packet request timestamp',
        'post-L2 trace includes instruction fetches and any pre-ROI outstanding requests',
        'requests issued near ROI end may have responses after ROI',
        'Ramulator LoadStoreTrace discards gem5 request timestamps and sizes',
        'single-channel DDR4/HBM2 sensitivity test, not closed-loop SpMV speedup']
    }

    return result


def stats_controller(yaml_path):
    """Read Ramulator YAML and return its memory-system and single-controller statistics."""
    import yaml
    # Controller statistics can be a dictionary or a one-element list.
    data=yaml.safe_load(yaml_path.read_text())
    m=data['memory_system'];c=m['controller']
    if isinstance(c,list):
        check(len(c)==1,'expected one Ramulator channel')
        c=c[0]
    return m,c


# --- Project paths and lightweight validation ---------------------------------
def save_json(path, data):
    """Write structured evidence; callers never need to parse console output."""
    path.parent.mkdir(parents=True, exist_ok=True)
    # Atomic replacement prevents an interrupted save from truncating a manifest.
    temporary = path.with_name(path.name + f'.{os.getpid()}.tmp')
    temporary.write_text(json.dumps(data, indent=2, default=str) + '\n')
    temporary.replace(path)
    return path


def source_check(ctx):
    """Require the reference file, but allow edits; hashes record its identity."""
    source = ctx.project / 'src/week7_spmv_lab.cpp'
    check(source.is_file(), 'Week7 reference source not found: ' + str(source))
    return source


def benchmark_options(ctx, pattern):
    """Build workload arguments for one locality pattern using the experiment context."""
    return ['--rows', str(ctx.args.rows), '--nnz-per-row', str(ctx.args.nnz_per_row),
            '--cols', str(ctx.args.cols), '--pattern', pattern]


def check_stage(ctx):
    """Inspect shared installations, but never install, patch, or build in them."""
    source = source_check(ctx)
    gem5 = ctx.args.gem5_root
    ram = ctx.args.ramulator_root
    check(os.access(gem5 / 'build/X86/gem5.opt', os.X_OK), 'gem5 executable inaccessible')
    check((gem5 / 'util/m5/build/x86/out/libm5.a').is_file(),
          'prebuilt libm5.a missing; ask the instructor (no shared-directory build)')
    patch = ram / 'src/ramulator/frontend/impl/memory_trace/loadstore_trace.cpp'
    check(patch.is_file() and 'W8_DRAIN_CALLBACK_PATCH_V1' in patch.read_text(),
          'installed Ramulator callback/drain patch absent')

    # Import optional simulation packages only when this stage actually runs.
    import ramulator  # noqa: F401 -- validate the interpreter actually used
    import yaml  # noqa: F401

    # Retain version commands and repository revisions as reproducibility evidence.
    versions = {}
    logs = []
    for name in ('g++',):
        check(shutil.which(name), name + ' missing from PATH')
        log = stage_log_file(ctx.logs, 'check')
        versions[name] = run([name, '--version'], log).split('\n\n', 1)[1].splitlines()[0]
        logs.append(log)

    log = stage_log_file(ctx.logs, 'check')
    commit = run(['git', '-C', str(gem5), 'rev-parse', 'HEAD'], log).splitlines()[-1]
    logs.append(log)
    log = stage_log_file(ctx.logs, 'check')
    try:
        ram_commit = run(['git', '-C', str(ram), 'rev-parse', 'HEAD'], log).splitlines()[-1]
    except RuntimeError:
        ram_commit = None  # Some installations do not retain their Git checkout.
    logs.append(log)

    # This describes the checked environment; it does not configure later stages.
    path = save_json(ctx.out / 'environment.json', {
        'status': 'PASS', 'python': sys.executable, 'python_version': sys.version,
        'gem5_root': gem5, 'gem5_commit': commit, 'ramulator_root': ram,
        'ramulator_commit': ram_commit,
        'ramulator_module_version': getattr(ramulator, '__version__', None),
        'ramulator_module': getattr(ramulator, '__file__', None),
        'drain_patch_sha256': sha256(patch), 'reference_source_sha256': sha256(source),
        'versions': versions,
    })
    print('W8_ACCESS=PASS', flush=True)
    return [path, *logs]


# --- Native correctness and generated source snapshot ------------------------
def baseline_stage(ctx):
    """Compile and run the Week 7 host oracle, returning its binary and shared stage log."""
    source = source_check(ctx)
    binary = ctx.project / 'build/week7_baseline'
    binary.parent.mkdir(parents=True, exist_ok=True)
    compile_log = stage_log_file(ctx.logs, 'baseline')
    run(['g++', '-std=c++17', '-O2', '-Wall', '-Wextra', '-pedantic', source,
         '-o', binary], compile_log, timeout=240)

    # Host execution is safe here: this reference binary contains no m5 markers.
    log = stage_log_file(ctx.logs, 'baseline')
    check('ORACLE = PASS' in run([binary, '--mode', 'baseline'], log, timeout=60),
          'original baseline oracle failed')
    return [binary, compile_log, log]


def generate_stage(ctx):
    """Snapshot templates and reference source, record hashes, and return generated paths."""
    source = source_check(ctx)
    generated = ctx.out / 'generated'
    generated.mkdir(parents=True, exist_ok=True)
    outputs = []
    for name in ('csr_spmv_large_roi.cpp', 'gem5_kernel_roi.py'):
        dest = generated / name
        dest.write_bytes((ctx.project / 'templates' / name).read_bytes())
        outputs.append(dest)

    # Record the exact snapshot compiled later, not a hard-coded or live-source hash.
    dest = generated / source.name
    dest.write_bytes(source.read_bytes())
    outputs.append(dest)

    outputs.append(save_json(generated / 'source_manifest.json', {
        'reference_source': source, 'reference_source_sha256': sha256(dest),
        'generated_sha256': {p.name: sha256(p) for p in outputs},
    }))
    return outputs


def build_stage(ctx):
    """Compile the snapshotted gem5 guest with active ROI markers and return build evidence."""
    generated = ctx.out / 'generated'
    build = ctx.project / 'build'
    build.mkdir(parents=True, exist_ok=True)
    m5lib = ctx.args.gem5_root / 'util/m5/build/x86/out/libm5.a'
    check(m5lib.is_file(), 'prebuilt libm5.a missing; shared tools will not be rebuilt')

    # Build against the snapshot and installed m5 library, rather than live templates.
    common = ['g++', '-std=c++17', '-O2', '-Wall', '-Wextra', '-pedantic', '-static',
              '-I' + str(generated)]
    cpp = generated / 'csr_spmv_large_roi.cpp'

    # Keep real m5 markers enabled; this executable runs only inside gem5.
    guest = build / 'spmv_large_gem5'
    log = stage_log_file(ctx.logs, 'build')
    run([*common, '-I' + str(ctx.args.gem5_root / 'include'), cpp, m5lib,
         '-o', guest], log, timeout=300)
    return [guest, log]



# --- Timing simulation and timestamp-window trace extraction -----------------
def gem5_stage(ctx):
    """Simulate each locality case, check ROI/oracle markers, and collect simulation artifacts."""
    outputs = []
    for pattern in ctx.patterns:  # Deliberately sequential on the shared server.
        case = ctx.out / pattern
        out = case / 'gem5'
        out.mkdir(parents=True, exist_ok=True)
        log = stage_log_file(ctx.logs, 'gem5')
        text = run([ctx.args.gem5_root / 'build/X86/gem5.opt', '-d', out,
                    ctx.out / 'generated/gem5_kernel_roi.py', ctx.project / 'build/spmv_large_gem5',
                    *benchmark_options(ctx, pattern)], log, timeout=ctx.args.gem5_timeout)

        # Successful process exit alone does not prove ROI boundaries or correctness.
        for marker in ('W8_LARGE_CSR_ORACLE=PASS', 'W8_START_EVENT: workbegin',
                       'W8_END_EVENT: workend'):
            check(marker in text, 'gem5 missing ' + marker)

        # The first dump follows the ROI; later dumps include post-ROI execution.
        sections = re.findall(r'---------- Begin Simulation Statistics ----------.*?'
                              r'---------- End Simulation Statistics\s+----------',
                              (out / 'stats.txt').read_text(), flags=re.S)
        check(len(sections) >= 2, 'expected ROI and final gem5 statistics sections')
        stats = case / 'gem5_kernel_roi_stats.txt'
        stats.write_text(sections[0] + '\n')
        outputs.extend([log, stats, out / 'stats.txt', out / 'roi_window.json',
                        out / 'kernel_postL2_all.trc', out / 'config.ini'])
    return outputs


def trace_stage(ctx):
    """Decode each case into an ROI replay trace and save the accompanying audit manifest."""
    outputs = []
    for pattern in ctx.patterns:
        case = ctx.out / pattern
        out = case / 'trace'
        out.mkdir(parents=True, exist_ok=True)
        trace = out / 'spmv_roi_postL2.trace'
        evidence = extract_roi_packets(ctx.args.gem5_root, case / 'gem5/kernel_postL2_all.trc',
                                       case / 'gem5/roi_window.json', trace)
        outputs.extend([trace, save_json(out / 'kernel_trace_manifest.json', evidence)])
    return outputs


# --- Initial replay: request-equivalent, NOT byte-equivalent ------------------
def replay_stage(ctx):
    """Run request-equivalent DDR4/HBM2 replays and verify completion and request accounting."""
    outputs = []
    # Attribute evidence to the compiled snapshot, even if the live source is edited.
    reference_sha256 = sha256(ctx.out / 'generated/week7_spmv_lab.cpp')
    for pattern in ctx.patterns:
        case = ctx.out / pattern
        manifest = json.loads((case / 'trace/kernel_trace_manifest.json').read_text())
        out = case / 'replay_req_equiv'
        text = ''
        for tech in ('ddr4', 'hbm2'):
            log = stage_log_file(ctx.logs, 'replay')
            text += run([sys.executable, ctx.project / 'scripts/replay_request_equivalent.py',
                         case / 'trace/spmv_roi_postL2.trace', '--out-dir', out,
                         '--technology', tech], log, timeout=ctx.args.replay_timeout)
            outputs.append(log)

        # Verify both backends drained all accepted requests before inspecting stats.
        callbacks = re.findall(r'W8_DRAIN_PASS submitted=(\d+) completed=(\d+) '
                               r'outstanding=(\d+) drain_ticks=(\d+)', text)
        check(len(callbacks) == 2, 'expected two completion callback summaries')
        for submitted, completed, outstanding, _ in callbacks:
            check(int(submitted) == int(completed) == manifest['output_records']
                  and int(outstanding) == 0, 'incomplete original replay')

        # Account for forwarded reads and coalesced writes as well as served requests.
        proof = {}
        for tech in ('ddr4', 'hbm2'):
            path = out / f'{tech}_stats.yaml'
            mem, c = stats_controller(path)
            reads = int(c['num_read_reqs_served']) + int(c.get('num_read_reqs_forwarded', 0))
            writes = int(c['num_write_reqs_served']) + int(c.get('num_write_reqs_coalesced', 0))
            check(mem['total_num_read_requests'] == reads == manifest['read'] and
                  mem['total_num_write_requests'] == writes == manifest['write'],
                  tech + ' request conservation failed')
            proof[tech] = {'accepted_read': reads, 'accepted_write': writes,
                           'controller_cycles': int(c['cycles']), 'outstanding': 0}
            outputs.append(path)
            print(f'W8_KERNEL_{tech.upper()}_DRAIN=PASS', flush=True)

        # Keep a per-case proof linked to the original trace and reference snapshot.
        outputs.extend([out / 'input_manifest.json', save_json(
            case / 'kernel_profile_verification.json', {
                'status': 'PASS', 'reference_source_sha256': reference_sha256,
                'gem5_oracle': True, 'gem5_roi_markers': True,
                'roi_sim_ticks': manifest['roi_ticks'],
                'roi_sim_seconds': manifest['roi_seconds_in_gem5'],
                'roi_trace_records': manifest['output_records'],
                'trace_sha256': manifest['trace_sha256'], **proof,
                'ramulator_callback_summaries': callbacks,
                'limitations': manifest['interpretation'],
            })])
        print('W8_KERNEL_ROI_PIPELINE=PASS', flush=True)
    return outputs


# --- Byte-equivalent replay: the same logical payload for DDR4 and HBM2. -------
def payload_stage(ctx):
    """Run byte-equivalent replay orchestration in-process and return its evidence paths."""
    # Import on demand: the replay module uses this module's shared run() helper.
    # Keeping this local avoids circular initialization between the two modules.
    import replay_byte_equivalent

    command = ['--run',
               '--ramulator-root', ctx.args.ramulator_root, '--out-dir', ctx.out,
               '--log-file', stage_log_file(ctx.logs, 'payload'),
               '--replay-timeout', str(ctx.args.replay_timeout)]
    for pattern in ctx.patterns:
        command.extend(['--source-dir', ctx.out / pattern / 'trace'])
    # Run orchestration in-process so each backend announces its actual command.
    replay_byte_equivalent.main(list(map(str, command)))

    # Return produced artifacts so execute() can validate existence and hash them.
    outputs = [ctx.out / 'payload_equivalent_summary.json']
    outputs.append(stage_log_file(ctx.logs, 'payload'))
    for pattern in ctx.patterns:
        outputs.extend(p for p in (ctx.out / pattern / 'replay_byte_equiv').iterdir() if p.is_file())
    return outputs
