// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtb_spmv_file__pch.h"
#include "Vtb_spmv_file.h"
#include "Vtb_spmv_file___024root.h"

// FUNCTIONS
Vtb_spmv_file__Syms::~Vtb_spmv_file__Syms()
{
}

Vtb_spmv_file__Syms::Vtb_spmv_file__Syms(VerilatedContext* contextp, const char* namep, Vtb_spmv_file* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(112);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_tb_spmv_file.configure(this, name(), "tb_spmv_file", "tb_spmv_file", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_tb_spmv_file__dut.configure(this, name(), "tb_spmv_file.dut", "dut", -9, VerilatedScope::SCOPE_OTHER);
}
