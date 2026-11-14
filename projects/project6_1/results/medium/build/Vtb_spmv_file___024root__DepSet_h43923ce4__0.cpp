// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_spmv_file.h for the primary calling header

#include "Vtb_spmv_file__pch.h"
#include "Vtb_spmv_file___024root.h"

VlCoroutine Vtb_spmv_file___024root___eval_initial__TOP__Vtiming__0(Vtb_spmv_file___024root* vlSelf);
VlCoroutine Vtb_spmv_file___024root___eval_initial__TOP__Vtiming__1(Vtb_spmv_file___024root* vlSelf);

void Vtb_spmv_file___024root___eval_initial(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___eval_initial\n"); );
    // Body
    Vtb_spmv_file___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_spmv_file___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__tb_spmv_file__DOT__clk__0 
        = vlSelf->tb_spmv_file__DOT__clk;
    vlSelf->__Vtrigprevexpr_h3330e079__0 = (0x400U 
                                            == vlSelf->tb_spmv_file__DOT__received);
}

VL_INLINE_OPT VlCoroutine Vtb_spmv_file___024root___eval_initial__TOP__Vtiming__1(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___eval_initial__TOP__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSelf->__VdlySched.delay(0x1388ULL, 
                                           nullptr, 
                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 
                                           10);
        vlSelf->tb_spmv_file__DOT__clk = (1U & (~ (IData)(vlSelf->tb_spmv_file__DOT__clk)));
    }
}

VL_INLINE_OPT void Vtb_spmv_file___024root___act_comb__TOP__0(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___act_comb__TOP__0\n"); );
    // Body
    vlSelf->tb_spmv_file__DOT__s_ready = ((IData)(vlSelf->tb_spmv_file__DOT__rst_n) 
                                          & (0U == (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__state)));
    vlSelf->tb_spmv_file__DOT__m_valid = ((IData)(vlSelf->tb_spmv_file__DOT__rst_n) 
                                          & (4U == (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__state)));
}

void Vtb_spmv_file___024root___eval_act(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___eval_act\n"); );
    // Body
    if ((7ULL & vlSelf->__VactTriggered.word(0U))) {
        Vtb_spmv_file___024root___act_comb__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtb_spmv_file___024root___nba_sequent__TOP__1(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___nba_sequent__TOP__1\n"); );
    // Body
    if (vlSelf->tb_spmv_file__DOT__rst_n) {
        vlSelf->tb_spmv_file__DOT__m_ready = ((2U != 
                                               VL_MODDIVS_III(32, vlSelf->tb_spmv_file__DOT__cycle_count, (IData)(7U))) 
                                              & (3U 
                                                 != 
                                                 VL_MODDIVS_III(32, vlSelf->tb_spmv_file__DOT__cycle_count, (IData)(7U))));
    }
}

void Vtb_spmv_file___024root___nba_sequent__TOP__0(Vtb_spmv_file___024root* vlSelf);

void Vtb_spmv_file___024root___eval_nba(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___eval_nba\n"); );
    // Body
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtb_spmv_file___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtb_spmv_file___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((7ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtb_spmv_file___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vtb_spmv_file___024root___timing_resume(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___timing_resume\n"); );
    // Body
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hb40da20d__0.resume("@(negedge tb_spmv_file.clk)");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hb40da84c__0.resume("@(posedge tb_spmv_file.clk)");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hb3171717__0.resume("@([changed] (32'h400 == tb_spmv_file.received))");
    }
    if ((8ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdlySched.resume();
    }
}

void Vtb_spmv_file___024root___timing_commit(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___timing_commit\n"); );
    // Body
    if ((! (1ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hb40da20d__0.commit("@(negedge tb_spmv_file.clk)");
    }
    if ((! (2ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hb40da84c__0.commit("@(posedge tb_spmv_file.clk)");
    }
    if ((! (4ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hb3171717__0.commit("@([changed] (32'h400 == tb_spmv_file.received))");
    }
}

void Vtb_spmv_file___024root___eval_triggers__act(Vtb_spmv_file___024root* vlSelf);

bool Vtb_spmv_file___024root___eval_phase__act(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<4> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_spmv_file___024root___eval_triggers__act(vlSelf);
    Vtb_spmv_file___024root___timing_commit(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vtb_spmv_file___024root___timing_resume(vlSelf);
        Vtb_spmv_file___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_spmv_file___024root___eval_phase__nba(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtb_spmv_file___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_spmv_file___024root___dump_triggers__nba(Vtb_spmv_file___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_spmv_file___024root___dump_triggers__act(Vtb_spmv_file___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_spmv_file___024root___eval(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtb_spmv_file___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 3, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vtb_spmv_file___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 3, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vtb_spmv_file___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vtb_spmv_file___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtb_spmv_file___024root___eval_debug_assertions(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
