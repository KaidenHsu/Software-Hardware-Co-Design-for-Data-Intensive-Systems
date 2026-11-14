// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_SPMV_FILE__SYMS_H_
#define VERILATED_VTB_SPMV_FILE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_spmv_file.h"

// INCLUDE MODULE CLASSES
#include "Vtb_spmv_file___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vtb_spmv_file__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_spmv_file* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_spmv_file___024root        TOP;

    // SCOPE NAMES
    VerilatedScope __Vscope_tb_spmv_file;
    VerilatedScope __Vscope_tb_spmv_file__dut;

    // CONSTRUCTORS
    Vtb_spmv_file__Syms(VerilatedContext* contextp, const char* namep, Vtb_spmv_file* modelp);
    ~Vtb_spmv_file__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
