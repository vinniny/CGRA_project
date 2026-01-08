// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top_cgra_pe__A4.h"

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__2(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__2\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__config_ram_valid = vlSelfRef.__PVT__u_config_mem__DOT__rst_n;
}
