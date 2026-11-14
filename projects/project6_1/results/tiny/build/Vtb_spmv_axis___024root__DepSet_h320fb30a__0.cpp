// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_spmv_axis.h for the primary calling header

#include "Vtb_spmv_axis__pch.h"
#include "Vtb_spmv_axis__Syms.h"
#include "Vtb_spmv_axis___024root.h"

VL_INLINE_OPT VlCoroutine Vtb_spmv_axis___024root___eval_initial__TOP__Vtiming__0(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___eval_initial__TOP__Vtiming__0\n"); );
    // Init
    QData/*63:0*/ __Vtask_tb_spmv_axis__DOT__send__0__command;
    __Vtask_tb_spmv_axis__DOT__send__0__command = 0;
    CData/*0:0*/ __Vtask_tb_spmv_axis__DOT__send__0__last;
    __Vtask_tb_spmv_axis__DOT__send__0__last = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__1__Vfuncout;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__1__op;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__op = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__1__row;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__row = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__1__col;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__col = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__1__value;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__value = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__1__t;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__t = 0;
    QData/*63:0*/ __Vtask_tb_spmv_axis__DOT__send__2__command;
    __Vtask_tb_spmv_axis__DOT__send__2__command = 0;
    CData/*0:0*/ __Vtask_tb_spmv_axis__DOT__send__2__last;
    __Vtask_tb_spmv_axis__DOT__send__2__last = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__3__op;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__op = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__3__row;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__row = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__3__col;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__col = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__3__value;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__value = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__3__t;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = 0;
    QData/*63:0*/ __Vtask_tb_spmv_axis__DOT__send__4__command;
    __Vtask_tb_spmv_axis__DOT__send__4__command = 0;
    CData/*0:0*/ __Vtask_tb_spmv_axis__DOT__send__4__last;
    __Vtask_tb_spmv_axis__DOT__send__4__last = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__5__Vfuncout;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__5__op;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__op = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__5__row;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__row = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__5__col;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__col = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__5__value;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__value = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__5__t;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__t = 0;
    QData/*63:0*/ __Vtask_tb_spmv_axis__DOT__send__6__command;
    __Vtask_tb_spmv_axis__DOT__send__6__command = 0;
    CData/*0:0*/ __Vtask_tb_spmv_axis__DOT__send__6__last;
    __Vtask_tb_spmv_axis__DOT__send__6__last = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__7__Vfuncout;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__7__op;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__op = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__7__row;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__row = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__7__col;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__col = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__7__value;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__value = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__7__t;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__t = 0;
    QData/*63:0*/ __Vtask_tb_spmv_axis__DOT__send__8__command;
    __Vtask_tb_spmv_axis__DOT__send__8__command = 0;
    CData/*0:0*/ __Vtask_tb_spmv_axis__DOT__send__8__last;
    __Vtask_tb_spmv_axis__DOT__send__8__last = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__9__Vfuncout;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__9__op;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__op = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__9__row;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__row = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__9__col;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__col = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__9__value;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__value = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__9__t;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__t = 0;
    QData/*63:0*/ __Vtask_tb_spmv_axis__DOT__send__10__command;
    __Vtask_tb_spmv_axis__DOT__send__10__command = 0;
    CData/*0:0*/ __Vtask_tb_spmv_axis__DOT__send__10__last;
    __Vtask_tb_spmv_axis__DOT__send__10__last = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__11__Vfuncout;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__11__op;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__op = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__11__row;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__row = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__11__col;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__col = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__11__value;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__value = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__11__t;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__t = 0;
    QData/*63:0*/ __Vtask_tb_spmv_axis__DOT__send__12__command;
    __Vtask_tb_spmv_axis__DOT__send__12__command = 0;
    CData/*0:0*/ __Vtask_tb_spmv_axis__DOT__send__12__last;
    __Vtask_tb_spmv_axis__DOT__send__12__last = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__13__Vfuncout;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__13__op;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__op = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__13__row;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__row = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__13__col;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__col = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__13__value;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__value = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__13__t;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__t = 0;
    QData/*63:0*/ __Vtask_tb_spmv_axis__DOT__send__14__command;
    __Vtask_tb_spmv_axis__DOT__send__14__command = 0;
    CData/*0:0*/ __Vtask_tb_spmv_axis__DOT__send__14__last;
    __Vtask_tb_spmv_axis__DOT__send__14__last = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__15__Vfuncout;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__15__op;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__op = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__15__row;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__row = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__15__col;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__col = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__15__value;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__value = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__15__t;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__t = 0;
    QData/*63:0*/ __Vtask_tb_spmv_axis__DOT__send__16__command;
    __Vtask_tb_spmv_axis__DOT__send__16__command = 0;
    CData/*0:0*/ __Vtask_tb_spmv_axis__DOT__send__16__last;
    __Vtask_tb_spmv_axis__DOT__send__16__last = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__17__Vfuncout;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__17__op;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__op = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__17__row;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__row = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__17__col;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__col = 0;
    IData/*31:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__17__value;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__value = 0;
    QData/*63:0*/ __Vfunc_tb_spmv_axis__DOT__cmd__17__t;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__t = 0;
    // Body
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       93);
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       93);
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       93);
    vlSelf->tb_spmv_axis__DOT__rst_n = 1U;
    __Vtask_tb_spmv_axis__DOT__send__0__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__value = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__col = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__row = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__op = 2U;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__1__t = ((0xfffffffffULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__1__t) 
                                            | ((QData)((IData)(
                                                               (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__1__op) 
                                                                 << 0x1aU) 
                                                                | ((0x3fff800U 
                                                                    & (__Vfunc_tb_spmv_axis__DOT__cmd__1__row 
                                                                       << 0xbU)) 
                                                                   | (0x7ffU 
                                                                      & __Vfunc_tb_spmv_axis__DOT__cmd__1__col))))) 
                                               << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__1__t = ((0xffffffff00000000ULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__1__t) 
                                            | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__1__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__1__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__1__t;
    __Vtask_tb_spmv_axis__DOT__send__0__command = __Vfunc_tb_spmv_axis__DOT__cmd__1__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__0__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__0__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__2__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__value = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__col = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__row = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__op = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = ((0xfffffffffULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__3__t) 
                                            | ((QData)((IData)(
                                                               (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__3__op) 
                                                                 << 0x1aU) 
                                                                | ((0x3fff800U 
                                                                    & (__Vfunc_tb_spmv_axis__DOT__cmd__3__row 
                                                                       << 0xbU)) 
                                                                   | (0x7ffU 
                                                                      & __Vfunc_tb_spmv_axis__DOT__cmd__3__col))))) 
                                               << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = ((0xffffffff00000000ULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__3__t) 
                                            | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__3__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__3__t;
    __Vtask_tb_spmv_axis__DOT__send__2__command = __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__2__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__2__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__2__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__value = 2U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__col = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__row = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__op = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = ((0xfffffffffULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__3__t) 
                                            | ((QData)((IData)(
                                                               (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__3__op) 
                                                                 << 0x1aU) 
                                                                | ((0x3fff800U 
                                                                    & (__Vfunc_tb_spmv_axis__DOT__cmd__3__row 
                                                                       << 0xbU)) 
                                                                   | (0x7ffU 
                                                                      & __Vfunc_tb_spmv_axis__DOT__cmd__3__col))))) 
                                               << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = ((0xffffffff00000000ULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__3__t) 
                                            | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__3__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__3__t;
    __Vtask_tb_spmv_axis__DOT__send__2__command = __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__2__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__2__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__2__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__value = 3U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__col = 2U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__row = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__op = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = ((0xfffffffffULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__3__t) 
                                            | ((QData)((IData)(
                                                               (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__3__op) 
                                                                 << 0x1aU) 
                                                                | ((0x3fff800U 
                                                                    & (__Vfunc_tb_spmv_axis__DOT__cmd__3__row 
                                                                       << 0xbU)) 
                                                                   | (0x7ffU 
                                                                      & __Vfunc_tb_spmv_axis__DOT__cmd__3__col))))) 
                                               << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = ((0xffffffff00000000ULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__3__t) 
                                            | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__3__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__3__t;
    __Vtask_tb_spmv_axis__DOT__send__2__command = __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__2__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__2__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__2__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__value = 4U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__col = 3U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__row = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__op = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = ((0xfffffffffULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__3__t) 
                                            | ((QData)((IData)(
                                                               (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__3__op) 
                                                                 << 0x1aU) 
                                                                | ((0x3fff800U 
                                                                    & (__Vfunc_tb_spmv_axis__DOT__cmd__3__row 
                                                                       << 0xbU)) 
                                                                   | (0x7ffU 
                                                                      & __Vfunc_tb_spmv_axis__DOT__cmd__3__col))))) 
                                               << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = ((0xffffffff00000000ULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__3__t) 
                                            | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__3__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__3__t;
    __Vtask_tb_spmv_axis__DOT__send__2__command = __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__2__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__2__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__2__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__value = 5U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__col = 4U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__row = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__op = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = ((0xfffffffffULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__3__t) 
                                            | ((QData)((IData)(
                                                               (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__3__op) 
                                                                 << 0x1aU) 
                                                                | ((0x3fff800U 
                                                                    & (__Vfunc_tb_spmv_axis__DOT__cmd__3__row 
                                                                       << 0xbU)) 
                                                                   | (0x7ffU 
                                                                      & __Vfunc_tb_spmv_axis__DOT__cmd__3__col))))) 
                                               << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__3__t = ((0xffffffff00000000ULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__3__t) 
                                            | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__3__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__3__t;
    __Vtask_tb_spmv_axis__DOT__send__2__command = __Vfunc_tb_spmv_axis__DOT__cmd__3__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__2__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__2__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__4__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__value = 2U;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__col = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__row = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__op = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__5__t = ((0xfffffffffULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__5__t) 
                                            | ((QData)((IData)(
                                                               (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__5__op) 
                                                                 << 0x1aU) 
                                                                | ((0x3fff800U 
                                                                    & (__Vfunc_tb_spmv_axis__DOT__cmd__5__row 
                                                                       << 0xbU)) 
                                                                   | (0x7ffU 
                                                                      & __Vfunc_tb_spmv_axis__DOT__cmd__5__col))))) 
                                               << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__5__t = ((0xffffffff00000000ULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__5__t) 
                                            | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__5__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__5__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__5__t;
    __Vtask_tb_spmv_axis__DOT__send__4__command = __Vfunc_tb_spmv_axis__DOT__cmd__5__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__4__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__4__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__6__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__value = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__col = 3U;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__row = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__op = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__7__t = ((0xfffffffffULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__7__t) 
                                            | ((QData)((IData)(
                                                               (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__7__op) 
                                                                 << 0x1aU) 
                                                                | ((0x3fff800U 
                                                                    & (__Vfunc_tb_spmv_axis__DOT__cmd__7__row 
                                                                       << 0xbU)) 
                                                                   | (0x7ffU 
                                                                      & __Vfunc_tb_spmv_axis__DOT__cmd__7__col))))) 
                                               << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__7__t = ((0xffffffff00000000ULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__7__t) 
                                            | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__7__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__7__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__7__t;
    __Vtask_tb_spmv_axis__DOT__send__6__command = __Vfunc_tb_spmv_axis__DOT__cmd__7__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__6__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__6__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__8__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__value = 3U;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__col = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__row = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__op = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__9__t = ((0xfffffffffULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__9__t) 
                                            | ((QData)((IData)(
                                                               (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__9__op) 
                                                                 << 0x1aU) 
                                                                | ((0x3fff800U 
                                                                    & (__Vfunc_tb_spmv_axis__DOT__cmd__9__row 
                                                                       << 0xbU)) 
                                                                   | (0x7ffU 
                                                                      & __Vfunc_tb_spmv_axis__DOT__cmd__9__col))))) 
                                               << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__9__t = ((0xffffffff00000000ULL 
                                             & __Vfunc_tb_spmv_axis__DOT__cmd__9__t) 
                                            | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__9__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__9__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__9__t;
    __Vtask_tb_spmv_axis__DOT__send__8__command = __Vfunc_tb_spmv_axis__DOT__cmd__9__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__8__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__8__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__10__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__value = 4U;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__col = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__row = 2U;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__op = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__11__t = ((0xfffffffffULL 
                                              & __Vfunc_tb_spmv_axis__DOT__cmd__11__t) 
                                             | ((QData)((IData)(
                                                                (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__11__op) 
                                                                  << 0x1aU) 
                                                                 | ((0x3fff800U 
                                                                     & (__Vfunc_tb_spmv_axis__DOT__cmd__11__row 
                                                                        << 0xbU)) 
                                                                    | (0x7ffU 
                                                                       & __Vfunc_tb_spmv_axis__DOT__cmd__11__col))))) 
                                                << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__11__t = ((0xffffffff00000000ULL 
                                              & __Vfunc_tb_spmv_axis__DOT__cmd__11__t) 
                                             | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__11__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__11__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__11__t;
    __Vtask_tb_spmv_axis__DOT__send__10__command = __Vfunc_tb_spmv_axis__DOT__cmd__11__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__10__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__10__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__12__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__value = 0xffffffffU;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__col = 4U;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__row = 2U;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__op = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__13__t = ((0xfffffffffULL 
                                              & __Vfunc_tb_spmv_axis__DOT__cmd__13__t) 
                                             | ((QData)((IData)(
                                                                (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__13__op) 
                                                                  << 0x1aU) 
                                                                 | ((0x3fff800U 
                                                                     & (__Vfunc_tb_spmv_axis__DOT__cmd__13__row 
                                                                        << 0xbU)) 
                                                                    | (0x7ffU 
                                                                       & __Vfunc_tb_spmv_axis__DOT__cmd__13__col))))) 
                                                << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__13__t = ((0xffffffff00000000ULL 
                                              & __Vfunc_tb_spmv_axis__DOT__cmd__13__t) 
                                             | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__13__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__13__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__13__t;
    __Vtask_tb_spmv_axis__DOT__send__12__command = __Vfunc_tb_spmv_axis__DOT__cmd__13__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__12__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__12__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__14__last = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__value = 5U;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__col = 2U;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__row = 3U;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__op = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__15__t = ((0xfffffffffULL 
                                              & __Vfunc_tb_spmv_axis__DOT__cmd__15__t) 
                                             | ((QData)((IData)(
                                                                (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__15__op) 
                                                                  << 0x1aU) 
                                                                 | ((0x3fff800U 
                                                                     & (__Vfunc_tb_spmv_axis__DOT__cmd__15__row 
                                                                        << 0xbU)) 
                                                                    | (0x7ffU 
                                                                       & __Vfunc_tb_spmv_axis__DOT__cmd__15__col))))) 
                                                << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__15__t = ((0xffffffff00000000ULL 
                                              & __Vfunc_tb_spmv_axis__DOT__cmd__15__t) 
                                             | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__15__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__15__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__15__t;
    __Vtask_tb_spmv_axis__DOT__send__14__command = __Vfunc_tb_spmv_axis__DOT__cmd__15__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__14__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__14__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    __Vtask_tb_spmv_axis__DOT__send__16__last = 1U;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__value = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__col = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__row = 0U;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__op = 3U;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__t = 0ULL;
    __Vfunc_tb_spmv_axis__DOT__cmd__17__t = ((0xfffffffffULL 
                                              & __Vfunc_tb_spmv_axis__DOT__cmd__17__t) 
                                             | ((QData)((IData)(
                                                                (((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__17__op) 
                                                                  << 0x1aU) 
                                                                 | ((0x3fff800U 
                                                                     & (__Vfunc_tb_spmv_axis__DOT__cmd__17__row 
                                                                        << 0xbU)) 
                                                                    | (0x7ffU 
                                                                       & __Vfunc_tb_spmv_axis__DOT__cmd__17__col))))) 
                                                << 0x24U));
    __Vfunc_tb_spmv_axis__DOT__cmd__17__t = ((0xffffffff00000000ULL 
                                              & __Vfunc_tb_spmv_axis__DOT__cmd__17__t) 
                                             | (IData)((IData)(__Vfunc_tb_spmv_axis__DOT__cmd__17__value)));
    __Vfunc_tb_spmv_axis__DOT__cmd__17__Vfuncout = __Vfunc_tb_spmv_axis__DOT__cmd__17__t;
    __Vtask_tb_spmv_axis__DOT__send__16__command = __Vfunc_tb_spmv_axis__DOT__cmd__17__Vfuncout;
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       54);
    vlSelf->tb_spmv_axis__DOT__s_data = __Vtask_tb_spmv_axis__DOT__send__16__command;
    vlSelf->tb_spmv_axis__DOT__s_last = __Vtask_tb_spmv_axis__DOT__send__16__last;
    vlSelf->tb_spmv_axis__DOT__s_valid = 1U;
    co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       58);
    while ((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_ready)))) {
        co_await vlSelf->__VtrigSched_h5acff1c0__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_spmv_axis.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           58);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       59);
    vlSelf->tb_spmv_axis__DOT__s_valid = 0U;
    vlSelf->tb_spmv_axis__DOT__s_last = 0U;
    while ((4U != vlSelf->tb_spmv_axis__DOT__captured)) {
        co_await vlSelf->__VtrigSched_h2c61e446__0.trigger(1U, 
                                                           nullptr, 
                                                           "@([changed] (32'sh4 == tb_spmv_axis.captured))", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                           108);
    }
    co_await vlSelf->__VtrigSched_h5acff1b1__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_spmv_axis.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 
                                                       109);
    if (VL_UNLIKELY(((6U != vlSelf->tb_spmv_axis__DOT__nmac) 
                     | (5U != vlSelf->tb_spmv_axis__DOT__nload)))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_week9_spmv_axis.sv:111: Assertion failed in %Ntb_spmv_axis: Counter mismatch MAC=%0# LOAD=%0#\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelf->tb_spmv_axis__DOT__nmac,
                     32,vlSelf->tb_spmv_axis__DOT__nload);
        VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 111, "");
    }
    VL_WRITEF_NX("W9_VERILATOR_SPMV=PASS rows=4 mac=6 y=[6,6,-1,15] cycles=%0#\n",0,
                 32,vlSelf->tb_spmv_axis__DOT__cycles);
    VL_FINISH_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 113, "");
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_spmv_axis___024root___dump_triggers__act(Vtb_spmv_axis___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_spmv_axis___024root___eval_triggers__act(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___eval_triggers__act\n"); );
    // Body
    CData/*0:0*/ __Vtrigcurrexpr_hbc56aa34__0;
    __Vtrigcurrexpr_hbc56aa34__0 = 0;
    __Vtrigcurrexpr_hbc56aa34__0 = (4U == vlSelf->tb_spmv_axis__DOT__captured);
    vlSelf->__VactTriggered.set(0U, ((~ (IData)(vlSelf->tb_spmv_axis__DOT__clk)) 
                                     & (IData)(vlSelf->__Vtrigprevexpr___TOP__tb_spmv_axis__DOT__clk__0)));
    vlSelf->__VactTriggered.set(1U, ((IData)(vlSelf->tb_spmv_axis__DOT__clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__tb_spmv_axis__DOT__clk__0))));
    vlSelf->__VactTriggered.set(2U, ((IData)(__Vtrigcurrexpr_hbc56aa34__0) 
                                     != (IData)(vlSelf->__Vtrigprevexpr_hbc56aa34__0)));
    vlSelf->__VactTriggered.set(3U, vlSelf->__VdlySched.awaitingCurrentTime());
    vlSelf->__Vtrigprevexpr___TOP__tb_spmv_axis__DOT__clk__0 
        = vlSelf->tb_spmv_axis__DOT__clk;
    vlSelf->__Vtrigprevexpr_hbc56aa34__0 = __Vtrigcurrexpr_hbc56aa34__0;
    if (VL_UNLIKELY((1U & (~ (IData)(vlSelf->__VactDidInit))))) {
        vlSelf->__VactDidInit = 1U;
        vlSelf->__VactTriggered.set(2U, 1U);
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_spmv_axis___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vtb_spmv_axis___024root___nba_sequent__TOP__0(Vtb_spmv_axis___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_spmv_axis__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_spmv_axis___024root___nba_sequent__TOP__0\n"); );
    // Init
    IData/*31:0*/ __Vdly__tb_spmv_axis__DOT__total_cycles;
    __Vdly__tb_spmv_axis__DOT__total_cycles = 0;
    CData/*2:0*/ __Vdly__tb_spmv_axis__DOT__dut__DOT__state;
    __Vdly__tb_spmv_axis__DOT__dut__DOT__state = 0;
    CData/*1:0*/ __Vdly__tb_spmv_axis__DOT__dut__DOT__row_idx;
    __Vdly__tb_spmv_axis__DOT__dut__DOT__row_idx = 0;
    CData/*1:0*/ __Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__ymem__v0;
    __Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__ymem__v0 = 0;
    IData/*31:0*/ __Vdlyvval__tb_spmv_axis__DOT__dut__DOT__ymem__v0;
    __Vdlyvval__tb_spmv_axis__DOT__dut__DOT__ymem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__ymem__v0;
    __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__ymem__v0 = 0;
    CData/*1:0*/ __Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__ymem__v1;
    __Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__ymem__v1 = 0;
    CData/*0:0*/ __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__ymem__v1;
    __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__ymem__v1 = 0;
    IData/*31:0*/ __Vdly__tb_spmv_axis__DOT__nmac;
    __Vdly__tb_spmv_axis__DOT__nmac = 0;
    IData/*31:0*/ __Vdly__tb_spmv_axis__DOT__nload;
    __Vdly__tb_spmv_axis__DOT__nload = 0;
    CData/*2:0*/ __Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__xmem__v0;
    __Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__xmem__v0 = 0;
    SData/*15:0*/ __Vdlyvval__tb_spmv_axis__DOT__dut__DOT__xmem__v0;
    __Vdlyvval__tb_spmv_axis__DOT__dut__DOT__xmem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__xmem__v0;
    __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__xmem__v0 = 0;
    // Body
    __Vdly__tb_spmv_axis__DOT__nload = vlSelf->tb_spmv_axis__DOT__nload;
    __Vdly__tb_spmv_axis__DOT__nmac = vlSelf->tb_spmv_axis__DOT__nmac;
    __Vdly__tb_spmv_axis__DOT__dut__DOT__row_idx = vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx;
    __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__xmem__v0 = 0U;
    __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__ymem__v0 = 0U;
    __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__ymem__v1 = 0U;
    __Vdly__tb_spmv_axis__DOT__dut__DOT__state = vlSelf->tb_spmv_axis__DOT__dut__DOT__state;
    __Vdly__tb_spmv_axis__DOT__total_cycles = vlSelf->tb_spmv_axis__DOT__total_cycles;
    if (vlSelf->tb_spmv_axis__DOT__rst_n) {
        __Vdly__tb_spmv_axis__DOT__total_cycles = ((IData)(1U) 
                                                   + vlSelf->tb_spmv_axis__DOT__total_cycles);
        if (VL_UNLIKELY(((IData)(vlSelf->tb_spmv_axis__DOT__stalled_prev) 
                         & (((~ (IData)(vlSelf->tb_spmv_axis__DOT__m_valid)) 
                             | (vlSelf->tb_spmv_axis__DOT__dut__DOT__out_q 
                                != vlSelf->tb_spmv_axis__DOT__stalled_data)) 
                            | ((3U == (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx)) 
                               != (IData)(vlSelf->tb_spmv_axis__DOT__stalled_last)))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_week9_spmv_axis.sv:72: Assertion failed in %Ntb_spmv_axis: Output changed while stalled\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name());
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 72, "");
        }
        if (((IData)(vlSelf->tb_spmv_axis__DOT__m_valid) 
             & (IData)(vlSelf->tb_spmv_axis__DOT__m_ready))) {
            if (VL_UNLIKELY((VL_LTES_III(32, 4U, vlSelf->tb_spmv_axis__DOT__captured) 
                             | (vlSelf->tb_spmv_axis__DOT__dut__DOT__out_q 
                                != vlSelf->tb_spmv_axis__DOT__exp_y
                                [(3U & vlSelf->tb_spmv_axis__DOT__captured)])))) {
                VL_WRITEF_NX("[%0t] %%Fatal: tb_week9_spmv_axis.sv:82: Assertion failed in %Ntb_spmv_axis: Output mismatch at %0d: %0d\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),32,
                             vlSelf->tb_spmv_axis__DOT__captured,
                             32,vlSelf->tb_spmv_axis__DOT__dut__DOT__out_q);
                VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 82, "");
            }
            if (VL_UNLIKELY(((3U == (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx)) 
                             != (3U == vlSelf->tb_spmv_axis__DOT__captured)))) {
                VL_WRITEF_NX("[%0t] %%Fatal: tb_week9_spmv_axis.sv:83: Assertion failed in %Ntb_spmv_axis: Incorrect TLAST\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name());
                VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 83, "");
            }
            vlSelf->tb_spmv_axis__DOT__captured = ((IData)(1U) 
                                                   + vlSelf->tb_spmv_axis__DOT__captured);
        }
        if (((IData)(vlSelf->tb_spmv_axis__DOT__m_valid) 
             & (~ (IData)(vlSelf->tb_spmv_axis__DOT__m_ready)))) {
            vlSelf->tb_spmv_axis__DOT__stalled_prev = 1U;
            vlSelf->tb_spmv_axis__DOT__stalled_data 
                = vlSelf->tb_spmv_axis__DOT__dut__DOT__out_q;
            vlSelf->tb_spmv_axis__DOT__stalled_last 
                = (3U == (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx));
        } else {
            vlSelf->tb_spmv_axis__DOT__stalled_prev = 0U;
        }
        if (VL_UNLIKELY(VL_LTS_III(32, 0x1f4U, vlSelf->tb_spmv_axis__DOT__total_cycles))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_week9_spmv_axis.sv:88: Assertion failed in %Ntb_spmv_axis: Timeout\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name());
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/tb_week9_spmv_axis.sv", 88, "");
        }
    }
    vlSelf->tb_spmv_axis__DOT__total_cycles = __Vdly__tb_spmv_axis__DOT__total_cycles;
    if (vlSelf->tb_spmv_axis__DOT__rst_n) {
        vlSelf->tb_spmv_axis__DOT__cycles = ((IData)(1U) 
                                             + vlSelf->tb_spmv_axis__DOT__cycles);
        if ((4U & (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__state))) {
            if (VL_UNLIKELY((2U & (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__state)))) {
                VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:183: Assertion failed in %Ntb_spmv_axis.dut: Illegal state\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name());
                VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/week9_spmv_axis.sv", 183, "");
            } else if (VL_UNLIKELY((1U & (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__state)))) {
                VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:183: Assertion failed in %Ntb_spmv_axis.dut: Illegal state\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name());
                VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/week9_spmv_axis.sv", 183, "");
            } else if (((IData)(vlSelf->tb_spmv_axis__DOT__m_valid) 
                        & (IData)(vlSelf->tb_spmv_axis__DOT__m_ready))) {
                if ((3U == (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx))) {
                    __Vdly__tb_spmv_axis__DOT__dut__DOT__state = 0U;
                } else {
                    __Vdly__tb_spmv_axis__DOT__dut__DOT__row_idx 
                        = (3U & ((IData)(1U) + (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx)));
                    __Vdly__tb_spmv_axis__DOT__dut__DOT__state = 3U;
                }
            }
        } else if ((2U & (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__state))) {
            if ((1U & (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__state))) {
                vlSelf->tb_spmv_axis__DOT__dut__DOT__out_q 
                    = vlSelf->tb_spmv_axis__DOT__dut__DOT__ymem
                    [vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx];
                __Vdly__tb_spmv_axis__DOT__dut__DOT__state = 4U;
            } else {
                __Vdlyvval__tb_spmv_axis__DOT__dut__DOT__ymem__v0 
                    = (vlSelf->tb_spmv_axis__DOT__dut__DOT__y_q 
                       + VL_MULS_III(32, VL_EXTENDS_II(32,16, (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__a_q)), 
                                     VL_EXTENDS_II(32,16, (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__x_q))));
                __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__ymem__v0 = 1U;
                __Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__ymem__v0 
                    = vlSelf->tb_spmv_axis__DOT__dut__DOT__row_q;
                __Vdly__tb_spmv_axis__DOT__dut__DOT__state = 0U;
            }
        } else if ((1U & (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__state))) {
            __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__ymem__v1 = 1U;
            __Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__ymem__v1 
                = vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx;
            if ((3U == (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx))) {
                __Vdly__tb_spmv_axis__DOT__dut__DOT__row_idx = 0U;
                __Vdly__tb_spmv_axis__DOT__dut__DOT__state = 0U;
            } else {
                __Vdly__tb_spmv_axis__DOT__dut__DOT__row_idx 
                    = (3U & ((IData)(1U) + (IData)(vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx)));
            }
        } else if (((IData)(vlSelf->tb_spmv_axis__DOT__s_valid) 
                    & (IData)(vlSelf->tb_spmv_axis__DOT__s_ready))) {
            if ((1U & (IData)((vlSelf->tb_spmv_axis__DOT__s_data 
                               >> 0x3fU)))) {
                if ((1U & (IData)((vlSelf->tb_spmv_axis__DOT__s_data 
                                   >> 0x3eU)))) {
                    if (VL_UNLIKELY((1U & (~ (IData)(vlSelf->tb_spmv_axis__DOT__s_last))))) {
                        VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:142: Assertion failed in %Ntb_spmv_axis.dut: DRAIN_Y must be final input command\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name());
                        VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/week9_spmv_axis.sv", 142, "");
                    }
                    __Vdly__tb_spmv_axis__DOT__dut__DOT__row_idx = 0U;
                    __Vdly__tb_spmv_axis__DOT__dut__DOT__state = 3U;
                } else {
                    if (VL_UNLIKELY(vlSelf->tb_spmv_axis__DOT__s_last)) {
                        VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:131: Assertion failed in %Ntb_spmv_axis.dut: CLEAR_Y cannot terminate command stream\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name());
                        VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/week9_spmv_axis.sv", 131, "");
                    }
                    __Vdly__tb_spmv_axis__DOT__dut__DOT__row_idx = 0U;
                    __Vdly__tb_spmv_axis__DOT__nmac = 0U;
                    __Vdly__tb_spmv_axis__DOT__nload = 0U;
                    __Vdly__tb_spmv_axis__DOT__dut__DOT__state = 1U;
                }
            } else if ((1U & (IData)((vlSelf->tb_spmv_axis__DOT__s_data 
                                      >> 0x3eU)))) {
                if (VL_UNLIKELY(((VL_LTES_III(32, 4U, 
                                              (0x7fffU 
                                               & (IData)(
                                                         (vlSelf->tb_spmv_axis__DOT__s_data 
                                                          >> 0x2fU)))) 
                                  | VL_LTES_III(32, 8U, 
                                                (0x7ffU 
                                                 & (IData)(
                                                           (vlSelf->tb_spmv_axis__DOT__s_data 
                                                            >> 0x24U))))) 
                                 | ((0xffffU & (IData)(
                                                       (vlSelf->tb_spmv_axis__DOT__s_data 
                                                        >> 0x10U))) 
                                    != (0xffffU & (- (IData)(
                                                             (1U 
                                                              & (IData)(
                                                                        (vlSelf->tb_spmv_axis__DOT__s_data 
                                                                         >> 0xfU)))))))))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:118: Assertion failed in %Ntb_spmv_axis.dut: MAC index/width violation\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name());
                    VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/week9_spmv_axis.sv", 118, "");
                }
                __Vdly__tb_spmv_axis__DOT__nmac = ((IData)(1U) 
                                                   + vlSelf->tb_spmv_axis__DOT__nmac);
                vlSelf->tb_spmv_axis__DOT__dut__DOT__row_q 
                    = (3U & (IData)((vlSelf->tb_spmv_axis__DOT__s_data 
                                     >> 0x2fU)));
                vlSelf->tb_spmv_axis__DOT__dut__DOT__a_q 
                    = (0xffffU & (IData)(vlSelf->tb_spmv_axis__DOT__s_data));
                vlSelf->tb_spmv_axis__DOT__dut__DOT__x_q 
                    = vlSelf->tb_spmv_axis__DOT__dut__DOT__xmem
                    [(7U & (IData)((vlSelf->tb_spmv_axis__DOT__s_data 
                                    >> 0x24U)))];
                vlSelf->tb_spmv_axis__DOT__dut__DOT__y_q 
                    = vlSelf->tb_spmv_axis__DOT__dut__DOT__ymem
                    [(3U & (IData)((vlSelf->tb_spmv_axis__DOT__s_data 
                                    >> 0x2fU)))];
                __Vdly__tb_spmv_axis__DOT__dut__DOT__state = 2U;
            } else {
                if (VL_UNLIKELY((VL_LTES_III(32, 8U, 
                                             (0x7ffU 
                                              & (IData)(
                                                        (vlSelf->tb_spmv_axis__DOT__s_data 
                                                         >> 0x24U)))) 
                                 | ((0xffffU & (IData)(
                                                       (vlSelf->tb_spmv_axis__DOT__s_data 
                                                        >> 0x10U))) 
                                    != (0xffffU & (- (IData)(
                                                             (1U 
                                                              & (IData)(
                                                                        (vlSelf->tb_spmv_axis__DOT__s_data 
                                                                         >> 0xfU)))))))))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: week9_spmv_axis.sv:106: Assertion failed in %Ntb_spmv_axis.dut: LOAD_X index/width violation\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name());
                    VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w9/results/tiny/sources/week9_spmv_axis.sv", 106, "");
                }
                __Vdly__tb_spmv_axis__DOT__nload = 
                    ((IData)(1U) + vlSelf->tb_spmv_axis__DOT__nload);
                __Vdlyvval__tb_spmv_axis__DOT__dut__DOT__xmem__v0 
                    = (0xffffU & (IData)(vlSelf->tb_spmv_axis__DOT__s_data));
                __Vdlyvset__tb_spmv_axis__DOT__dut__DOT__xmem__v0 = 1U;
                __Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__xmem__v0 
                    = (7U & (IData)((vlSelf->tb_spmv_axis__DOT__s_data 
                                     >> 0x24U)));
            }
        }
    } else {
        __Vdly__tb_spmv_axis__DOT__dut__DOT__row_idx = 0U;
        vlSelf->tb_spmv_axis__DOT__cycles = 0U;
        __Vdly__tb_spmv_axis__DOT__dut__DOT__state = 0U;
        vlSelf->tb_spmv_axis__DOT__dut__DOT__row_q = 0U;
        vlSelf->tb_spmv_axis__DOT__dut__DOT__a_q = 0U;
        vlSelf->tb_spmv_axis__DOT__dut__DOT__x_q = 0U;
        vlSelf->tb_spmv_axis__DOT__dut__DOT__y_q = 0U;
        vlSelf->tb_spmv_axis__DOT__dut__DOT__out_q = 0U;
        __Vdly__tb_spmv_axis__DOT__nmac = 0U;
        __Vdly__tb_spmv_axis__DOT__nload = 0U;
    }
    vlSelf->tb_spmv_axis__DOT__dut__DOT__row_idx = __Vdly__tb_spmv_axis__DOT__dut__DOT__row_idx;
    vlSelf->tb_spmv_axis__DOT__nmac = __Vdly__tb_spmv_axis__DOT__nmac;
    vlSelf->tb_spmv_axis__DOT__nload = __Vdly__tb_spmv_axis__DOT__nload;
    if (__Vdlyvset__tb_spmv_axis__DOT__dut__DOT__xmem__v0) {
        vlSelf->tb_spmv_axis__DOT__dut__DOT__xmem[__Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__xmem__v0] 
            = __Vdlyvval__tb_spmv_axis__DOT__dut__DOT__xmem__v0;
    }
    if (__Vdlyvset__tb_spmv_axis__DOT__dut__DOT__ymem__v0) {
        vlSelf->tb_spmv_axis__DOT__dut__DOT__ymem[__Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__ymem__v0] 
            = __Vdlyvval__tb_spmv_axis__DOT__dut__DOT__ymem__v0;
    }
    if (__Vdlyvset__tb_spmv_axis__DOT__dut__DOT__ymem__v1) {
        vlSelf->tb_spmv_axis__DOT__dut__DOT__ymem[__Vdlyvdim0__tb_spmv_axis__DOT__dut__DOT__ymem__v1] = 0U;
    }
    vlSelf->tb_spmv_axis__DOT__dut__DOT__state = __Vdly__tb_spmv_axis__DOT__dut__DOT__state;
}
