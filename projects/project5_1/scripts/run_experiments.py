#!/usr/bin/env python3
"""Stage-oriented Week 8 experiments. Run via ../run.sh for compiler setup."""
import argparse
import contextlib
import datetime
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

import experiment_stages
import generate_report


# --- Stage graph: payload replay needs only the ROI trace. -------------------
STAGES = ('check', 'baseline', 'generate', 'build', 'gem5', 'trace', 'replay',
          'payload', 'report')
DEPS = {name: [] for name in STAGES}
DEPS.update(build=['generate'], gem5=['build'], trace=['gem5'], replay=['trace'],
            payload=['trace'], report=['payload'])


# FUNCTIONS is a dictionary that maps stage names to the Python functions that execute them.
FUNCTIONS = {name: getattr(experiment_stages, name + '_stage') for name in STAGES[:-1]}
FUNCTIONS['report'] = generate_report.report_stage


# --- Manifest: configuration, implementation fingerprint, and artifact hashes. --
class Experiment:
    def __init__(self, args, project, out, manifest):
        """Store CLI options, project paths, selected patterns, and the current run manifest."""
        self.args, self.project, self.out = args, project, out
        self.logs = out.parent / 'logs'
        self.patterns = ['scattered', 'clustered'] if args.pattern == 'both' else [args.pattern]
        self.path = out / 'run_manifest.json'
        self.manifest = manifest

    def save(self):
        """Atomically persist the current experiment manifest to run_manifest.json."""
        experiment_stages.save_json(self.path, self.manifest)

    def configure(self, configuration):
        """One current experiment: changed parameters make old evidence stale."""
        if configuration != self.manifest['configuration']:
            for record in self.manifest['stages'].values():
                record['status'] = 'STALE'
            self.manifest['configuration'] = configuration

    def signature(self, stage):
        # Conservative invalidation: any implementation change invalidates reuse.
        """Fingerprint configuration, source contents, and tool metadata for stage reuse checks."""
        inputs = [self.project / 'run.sh', self.project / 'config/default.env']
        for folder in ('scripts', 'templates'):
            inputs.extend(p for p in (self.project / folder).iterdir()
                          if p.is_file() and p.suffix in ('.py', '.cpp', '.sv'))
        inputs.append(self.project / 'src/week7_spmv_lab.cpp')

        # Serialize stable input descriptions before hashing the stage identity.
        data = {'config': self.manifest['configuration'],
                'sources': {str(p.relative_to(self.project)): experiment_stages.sha256(p)
                            for p in sorted(inputs)}}
        # Detect replaced shared binaries/libraries without hashing huge tool installs.
        tools = [self.args.gem5_root / 'build/X86/gem5.opt',
                 self.args.gem5_root / 'util/m5/build/x86/out/libm5.a',
                 self.args.ramulator_root / 'src/ramulator/frontend/impl/memory_trace/loadstore_trace.cpp',
                 Path(sys.executable).resolve()]
        data['tools'] = {str(p): [p.stat().st_size, p.stat().st_mtime_ns]
                         if p.is_file() else None for p in tools}

        # Report completeness also depends on optional evidence outside its DEPS.
        if stage == 'report':
            data['optional_evidence'] = {s: self.manifest['stages'].get(s)
                                         for s in ('baseline', 'replay', 'check')}
        return hashlib.sha256(json.dumps(data, sort_keys=True).encode()).hexdigest()

    def valid(self, stage):
        """Check a stage record, output hashes, and recursively required prerequisite evidence."""
        record = self.manifest['stages'].get(stage, {})
        if record.get('status') != 'PASS' or record.get('signature') != self.signature(stage):
            return False

        # PASS is insufficient if any retained artifact was changed or removed.
        for relative, digest in record.get('outputs', {}).items():
            path = self.out / relative
            if not path.is_file() or experiment_stages.sha256(path) != digest:
                return False
        return bool(record.get('outputs')) and all(self.valid(s) for s in DEPS[stage])

    def invalidate(self, stage):
        # Stale records stay visible for debugging but cannot qualify for resume.
        """Mark this stage, its downstream dependents, and report evidence stale before rerunning."""
        affected = {stage}
        # Expand dependencies until no further downstream stages are discovered.
        while True:
            more = {s for s in STAGES if any(d in affected for d in DEPS[s])}
            if more <= affected:
                break
            affected |= more
        if stage != 'report':
            affected.add('report')
        for name in affected:
            if name in self.manifest['stages']:
                self.manifest['stages'][name]['status'] = 'STALE'

    def execute(self, stage):
        """Validate prerequisites, optionally resume, execute a stage, and persist success or failure."""
        if self.args.resume and self.valid(stage):
            return
        for dependency in DEPS[stage]:
            experiment_stages.check(self.valid(dependency),
                         f'{stage} requires valid {dependency} outputs. '
                         f'Use --from {dependency} --to {stage}, '
                         'or resume the full run.')

        # Record RUNNING before work starts, so interrupted runs cannot look complete.
        self.invalidate(stage)
        record = {'status': 'RUNNING', 'started_utc': now(), 'signature': self.signature(stage)}
        self.manifest['stages'][stage] = record
        self.save()

        stage_log = experiment_stages.stage_log_file(self.logs, stage)
        stage_log.parent.mkdir(parents=True, exist_ok=True)
        command = [sys.executable, str(self.project / 'scripts/run_experiments.py'),
                   '--results-dir', str(self.out), '--stage', stage,
                   '--gem5-root', str(self.args.gem5_root),
                   '--ramulator-root', str(self.args.ramulator_root)]
        # This reproducible stage invocation covers in-process work and diagnostics.
        heading = '$ ' + experiment_stages.shlex.join(command)
        print(experiment_stages.shlex.join(command), file=experiment_stages.COMMAND_STREAM, flush=True)
        try:
            # Truncate once per execution, then use append handles for all writers.
            stage_log.write_text('')
            with stage_log.open('a', buffering=1) as stream:
                stream.write(heading + '\n\n')
                stream.flush()
                with contextlib.redirect_stdout(stream), contextlib.redirect_stderr(stream):
                    try:
                        outputs = FUNCTIONS[stage](self)
                        experiment_stages.check(outputs and all(p.is_file() for p in outputs),
                                     stage + ' did not produce its required artifacts')
                    except Exception:
                        import traceback
                        traceback.print_exc()
                        raise

            # Close every writer and record the shared stage log only once.
            outputs = list(dict.fromkeys([*outputs, stage_log]))
            record.update(status='PASS', finished_utc=now(),
                          outputs={os.path.relpath(p, self.out): experiment_stages.sha256(p) for p in outputs},
                          log=os.path.relpath(stage_log, self.out))
        except Exception as exc:
            record.update(status='FAILED', error=str(exc), finished_utc=now())
            raise RuntimeError(f'{stage} failed; see {stage_log}') from exc
        finally:
            self.save()


def now():
    """Return an ISO-formatted UTC timestamp for manifest lifecycle records."""
    return datetime.datetime.now(datetime.timezone.utc).isoformat()


# --- CLI selection for the single current experiment -------------------------
def main():
    # Resolve the project independently of the directory used to launch the runner.
    """Resolve CLI configuration, select stages, lock the run directory, and execute the plan."""
    project = Path(__file__).resolve().parents[1]

    # --- CLI options: stage selection, workload, installed tools, and timeouts. ---
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--stage', choices=STAGES, help='Execute only this stage')
    parser.add_argument('--from', dest='first', choices=STAGES, help='First stage of a range')
    parser.add_argument('--to', dest='last', choices=STAGES, help='Last stage of a range')
    parser.add_argument('--results-dir', type=Path, default=project / 'results')
    parser.add_argument('--resume', action='store_true', help='Skip only validated stages')
    parser.add_argument('--dry-run', action='store_true', help='Show stage plan and paths without running or writing')

    # Omitted workload options inherit the current experiment's values below.
    parser.add_argument('--pattern', choices=['both', 'scattered', 'clustered'])
    for flag in ('rows', 'nnz-per-row', 'cols'):
        parser.add_argument('--' + flag, type=int)

    parser.add_argument('--gem5-root', type=Path, default=Path('/home/asinha/gem5'))
    parser.add_argument('--ramulator-root', type=Path, default=Path('/home/asinha/tools/week8/ramulator2'))
    parser.add_argument('--gem5-timeout', type=int, default=7200)
    parser.add_argument('--replay-timeout', type=int, default=3600)

    args = parser.parse_args()

    # Choose either one stage or an inclusive range, never both.
    if args.stage and (args.first or args.last):
        parser.error('--stage cannot be combined with --from/--to')

    # --- Load existing configuration to fill in omitted workload arguments. ---
    # This preliminary read also supports --dry-run without creating any files.
    out = args.results_dir.expanduser().resolve()
    manifest_path = out / 'run_manifest.json'
    manifest = json.loads(manifest_path.read_text()) if manifest_path.exists() else None
    previous = manifest['configuration'] if manifest else {}
    defaults = {'rows': 32768, 'nnz_per_row': 16, 'cols': 262144, 'pattern': 'both'}

    # Priority: explicit CLI value, recorded value, then first-run default.
    for key, default in defaults.items():
        if getattr(args, key) is None:
            setattr(args, key, previous.get(key, default))

    # Normalize installed tool paths before recording or using them.
    for key in ('gem5_root', 'ramulator_root'):
        setattr(args, key, getattr(args, key).expanduser().resolve())

    # --- Validate dimensions and timeouts before allocating or launching tools. ---
    if not (1 <= args.rows <= 1000000 and 1 <= args.nnz_per_row <= 64
            and 4096 <= args.cols <= 10000000 and args.gem5_timeout > 0 and args.replay_timeout > 0):
        parser.error('invalid dimensions or timeout; check harness limits')

    # Match the C++ harness limits: signed-int nonzero indices and a 96 MiB
    # budget for values, column indices, row pointers, input x, and output y.
    nz = args.rows * args.nnz_per_row
    if nz > 2**31 - 1 or 4 * (2*nz + 2*args.rows + 1 + args.cols) > 96 << 20:
        parser.error('benchmark exceeds integer or 96 MiB array budget')

    # --- Record the workload/tool configuration used to validate stage reuse. ---
    # Convert Path objects to strings so the configuration can be stored as JSON.
    configuration = {key: str(getattr(args, key)) if key.endswith('_root') else getattr(args, key)
                     for key in (*defaults, 'gem5_root', 'ramulator_root')}

    # Stage order comes from STAGES; Python slicing includes first but excludes
    # its upper bound, so last+1 makes the requested range inclusive.
    first = STAGES.index(args.first) if args.first else 0
    last = STAGES.index(args.last) if args.last else len(STAGES)-1
    if first > last:
        parser.error('--from must precede --to')

    selected = [args.stage] if args.stage else STAGES[first:last+1]

    # --- Preview the resolved plan without locking, writing, or running stages. ---
    if args.dry_run:
        print('RESULTS_DIR=' + str(out))
        print('STAGES=' + ','.join(selected))
        print('CONFIG=' + json.dumps(configuration, sort_keys=True))
        for stage in selected:
            print(f'  {stage}: prerequisites={DEPS[stage] or "none"}; runner={FUNCTIONS[stage].__module__}.{FUNCTIONS[stage].__name__}')
        print('Executables: g++, gem5.opt, replay_request_equivalent.py, replay_byte_equivalent.py (stage-dependent)')
        return

    # --- Initialize bookkeeping for a real run. Existing stage records are kept. ---
    manifest = manifest or {'schema_version': 2, 'created_utc': now(),
                            'configuration': configuration, 'stages': {}}
    out.mkdir(parents=True, exist_ok=True)

    # A lock prevents two writers from mixing outputs in the current experiment.
    lock = out / '.run_experiments.lock'
    import fcntl

    # LOCK_NB fails immediately if another process already owns the OS lock.
    # Closing the handle releases it; the lock file itself may remain afterward.
    with lock.open('w') as handle:
        try:
            fcntl.flock(handle, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError:
            parser.error('another process is using this run directory')

        # Re-read under the lock to avoid using state read while another run wrote it.
        if manifest_path.exists():
            manifest = json.loads(manifest_path.read_text())

        # Bundle paths, options, and manifest into the context passed to stages.
        # configure() marks recorded evidence stale when the configuration changes.
        ctx = Experiment(args, project, out, manifest)
        ctx.configure(configuration)
        ctx.save()

        # execute() handles prerequisites, resume validation, logs, and stage status.
        for stage in selected:
            ctx.execute(stage)


if __name__ == '__main__':
    try:
        main()
    except (RuntimeError, OSError, ValueError, subprocess.SubprocessError, ImportError) as exc:
        print(f'W8_PIPELINE_FATAL={type(exc).__name__}: {exc}', file=sys.stderr)
        sys.exit(1)
