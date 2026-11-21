// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_scheduler.h for the primary calling header

#ifndef VERILATED_VTB_SCHEDULER___024ROOT_H_
#define VERILATED_VTB_SCHEDULER___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_scheduler__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_scheduler___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_scheduler__DOT__clk;
    CData/*0:0*/ tb_scheduler__DOT__rst;
    CData/*1:0*/ tb_scheduler__DOT__head_valid;
    CData/*3:0*/ tb_scheduler__DOT__head_row0;
    CData/*3:0*/ tb_scheduler__DOT__head_row1;
    CData/*1:0*/ tb_scheduler__DOT__issue_valid;
    CData/*1:0*/ tb_scheduler__DOT__pop_count;
    CData/*3:0*/ tb_scheduler__DOT__issue_row0;
    CData/*3:0*/ tb_scheduler__DOT__issue_row1;
    CData/*0:0*/ tb_scheduler__DOT__dut__DOT__row_stall_event;
    CData/*0:0*/ tb_scheduler__DOT__dut__DOT__bank_conflict_event;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_scheduler__DOT__clk__0;
    CData/*0:0*/ __VactContinue;
    SData/*15:0*/ tb_scheduler__DOT__busy_rows;
    SData/*15:0*/ tb_scheduler__DOT__dut__DOT__unnamedblk1__DOT__next_busy_rows;
    IData/*31:0*/ tb_scheduler__DOT__issued_total;
    IData/*31:0*/ tb_scheduler__DOT__row_hazard_cycles;
    IData/*31:0*/ tb_scheduler__DOT__bank_conflict_cycles;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*3:0*/, 64> tb_scheduler__DOT__trace_mem;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_hc942a4a9__0;
    VlTriggerScheduler __VtrigSched_hc9429d78__0;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<3> __VactTriggered;
    VlTriggerVec<3> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtb_scheduler__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtb_scheduler___024root(Vtb_scheduler__Syms* symsp, const char* v__name);
    ~Vtb_scheduler___024root();
    VL_UNCOPYABLE(Vtb_scheduler___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
