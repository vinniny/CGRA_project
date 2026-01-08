// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top__Syms.h"
#include "Vtb_top_cgra_pe__A4.h"

void Vtb_top_cgra_pe__A4___ctor_var_reset(Vtb_top_cgra_pe__A4* vlSelf);

Vtb_top_cgra_pe__A4::Vtb_top_cgra_pe__A4(Vtb_top__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vtb_top_cgra_pe__A4___ctor_var_reset(this);
}

void Vtb_top_cgra_pe__A4::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_top_cgra_pe__A4::~Vtb_top_cgra_pe__A4() {
}
