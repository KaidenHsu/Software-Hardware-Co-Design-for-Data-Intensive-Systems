// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_scheduler__pch.h"

//============================================================
// Constructors

Vtb_scheduler::Vtb_scheduler(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_scheduler__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_scheduler::Vtb_scheduler(const char* _vcname__)
    : Vtb_scheduler(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_scheduler::~Vtb_scheduler() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_scheduler___024root___eval_debug_assertions(Vtb_scheduler___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_scheduler___024root___eval_static(Vtb_scheduler___024root* vlSelf);
void Vtb_scheduler___024root___eval_initial(Vtb_scheduler___024root* vlSelf);
void Vtb_scheduler___024root___eval_settle(Vtb_scheduler___024root* vlSelf);
void Vtb_scheduler___024root___eval(Vtb_scheduler___024root* vlSelf);

void Vtb_scheduler::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_scheduler::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_scheduler___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_scheduler___024root___eval_static(&(vlSymsp->TOP));
        Vtb_scheduler___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_scheduler___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_scheduler___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_scheduler::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vtb_scheduler::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_scheduler::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_scheduler___024root___eval_final(Vtb_scheduler___024root* vlSelf);

VL_ATTR_COLD void Vtb_scheduler::final() {
    Vtb_scheduler___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_scheduler::hierName() const { return vlSymsp->name(); }
const char* Vtb_scheduler::modelName() const { return "Vtb_scheduler"; }
unsigned Vtb_scheduler::threads() const { return 1; }
void Vtb_scheduler::prepareClone() const { contextp()->prepareClone(); }
void Vtb_scheduler::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vtb_scheduler::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vtb_scheduler::trace()' called on model that was Verilated without --trace option");
}
