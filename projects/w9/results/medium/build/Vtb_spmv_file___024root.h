// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_spmv_file.h for the primary calling header

#ifndef VERILATED_VTB_SPMV_FILE___024ROOT_H_
#define VERILATED_VTB_SPMV_FILE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_spmv_file__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_spmv_file___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_spmv_file__DOT__clk;
    CData/*0:0*/ tb_spmv_file__DOT__rst_n;
    CData/*0:0*/ tb_spmv_file__DOT__s_valid;
    CData/*0:0*/ tb_spmv_file__DOT__s_last;
    CData/*0:0*/ tb_spmv_file__DOT__s_ready;
    CData/*0:0*/ tb_spmv_file__DOT__m_valid;
    CData/*0:0*/ tb_spmv_file__DOT__m_ready;
    CData/*0:0*/ tb_spmv_file__DOT__stalled_prev;
    CData/*0:0*/ tb_spmv_file__DOT__stalled_last;
    CData/*2:0*/ tb_spmv_file__DOT__dut__DOT__state;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_spmv_file__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr_h3330e079__0;
    CData/*0:0*/ __VactDidInit;
    CData/*0:0*/ __VactContinue;
    SData/*9:0*/ tb_spmv_file__DOT__dut__DOT__row_q;
    SData/*9:0*/ tb_spmv_file__DOT__dut__DOT__row_idx;
    SData/*15:0*/ tb_spmv_file__DOT__dut__DOT__a_q;
    SData/*15:0*/ tb_spmv_file__DOT__dut__DOT__x_q;
    IData/*31:0*/ tb_spmv_file__DOT__nmac;
    IData/*31:0*/ tb_spmv_file__DOT__nload;
    IData/*31:0*/ tb_spmv_file__DOT__cycles;
    IData/*31:0*/ tb_spmv_file__DOT__received;
    IData/*31:0*/ tb_spmv_file__DOT__cycle_count;
    IData/*31:0*/ tb_spmv_file__DOT__stalled_data;
    IData/*31:0*/ tb_spmv_file__DOT__dut__DOT__y_q;
    IData/*31:0*/ tb_spmv_file__DOT__dut__DOT__out_q;
    IData/*31:0*/ __VactIterCount;
    QData/*63:0*/ tb_spmv_file__DOT__s_data;
    VlUnpacked<QData/*63:0*/, 12290> tb_spmv_file__DOT__commands;
    VlUnpacked<IData/*31:0*/, 1024> tb_spmv_file__DOT__expected;
    VlUnpacked<IData/*31:0*/, 1024> tb_spmv_file__DOT__dut__DOT__ymem;
    VlUnpacked<SData/*15:0*/, 2048> tb_spmv_file__DOT__dut__DOT__xmem;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_hb40da20d__0;
    VlTriggerScheduler __VtrigSched_hb40da84c__0;
    VlTriggerScheduler __VtrigSched_hb3171717__0;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<4> __VactTriggered;
    VlTriggerVec<4> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtb_spmv_file__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtb_spmv_file___024root(Vtb_spmv_file__Syms* symsp, const char* v__name);
    ~Vtb_spmv_file___024root();
    VL_UNCOPYABLE(Vtb_spmv_file___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
