// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtb_spmv_axis__pch.h"
#include "Vtb_spmv_axis.h"
#include "Vtb_spmv_axis___024root.h"

// FUNCTIONS
Vtb_spmv_axis__Syms::~Vtb_spmv_axis__Syms()
{
}

Vtb_spmv_axis__Syms::Vtb_spmv_axis__Syms(VerilatedContext* contextp, const char* namep, Vtb_spmv_axis* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(414);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_tb_spmv_axis.configure(this, name(), "tb_spmv_axis", "tb_spmv_axis", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_tb_spmv_axis__dut.configure(this, name(), "tb_spmv_axis.dut", "dut", -9, VerilatedScope::SCOPE_OTHER);
}
