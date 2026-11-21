// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_scheduler.h for the primary calling header

#include "Vtb_scheduler__pch.h"
#include "Vtb_scheduler__Syms.h"
#include "Vtb_scheduler___024root.h"

VL_INLINE_OPT VlCoroutine Vtb_scheduler___024root___eval_initial__TOP__Vtiming__0(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_initial__TOP__Vtiming__0\n"); );
    // Init
    IData/*31:0*/ tb_scheduler__DOT__trace_len;
    tb_scheduler__DOT__trace_len = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__0__case_id;
    __Vtask_tb_scheduler__DOT__run_case__0__case_id = 0;
    std::string __Vtask_tb_scheduler__DOT__run_case__0__test_name;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__0__ptr;
    __Vtask_tb_scheduler__DOT__run_case__0__ptr = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__0__cycles;
    __Vtask_tb_scheduler__DOT__run_case__0__cycles = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__0__expected_issued;
    __Vtask_tb_scheduler__DOT__run_case__0__expected_issued = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__0__expected_row_events;
    __Vtask_tb_scheduler__DOT__run_case__0__expected_row_events = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__0__expected_bank_events;
    __Vtask_tb_scheduler__DOT__run_case__0__expected_bank_events = 0;
    SData/*15:0*/ __Vtask_tb_scheduler__DOT__run_case__0__previous_cycle_issued;
    __Vtask_tb_scheduler__DOT__run_case__0__previous_cycle_issued = 0;
    SData/*15:0*/ __Vtask_tb_scheduler__DOT__run_case__0__new_reservations;
    __Vtask_tb_scheduler__DOT__run_case__0__new_reservations = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__0__expect0;
    __Vtask_tb_scheduler__DOT__run_case__0__expect0 = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__0__expect1;
    __Vtask_tb_scheduler__DOT__run_case__0__expect1 = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__0__row_event;
    __Vtask_tb_scheduler__DOT__run_case__0__row_event = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__0__bank_event;
    __Vtask_tb_scheduler__DOT__run_case__0__bank_event = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__0__gap;
    __Vtask_tb_scheduler__DOT__run_case__0__gap = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__0__expected_pop;
    __Vtask_tb_scheduler__DOT__run_case__0__expected_pop = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__2__case_id;
    __Vtask_tb_scheduler__DOT__run_case__2__case_id = 0;
    std::string __Vtask_tb_scheduler__DOT__run_case__2__test_name;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__2__ptr;
    __Vtask_tb_scheduler__DOT__run_case__2__ptr = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__2__cycles;
    __Vtask_tb_scheduler__DOT__run_case__2__cycles = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__2__expected_issued;
    __Vtask_tb_scheduler__DOT__run_case__2__expected_issued = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__2__expected_row_events;
    __Vtask_tb_scheduler__DOT__run_case__2__expected_row_events = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__2__expected_bank_events;
    __Vtask_tb_scheduler__DOT__run_case__2__expected_bank_events = 0;
    SData/*15:0*/ __Vtask_tb_scheduler__DOT__run_case__2__previous_cycle_issued;
    __Vtask_tb_scheduler__DOT__run_case__2__previous_cycle_issued = 0;
    SData/*15:0*/ __Vtask_tb_scheduler__DOT__run_case__2__new_reservations;
    __Vtask_tb_scheduler__DOT__run_case__2__new_reservations = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__2__expect0;
    __Vtask_tb_scheduler__DOT__run_case__2__expect0 = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__2__expect1;
    __Vtask_tb_scheduler__DOT__run_case__2__expect1 = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__2__row_event;
    __Vtask_tb_scheduler__DOT__run_case__2__row_event = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__2__bank_event;
    __Vtask_tb_scheduler__DOT__run_case__2__bank_event = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__2__gap;
    __Vtask_tb_scheduler__DOT__run_case__2__gap = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__2__expected_pop;
    __Vtask_tb_scheduler__DOT__run_case__2__expected_pop = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__load_trace__3__case_id;
    __Vtask_tb_scheduler__DOT__load_trace__3__case_id = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__4__case_id;
    __Vtask_tb_scheduler__DOT__run_case__4__case_id = 0;
    std::string __Vtask_tb_scheduler__DOT__run_case__4__test_name;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__4__ptr;
    __Vtask_tb_scheduler__DOT__run_case__4__ptr = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__4__cycles;
    __Vtask_tb_scheduler__DOT__run_case__4__cycles = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__4__expected_issued;
    __Vtask_tb_scheduler__DOT__run_case__4__expected_issued = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__4__expected_row_events;
    __Vtask_tb_scheduler__DOT__run_case__4__expected_row_events = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__4__expected_bank_events;
    __Vtask_tb_scheduler__DOT__run_case__4__expected_bank_events = 0;
    SData/*15:0*/ __Vtask_tb_scheduler__DOT__run_case__4__previous_cycle_issued;
    __Vtask_tb_scheduler__DOT__run_case__4__previous_cycle_issued = 0;
    SData/*15:0*/ __Vtask_tb_scheduler__DOT__run_case__4__new_reservations;
    __Vtask_tb_scheduler__DOT__run_case__4__new_reservations = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__4__expect0;
    __Vtask_tb_scheduler__DOT__run_case__4__expect0 = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__4__expect1;
    __Vtask_tb_scheduler__DOT__run_case__4__expect1 = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__4__row_event;
    __Vtask_tb_scheduler__DOT__run_case__4__row_event = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__4__bank_event;
    __Vtask_tb_scheduler__DOT__run_case__4__bank_event = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__4__gap;
    __Vtask_tb_scheduler__DOT__run_case__4__gap = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__4__expected_pop;
    __Vtask_tb_scheduler__DOT__run_case__4__expected_pop = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__load_trace__5__case_id;
    __Vtask_tb_scheduler__DOT__load_trace__5__case_id = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__6__case_id;
    __Vtask_tb_scheduler__DOT__run_case__6__case_id = 0;
    std::string __Vtask_tb_scheduler__DOT__run_case__6__test_name;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__6__ptr;
    __Vtask_tb_scheduler__DOT__run_case__6__ptr = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__6__cycles;
    __Vtask_tb_scheduler__DOT__run_case__6__cycles = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__6__expected_issued;
    __Vtask_tb_scheduler__DOT__run_case__6__expected_issued = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__6__expected_row_events;
    __Vtask_tb_scheduler__DOT__run_case__6__expected_row_events = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__6__expected_bank_events;
    __Vtask_tb_scheduler__DOT__run_case__6__expected_bank_events = 0;
    SData/*15:0*/ __Vtask_tb_scheduler__DOT__run_case__6__previous_cycle_issued;
    __Vtask_tb_scheduler__DOT__run_case__6__previous_cycle_issued = 0;
    SData/*15:0*/ __Vtask_tb_scheduler__DOT__run_case__6__new_reservations;
    __Vtask_tb_scheduler__DOT__run_case__6__new_reservations = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__6__expect0;
    __Vtask_tb_scheduler__DOT__run_case__6__expect0 = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__6__expect1;
    __Vtask_tb_scheduler__DOT__run_case__6__expect1 = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__6__row_event;
    __Vtask_tb_scheduler__DOT__run_case__6__row_event = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__6__bank_event;
    __Vtask_tb_scheduler__DOT__run_case__6__bank_event = 0;
    CData/*0:0*/ __Vtask_tb_scheduler__DOT__run_case__6__gap;
    __Vtask_tb_scheduler__DOT__run_case__6__gap = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__run_case__6__expected_pop;
    __Vtask_tb_scheduler__DOT__run_case__6__expected_pop = 0;
    IData/*31:0*/ __Vtask_tb_scheduler__DOT__load_trace__7__case_id;
    __Vtask_tb_scheduler__DOT__load_trace__7__case_id = 0;
    // Body
    __Vtask_tb_scheduler__DOT__run_case__0__test_name = 
        std::string{"slide8_combined"};
    __Vtask_tb_scheduler__DOT__run_case__0__case_id = 1U;
    tb_scheduler__DOT__trace_len = 8U;
    vlSelf->tb_scheduler__DOT__trace_mem[0U] = 0U;
    vlSelf->tb_scheduler__DOT__trace_mem[1U] = 1U;
    vlSelf->tb_scheduler__DOT__trace_mem[2U] = 0U;
    vlSelf->tb_scheduler__DOT__trace_mem[3U] = 2U;
    vlSelf->tb_scheduler__DOT__trace_mem[4U] = 3U;
    vlSelf->tb_scheduler__DOT__trace_mem[5U] = 3U;
    vlSelf->tb_scheduler__DOT__trace_mem[6U] = 4U;
    vlSelf->tb_scheduler__DOT__trace_mem[7U] = 5U;
    vlSelf->tb_scheduler__DOT__rst = 1U;
    vlSelf->tb_scheduler__DOT__head_valid = 0U;
    vlSelf->tb_scheduler__DOT__head_row0 = 0U;
    vlSelf->tb_scheduler__DOT__head_row1 = 0U;
    co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       77);
    co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       77);
    co_await vlSelf->__VtrigSched_hc9429d78__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       78);
    vlSelf->tb_scheduler__DOT__rst = 0U;
    __Vtask_tb_scheduler__DOT__run_case__0__ptr = 0U;
    __Vtask_tb_scheduler__DOT__run_case__0__cycles = 0U;
    __Vtask_tb_scheduler__DOT__run_case__0__expected_issued = 0U;
    __Vtask_tb_scheduler__DOT__run_case__0__expected_row_events = 0U;
    __Vtask_tb_scheduler__DOT__run_case__0__expected_bank_events = 0U;
    __Vtask_tb_scheduler__DOT__run_case__0__previous_cycle_issued = 0U;
    while (VL_LTS_III(32, __Vtask_tb_scheduler__DOT__run_case__0__ptr, tb_scheduler__DOT__trace_len)) {
        if (VL_UNLIKELY(VL_LTS_III(32, 0x32U, __Vtask_tb_scheduler__DOT__run_case__0__cycles))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:89: Assertion failed in %Ntb_scheduler.run_case: %@: timeout / no forward progress\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__0__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 89, "");
        }
        co_await vlSelf->__VtrigSched_hc9429d78__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(negedge tb_scheduler.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                           90);
        __Vtask_tb_scheduler__DOT__run_case__0__gap 
            = ((4U == __Vtask_tb_scheduler__DOT__run_case__0__case_id) 
               & ((2U == __Vtask_tb_scheduler__DOT__run_case__0__cycles) 
                  | (5U == __Vtask_tb_scheduler__DOT__run_case__0__cycles)));
        vlSelf->tb_scheduler__DOT__head_valid = 0U;
        vlSelf->tb_scheduler__DOT__head_row0 = 0U;
        vlSelf->tb_scheduler__DOT__head_row1 = 0U;
        if (((~ (IData)(__Vtask_tb_scheduler__DOT__run_case__0__gap)) 
             & VL_LTS_III(32, __Vtask_tb_scheduler__DOT__run_case__0__ptr, tb_scheduler__DOT__trace_len))) {
            vlSelf->tb_scheduler__DOT__head_valid = 
                (1U | (IData)(vlSelf->tb_scheduler__DOT__head_valid));
            vlSelf->tb_scheduler__DOT__head_row0 = 
                vlSelf->tb_scheduler__DOT__trace_mem
                [(0x3fU & __Vtask_tb_scheduler__DOT__run_case__0__ptr)];
            if (VL_LTS_III(32, ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__0__ptr), tb_scheduler__DOT__trace_len)) {
                vlSelf->tb_scheduler__DOT__head_valid 
                    = (2U | (IData)(vlSelf->tb_scheduler__DOT__head_valid));
                vlSelf->tb_scheduler__DOT__head_row1 
                    = vlSelf->tb_scheduler__DOT__trace_mem
                    [(0x3fU & ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__0__ptr))];
            }
        }
        co_await vlSelf->__VdlySched.delay(0x3e8ULL, 
                                           nullptr, 
                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                           106);
        __Vtask_tb_scheduler__DOT__run_case__0__expect0 = 0U;
        __Vtask_tb_scheduler__DOT__run_case__0__expect1 = 0U;
        __Vtask_tb_scheduler__DOT__run_case__0__row_event = 0U;
        __Vtask_tb_scheduler__DOT__run_case__0__bank_event = 0U;
        if ((1U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
            if ((1U & ((IData)(__Vtask_tb_scheduler__DOT__run_case__0__previous_cycle_issued) 
                       >> (IData)(vlSelf->tb_scheduler__DOT__head_row0)))) {
                __Vtask_tb_scheduler__DOT__run_case__0__row_event = 1U;
            } else {
                __Vtask_tb_scheduler__DOT__run_case__0__expect0 = 1U;
                if ((2U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
                    if ((1U & (((IData)(__Vtask_tb_scheduler__DOT__run_case__0__previous_cycle_issued) 
                                >> (IData)(vlSelf->tb_scheduler__DOT__head_row1)) 
                               | ((IData)(vlSelf->tb_scheduler__DOT__head_row0) 
                                  == (IData)(vlSelf->tb_scheduler__DOT__head_row1))))) {
                        __Vtask_tb_scheduler__DOT__run_case__0__row_event = 1U;
                    } else if (((1U & (IData)(vlSelf->tb_scheduler__DOT__head_row0)) 
                                == (1U & (IData)(vlSelf->tb_scheduler__DOT__head_row1)))) {
                        __Vtask_tb_scheduler__DOT__run_case__0__bank_event = 1U;
                    } else {
                        __Vtask_tb_scheduler__DOT__run_case__0__expect1 = 1U;
                    }
                }
            }
        }
        __Vtask_tb_scheduler__DOT__run_case__0__expected_pop 
            = (((IData)(__Vtask_tb_scheduler__DOT__run_case__0__expect0)
                 ? 1U : 0U) + ((IData)(__Vtask_tb_scheduler__DOT__run_case__0__expect1)
                                ? 1U : 0U));
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__issue_valid) 
                         != (((IData)(__Vtask_tb_scheduler__DOT__run_case__0__expect1) 
                              << 1U) | (IData)(__Vtask_tb_scheduler__DOT__run_case__0__expect0))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:132: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: issue_valid=%b expected=%b\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__0__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__0__cycles,
                         2,(IData)(vlSelf->tb_scheduler__DOT__issue_valid),
                         2,(((IData)(__Vtask_tb_scheduler__DOT__run_case__0__expect1) 
                             << 1U) | (IData)(__Vtask_tb_scheduler__DOT__run_case__0__expect0)));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 132, "");
        }
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__pop_count) 
                         != __Vtask_tb_scheduler__DOT__run_case__0__expected_pop))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:134: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: pop=%0# expected=%0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__0__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__0__cycles,
                         2,(IData)(vlSelf->tb_scheduler__DOT__pop_count),
                         32,__Vtask_tb_scheduler__DOT__run_case__0__expected_pop);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 134, "");
        }
        if (VL_UNLIKELY(((IData)(__Vtask_tb_scheduler__DOT__run_case__0__expect0) 
                         & ((IData)(vlSelf->tb_scheduler__DOT__issue_row0) 
                            != (IData)(vlSelf->tb_scheduler__DOT__head_row0))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:136: Assertion failed in %Ntb_scheduler.run_case: %@: lane0 row mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__0__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 136, "");
        }
        if (VL_UNLIKELY(((IData)(__Vtask_tb_scheduler__DOT__run_case__0__expect1) 
                         & ((IData)(vlSelf->tb_scheduler__DOT__issue_row1) 
                            != (IData)(vlSelf->tb_scheduler__DOT__head_row1))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:138: Assertion failed in %Ntb_scheduler.run_case: %@: lane1 row mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__0__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 138, "");
        }
        __Vtask_tb_scheduler__DOT__run_case__0__new_reservations = 0U;
        if (__Vtask_tb_scheduler__DOT__run_case__0__expect0) {
            __Vtask_tb_scheduler__DOT__run_case__0__new_reservations 
                = ((IData)(__Vtask_tb_scheduler__DOT__run_case__0__new_reservations) 
                   | (0xffffU & ((IData)(1U) << (IData)(vlSelf->tb_scheduler__DOT__head_row0))));
        }
        if (__Vtask_tb_scheduler__DOT__run_case__0__expect1) {
            __Vtask_tb_scheduler__DOT__run_case__0__new_reservations 
                = ((IData)(__Vtask_tb_scheduler__DOT__run_case__0__new_reservations) 
                   | (0xffffU & ((IData)(1U) << (IData)(vlSelf->tb_scheduler__DOT__head_row1))));
        }
        __Vtask_tb_scheduler__DOT__run_case__0__expected_issued 
            = (__Vtask_tb_scheduler__DOT__run_case__0__expected_issued 
               + __Vtask_tb_scheduler__DOT__run_case__0__expected_pop);
        if (__Vtask_tb_scheduler__DOT__run_case__0__row_event) {
            __Vtask_tb_scheduler__DOT__run_case__0__expected_row_events 
                = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__0__expected_row_events);
        }
        if (__Vtask_tb_scheduler__DOT__run_case__0__bank_event) {
            __Vtask_tb_scheduler__DOT__run_case__0__expected_bank_events 
                = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__0__expected_bank_events);
        }
        co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_scheduler.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                           148);
        co_await vlSelf->__VdlySched.delay(0x3e8ULL, 
                                           nullptr, 
                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                           149);
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__busy_rows) 
                         != (IData)(__Vtask_tb_scheduler__DOT__run_case__0__new_reservations)))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:151: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: busy=%x expected=%x\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__0__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__0__cycles,
                         16,(IData)(vlSelf->tb_scheduler__DOT__busy_rows),
                         16,__Vtask_tb_scheduler__DOT__run_case__0__new_reservations);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 151, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__issued_total 
                         != __Vtask_tb_scheduler__DOT__run_case__0__expected_issued))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:153: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: issued counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__0__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__0__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 153, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__row_hazard_cycles 
                         != __Vtask_tb_scheduler__DOT__run_case__0__expected_row_events))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:155: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: row counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__0__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__0__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 155, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__bank_conflict_cycles 
                         != __Vtask_tb_scheduler__DOT__run_case__0__expected_bank_events))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:157: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: bank counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__0__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__0__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 157, "");
        }
        __Vtask_tb_scheduler__DOT__run_case__0__previous_cycle_issued 
            = __Vtask_tb_scheduler__DOT__run_case__0__new_reservations;
        __Vtask_tb_scheduler__DOT__run_case__0__ptr 
            = (__Vtask_tb_scheduler__DOT__run_case__0__ptr 
               + __Vtask_tb_scheduler__DOT__run_case__0__expected_pop);
        __Vtask_tb_scheduler__DOT__run_case__0__cycles 
            = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__0__cycles);
    }
    vlSelf->tb_scheduler__DOT__head_valid = 0U;
    VL_WRITEF_NX("PASS %-26@ cycles=%0d MACs=%0d row_stall=%0d bank_conflict=%0d\n",0,
                 -1,&(__Vtask_tb_scheduler__DOT__run_case__0__test_name),
                 32,__Vtask_tb_scheduler__DOT__run_case__0__cycles,
                 32,__Vtask_tb_scheduler__DOT__run_case__0__expected_issued,
                 32,__Vtask_tb_scheduler__DOT__run_case__0__expected_row_events,
                 32,__Vtask_tb_scheduler__DOT__run_case__0__expected_bank_events);
    __Vtask_tb_scheduler__DOT__run_case__2__test_name = 
        std::string{"same_bank_rows"};
    __Vtask_tb_scheduler__DOT__run_case__2__case_id = 2U;
    __Vtask_tb_scheduler__DOT__load_trace__3__case_id 
        = __Vtask_tb_scheduler__DOT__run_case__2__case_id;
    tb_scheduler__DOT__trace_len = 0U;
    if ((1U == __Vtask_tb_scheduler__DOT__load_trace__3__case_id)) {
        tb_scheduler__DOT__trace_len = 8U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 1U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 2U;
        vlSelf->tb_scheduler__DOT__trace_mem[4U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[5U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[6U] = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[7U] = 5U;
    } else if ((2U == __Vtask_tb_scheduler__DOT__load_trace__3__case_id)) {
        tb_scheduler__DOT__trace_len = 6U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 2U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 6U;
        vlSelf->tb_scheduler__DOT__trace_mem[4U] = 8U;
        vlSelf->tb_scheduler__DOT__trace_mem[5U] = 0xaU;
    } else if ((3U == __Vtask_tb_scheduler__DOT__load_trace__3__case_id)) {
        tb_scheduler__DOT__trace_len = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 3U;
    } else if (VL_LIKELY((4U == __Vtask_tb_scheduler__DOT__load_trace__3__case_id))) {
        tb_scheduler__DOT__trace_len = 8U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 1U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 2U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[4U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[5U] = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[6U] = 5U;
        vlSelf->tb_scheduler__DOT__trace_mem[7U] = 6U;
    } else {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:52: Assertion failed in %Ntb_scheduler.load_trace: Unknown case %0d\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_scheduler__DOT__load_trace__3__case_id);
        VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 52, "");
    }
    vlSelf->tb_scheduler__DOT__rst = 1U;
    vlSelf->tb_scheduler__DOT__head_valid = 0U;
    vlSelf->tb_scheduler__DOT__head_row0 = 0U;
    vlSelf->tb_scheduler__DOT__head_row1 = 0U;
    co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       77);
    co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       77);
    co_await vlSelf->__VtrigSched_hc9429d78__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       78);
    vlSelf->tb_scheduler__DOT__rst = 0U;
    __Vtask_tb_scheduler__DOT__run_case__2__ptr = 0U;
    __Vtask_tb_scheduler__DOT__run_case__2__cycles = 0U;
    __Vtask_tb_scheduler__DOT__run_case__2__expected_issued = 0U;
    __Vtask_tb_scheduler__DOT__run_case__2__expected_row_events = 0U;
    __Vtask_tb_scheduler__DOT__run_case__2__expected_bank_events = 0U;
    __Vtask_tb_scheduler__DOT__run_case__2__previous_cycle_issued = 0U;
    while (VL_LTS_III(32, __Vtask_tb_scheduler__DOT__run_case__2__ptr, tb_scheduler__DOT__trace_len)) {
        if (VL_UNLIKELY(VL_LTS_III(32, 0x32U, __Vtask_tb_scheduler__DOT__run_case__2__cycles))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:89: Assertion failed in %Ntb_scheduler.run_case: %@: timeout / no forward progress\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__2__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 89, "");
        }
        co_await vlSelf->__VtrigSched_hc9429d78__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(negedge tb_scheduler.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                           90);
        __Vtask_tb_scheduler__DOT__run_case__2__gap 
            = ((4U == __Vtask_tb_scheduler__DOT__run_case__2__case_id) 
               & ((2U == __Vtask_tb_scheduler__DOT__run_case__2__cycles) 
                  | (5U == __Vtask_tb_scheduler__DOT__run_case__2__cycles)));
        vlSelf->tb_scheduler__DOT__head_valid = 0U;
        vlSelf->tb_scheduler__DOT__head_row0 = 0U;
        vlSelf->tb_scheduler__DOT__head_row1 = 0U;
        if (((~ (IData)(__Vtask_tb_scheduler__DOT__run_case__2__gap)) 
             & VL_LTS_III(32, __Vtask_tb_scheduler__DOT__run_case__2__ptr, tb_scheduler__DOT__trace_len))) {
            vlSelf->tb_scheduler__DOT__head_valid = 
                (1U | (IData)(vlSelf->tb_scheduler__DOT__head_valid));
            vlSelf->tb_scheduler__DOT__head_row0 = 
                vlSelf->tb_scheduler__DOT__trace_mem
                [(0x3fU & __Vtask_tb_scheduler__DOT__run_case__2__ptr)];
            if (VL_LTS_III(32, ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__2__ptr), tb_scheduler__DOT__trace_len)) {
                vlSelf->tb_scheduler__DOT__head_valid 
                    = (2U | (IData)(vlSelf->tb_scheduler__DOT__head_valid));
                vlSelf->tb_scheduler__DOT__head_row1 
                    = vlSelf->tb_scheduler__DOT__trace_mem
                    [(0x3fU & ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__2__ptr))];
            }
        }
        co_await vlSelf->__VdlySched.delay(0x3e8ULL, 
                                           nullptr, 
                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                           106);
        __Vtask_tb_scheduler__DOT__run_case__2__expect0 = 0U;
        __Vtask_tb_scheduler__DOT__run_case__2__expect1 = 0U;
        __Vtask_tb_scheduler__DOT__run_case__2__row_event = 0U;
        __Vtask_tb_scheduler__DOT__run_case__2__bank_event = 0U;
        if ((1U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
            if ((1U & ((IData)(__Vtask_tb_scheduler__DOT__run_case__2__previous_cycle_issued) 
                       >> (IData)(vlSelf->tb_scheduler__DOT__head_row0)))) {
                __Vtask_tb_scheduler__DOT__run_case__2__row_event = 1U;
            } else {
                __Vtask_tb_scheduler__DOT__run_case__2__expect0 = 1U;
                if ((2U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
                    if ((1U & (((IData)(__Vtask_tb_scheduler__DOT__run_case__2__previous_cycle_issued) 
                                >> (IData)(vlSelf->tb_scheduler__DOT__head_row1)) 
                               | ((IData)(vlSelf->tb_scheduler__DOT__head_row0) 
                                  == (IData)(vlSelf->tb_scheduler__DOT__head_row1))))) {
                        __Vtask_tb_scheduler__DOT__run_case__2__row_event = 1U;
                    } else if (((1U & (IData)(vlSelf->tb_scheduler__DOT__head_row0)) 
                                == (1U & (IData)(vlSelf->tb_scheduler__DOT__head_row1)))) {
                        __Vtask_tb_scheduler__DOT__run_case__2__bank_event = 1U;
                    } else {
                        __Vtask_tb_scheduler__DOT__run_case__2__expect1 = 1U;
                    }
                }
            }
        }
        __Vtask_tb_scheduler__DOT__run_case__2__expected_pop 
            = (((IData)(__Vtask_tb_scheduler__DOT__run_case__2__expect0)
                 ? 1U : 0U) + ((IData)(__Vtask_tb_scheduler__DOT__run_case__2__expect1)
                                ? 1U : 0U));
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__issue_valid) 
                         != (((IData)(__Vtask_tb_scheduler__DOT__run_case__2__expect1) 
                              << 1U) | (IData)(__Vtask_tb_scheduler__DOT__run_case__2__expect0))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:132: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: issue_valid=%b expected=%b\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__2__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__2__cycles,
                         2,(IData)(vlSelf->tb_scheduler__DOT__issue_valid),
                         2,(((IData)(__Vtask_tb_scheduler__DOT__run_case__2__expect1) 
                             << 1U) | (IData)(__Vtask_tb_scheduler__DOT__run_case__2__expect0)));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 132, "");
        }
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__pop_count) 
                         != __Vtask_tb_scheduler__DOT__run_case__2__expected_pop))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:134: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: pop=%0# expected=%0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__2__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__2__cycles,
                         2,(IData)(vlSelf->tb_scheduler__DOT__pop_count),
                         32,__Vtask_tb_scheduler__DOT__run_case__2__expected_pop);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 134, "");
        }
        if (VL_UNLIKELY(((IData)(__Vtask_tb_scheduler__DOT__run_case__2__expect0) 
                         & ((IData)(vlSelf->tb_scheduler__DOT__issue_row0) 
                            != (IData)(vlSelf->tb_scheduler__DOT__head_row0))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:136: Assertion failed in %Ntb_scheduler.run_case: %@: lane0 row mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__2__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 136, "");
        }
        if (VL_UNLIKELY(((IData)(__Vtask_tb_scheduler__DOT__run_case__2__expect1) 
                         & ((IData)(vlSelf->tb_scheduler__DOT__issue_row1) 
                            != (IData)(vlSelf->tb_scheduler__DOT__head_row1))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:138: Assertion failed in %Ntb_scheduler.run_case: %@: lane1 row mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__2__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 138, "");
        }
        __Vtask_tb_scheduler__DOT__run_case__2__new_reservations = 0U;
        if (__Vtask_tb_scheduler__DOT__run_case__2__expect0) {
            __Vtask_tb_scheduler__DOT__run_case__2__new_reservations 
                = ((IData)(__Vtask_tb_scheduler__DOT__run_case__2__new_reservations) 
                   | (0xffffU & ((IData)(1U) << (IData)(vlSelf->tb_scheduler__DOT__head_row0))));
        }
        if (__Vtask_tb_scheduler__DOT__run_case__2__expect1) {
            __Vtask_tb_scheduler__DOT__run_case__2__new_reservations 
                = ((IData)(__Vtask_tb_scheduler__DOT__run_case__2__new_reservations) 
                   | (0xffffU & ((IData)(1U) << (IData)(vlSelf->tb_scheduler__DOT__head_row1))));
        }
        __Vtask_tb_scheduler__DOT__run_case__2__expected_issued 
            = (__Vtask_tb_scheduler__DOT__run_case__2__expected_issued 
               + __Vtask_tb_scheduler__DOT__run_case__2__expected_pop);
        if (__Vtask_tb_scheduler__DOT__run_case__2__row_event) {
            __Vtask_tb_scheduler__DOT__run_case__2__expected_row_events 
                = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__2__expected_row_events);
        }
        if (__Vtask_tb_scheduler__DOT__run_case__2__bank_event) {
            __Vtask_tb_scheduler__DOT__run_case__2__expected_bank_events 
                = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__2__expected_bank_events);
        }
        co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_scheduler.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                           148);
        co_await vlSelf->__VdlySched.delay(0x3e8ULL, 
                                           nullptr, 
                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                           149);
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__busy_rows) 
                         != (IData)(__Vtask_tb_scheduler__DOT__run_case__2__new_reservations)))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:151: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: busy=%x expected=%x\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__2__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__2__cycles,
                         16,(IData)(vlSelf->tb_scheduler__DOT__busy_rows),
                         16,__Vtask_tb_scheduler__DOT__run_case__2__new_reservations);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 151, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__issued_total 
                         != __Vtask_tb_scheduler__DOT__run_case__2__expected_issued))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:153: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: issued counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__2__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__2__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 153, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__row_hazard_cycles 
                         != __Vtask_tb_scheduler__DOT__run_case__2__expected_row_events))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:155: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: row counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__2__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__2__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 155, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__bank_conflict_cycles 
                         != __Vtask_tb_scheduler__DOT__run_case__2__expected_bank_events))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:157: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: bank counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__2__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__2__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 157, "");
        }
        __Vtask_tb_scheduler__DOT__run_case__2__previous_cycle_issued 
            = __Vtask_tb_scheduler__DOT__run_case__2__new_reservations;
        __Vtask_tb_scheduler__DOT__run_case__2__ptr 
            = (__Vtask_tb_scheduler__DOT__run_case__2__ptr 
               + __Vtask_tb_scheduler__DOT__run_case__2__expected_pop);
        __Vtask_tb_scheduler__DOT__run_case__2__cycles 
            = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__2__cycles);
    }
    vlSelf->tb_scheduler__DOT__head_valid = 0U;
    VL_WRITEF_NX("PASS %-26@ cycles=%0d MACs=%0d row_stall=%0d bank_conflict=%0d\n",0,
                 -1,&(__Vtask_tb_scheduler__DOT__run_case__2__test_name),
                 32,__Vtask_tb_scheduler__DOT__run_case__2__cycles,
                 32,__Vtask_tb_scheduler__DOT__run_case__2__expected_issued,
                 32,__Vtask_tb_scheduler__DOT__run_case__2__expected_row_events,
                 32,__Vtask_tb_scheduler__DOT__run_case__2__expected_bank_events);
    __Vtask_tb_scheduler__DOT__run_case__4__test_name = 
        std::string{"repeated_row"};
    __Vtask_tb_scheduler__DOT__run_case__4__case_id = 3U;
    __Vtask_tb_scheduler__DOT__load_trace__5__case_id 
        = __Vtask_tb_scheduler__DOT__run_case__4__case_id;
    tb_scheduler__DOT__trace_len = 0U;
    if ((1U == __Vtask_tb_scheduler__DOT__load_trace__5__case_id)) {
        tb_scheduler__DOT__trace_len = 8U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 1U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 2U;
        vlSelf->tb_scheduler__DOT__trace_mem[4U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[5U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[6U] = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[7U] = 5U;
    } else if ((2U == __Vtask_tb_scheduler__DOT__load_trace__5__case_id)) {
        tb_scheduler__DOT__trace_len = 6U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 2U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 6U;
        vlSelf->tb_scheduler__DOT__trace_mem[4U] = 8U;
        vlSelf->tb_scheduler__DOT__trace_mem[5U] = 0xaU;
    } else if ((3U == __Vtask_tb_scheduler__DOT__load_trace__5__case_id)) {
        tb_scheduler__DOT__trace_len = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 3U;
    } else if (VL_LIKELY((4U == __Vtask_tb_scheduler__DOT__load_trace__5__case_id))) {
        tb_scheduler__DOT__trace_len = 8U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 1U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 2U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[4U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[5U] = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[6U] = 5U;
        vlSelf->tb_scheduler__DOT__trace_mem[7U] = 6U;
    } else {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:52: Assertion failed in %Ntb_scheduler.load_trace: Unknown case %0d\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_scheduler__DOT__load_trace__5__case_id);
        VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 52, "");
    }
    vlSelf->tb_scheduler__DOT__rst = 1U;
    vlSelf->tb_scheduler__DOT__head_valid = 0U;
    vlSelf->tb_scheduler__DOT__head_row0 = 0U;
    vlSelf->tb_scheduler__DOT__head_row1 = 0U;
    co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       77);
    co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       77);
    co_await vlSelf->__VtrigSched_hc9429d78__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       78);
    vlSelf->tb_scheduler__DOT__rst = 0U;
    __Vtask_tb_scheduler__DOT__run_case__4__ptr = 0U;
    __Vtask_tb_scheduler__DOT__run_case__4__cycles = 0U;
    __Vtask_tb_scheduler__DOT__run_case__4__expected_issued = 0U;
    __Vtask_tb_scheduler__DOT__run_case__4__expected_row_events = 0U;
    __Vtask_tb_scheduler__DOT__run_case__4__expected_bank_events = 0U;
    __Vtask_tb_scheduler__DOT__run_case__4__previous_cycle_issued = 0U;
    while (VL_LTS_III(32, __Vtask_tb_scheduler__DOT__run_case__4__ptr, tb_scheduler__DOT__trace_len)) {
        if (VL_UNLIKELY(VL_LTS_III(32, 0x32U, __Vtask_tb_scheduler__DOT__run_case__4__cycles))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:89: Assertion failed in %Ntb_scheduler.run_case: %@: timeout / no forward progress\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__4__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 89, "");
        }
        co_await vlSelf->__VtrigSched_hc9429d78__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(negedge tb_scheduler.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                           90);
        __Vtask_tb_scheduler__DOT__run_case__4__gap 
            = ((4U == __Vtask_tb_scheduler__DOT__run_case__4__case_id) 
               & ((2U == __Vtask_tb_scheduler__DOT__run_case__4__cycles) 
                  | (5U == __Vtask_tb_scheduler__DOT__run_case__4__cycles)));
        vlSelf->tb_scheduler__DOT__head_valid = 0U;
        vlSelf->tb_scheduler__DOT__head_row0 = 0U;
        vlSelf->tb_scheduler__DOT__head_row1 = 0U;
        if (((~ (IData)(__Vtask_tb_scheduler__DOT__run_case__4__gap)) 
             & VL_LTS_III(32, __Vtask_tb_scheduler__DOT__run_case__4__ptr, tb_scheduler__DOT__trace_len))) {
            vlSelf->tb_scheduler__DOT__head_valid = 
                (1U | (IData)(vlSelf->tb_scheduler__DOT__head_valid));
            vlSelf->tb_scheduler__DOT__head_row0 = 
                vlSelf->tb_scheduler__DOT__trace_mem
                [(0x3fU & __Vtask_tb_scheduler__DOT__run_case__4__ptr)];
            if (VL_LTS_III(32, ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__4__ptr), tb_scheduler__DOT__trace_len)) {
                vlSelf->tb_scheduler__DOT__head_valid 
                    = (2U | (IData)(vlSelf->tb_scheduler__DOT__head_valid));
                vlSelf->tb_scheduler__DOT__head_row1 
                    = vlSelf->tb_scheduler__DOT__trace_mem
                    [(0x3fU & ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__4__ptr))];
            }
        }
        co_await vlSelf->__VdlySched.delay(0x3e8ULL, 
                                           nullptr, 
                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                           106);
        __Vtask_tb_scheduler__DOT__run_case__4__expect0 = 0U;
        __Vtask_tb_scheduler__DOT__run_case__4__expect1 = 0U;
        __Vtask_tb_scheduler__DOT__run_case__4__row_event = 0U;
        __Vtask_tb_scheduler__DOT__run_case__4__bank_event = 0U;
        if ((1U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
            if ((1U & ((IData)(__Vtask_tb_scheduler__DOT__run_case__4__previous_cycle_issued) 
                       >> (IData)(vlSelf->tb_scheduler__DOT__head_row0)))) {
                __Vtask_tb_scheduler__DOT__run_case__4__row_event = 1U;
            } else {
                __Vtask_tb_scheduler__DOT__run_case__4__expect0 = 1U;
                if ((2U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
                    if ((1U & (((IData)(__Vtask_tb_scheduler__DOT__run_case__4__previous_cycle_issued) 
                                >> (IData)(vlSelf->tb_scheduler__DOT__head_row1)) 
                               | ((IData)(vlSelf->tb_scheduler__DOT__head_row0) 
                                  == (IData)(vlSelf->tb_scheduler__DOT__head_row1))))) {
                        __Vtask_tb_scheduler__DOT__run_case__4__row_event = 1U;
                    } else if (((1U & (IData)(vlSelf->tb_scheduler__DOT__head_row0)) 
                                == (1U & (IData)(vlSelf->tb_scheduler__DOT__head_row1)))) {
                        __Vtask_tb_scheduler__DOT__run_case__4__bank_event = 1U;
                    } else {
                        __Vtask_tb_scheduler__DOT__run_case__4__expect1 = 1U;
                    }
                }
            }
        }
        __Vtask_tb_scheduler__DOT__run_case__4__expected_pop 
            = (((IData)(__Vtask_tb_scheduler__DOT__run_case__4__expect0)
                 ? 1U : 0U) + ((IData)(__Vtask_tb_scheduler__DOT__run_case__4__expect1)
                                ? 1U : 0U));
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__issue_valid) 
                         != (((IData)(__Vtask_tb_scheduler__DOT__run_case__4__expect1) 
                              << 1U) | (IData)(__Vtask_tb_scheduler__DOT__run_case__4__expect0))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:132: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: issue_valid=%b expected=%b\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__4__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__4__cycles,
                         2,(IData)(vlSelf->tb_scheduler__DOT__issue_valid),
                         2,(((IData)(__Vtask_tb_scheduler__DOT__run_case__4__expect1) 
                             << 1U) | (IData)(__Vtask_tb_scheduler__DOT__run_case__4__expect0)));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 132, "");
        }
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__pop_count) 
                         != __Vtask_tb_scheduler__DOT__run_case__4__expected_pop))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:134: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: pop=%0# expected=%0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__4__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__4__cycles,
                         2,(IData)(vlSelf->tb_scheduler__DOT__pop_count),
                         32,__Vtask_tb_scheduler__DOT__run_case__4__expected_pop);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 134, "");
        }
        if (VL_UNLIKELY(((IData)(__Vtask_tb_scheduler__DOT__run_case__4__expect0) 
                         & ((IData)(vlSelf->tb_scheduler__DOT__issue_row0) 
                            != (IData)(vlSelf->tb_scheduler__DOT__head_row0))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:136: Assertion failed in %Ntb_scheduler.run_case: %@: lane0 row mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__4__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 136, "");
        }
        if (VL_UNLIKELY(((IData)(__Vtask_tb_scheduler__DOT__run_case__4__expect1) 
                         & ((IData)(vlSelf->tb_scheduler__DOT__issue_row1) 
                            != (IData)(vlSelf->tb_scheduler__DOT__head_row1))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:138: Assertion failed in %Ntb_scheduler.run_case: %@: lane1 row mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__4__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 138, "");
        }
        __Vtask_tb_scheduler__DOT__run_case__4__new_reservations = 0U;
        if (__Vtask_tb_scheduler__DOT__run_case__4__expect0) {
            __Vtask_tb_scheduler__DOT__run_case__4__new_reservations 
                = ((IData)(__Vtask_tb_scheduler__DOT__run_case__4__new_reservations) 
                   | (0xffffU & ((IData)(1U) << (IData)(vlSelf->tb_scheduler__DOT__head_row0))));
        }
        if (__Vtask_tb_scheduler__DOT__run_case__4__expect1) {
            __Vtask_tb_scheduler__DOT__run_case__4__new_reservations 
                = ((IData)(__Vtask_tb_scheduler__DOT__run_case__4__new_reservations) 
                   | (0xffffU & ((IData)(1U) << (IData)(vlSelf->tb_scheduler__DOT__head_row1))));
        }
        __Vtask_tb_scheduler__DOT__run_case__4__expected_issued 
            = (__Vtask_tb_scheduler__DOT__run_case__4__expected_issued 
               + __Vtask_tb_scheduler__DOT__run_case__4__expected_pop);
        if (__Vtask_tb_scheduler__DOT__run_case__4__row_event) {
            __Vtask_tb_scheduler__DOT__run_case__4__expected_row_events 
                = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__4__expected_row_events);
        }
        if (__Vtask_tb_scheduler__DOT__run_case__4__bank_event) {
            __Vtask_tb_scheduler__DOT__run_case__4__expected_bank_events 
                = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__4__expected_bank_events);
        }
        co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_scheduler.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                           148);
        co_await vlSelf->__VdlySched.delay(0x3e8ULL, 
                                           nullptr, 
                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                           149);
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__busy_rows) 
                         != (IData)(__Vtask_tb_scheduler__DOT__run_case__4__new_reservations)))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:151: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: busy=%x expected=%x\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__4__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__4__cycles,
                         16,(IData)(vlSelf->tb_scheduler__DOT__busy_rows),
                         16,__Vtask_tb_scheduler__DOT__run_case__4__new_reservations);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 151, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__issued_total 
                         != __Vtask_tb_scheduler__DOT__run_case__4__expected_issued))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:153: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: issued counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__4__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__4__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 153, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__row_hazard_cycles 
                         != __Vtask_tb_scheduler__DOT__run_case__4__expected_row_events))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:155: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: row counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__4__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__4__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 155, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__bank_conflict_cycles 
                         != __Vtask_tb_scheduler__DOT__run_case__4__expected_bank_events))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:157: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: bank counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__4__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__4__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 157, "");
        }
        __Vtask_tb_scheduler__DOT__run_case__4__previous_cycle_issued 
            = __Vtask_tb_scheduler__DOT__run_case__4__new_reservations;
        __Vtask_tb_scheduler__DOT__run_case__4__ptr 
            = (__Vtask_tb_scheduler__DOT__run_case__4__ptr 
               + __Vtask_tb_scheduler__DOT__run_case__4__expected_pop);
        __Vtask_tb_scheduler__DOT__run_case__4__cycles 
            = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__4__cycles);
    }
    vlSelf->tb_scheduler__DOT__head_valid = 0U;
    VL_WRITEF_NX("PASS %-26@ cycles=%0d MACs=%0d row_stall=%0d bank_conflict=%0d\n",0,
                 -1,&(__Vtask_tb_scheduler__DOT__run_case__4__test_name),
                 32,__Vtask_tb_scheduler__DOT__run_case__4__cycles,
                 32,__Vtask_tb_scheduler__DOT__run_case__4__expected_issued,
                 32,__Vtask_tb_scheduler__DOT__run_case__4__expected_row_events,
                 32,__Vtask_tb_scheduler__DOT__run_case__4__expected_bank_events);
    __Vtask_tb_scheduler__DOT__run_case__6__test_name = 
        std::string{"source_gaps"};
    __Vtask_tb_scheduler__DOT__run_case__6__case_id = 4U;
    __Vtask_tb_scheduler__DOT__load_trace__7__case_id 
        = __Vtask_tb_scheduler__DOT__run_case__6__case_id;
    tb_scheduler__DOT__trace_len = 0U;
    if ((1U == __Vtask_tb_scheduler__DOT__load_trace__7__case_id)) {
        tb_scheduler__DOT__trace_len = 8U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 1U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 2U;
        vlSelf->tb_scheduler__DOT__trace_mem[4U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[5U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[6U] = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[7U] = 5U;
    } else if ((2U == __Vtask_tb_scheduler__DOT__load_trace__7__case_id)) {
        tb_scheduler__DOT__trace_len = 6U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 2U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 6U;
        vlSelf->tb_scheduler__DOT__trace_mem[4U] = 8U;
        vlSelf->tb_scheduler__DOT__trace_mem[5U] = 0xaU;
    } else if ((3U == __Vtask_tb_scheduler__DOT__load_trace__7__case_id)) {
        tb_scheduler__DOT__trace_len = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 3U;
    } else if (VL_LIKELY((4U == __Vtask_tb_scheduler__DOT__load_trace__7__case_id))) {
        tb_scheduler__DOT__trace_len = 8U;
        vlSelf->tb_scheduler__DOT__trace_mem[0U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[1U] = 1U;
        vlSelf->tb_scheduler__DOT__trace_mem[2U] = 2U;
        vlSelf->tb_scheduler__DOT__trace_mem[3U] = 3U;
        vlSelf->tb_scheduler__DOT__trace_mem[4U] = 0U;
        vlSelf->tb_scheduler__DOT__trace_mem[5U] = 4U;
        vlSelf->tb_scheduler__DOT__trace_mem[6U] = 5U;
        vlSelf->tb_scheduler__DOT__trace_mem[7U] = 6U;
    } else {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:52: Assertion failed in %Ntb_scheduler.load_trace: Unknown case %0d\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_scheduler__DOT__load_trace__7__case_id);
        VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 52, "");
    }
    vlSelf->tb_scheduler__DOT__rst = 1U;
    vlSelf->tb_scheduler__DOT__head_valid = 0U;
    vlSelf->tb_scheduler__DOT__head_row0 = 0U;
    vlSelf->tb_scheduler__DOT__head_row1 = 0U;
    co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       77);
    co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       77);
    co_await vlSelf->__VtrigSched_hc9429d78__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(negedge tb_scheduler.clk)", 
                                                       "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                       78);
    vlSelf->tb_scheduler__DOT__rst = 0U;
    __Vtask_tb_scheduler__DOT__run_case__6__ptr = 0U;
    __Vtask_tb_scheduler__DOT__run_case__6__cycles = 0U;
    __Vtask_tb_scheduler__DOT__run_case__6__expected_issued = 0U;
    __Vtask_tb_scheduler__DOT__run_case__6__expected_row_events = 0U;
    __Vtask_tb_scheduler__DOT__run_case__6__expected_bank_events = 0U;
    __Vtask_tb_scheduler__DOT__run_case__6__previous_cycle_issued = 0U;
    while (VL_LTS_III(32, __Vtask_tb_scheduler__DOT__run_case__6__ptr, tb_scheduler__DOT__trace_len)) {
        if (VL_UNLIKELY(VL_LTS_III(32, 0x32U, __Vtask_tb_scheduler__DOT__run_case__6__cycles))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:89: Assertion failed in %Ntb_scheduler.run_case: %@: timeout / no forward progress\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__6__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 89, "");
        }
        co_await vlSelf->__VtrigSched_hc9429d78__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(negedge tb_scheduler.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                           90);
        __Vtask_tb_scheduler__DOT__run_case__6__gap 
            = ((4U == __Vtask_tb_scheduler__DOT__run_case__6__case_id) 
               & ((2U == __Vtask_tb_scheduler__DOT__run_case__6__cycles) 
                  | (5U == __Vtask_tb_scheduler__DOT__run_case__6__cycles)));
        vlSelf->tb_scheduler__DOT__head_valid = 0U;
        vlSelf->tb_scheduler__DOT__head_row0 = 0U;
        vlSelf->tb_scheduler__DOT__head_row1 = 0U;
        if (((~ (IData)(__Vtask_tb_scheduler__DOT__run_case__6__gap)) 
             & VL_LTS_III(32, __Vtask_tb_scheduler__DOT__run_case__6__ptr, tb_scheduler__DOT__trace_len))) {
            vlSelf->tb_scheduler__DOT__head_valid = 
                (1U | (IData)(vlSelf->tb_scheduler__DOT__head_valid));
            vlSelf->tb_scheduler__DOT__head_row0 = 
                vlSelf->tb_scheduler__DOT__trace_mem
                [(0x3fU & __Vtask_tb_scheduler__DOT__run_case__6__ptr)];
            if (VL_LTS_III(32, ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__6__ptr), tb_scheduler__DOT__trace_len)) {
                vlSelf->tb_scheduler__DOT__head_valid 
                    = (2U | (IData)(vlSelf->tb_scheduler__DOT__head_valid));
                vlSelf->tb_scheduler__DOT__head_row1 
                    = vlSelf->tb_scheduler__DOT__trace_mem
                    [(0x3fU & ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__6__ptr))];
            }
        }
        co_await vlSelf->__VdlySched.delay(0x3e8ULL, 
                                           nullptr, 
                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                           106);
        __Vtask_tb_scheduler__DOT__run_case__6__expect0 = 0U;
        __Vtask_tb_scheduler__DOT__run_case__6__expect1 = 0U;
        __Vtask_tb_scheduler__DOT__run_case__6__row_event = 0U;
        __Vtask_tb_scheduler__DOT__run_case__6__bank_event = 0U;
        if ((1U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
            if ((1U & ((IData)(__Vtask_tb_scheduler__DOT__run_case__6__previous_cycle_issued) 
                       >> (IData)(vlSelf->tb_scheduler__DOT__head_row0)))) {
                __Vtask_tb_scheduler__DOT__run_case__6__row_event = 1U;
            } else {
                __Vtask_tb_scheduler__DOT__run_case__6__expect0 = 1U;
                if ((2U & (IData)(vlSelf->tb_scheduler__DOT__head_valid))) {
                    if ((1U & (((IData)(__Vtask_tb_scheduler__DOT__run_case__6__previous_cycle_issued) 
                                >> (IData)(vlSelf->tb_scheduler__DOT__head_row1)) 
                               | ((IData)(vlSelf->tb_scheduler__DOT__head_row0) 
                                  == (IData)(vlSelf->tb_scheduler__DOT__head_row1))))) {
                        __Vtask_tb_scheduler__DOT__run_case__6__row_event = 1U;
                    } else if (((1U & (IData)(vlSelf->tb_scheduler__DOT__head_row0)) 
                                == (1U & (IData)(vlSelf->tb_scheduler__DOT__head_row1)))) {
                        __Vtask_tb_scheduler__DOT__run_case__6__bank_event = 1U;
                    } else {
                        __Vtask_tb_scheduler__DOT__run_case__6__expect1 = 1U;
                    }
                }
            }
        }
        __Vtask_tb_scheduler__DOT__run_case__6__expected_pop 
            = (((IData)(__Vtask_tb_scheduler__DOT__run_case__6__expect0)
                 ? 1U : 0U) + ((IData)(__Vtask_tb_scheduler__DOT__run_case__6__expect1)
                                ? 1U : 0U));
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__issue_valid) 
                         != (((IData)(__Vtask_tb_scheduler__DOT__run_case__6__expect1) 
                              << 1U) | (IData)(__Vtask_tb_scheduler__DOT__run_case__6__expect0))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:132: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: issue_valid=%b expected=%b\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__6__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__6__cycles,
                         2,(IData)(vlSelf->tb_scheduler__DOT__issue_valid),
                         2,(((IData)(__Vtask_tb_scheduler__DOT__run_case__6__expect1) 
                             << 1U) | (IData)(__Vtask_tb_scheduler__DOT__run_case__6__expect0)));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 132, "");
        }
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__pop_count) 
                         != __Vtask_tb_scheduler__DOT__run_case__6__expected_pop))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:134: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: pop=%0# expected=%0d\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__6__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__6__cycles,
                         2,(IData)(vlSelf->tb_scheduler__DOT__pop_count),
                         32,__Vtask_tb_scheduler__DOT__run_case__6__expected_pop);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 134, "");
        }
        if (VL_UNLIKELY(((IData)(__Vtask_tb_scheduler__DOT__run_case__6__expect0) 
                         & ((IData)(vlSelf->tb_scheduler__DOT__issue_row0) 
                            != (IData)(vlSelf->tb_scheduler__DOT__head_row0))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:136: Assertion failed in %Ntb_scheduler.run_case: %@: lane0 row mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__6__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 136, "");
        }
        if (VL_UNLIKELY(((IData)(__Vtask_tb_scheduler__DOT__run_case__6__expect1) 
                         & ((IData)(vlSelf->tb_scheduler__DOT__issue_row1) 
                            != (IData)(vlSelf->tb_scheduler__DOT__head_row1))))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:138: Assertion failed in %Ntb_scheduler.run_case: %@: lane1 row mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__6__test_name));
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 138, "");
        }
        __Vtask_tb_scheduler__DOT__run_case__6__new_reservations = 0U;
        if (__Vtask_tb_scheduler__DOT__run_case__6__expect0) {
            __Vtask_tb_scheduler__DOT__run_case__6__new_reservations 
                = ((IData)(__Vtask_tb_scheduler__DOT__run_case__6__new_reservations) 
                   | (0xffffU & ((IData)(1U) << (IData)(vlSelf->tb_scheduler__DOT__head_row0))));
        }
        if (__Vtask_tb_scheduler__DOT__run_case__6__expect1) {
            __Vtask_tb_scheduler__DOT__run_case__6__new_reservations 
                = ((IData)(__Vtask_tb_scheduler__DOT__run_case__6__new_reservations) 
                   | (0xffffU & ((IData)(1U) << (IData)(vlSelf->tb_scheduler__DOT__head_row1))));
        }
        __Vtask_tb_scheduler__DOT__run_case__6__expected_issued 
            = (__Vtask_tb_scheduler__DOT__run_case__6__expected_issued 
               + __Vtask_tb_scheduler__DOT__run_case__6__expected_pop);
        if (__Vtask_tb_scheduler__DOT__run_case__6__row_event) {
            __Vtask_tb_scheduler__DOT__run_case__6__expected_row_events 
                = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__6__expected_row_events);
        }
        if (__Vtask_tb_scheduler__DOT__run_case__6__bank_event) {
            __Vtask_tb_scheduler__DOT__run_case__6__expected_bank_events 
                = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__6__expected_bank_events);
        }
        co_await vlSelf->__VtrigSched_hc942a4a9__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_scheduler.clk)", 
                                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                                           148);
        co_await vlSelf->__VdlySched.delay(0x3e8ULL, 
                                           nullptr, 
                                           "/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 
                                           149);
        if (VL_UNLIKELY(((IData)(vlSelf->tb_scheduler__DOT__busy_rows) 
                         != (IData)(__Vtask_tb_scheduler__DOT__run_case__6__new_reservations)))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:151: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: busy=%x expected=%x\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__6__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__6__cycles,
                         16,(IData)(vlSelf->tb_scheduler__DOT__busy_rows),
                         16,__Vtask_tb_scheduler__DOT__run_case__6__new_reservations);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 151, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__issued_total 
                         != __Vtask_tb_scheduler__DOT__run_case__6__expected_issued))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:153: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: issued counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__6__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__6__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 153, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__row_hazard_cycles 
                         != __Vtask_tb_scheduler__DOT__run_case__6__expected_row_events))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:155: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: row counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__6__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__6__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 155, "");
        }
        if (VL_UNLIKELY((vlSelf->tb_scheduler__DOT__bank_conflict_cycles 
                         != __Vtask_tb_scheduler__DOT__run_case__6__expected_bank_events))) {
            VL_WRITEF_NX("[%0t] %%Fatal: tb_scheduler.sv:157: Assertion failed in %Ntb_scheduler.run_case: %@ cycle %0d: bank counter mismatch\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(__Vtask_tb_scheduler__DOT__run_case__6__test_name),
                         32,__Vtask_tb_scheduler__DOT__run_case__6__cycles);
            VL_STOP_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 157, "");
        }
        __Vtask_tb_scheduler__DOT__run_case__6__previous_cycle_issued 
            = __Vtask_tb_scheduler__DOT__run_case__6__new_reservations;
        __Vtask_tb_scheduler__DOT__run_case__6__ptr 
            = (__Vtask_tb_scheduler__DOT__run_case__6__ptr 
               + __Vtask_tb_scheduler__DOT__run_case__6__expected_pop);
        __Vtask_tb_scheduler__DOT__run_case__6__cycles 
            = ((IData)(1U) + __Vtask_tb_scheduler__DOT__run_case__6__cycles);
    }
    vlSelf->tb_scheduler__DOT__head_valid = 0U;
    VL_WRITEF_NX("PASS %-26@ cycles=%0d MACs=%0d row_stall=%0d bank_conflict=%0d\nALL FOUR DIRECTED TESTS PASS\n",0,
                 -1,&(__Vtask_tb_scheduler__DOT__run_case__6__test_name),
                 32,__Vtask_tb_scheduler__DOT__run_case__6__cycles,
                 32,__Vtask_tb_scheduler__DOT__run_case__6__expected_issued,
                 32,__Vtask_tb_scheduler__DOT__run_case__6__expected_row_events,
                 32,__Vtask_tb_scheduler__DOT__run_case__6__expected_bank_events);
    VL_FINISH_MT("/home/kaiden_di/Hw_Sw_CoDesign/w11/tb/tb_scheduler.sv", 181, "");
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_scheduler___024root___dump_triggers__act(Vtb_scheduler___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_scheduler___024root___eval_triggers__act(Vtb_scheduler___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtb_scheduler__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_scheduler___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->tb_scheduler__DOT__clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__tb_scheduler__DOT__clk__0))));
    vlSelf->__VactTriggered.set(1U, ((~ (IData)(vlSelf->tb_scheduler__DOT__clk)) 
                                     & (IData)(vlSelf->__Vtrigprevexpr___TOP__tb_scheduler__DOT__clk__0)));
    vlSelf->__VactTriggered.set(2U, vlSelf->__VdlySched.awaitingCurrentTime());
    vlSelf->__Vtrigprevexpr___TOP__tb_scheduler__DOT__clk__0 
        = vlSelf->tb_scheduler__DOT__clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_scheduler___024root___dump_triggers__act(vlSelf);
    }
#endif
}
