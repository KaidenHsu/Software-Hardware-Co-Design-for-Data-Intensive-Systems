"""Build evidence tables, keeping gem5 execution and controller replay separate."""
import json

from experiment_stages import check, save_json, sha256


# --- Read verified artifacts, not instructor reference numbers. ---------------
def report_stage(ctx):
    """Validate replay/trace evidence and write separate gem5 and memory-replay report tables."""
    summary = json.loads((ctx.out / 'payload_equivalent_summary.json').read_text())
    check(summary['status'] == 'PASS', 'payload summary is not PASS')

    # Keep measured gem5 execution separate from normalized controller replay.
    kernel_rows, dram_rows = [], []
    for pattern in ctx.patterns:
        case = ctx.out / pattern
        trace = json.loads((case / 'trace/kernel_trace_manifest.json').read_text())
        data = summary['results'][pattern]
        check(trace['trace_sha256'] == data['source_trace_sha256'] ==
              sha256(case / 'trace/spmv_roi_postL2.trace'), 'report source trace mismatch')

        # Match trace identity, request counts, and packet sizes before using results.
        count = trace['output_records']
        check(trace['read'] + trace['write'] == count, 'trace request accounting failed')
        check(trace['size_histogram_bytes'] == {'64': count}, 'report requires 64B packets')
        kernel_rows.append({'pattern': pattern,
                            'gem5_roi_ms': trace['roi_seconds_in_gem5'] * 1000,
                            'post_l2_requests': count, 'logical_bytes': 64 * count})

        # HBM2 has twice as many requests but the same logical byte count as DDR4.
        for technology in ('ddr4', 'hbm2'):
            value = data[technology]
            expected = count * (2 if technology == 'hbm2' else 1)
            check(value['outstanding'] == 0 and value['callbacks_completed'] ==
                  value['requests'] == expected, 'replay completion invariant failed')
            denominator = value['row_hits'] + value['row_misses'] + value['row_conflicts']
            dram_rows.append({'pattern': pattern, 'technology': technology,
                              'logical_bytes': count * 64, 'requests': expected,
                              'controller_cycles': value['controller_cycles'],
                              'tCK_ps': value['assumed_preset_tCK_ps'],
                              'modeled_time_ms': value['modeled_controller_time_ms'],
                              'row_hit_pct': 100 * value['row_hits'] / denominator if denominator else None,
                              'outstanding': value['outstanding']})


    # Optional stages may not have been requested in a single-pattern analysis.
    evidence = {name: ctx.valid(name) for name in ('check', 'baseline', 'replay')}
    complete = len(ctx.patterns) == 2 and all(evidence.values())

    ratios = {}
    if len(kernel_rows) == 2:
        by_pattern = {row['pattern']: row for row in kernel_rows}
        s, c = by_pattern['scattered'], by_pattern['clustered']
        ratios = {'gem5_time_scattered_to_clustered': s['gem5_roi_ms'] / c['gem5_roi_ms'],
                  'request_count_scattered_to_clustered': s['post_l2_requests'] / c['post_l2_requests']}

    # These ratios concern replay time, not end-to-end application speedup.
    replay_ratios = {p: summary['results'][p]['replay_time_ratio_ddr4_to_hbm2'] for p in ctx.patterns}

    output = ctx.out / 'report'
    output.mkdir(parents=True, exist_ok=True)
    result = save_json(output / 'summary.json', {
        'status': 'COMPLETE' if complete else 'PARTIAL', 'evidence': evidence,
        'gem5': kernel_rows, 'payload_equivalent_replay': dram_rows,
        'locality_ratios': ratios, 'replay_ratios_ddr4_to_hbm2': replay_ratios,
        'limitations': summary['limitations'],
    })


    # --- Human-readable evidence sheet with explicit units and missing stages. --
    lines = ['# Week 8 experiment evidence', '',
             f'Status: {"COMPLETE" if complete else "PARTIAL"}.', '',
             '## gem5 kernel execution (DDR4 baseline)', '',
             '| Pattern | ROI ms | Post-L2 requests | Logical bytes |',
             '|---|---:|---:|---:|']
    lines.extend(f"| {r['pattern']} | {r['gem5_roi_ms']:.6f} | {r['post_l2_requests']} | {r['logical_bytes']} |"
                 for r in kernel_rows)

    lines.extend(['', '## Byte-equivalent standalone Ramulator replay', '',
                  '| Pattern | DRAM | Bytes | Requests | Cycles | tCK ps | Time ms | Row-hit % | Outstanding |',
                  '|---|---|---:|---:|---:|---:|---:|---:|---:|'])
    for r in dram_rows:
        hit = 'N/A' if r['row_hit_pct'] is None else f"{r['row_hit_pct']:.2f}"
        lines.append(f"| {r['pattern']} | {r['technology']} | {r['logical_bytes']} | {r['requests']} | "
                     f"{r['controller_cycles']} | {r['tCK_ps']} | {r['modeled_time_ms']:.6f} | {hit} | 0 |")

    lines.extend(['', '## Ratios and evidence', ''])
    lines.extend(f'- {name}: {value:.6f}' for name, value in ratios.items())
    lines.extend(f'- {p} DDR4/HBM2 replay-time ratio: {v:.6f}' for p, v in replay_ratios.items())
    lines.extend(f'- {name}: {"validated" if passed else "missing or stale"}' for name, passed in evidence.items())
    lines.extend(['', '## Interpretation limits', ''])
    lines.extend('- ' + item for item in summary['limitations'])
    lines.extend(['', 'These tables are generated evidence, not the student\'s analytical conclusions.',
                  'Standalone HBM2 replay timing is not an end-to-end SpMV speedup.', ''])

    # Both machine-readable and human-readable outputs become tracked artifacts.
    markdown = output / 'report.md'
    markdown.write_text('\n'.join(lines))
    return [result, markdown]
