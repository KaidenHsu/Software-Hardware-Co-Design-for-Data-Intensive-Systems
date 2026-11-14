// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_spmv_file__pch.h"

//============================================================
// Constructors

Vtb_spmv_file::Vtb_spmv_file(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_spmv_file__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_spmv_file::Vtb_spmv_file(const char* _vcname__)
    : Vtb_spmv_file(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_spmv_file::~Vtb_spmv_file() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_spmv_file___024root___eval_debug_assertions(Vtb_spmv_file___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_spmv_file___024root___eval_static(Vtb_spmv_file___024root* vlSelf);
void Vtb_spmv_file___024root___eval_initial(Vtb_spmv_file___024root* vlSelf);
void Vtb_spmv_file___024root___eval_settle(Vtb_spmv_file___024root* vlSelf);
void Vtb_spmv_file___024root___eval(Vtb_spmv_file___024root* vlSelf);

void Vtb_spmv_file::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_spmv_file::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_spmv_file___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_spmv_file___024root___eval_static(&(vlSymsp->TOP));
        Vtb_spmv_file___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_spmv_file___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_spmv_file___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_spmv_file::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vtb_spmv_file::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_spmv_file::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_spmv_file___024root___eval_final(Vtb_spmv_file___024root* vlSelf);

VL_ATTR_COLD void Vtb_spmv_file::final() {
    Vtb_spmv_file___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_spmv_file::hierName() const { return vlSymsp->name(); }
const char* Vtb_spmv_file::modelName() const { return "Vtb_spmv_file"; }
unsigned Vtb_spmv_file::threads() const { return 1; }
void Vtb_spmv_file::prepareClone() const { contextp()->prepareClone(); }
void Vtb_spmv_file::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vtb_spmv_file::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vtb_spmv_file::trace()' called on model that was Verilated without --trace option");
}
