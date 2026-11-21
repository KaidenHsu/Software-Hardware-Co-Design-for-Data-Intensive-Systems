// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_scheduler.h for the primary calling header

#include "Vtb_scheduler__pch.h"
#include "Vtb_scheduler___024root.h"

VlCoroutine Vtb_scheduler___024root___eval_initial__TOP__Vtiming__0(Vtb_scheduler___024root* vlSelf);
VlCoroutine Vtb_scheduler___024root___eval_initial__TOP__Vtiming__1(Vtb_scheduler___024root* vlSelf);

void Vtb_scheduler___024root___eval_initial(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_initial\n"); );
    // Body
    Vtb_scheduler___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_scheduler___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__tb_scheduler__DOT__clk__0 
        = vlSelf->tb_scheduler__DOT__clk;
}

VL_INLINE_OPT VlCoroutine Vtb_scheduler___024root___eval_initial__TOP__Vtiming__1(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_initial__TOP__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSelf->__VdlySched.delay(0x1388ULL, 
                                           nullptr, 
                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                           8);
        vlSelf->tb_scheduler__DOT__clk = (1U & (~ (IData)(vlSelf->tb_scheduler__DOT__clk)));
    }
}

VL_INLINE_OPT void Vtb_scheduler___024root___act_comb__TOP__0(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___act_comb__TOP__0\n"); );
    // Body
    vlSelf->tb_scheduler__DOT__issue_row0 = vlSelf->tb_scheduler__DOT__head_row0;
    vlSelf->tb_scheduler__DOT__issue_row1 = vlSelf->tb_scheduler__DOT__head_row1;
    vlSelf->tb_scheduler__DOT__dut__DOT__row_stall_event = 0U;
    vlSelf->tb_scheduler__DOT__dut__DOT__bank_conflict_event = 0U;
    vlSelf->tb_scheduler__DOT__issue_valid = 0U;
    if ((1U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
        if ((1U & ((IData)(vlSelf->tb_scheduler__DOT__busy_rows) 
                   >> (IData)(vlSelf->tb_scheduler__DOT__head_row0)))) {
            vlSelf->tb_scheduler__DOT__dut__DOT__row_stall_event = 1U;
        } else if ((2U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
            if ((1U & (((IData)(vlSelf->tb_scheduler__DOT__busy_rows) 
                        >> (IData)(vlSelf->tb_scheduler__DOT__head_row1)) 
                       | ((IData)(vlSelf->tb_scheduler__DOT__head_row0) 
                          == (IData)(vlSelf->tb_scheduler__DOT__head_row1))))) {
                vlSelf->tb_scheduler__DOT__dut__DOT__row_stall_event = 1U;
            }
        }
        if ((1U & (~ ((IData)(vlSelf->tb_scheduler__DOT__busy_rows) 
                      >> (IData)(vlSelf->tb_scheduler__DOT__head_row0))))) {
            vlSelf->tb_scheduler__DOT__issue_valid 
                = (1U | (IData)(vlSelf->tb_scheduler__DOT__issue_valid));
            if ((2U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
                if ((1U & (~ (((IData)(vlSelf->tb_scheduler__DOT__busy_rows) 
                               >> (IData)(vlSelf->tb_scheduler__DOT__head_row1)) 
                              | ((IData)(vlSelf->tb_scheduler__DOT__head_row0) 
                                 == (IData)(vlSelf->tb_scheduler__DOT__head_row1)))))) {
                    if (((1U & (IData)(vlSelf->tb_scheduler__DOT__head_row0)) 
                         == (1U & (IData)(vlSelf->tb_scheduler__DOT__head_row1)))) {
                        vlSelf->tb_scheduler__DOT__dut__DOT__bank_conflict_event = 1U;
                    }
                    if (((1U & (IData)(vlSelf->tb_scheduler__DOT__head_row0)) 
                         != (1U & (IData)(vlSelf->tb_scheduler__DOT__head_row1)))) {
                        vlSelf->tb_scheduler__DOT__issue_valid 
                            = (2U | (IData)(vlSelf->tb_scheduler__DOT__issue_valid));
                    }
                }
            }
        }
    }
    vlSelf->tb_scheduler__DOT__pop_count = (3U & ((1U 
                                                   & (IData)(vlSelf->tb_scheduler__DOT__issue_valid)) 
                                                  + 
                                                  (1U 
                                                   & ((IData)(vlSelf->tb_scheduler__DOT__issue_valid) 
                                                      >> 1U))));
}

void Vtb_scheduler___024root___eval_act(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_act\n"); );
    // Body
    if ((7ULL & vlSelf->__VactTriggered.word(0U))) {
        Vtb_scheduler___024root___act_comb__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtb_scheduler___024root___nba_sequent__TOP__0(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___nba_sequent__TOP__0\n"); );
    // Init
    IData/*31:0*/ __Vdly__tb_scheduler__DOT__row_hazard_cycles;
    __Vdly__tb_scheduler__DOT__row_hazard_cycles = 0;
    IData/*31:0*/ __Vdly__tb_scheduler__DOT__bank_conflict_cycles;
    __Vdly__tb_scheduler__DOT__bank_conflict_cycles = 0;
    // Body
    __Vdly__tb_scheduler__DOT__bank_conflict_cycles 
        = vlSelf->tb_scheduler__DOT__bank_conflict_cycles;
    __Vdly__tb_scheduler__DOT__row_hazard_cycles = vlSelf->tb_scheduler__DOT__row_hazard_cycles;
    if (vlSelf->tb_scheduler__DOT__rst) {
        __Vdly__tb_scheduler__DOT__bank_conflict_cycles = 0U;
        __Vdly__tb_scheduler__DOT__row_hazard_cycles = 0U;
        vlSelf->tb_scheduler__DOT__issued_total = 0U;
        vlSelf->tb_scheduler__DOT__busy_rows = 0U;
    } else {
        if (vlSelf->tb_scheduler__DOT__dut__DOT__bank_conflict_event) {
            __Vdly__tb_scheduler__DOT__bank_conflict_cycles 
                = ((IData)(1U) + vlSelf->tb_scheduler__DOT__bank_conflict_cycles);
        }
        if (vlSelf->tb_scheduler__DOT__dut__DOT__row_stall_event) {
            __Vdly__tb_scheduler__DOT__row_hazard_cycles 
                = ((IData)(1U) + vlSelf->tb_scheduler__DOT__row_hazard_cycles);
        }
        vlSelf->tb_scheduler__DOT__issued_total = (vlSelf->tb_scheduler__DOT__issued_total 
                                                   + (IData)(vlSelf->tb_scheduler__DOT__pop_count));
        vlSelf->tb_scheduler__DOT__dut__DOT__unnamedblk1__DOT__next_busy_rows = 0U;
        if ((1U & (IData)(vlSelf->tb_scheduler__DOT__issue_valid))) {
            vlSelf->tb_scheduler__DOT__dut__DOT__unnamedblk1__DOT__next_busy_rows 
                = ((IData)(vlSelf->tb_scheduler__DOT__dut__DOT__unnamedblk1__DOT__next_busy_rows) 
                   | (0xffffU & ((IData)(1U) << (IData)(vlSelf->tb_scheduler__DOT__head_row0))));
        }
        if ((2U & (IData)(vlSelf->tb_scheduler__DOT__issue_valid))) {
            vlSelf->tb_scheduler__DOT__dut__DOT__unnamedblk1__DOT__next_busy_rows 
                = ((IData)(vlSelf->tb_scheduler__DOT__dut__DOT__unnamedblk1__DOT__next_busy_rows) 
                   | (0xffffU & ((IData)(1U) << (IData)(vlSelf->tb_scheduler__DOT__head_row1))));
        }
        vlSelf->tb_scheduler__DOT__busy_rows = vlSelf->tb_scheduler__DOT__dut__DOT__unnamedblk1__DOT__next_busy_rows;
    }
    vlSelf->tb_scheduler__DOT__bank_conflict_cycles 
        = __Vdly__tb_scheduler__DOT__bank_conflict_cycles;
    vlSelf->tb_scheduler__DOT__row_hazard_cycles = __Vdly__tb_scheduler__DOT__row_hazard_cycles;
}

void Vtb_scheduler___024root___eval_nba(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtb_scheduler___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((7ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtb_scheduler___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vtb_scheduler___024root___timing_resume(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___timing_resume\n"); );
    // Body
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hc942a4a9__0.resume("@(posedge tb_scheduler.clk)");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hc9429d78__0.resume("@(negedge tb_scheduler.clk)");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdlySched.resume();
    }
}

void Vtb_scheduler___024root___timing_commit(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___timing_commit\n"); );
    // Body
    if ((! (1ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hc942a4a9__0.commit("@(posedge tb_scheduler.clk)");
    }
    if ((! (2ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hc9429d78__0.commit("@(negedge tb_scheduler.clk)");
    }
}

void Vtb_scheduler___024root___eval_triggers__act(Vtb_scheduler___024root* vlSelf);

bool Vtb_scheduler___024root___eval_phase__act(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<3> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_scheduler___024root___eval_triggers__act(vlSelf);
    Vtb_scheduler___024root___timing_commit(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vtb_scheduler___024root___timing_resume(vlSelf);
        Vtb_scheduler___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_scheduler___024root___eval_phase__nba(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtb_scheduler___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_scheduler___024root___dump_triggers__nba(Vtb_scheduler___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_scheduler___024root___dump_triggers__act(Vtb_scheduler___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_scheduler___024root___eval(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtb_scheduler___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vtb_scheduler___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 2, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vtb_scheduler___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vtb_scheduler___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtb_scheduler___024root___eval_debug_assertions(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
