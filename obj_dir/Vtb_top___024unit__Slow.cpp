// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top__Syms.h"
#include "Vtb_top___024unit.h"

void Vtb_top___024unit___ctor_var_reset(Vtb_top___024unit* vlSelf);

Vtb_top___024unit::Vtb_top___024unit(Vtb_top__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vtb_top___024unit___ctor_var_reset(this);
}

void Vtb_top___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_top___024unit::~Vtb_top___024unit() {
}
