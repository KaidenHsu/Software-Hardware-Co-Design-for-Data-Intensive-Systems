// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_spmv_axis.h for the primary calling header

#include "Vtb_spmv_axis__pch.h"
#include "Vtb_spmv_axis___024root.h"

VL_ATTR_COLD void Vtb_spmv_axis___024root___eval_static__TOP(Vtb_spmv_axis___024root* vlSelf);

VL_ATTR_COLD void Vtb_spmv_axis___024root___eval_static(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___eval_static\n"); );
    // Body
    Vtb_spmv_axis___024root___eval_static__TOP(vlSelf);
}

VL_ATTR_COLD void Vtb_spmv_axis___024root___eval_static__TOP(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___eval_static__TOP\n"); );
    // Body
    vlSelf->tb_spmv_axis__DOT__clk = 0U;
    vlSelf->tb_spmv_axis__DOT__rst_n = 0U;
    vlSelf->tb_spmv_axis__DOT__s_data = 0ULL;
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    vlSelf->tb_spmv_axis__DOT__m_ready = 0U;
    vlSelf->tb_spmv_axis__DOT__captured = 0U;
    vlSelf->tb_spmv_axis__DOT__total_cycles = 0U;
    vlSelf->tb_spmv_axis__DOT__exp_y[0U] = 6U;
    vlSelf->tb_spmv_axis__DOT__exp_y[1U] = 6U;
    vlSelf->tb_spmv_axis__DOT__exp_y[2U] = 0xffffffffU;
    vlSelf->tb_spmv_axis__DOT__exp_y[3U] = 0xfU;
    vlSelf->tb_spmv_axis__DOT__stalled_prev = 0U;
    vlSelf->tb_spmv_axis__DOT__stalled_data = 0U;
    vlSelf->tb_spmv_axis__DOT__stalled_last = 0U;
}

VL_ATTR_COLD void Vtb_spmv_axis___024root___eval_final(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_spmv_axis___024root___dump_triggers__stl(Vtb_spmv_axis___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_spmv_axis___024root___eval_phase__stl(Vtb_spmv_axis___024root* vlSelf);

VL_ATTR_COLD void Vtb_spmv_axis___024root___eval_settle(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vtb_spmv_axis___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 3, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtb_spmv_axis___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_spmv_axis___024root___dump_triggers__stl(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

void Vtb_spmv_axis___024root___act_comb__TOP__0(Vtb_spmv_axis___024root* vlSelf);

VL_ATTR_COLD void Vtb_spmv_axis___024root___eval_stl(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vtb_spmv_axis___024root___act_comb__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vtb_spmv_axis___024root___eval_triggers__stl(Vtb_spmv_axis___024root* vlSelf);

VL_ATTR_COLD bool Vtb_spmv_axis___024root___eval_phase__stl(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_spmv_axis___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vtb_spmv_axis___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_spmv_axis___024root___dump_triggers__act(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(negedge tb_spmv_axis.clk)\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge tb_spmv_axis.clk)\n");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 2 is active: @([changed] (32'sh4 == tb_spmv_axis.captured))\n");
    }
    if ((8ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 3 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_spmv_axis___024root___dump_triggers__nba(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(negedge tb_spmv_axis.clk)\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge tb_spmv_axis.clk)\n");
    }
    if ((4ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 2 is active: @([changed] (32'sh4 == tb_spmv_axis.captured))\n");
    }
    if ((8ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 3 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_spmv_axis___024root___ctor_var_reset(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->tb_spmv_axis__DOT__clk = VL_RAND_RESET_I(1);
    vlSelf->tb_spmv_axis__DOT__rst_n = VL_RAND_RESET_I(1);
    vlSelf->tb_spmv_axis__DOT__s_data = VL_RAND_RESET_Q(64);
    vlSelf->tb_spmv_axis__DOT__s_valid = VL_RAND_RESET_I(1);
    vlSelf->tb_spmv_axis__DOT__s_ready = VL_RAND_RESET_I(1);
    vlSelf->tb_spmv_axis__DOT__s_last = VL_RAND_RESET_I(1);
    vlSelf->tb_spmv_axis__DOT__m_valid = VL_RAND_RESET_I(1);
    vlSelf->tb_spmv_axis__DOT__m_ready = VL_RAND_RESET_I(1);
    vlSelf->tb_spmv_axis__DOT__nmac = VL_RAND_RESET_I(32);
    vlSelf->tb_spmv_axis__DOT__nload = VL_RAND_RESET_I(32);
    vlSelf->tb_spmv_axis__DOT__cycles = VL_RAND_RESET_I(32);
    vlSelf->tb_spmv_axis__DOT__captured = VL_RAND_RESET_I(32);
    vlSelf->tb_spmv_axis__DOT__total_cycles = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_spmv_axis__DOT__exp_y[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->tb_spmv_axis__DOT__stalled_prev = VL_RAND_RESET_I(1);
    vlSelf->tb_spmv_axis__DOT__stalled_data = VL_RAND_RESET_I(32);
    vlSelf->tb_spmv_axis__DOT__stalled_last = VL_RAND_RESET_I(1);
    vlSelf->tb_spmv_axis__DOT__dut__DOT__state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_spmv_axis__DOT__dut__DOT__ymem[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_spmv_axis__DOT__dut__DOT__xmem[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->tb_spmv_axis__DOT__dut__DOT__row_q = VL_RAND_RESET_I(2);
    vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx = VL_RAND_RESET_I(2);
    vlSelf->tb_spmv_axis__DOT__dut__DOT__a_q = VL_RAND_RESET_I(16);
    vlSelf->tb_spmv_axis__DOT__dut__DOT__x_q = VL_RAND_RESET_I(16);
    vlSelf->tb_spmv_axis__DOT__dut__DOT__y_q = VL_RAND_RESET_I(32);
    vlSelf->tb_spmv_axis__DOT__dut__DOT__out_q = VL_RAND_RESET_I(32);
    vlSelf->__Vtrigprevexpr___TOP__tb_spmv_axis__DOT__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr_hbc56aa34__0 = VL_RAND_RESET_I(1);
    vlSelf->__VactDidInit = 0;
}
