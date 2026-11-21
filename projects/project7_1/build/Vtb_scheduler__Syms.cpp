// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtb_scheduler__pch.h"
#include "Vtb_scheduler.h"
#include "Vtb_scheduler___024root.h"

// FUNCTIONS
Vtb_scheduler__Syms::~Vtb_scheduler__Syms()
{
}

Vtb_scheduler__Syms::Vtb_scheduler__Syms(VerilatedContext* contextp, const char* namep, Vtb_scheduler* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(230);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_tb_scheduler.configure(this, name(), "tb_scheduler", "tb_scheduler", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_tb_scheduler__load_trace.configure(this, name(), "tb_scheduler.load_trace", "load_trace", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_tb_scheduler__run_case.configure(this, name(), "tb_scheduler.run_case", "run_case", -9, VerilatedScope::SCOPE_OTHER);
}
