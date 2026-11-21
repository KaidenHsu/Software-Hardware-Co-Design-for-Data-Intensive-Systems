// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_SCHEDULER__SYMS_H_
#define VERILATED_VTB_SCHEDULER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_scheduler.h"

// INCLUDE MODULE CLASSES
#include "Vtb_scheduler___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vtb_scheduler__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_scheduler* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_scheduler___024root        TOP;

    // SCOPE NAMES
    VerilatedScope __Vscope_tb_scheduler;
    VerilatedScope __Vscope_tb_scheduler__load_trace;
    VerilatedScope __Vscope_tb_scheduler__run_case;

    // CONSTRUCTORS
    Vtb_scheduler__Syms(VerilatedContext* contextp, const char* namep, Vtb_scheduler* modelp);
    ~Vtb_scheduler__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
