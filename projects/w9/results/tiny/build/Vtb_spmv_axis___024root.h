// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_spmv_axis.h for the primary calling header

#ifndef VERILATED_VTB_SPMV_AXIS___024ROOT_H_
#define VERILATED_VTB_SPMV_AXIS___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_spmv_axis__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_spmv_axis___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_spmv_axis__DOT__clk;
    CData/*0:0*/ tb_spmv_axis__DOT__rst_n;
    CData/*0:0*/ tb_spmv_axis__DOT__s_valid;
    CData/*0:0*/ tb_spmv_axis__DOT__s_ready;
    CData/*0:0*/ tb_spmv_axis__DOT__s_last;
    CData/*0:0*/ tb_spmv_axis__DOT__m_valid;
    CData/*0:0*/ tb_spmv_axis__DOT__m_ready;
    CData/*0:0*/ tb_spmv_axis__DOT__stalled_prev;
    CData/*0:0*/ tb_spmv_axis__DOT__stalled_last;
    CData/*2:0*/ tb_spmv_axis__DOT__dut__DOT__state;
    CData/*1:0*/ tb_spmv_axis__DOT__dut__DOT__row_q;
    CData/*1:0*/ tb_spmv_axis__DOT__dut__DOT__row_idx;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_spmv_axis__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr_hbc56aa34__0;
    CData/*0:0*/ __VactDidInit;
    CData/*0:0*/ __VactContinue;
    SData/*15:0*/ tb_spmv_axis__DOT__dut__DOT__a_q;
    SData/*15:0*/ tb_spmv_axis__DOT__dut__DOT__x_q;
    IData/*31:0*/ tb_spmv_axis__DOT__nmac;
    IData/*31:0*/ tb_spmv_axis__DOT__nload;
    IData/*31:0*/ tb_spmv_axis__DOT__cycles;
    IData/*31:0*/ tb_spmv_axis__DOT__captured;
    IData/*31:0*/ tb_spmv_axis__DOT__total_cycles;
    IData/*31:0*/ tb_spmv_axis__DOT__stalled_data;
    IData/*31:0*/ tb_spmv_axis__DOT__dut__DOT__y_q;
    IData/*31:0*/ tb_spmv_axis__DOT__dut__DOT__out_q;
    IData/*31:0*/ __VactIterCount;
    QData/*63:0*/ tb_spmv_axis__DOT__s_data;
    VlUnpacked<IData/*31:0*/, 4> tb_spmv_axis__DOT__exp_y;
    VlUnpacked<IData/*31:0*/, 4> tb_spmv_axis__DOT__dut__DOT__ymem;
    VlUnpacked<SData/*15:0*/, 8> tb_spmv_axis__DOT__dut__DOT__xmem;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h5acff1b1__0;
    VlTriggerScheduler __VtrigSched_h5acff1c0__0;
    VlTriggerScheduler __VtrigSched_h2c61e446__0;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<4> __VactTriggered;
    VlTriggerVec<4> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtb_spmv_axis__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtb_spmv_axis___024root(Vtb_spmv_axis__Syms* symsp, const char* v__name);
    ~Vtb_spmv_axis___024root();
    VL_UNCOPYABLE(Vtb_spmv_axis___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
