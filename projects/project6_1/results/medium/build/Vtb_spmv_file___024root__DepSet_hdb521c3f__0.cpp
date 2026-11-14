// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_spmv_file.h for the primary calling header

#include "Vtb_spmv_file__pch.h"
#include "Vtb_spmv_file__Syms.h"
#include "Vtb_spmv_file___024root.h"

VL_INLINE_OPT VlCoroutine Vtb_spmv_file___024root___eval_initial__TOP__Vtiming__0(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___eval_initial__TOP__Vtiming__0\n"); );
    // Init
    IData/*31:0*/ tb_spmv_file__DOT__unnamedblk1__DOT__i;
    tb_spmv_file__DOT__unnamedblk1__DOT__i = 0;
    VlWide<3>/*95:0*/ __Vtemp_1;
    VlWide<4>/*127:0*/ __Vtemp_2;
    // Body
    __Vtemp_1[0U] = 0x6d656d68U;
    __Vtemp_1[1U] = 0x6d64732eU;
    __Vtemp_1[2U] = 0x63U;
    VL_READMEM_N(true, 64, 12290, 0, VL_CVT_PACK_STR_NW(3, __Vtemp_1)
                 ,  &(vlSelf->tb_spmv_file__DOT__commands)
                 , 0, ~0ULL);
    __Vtemp_2[0U] = 0x6d656d68U;
    __Vtemp_2[1U] = 0x7465642eU;
    __Vtemp_2[2U] = 0x78706563U;
    __Vtemp_2[3U] = 0x65U;
    VL_READMEM_N(true, 32, 1024, 0, VL_CVT_PACK_STR_NW(4, __Vtemp_2)
                 ,  &(vlSelf->tb_spmv_file__DOT__expected)
                 , 0, ~0ULL);
    co_await vlSelf->__VtrigSched_hb40da20d__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_file.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 
                                                       47);
    co_await vlSelf->__VtrigSched_hb40da20d__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_file.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 
                                                       47);
    co_await vlSelf->__VtrigSched_hb40da20d__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_file.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 
                                                       47);
    vlSelf->tb_spmv_file__DOT__rst_n = 1U;
    tb_spmv_file__DOT__unnamedblk1__DOT__i = 0U;
    while (VL_GTS_III(32, 0x3002U, tb_spmv_file__DOT__unnamedblk1__DOT__i)) {
        co_await vlSelf->__VtrigSched_hb40da20d__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(negedge tb_spmv_file.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 
                                                           52);
        vlSelf->tb_spmv_file__DOT__s_data = ((0x3001U 
                                              >= (0x3fffU 
                                                  & tb_spmv_file__DOT__unnamedblk1__DOT__i))
                                              ? vlSelf->tb_spmv_file__DOT__commands
                                             [(0x3fffU 
                                               & tb_spmv_file__DOT__unnamedblk1__DOT__i)]
                                              : 0ULL);
        vlSelf->tb_spmv_file__DOT__s_last = (0x3001U 
                                             == tb_spmv_file__DOT__unnamedblk1__DOT__i);
        vlSelf->tb_spmv_file__DOT__s_valid = 1U;
        co_await vlSelf->__VtrigSched_hb40da84c__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_file.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 
                                                           56);
        while ((1U & (~ (IData)(vlSelf->tb_spmv_file__DOT__s_ready)))) {
            co_await vlSelf->__VtrigSched_hb40da84c__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_spmv_file.clk)", 
                                                               "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 
                                                               56);
        }
        tb_spmv_file__DOT__unnamedblk1__DOT__i = ((IData)(1U) 
                                                  + tb_spmv_file__DOT__unnamedblk1__DOT__i);
    }
    co_await vlSelf->__VtrigSched_hb40da20d__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_file.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 
                                                       60);
    vlSelf->tb_spmv_file__DOT__s_valid = 0U;
    vlSelf->tb_spmv_file__DOT__s_last = 0U;
    while ((0x400U != vlSelf->tb_spmv_file__DOT__received)) {
        co_await vlSelf->__VtrigSched_hb3171717__0.trigger(1U, 
                                                           nullptr, 
                                                           "@([changed] (32'h400 == tb_spmv_file.received))", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 
                                                           63);
    }
    co_await vlSelf->__VtrigSched_hb40da20d__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_file.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 
                                                       64);
    if (VL_UNLIKELY((vlSelf->tb_spmv_file__DOT__nmac 
                     != ((IData)(0x3000U) - vlSelf->tb_spmv_file__DOT__nload)))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_week9_file.sv:68: Assertion failed in %Ntb_spmv_file: Input count accounting violation MAC=%0# LOAD=%0# CMD=12290\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelf->tb_spmv_file__DOT__nmac,
                     32,vlSelf->tb_spmv_file__DOT__nload);
        VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 68, "");
    }
    VL_WRITEF_NX("W9_FILE_RTL=PASS rows=1024 macs=%0# xloads=%0# cycles=%0#\n",0,
                 32,vlSelf->tb_spmv_file__DOT__nmac,
                 32,vlSelf->tb_spmv_file__DOT__nload,
                 32,vlSelf->tb_spmv_file__DOT__cycles);
    VL_FINISH_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 70, "");
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_spmv_file___024root___dump_triggers__act(Vtb_spmv_file___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_spmv_file___024root___eval_triggers__act(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___eval_triggers__act\n"); );
    // Body
    CData/*0:0*/ __Vtrigcurrexpr_h3330e079__0;
    __Vtrigcurrexpr_h3330e079__0 = 0;
    __Vtrigcurrexpr_h3330e079__0 = (0x400U == vlSelf->tb_spmv_file__DOT__received);
    vlSelf->__VactTriggered.set(0U, ((~ (IData)(vlSelf->tb_spmv_file__DOT__clk)) 
                                     & (IData)(vlSelf->__Vtrigprevexpr___TOP__tb_spmv_file__DOT__clk__0)));
    vlSelf->__VactTriggered.set(1U, ((IData)(vlSelf->tb_spmv_file__DOT__clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__tb_spmv_file__DOT__clk__0))));
    vlSelf->__VactTriggered.set(2U, ((IData)(__Vtrigcurrexpr_h3330e079__0) 
                                     != (IData)(vlSelf->__Vtrigprevexpr_h3330e079__0)));
    vlSelf->__VactTriggered.set(3U, vlSelf->__VdlySched.awaitingCurrentTime());
    vlSelf->__Vtrigprevexpr___TOP__tb_spmv_file__DOT__clk__0 
        = vlSelf->tb_spmv_file__DOT__clk;
    vlSelf->__Vtrigprevexpr_h3330e079__0 = __Vtrigcurrexpr_h3330e079__0;
    if (VL_UNLIKELY((1U & (~ (IData)(vlSelf->__VactDidInit))))) {
        vlSelf->__VactDidInit = 1U;
        vlSelf->__VactTriggered.set(2U, 1U);
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_spmv_file___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vtb_spmv_file___024root___nba_sequent__TOP__0(Vtb_spmv_file___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_file___024root___nba_sequent__TOP__0\n"); );
    // Init
    IData/*31:0*/ __Vdly__tb_spmv_file__DOT__cycle_count;
    __Vdly__tb_spmv_file__DOT__cycle_count = 0;
    CData/*2:0*/ __Vdly__tb_spmv_file__DOT__dut__DOT__state;
    __Vdly__tb_spmv_file__DOT__dut__DOT__state = 0;
    SData/*9:0*/ __Vdly__tb_spmv_file__DOT__dut__DOT__row_idx;
    __Vdly__tb_spmv_file__DOT__dut__DOT__row_idx = 0;
    SData/*9:0*/ __Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__ymem__v0;
    __Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__ymem__v0 = 0;
    IData/*31:0*/ __Vdlyvval__tb_spmv_file__DOT__dut__DOT__ymem__v0;
    __Vdlyvval__tb_spmv_file__DOT__dut__DOT__ymem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__tb_spmv_file__DOT__dut__DOT__ymem__v0;
    __Vdlyvset__tb_spmv_file__DOT__dut__DOT__ymem__v0 = 0;
    SData/*9:0*/ __Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__ymem__v1;
    __Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__ymem__v1 = 0;
    CData/*0:0*/ __Vdlyvset__tb_spmv_file__DOT__dut__DOT__ymem__v1;
    __Vdlyvset__tb_spmv_file__DOT__dut__DOT__ymem__v1 = 0;
    IData/*31:0*/ __Vdly__tb_spmv_file__DOT__nmac;
    __Vdly__tb_spmv_file__DOT__nmac = 0;
    IData/*31:0*/ __Vdly__tb_spmv_file__DOT__nload;
    __Vdly__tb_spmv_file__DOT__nload = 0;
    SData/*10:0*/ __Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__xmem__v0;
    __Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__xmem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__tb_spmv_file__DOT__dut__DOT__xmem__v0;
    __Vdlyvval__tb_spmv_file__DOT__dut__DOT__xmem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__tb_spmv_file__DOT__dut__DOT__xmem__v0;
    __Vdlyvset__tb_spmv_file__DOT__dut__DOT__xmem__v0 = 0;
    // Body
    __Vdly__tb_spmv_file__DOT__nload = vlSelf->tb_spmv_file__DOT__nload;
    __Vdly__tb_spmv_file__DOT__nmac = vlSelf->tb_spmv_file__DOT__nmac;
    __Vdly__tb_spmv_file__DOT__dut__DOT__row_idx = vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx;
    __Vdlyvset__tb_spmv_file__DOT__dut__DOT__xmem__v0 = 0U;
    __Vdlyvset__tb_spmv_file__DOT__dut__DOT__ymem__v0 = 0U;
    __Vdlyvset__tb_spmv_file__DOT__dut__DOT__ymem__v1 = 0U;
    __Vdly__tb_spmv_file__DOT__dut__DOT__state = vlSelf->tb_spmv_file__DOT__dut__DOT__state;
    __Vdly__tb_spmv_file__DOT__cycle_count = vlSelf->tb_spmv_file__DOT__cycle_count;
    if (vlSelf->tb_spmv_file__DOT__rst_n) {
        __Vdly__tb_spmv_file__DOT__cycle_count = ((IData)(1U) 
                                                  + vlSelf->tb_spmv_file__DOT__cycle_count);
        if (VL_UNLIKELY(((IData)(vlSelf->tb_spmv_file__DOT__stalled_prev) 
                         & (((~ (IData)(vlSelf->tb_spmv_file__DOT__m_valid)) 
                             | (vlSelf->tb_spmv_file__DOT__dut__DOT__out_q 
                                != vlSelf->tb_spmv_file__DOT__stalled_data)) 
                            | ((0x3ffU == (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx)) 
                               != (IData)(vlSelf->tb_spmv_file__DOT__stalled_last)))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_week9_file.sv:81: Assertion failed in %Ntb_spmv_file: Output payload changed under backpressure\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name());
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 81, "");
        }
        if (((IData)(vlSelf->tb_spmv_file__DOT__m_valid) 
             & (IData)(vlSelf->tb_spmv_file__DOT__m_ready))) {
            if (VL_UNLIKELY(((VL_LTES_III(32, 0x400U, vlSelf->tb_spmv_file__DOT__received) 
                              | (vlSelf->tb_spmv_file__DOT__dut__DOT__out_q 
                                 != vlSelf->tb_spmv_file__DOT__expected
                                 [(0x3ffU & vlSelf->tb_spmv_file__DOT__received)])) 
                             | ((0x3ffU == (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx)) 
                                != (0x3ffU == vlSelf->tb_spmv_file__DOT__received))))) {
                VL_WRITEF_NX("[%0t] %%Fatal: tb_week9_file.sv:92: Assertion failed in %Ntb_spmv_file: Mismatch at row %0d, got=%0d expected=%0d\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),32,
                             vlSelf->tb_spmv_file__DOT__received,
                             32,vlSelf->tb_spmv_file__DOT__dut__DOT__out_q,
                             32,vlSelf->tb_spmv_file__DOT__expected
                             [(0x3ffU & vlSelf->tb_spmv_file__DOT__received)]);
                VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 92, "");
            }
            vlSelf->tb_spmv_file__DOT__received = ((IData)(1U) 
                                                   + vlSelf->tb_spmv_file__DOT__received);
        }
        if (((IData)(vlSelf->tb_spmv_file__DOT__m_valid) 
             & (~ (IData)(vlSelf->tb_spmv_file__DOT__m_ready)))) {
            vlSelf->tb_spmv_file__DOT__stalled_prev = 1U;
            vlSelf->tb_spmv_file__DOT__stalled_data 
                = vlSelf->tb_spmv_file__DOT__dut__DOT__out_q;
            vlSelf->tb_spmv_file__DOT__stalled_last 
                = (0x3ffU == (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx));
        } else {
            vlSelf->tb_spmv_file__DOT__stalled_prev = 0U;
        }
        if (VL_UNLIKELY(VL_LTS_III(32, 0x22f24U, vlSelf->tb_spmv_file__DOT__cycle_count))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_week9_file.sv:97: Assertion failed in %Ntb_spmv_file: Simulation timeout\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name());
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/tb_week9_file.sv", 97, "");
        }
    }
    vlSelf->tb_spmv_file__DOT__cycle_count = __Vdly__tb_spmv_file__DOT__cycle_count;
    if (vlSelf->tb_spmv_file__DOT__rst_n) {
        vlSelf->tb_spmv_file__DOT__cycles = ((IData)(1U) 
                                             + vlSelf->tb_spmv_file__DOT__cycles);
        if ((4U & (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__state))) {
            if (VL_UNLIKELY((2U & (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__state)))) {
                VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:183: Assertion failed in %Ntb_spmv_file.dut: Illegal state\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name());
                VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/week9_spmv_axis.sv", 183, "");
            } else if (VL_UNLIKELY((1U & (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__state)))) {
                VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:183: Assertion failed in %Ntb_spmv_file.dut: Illegal state\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name());
                VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/week9_spmv_axis.sv", 183, "");
            } else if (((IData)(vlSelf->tb_spmv_file__DOT__m_valid) 
                        & (IData)(vlSelf->tb_spmv_file__DOT__m_ready))) {
                if ((0x3ffU == (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx))) {
                    __Vdly__tb_spmv_file__DOT__dut__DOT__state = 0U;
                } else {
                    __Vdly__tb_spmv_file__DOT__dut__DOT__row_idx 
                        = (0x3ffU & ((IData)(1U) + (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx)));
                    __Vdly__tb_spmv_file__DOT__dut__DOT__state = 3U;
                }
            }
        } else if ((2U & (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__state))) {
            if ((1U & (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__state))) {
                vlSelf->tb_spmv_file__DOT__dut__DOT__out_q 
                    = vlSelf->tb_spmv_file__DOT__dut__DOT__ymem
                    [vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx];
                __Vdly__tb_spmv_file__DOT__dut__DOT__state = 4U;
            } else {
                __Vdlyvval__tb_spmv_file__DOT__dut__DOT__ymem__v0 
                    = (vlSelf->tb_spmv_file__DOT__dut__DOT__y_q 
                       + VL_MULS_III(32, VL_EXTENDS_II(32,16, (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__a_q)), 
                                     VL_EXTENDS_II(32,16, (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__x_q))));
                __Vdlyvset__tb_spmv_file__DOT__dut__DOT__ymem__v0 = 1U;
                __Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__ymem__v0 
                    = vlSelf->tb_spmv_file__DOT__dut__DOT__row_q;
                __Vdly__tb_spmv_file__DOT__dut__DOT__state = 0U;
            }
        } else if ((1U & (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__state))) {
            __Vdlyvset__tb_spmv_file__DOT__dut__DOT__ymem__v1 = 1U;
            __Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__ymem__v1 
                = vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx;
            if ((0x3ffU == (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx))) {
                __Vdly__tb_spmv_file__DOT__dut__DOT__row_idx = 0U;
                __Vdly__tb_spmv_file__DOT__dut__DOT__state = 0U;
            } else {
                __Vdly__tb_spmv_file__DOT__dut__DOT__row_idx 
                    = (0x3ffU & ((IData)(1U) + (IData)(vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx)));
            }
        } else if (((IData)(vlSelf->tb_spmv_file__DOT__s_valid) 
                    & (IData)(vlSelf->tb_spmv_file__DOT__s_ready))) {
            if ((1U & (IData)((vlSelf->tb_spmv_file__DOT__s_data 
                               >> 0x3fU)))) {
                if ((1U & (IData)((vlSelf->tb_spmv_file__DOT__s_data 
                                   >> 0x3eU)))) {
                    if (VL_UNLIKELY((1U & (~ (IData)(vlSelf->tb_spmv_file__DOT__s_last))))) {
                        VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:142: Assertion failed in %Ntb_spmv_file.dut: DRAIN_Y must be final input command\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name());
                        VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/week9_spmv_axis.sv", 142, "");
                    }
                    __Vdly__tb_spmv_file__DOT__dut__DOT__row_idx = 0U;
                    __Vdly__tb_spmv_file__DOT__dut__DOT__state = 3U;
                } else {
                    if (VL_UNLIKELY(vlSelf->tb_spmv_file__DOT__s_last)) {
                        VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:131: Assertion failed in %Ntb_spmv_file.dut: CLEAR_Y cannot terminate command stream\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name());
                        VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/week9_spmv_axis.sv", 131, "");
                    }
                    __Vdly__tb_spmv_file__DOT__dut__DOT__row_idx = 0U;
                    __Vdly__tb_spmv_file__DOT__nmac = 0U;
                    __Vdly__tb_spmv_file__DOT__nload = 0U;
                    __Vdly__tb_spmv_file__DOT__dut__DOT__state = 1U;
                }
            } else if ((1U & (IData)((vlSelf->tb_spmv_file__DOT__s_data 
                                      >> 0x3eU)))) {
                if (VL_UNLIKELY(((VL_LTES_III(32, 0x400U, 
                                              (0x7fffU 
                                               & (IData)(
                                                         (vlSelf->tb_spmv_file__DOT__s_data 
                                                          >> 0x2fU)))) 
                                  | VL_LTES_III(32, 0x800U, 
                                                (0x7ffU 
                                                 & (IData)(
                                                           (vlSelf->tb_spmv_file__DOT__s_data 
                                                            >> 0x24U))))) 
                                 | ((0xffffU & (IData)(
                                                       (vlSelf->tb_spmv_file__DOT__s_data 
                                                        >> 0x10U))) 
                                    != (0xffffU & (- (IData)(
                                                             (1U 
                                                              & (IData)(
                                                                        (vlSelf->tb_spmv_file__DOT__s_data 
                                                                         >> 0xfU)))))))))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:118: Assertion failed in %Ntb_spmv_file.dut: MAC index/width violation\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name());
                    VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/week9_spmv_axis.sv", 118, "");
                }
                __Vdly__tb_spmv_file__DOT__nmac = ((IData)(1U) 
                                                   + vlSelf->tb_spmv_file__DOT__nmac);
                vlSelf->tb_spmv_file__DOT__dut__DOT__row_q 
                    = (0x3ffU & (IData)((vlSelf->tb_spmv_file__DOT__s_data 
                                         >> 0x2fU)));
                vlSelf->tb_spmv_file__DOT__dut__DOT__a_q 
                    = (0xffffU & (IData)(vlSelf->tb_spmv_file__DOT__s_data));
                vlSelf->tb_spmv_file__DOT__dut__DOT__x_q 
                    = vlSelf->tb_spmv_file__DOT__dut__DOT__xmem
                    [(0x7ffU & (IData)((vlSelf->tb_spmv_file__DOT__s_data 
                                        >> 0x24U)))];
                vlSelf->tb_spmv_file__DOT__dut__DOT__y_q 
                    = vlSelf->tb_spmv_file__DOT__dut__DOT__ymem
                    [(0x3ffU & (IData)((vlSelf->tb_spmv_file__DOT__s_data 
                                        >> 0x2fU)))];
                __Vdly__tb_spmv_file__DOT__dut__DOT__state = 2U;
            } else {
                if (VL_UNLIKELY((VL_LTES_III(32, 0x800U, 
                                             (0x7ffU 
                                              & (IData)(
                                                        (vlSelf->tb_spmv_file__DOT__s_data 
                                                         >> 0x24U)))) 
                                 | ((0xffffU & (IData)(
                                                       (vlSelf->tb_spmv_file__DOT__s_data 
                                                        >> 0x10U))) 
                                    != (0xffffU & (- (IData)(
                                                             (1U 
                                                              & (IData)(
                                                                        (vlSelf->tb_spmv_file__DOT__s_data 
                                                                         >> 0xfU)))))))))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:106: Assertion failed in %Ntb_spmv_file.dut: LOAD_X index/width violation\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name());
                    VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/medium/sources/week9_spmv_axis.sv", 106, "");
                }
                __Vdly__tb_spmv_file__DOT__nload = 
                    ((IData)(1U) + vlSelf->tb_spmv_file__DOT__nload);
                __Vdlyvval__tb_spmv_file__DOT__dut__DOT__xmem__v0 
                    = (0xffffU & (IData)(vlSelf->tb_spmv_file__DOT__s_data));
                __Vdlyvset__tb_spmv_file__DOT__dut__DOT__xmem__v0 = 1U;
                __Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__xmem__v0 
                    = (0x7ffU & (IData)((vlSelf->tb_spmv_file__DOT__s_data 
                                         >> 0x24U)));
            }
        }
    } else {
        __Vdly__tb_spmv_file__DOT__dut__DOT__row_idx = 0U;
        vlSelf->tb_spmv_file__DOT__cycles = 0U;
        __Vdly__tb_spmv_file__DOT__dut__DOT__state = 0U;
        vlSelf->tb_spmv_file__DOT__dut__DOT__row_q = 0U;
        vlSelf->tb_spmv_file__DOT__dut__DOT__a_q = 0U;
        vlSelf->tb_spmv_file__DOT__dut__DOT__x_q = 0U;
        vlSelf->tb_spmv_file__DOT__dut__DOT__y_q = 0U;
        vlSelf->tb_spmv_file__DOT__dut__DOT__out_q = 0U;
        __Vdly__tb_spmv_file__DOT__nmac = 0U;
        __Vdly__tb_spmv_file__DOT__nload = 0U;
    }
    vlSelf->tb_spmv_file__DOT__dut__DOT__row_idx = __Vdly__tb_spmv_file__DOT__dut__DOT__row_idx;
    vlSelf->tb_spmv_file__DOT__nmac = __Vdly__tb_spmv_file__DOT__nmac;
    vlSelf->tb_spmv_file__DOT__nload = __Vdly__tb_spmv_file__DOT__nload;
    if (__Vdlyvset__tb_spmv_file__DOT__dut__DOT__xmem__v0) {
        vlSelf->tb_spmv_file__DOT__dut__DOT__xmem[__Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__xmem__v0] 
            = __Vdlyvval__tb_spmv_file__DOT__dut__DOT__xmem__v0;
    }
    if (__Vdlyvset__tb_spmv_file__DOT__dut__DOT__ymem__v0) {
        vlSelf->tb_spmv_file__DOT__dut__DOT__ymem[__Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__ymem__v0] 
            = __Vdlyvval__tb_spmv_file__DOT__dut__DOT__ymem__v0;
    }
    if (__Vdlyvset__tb_spmv_file__DOT__dut__DOT__ymem__v1) {
        vlSelf->tb_spmv_file__DOT__dut__DOT__ymem[__Vdlyvdim0__tb_spmv_file__DOT__dut__DOT__ymem__v1] = 0U;
    }
    vlSelf->tb_spmv_file__DOT__dut__DOT__state = __Vdly__tb_spmv_file__DOT__dut__DOT__state;
}
