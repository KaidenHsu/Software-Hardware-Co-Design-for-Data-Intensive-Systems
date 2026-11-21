"""WorkBegin/WorkEnd ROI gem5 v25.1 x86 timing SE, post-L2 protobuf."""
import json
import os
import sys

import m5
from m5.objects import (AddrRange, Cache, CommMonitor, DDR4_2400_8x8,
                        L2XBar, MemCtrl, MemTraceProbe, Process, Root,
                        SEWorkload, SrcClockDomain, System, SystemXBar,
                        VoltageDomain, X86TimingSimpleCPU)


# --- Guest arguments: pass workload options through without changing them. ---
if len(sys.argv) < 2:
    raise SystemExit('usage: config.py absolute/binary [binary-options]')
binary = os.path.abspath(sys.argv[1])
args = sys.argv[2:]
if not os.path.isfile(binary):
    raise RuntimeError('binary not found: ' + binary)


# --- CPU, clocks, and cache hierarchy (shared DDR4 baseline for both cases). ---
system=System()
system.clk_domain=SrcClockDomain(clock='2GHz',voltage_domain=VoltageDomain())
system.mem_mode='timing'
system.mem_ranges=[AddrRange('512MiB')]
# Return control to this Python script when the guest reaches workbegin/workend.
system.exit_on_work_items=True
system.cpu=X86TimingSimpleCPU()
system.membus=SystemXBar(); system.l2bus=L2XBar()


def cache(size,assoc,lat,mshrs):
    """Create a cache with the requested capacity, associativity, latency, and miss resources."""
    return Cache(size=size,assoc=assoc,tag_latency=lat,data_latency=lat,
                 response_latency=lat,mshrs=mshrs,tgts_per_mshr=12)


# Private L1 caches share the L2 bus; both workload patterns use this hierarchy.
system.cpu.icache=cache('32KiB',4,2,4)
system.cpu.dcache=cache('32KiB',8,2,8)
system.cpu.icache.cpu_side=system.cpu.icache_port
system.cpu.dcache.cpu_side=system.cpu.dcache_port
system.cpu.icache.mem_side=system.l2bus.cpu_side_ports
system.cpu.dcache.mem_side=system.l2bus.cpu_side_ports

# Shared L2 feeds the monitor, then the system memory bus.
system.l2=cache('256KiB',8,12,20)
system.l2.cpu_side=system.l2bus.mem_side_ports


# --- Capture memory-facing requests after L2, including instruction traffic. ---
system.monitor=CommMonitor()
# Binary protobuf records cover the whole run; trace_stage later selects the ROI.
system.monitor.trace=MemTraceProbe(trace_file='kernel_postL2_all.trc',trace_compress=False)
system.l2.mem_side=system.monitor.cpu_side_port
system.monitor.mem_side_port=system.membus.cpu_side_ports


# --- DDR4 controller and x86 interrupt wiring for syscall emulation. ---
system.mem_ctrl=MemCtrl()
system.mem_ctrl.dram=DDR4_2400_8x8()
system.mem_ctrl.dram.range=system.mem_ranges[0]
system.mem_ctrl.port=system.membus.mem_side_ports
system.system_port=system.membus.cpu_side_ports

# Standard x86 interrupt-controller port wiring; unrelated to trace recording.
system.cpu.createInterruptController()
system.cpu.interrupts[0].pio=system.membus.mem_side_ports
system.cpu.interrupts[0].int_requestor=system.membus.cpu_side_ports
system.cpu.interrupts[0].int_responder=system.membus.mem_side_ports


# --- Load the guest binary; allocation and initialization run before workbegin. ---
# System workload selects the SE environment; CPU workload selects the guest process.
system.workload=SEWorkload.init_compatible(binary)
system.cpu.workload=Process(cmd=[binary]+args)
system.cpu.createThreads()
# Root is the simulation object-tree root, not the Linux root user.
root=Root(full_system=False,system=system)


# --- Stop on ROI events, reset/dump counters, then allow the oracle to finish. ---
# Build the configured machine before executing guest instructions.
m5.instantiate()

# First simulate call runs setup until the C++ guest calls m5_work_begin.
start_event=m5.simulate()
print('W8_START_EVENT:',start_event.getCause(),flush=True)
if start_event.getCause().strip().lower() != 'workbegin':
    raise RuntimeError('expected m5_work_begin but got '+start_event.getCause())
start_tick=m5.curTick()
print('W8_ROI_START_TICK:',start_tick,flush=True)
# Reset counters only: cache contents and CPU state remain intact.
m5.stats.reset()

# Measure only the interval between the guest work-item markers.
end_event=m5.simulate()
print('W8_END_EVENT:',end_event.getCause(),flush=True)
if end_event.getCause().strip().lower() != 'workend':
    raise RuntimeError('expected m5_work_end but got '+end_event.getCause())
end_tick=m5.curTick()
print('W8_ROI_END_TICK:',end_tick,flush=True)
if end_tick <= start_tick:
    raise RuntimeError('non-positive ROI duration')
# Write the ROI counters before the reference check adds more simulated work.
m5.stats.dump()

# Let the guest finish its numerical oracle after counters have been dumped.
exit_event=m5.simulate()
print('W8_FINAL_EXIT:',exit_event.getCause(),flush=True)
if 'exiting with last active thread context' not in exit_event.getCause().lower():
    raise RuntimeError('unexpected termination '+exit_event.getCause())


# --- Persist the exact tick window for downstream post-L2 trace filtering. ---
# gem5 uses a 1 THz tick clock here; CPU frequency is configured separately.
with open(os.path.join(m5.options.outdir,'roi_window.json'),'w') as f:
    json.dump({'roi_start_tick':start_tick,'roi_end_tick':end_tick,
               'roi_sim_ticks':end_tick-start_tick,
               'gem5_tick_frequency_hz':1000000000000,
               'exit_event':exit_event.getCause(),
               'roi_scope':'m5_work_begin/end around CSR compute loop',
               'post_l2_boundary':'request tick in [start,end)'},f,indent=2)
    f.write('\n')
