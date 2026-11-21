// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_scheduler.h for the primary calling header

#include "Vtb_scheduler__pch.h"
#include "Vtb_scheduler___024root.h"

VL_ATTR_COLD void Vtb_scheduler___024root___eval_static__TOP(Vtb_scheduler___024root* vlSelf);

VL_ATTR_COLD void Vtb_scheduler___024root___eval_static(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_static\n"); );
    // Body
    Vtb_scheduler___024root___eval_static__TOP(vlSelf);
}

VL_ATTR_COLD void Vtb_scheduler___024root___eval_static__TOP(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_static__TOP\n"); );
    // Body
    vlSelf->tb_scheduler__DOT__clk = 0U;
}

VL_ATTR_COLD void Vtb_scheduler___024root___eval_final(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_scheduler___024root___dump_triggers__stl(Vtb_scheduler___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_scheduler___024root___eval_phase__stl(Vtb_scheduler___024root* vlSelf);

VL_ATTR_COLD void Vtb_scheduler___024root___eval_settle(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_settle\n"); );
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
            Vtb_scheduler___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 2, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtb_scheduler___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_scheduler___024root___dump_triggers__stl(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

void Vtb_scheduler___024root___act_comb__TOP__0(Vtb_scheduler___024root* vlSelf);

VL_ATTR_COLD void Vtb_scheduler___024root___eval_stl(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vtb_scheduler___024root___act_comb__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vtb_scheduler___024root___eval_triggers__stl(Vtb_scheduler___024root* vlSelf);

VL_ATTR_COLD bool Vtb_scheduler___024root___eval_phase__stl(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_scheduler___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vtb_scheduler___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_scheduler___024root___dump_triggers__act(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge tb_scheduler.clk)\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(negedge tb_scheduler.clk)\n");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_scheduler___024root___dump_triggers__nba(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge tb_scheduler.clk)\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(negedge tb_scheduler.clk)\n");
    }
    if ((4ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_scheduler___024root___ctor_var_reset(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->tb_scheduler__DOT__clk = VL_RAND_RESET_I(1);
    vlSelf->tb_scheduler__DOT__rst = VL_RAND_RESET_I(1);
    vlSelf->tb_scheduler__DOT__head_valid = VL_RAND_RESET_I(2);
    vlSelf->tb_scheduler__DOT__head_row0 = VL_RAND_RESET_I(4);
    vlSelf->tb_scheduler__DOT__head_row1 = VL_RAND_RESET_I(4);
    vlSelf->tb_scheduler__DOT__issue_valid = VL_RAND_RESET_I(2);
    vlSelf->tb_scheduler__DOT__pop_count = VL_RAND_RESET_I(2);
    vlSelf->tb_scheduler__DOT__issue_row0 = VL_RAND_RESET_I(4);
    vlSelf->tb_scheduler__DOT__issue_row1 = VL_RAND_RESET_I(4);
    vlSelf->tb_scheduler__DOT__busy_rows = VL_RAND_RESET_I(16);
    vlSelf->tb_scheduler__DOT__issued_total = VL_RAND_RESET_I(32);
    vlSelf->tb_scheduler__DOT__row_hazard_cycles = VL_RAND_RESET_I(32);
    vlSelf->tb_scheduler__DOT__bank_conflict_cycles = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        vlSelf->tb_scheduler__DOT__trace_mem[__Vi0] = VL_RAND_RESET_I(4);
    }
    vlSelf->tb_scheduler__DOT__dut__DOT__row_stall_event = VL_RAND_RESET_I(1);
    vlSelf->tb_scheduler__DOT__dut__DOT__bank_conflict_event = VL_RAND_RESET_I(1);
    vlSelf->tb_scheduler__DOT__dut__DOT__unnamedblk1__DOT__next_busy_rows = VL_RAND_RESET_I(16);
    vlSelf->__Vtrigprevexpr___TOP__tb_scheduler__DOT__clk__0 = VL_RAND_RESET_I(1);
}
