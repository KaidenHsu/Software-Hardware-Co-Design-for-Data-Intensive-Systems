// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_spmv_axis.h for the primary calling header

#include "Vtb_spmv_axis__pch.h"
#include "Vtb_spmv_axis__Syms.h"
#include "Vtb_spmv_axis___024root.h"

void Vtb_spmv_axis___024root___ctor_var_reset(Vtb_spmv_axis___024root* vlSelf);

Vtb_spmv_axis___024root::Vtb_spmv_axis___024root(Vtb_spmv_axis__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __VdlySched{*symsp->_vm_contextp__}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vtb_spmv_axis___024root___ctor_var_reset(this);
}

void Vtb_spmv_axis___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_spmv_axis___024root::~Vtb_spmv_axis___024root() {
}
