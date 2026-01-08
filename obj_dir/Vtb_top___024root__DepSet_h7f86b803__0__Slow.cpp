// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top__Syms.h"
#include "Vtb_top___024root.h"

VL_ATTR_COLD void Vtb_top___024root___eval_static__TOP(Vtb_top___024root* vlSelf);
VL_ATTR_COLD void Vtb_top___024root____Vm_traceActivitySetAll(Vtb_top___024root* vlSelf);

VL_ATTR_COLD void Vtb_top___024root___eval_static(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_static\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_top___024root___eval_static__TOP(vlSelf);
    Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready__1 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__ready_out__1 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__clk__0 
        = vlSelfRef.tb_top__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__rst_n__0 
        = vlSelfRef.tb_top__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe____PVT__u_config_mem__DOT__rst_n__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__axi_arvalid__0 
        = vlSelfRef.tb_top__DOT__axi_arvalid;
    vlSelfRef.__Vtrigprevexpr_h598af589__1 = ((IData)(vlSelfRef.tb_top__DOT__axi_bvalid_reg) 
                                              & (IData)(vlSelfRef.tb_top__DOT__axi_bready));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__stl(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_top___024root___eval_triggers__stl(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_triggers__stl\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.setBit(0U, (IData)(vlSelfRef.__VstlFirstIteration));
    vlSelfRef.__VstlTriggered.setBit(1U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.ready_out) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(2U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(3U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(4U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.ready_out) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(5U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(6U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(7U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.ready_out) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(8U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(9U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0xaU, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.ready_out) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0xbU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0xcU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0xdU, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.ready_out) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0xeU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0xfU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x10U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0x11U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x12U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0x13U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x14U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x15U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0x16U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x17U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0x18U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x19U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x1aU, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0x1bU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x1cU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x1dU, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0x1eU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x1fU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x20U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0x21U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x22U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0x23U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x24U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0x25U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x26U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__ready_out__0)));
    vlSelfRef.__VstlTriggered.setBit(0x27U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready__0)));
    vlSelfRef.__VstlTriggered.setBit(0x28U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__ready_out__0)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready__0 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__ready_out__0 
        = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out;
    if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VstlDidInit)))))) {
        vlSelfRef.__VstlDidInit = 1U;
        vlSelfRef.__VstlTriggered.setBit(1U, 1U);
        vlSelfRef.__VstlTriggered.setBit(2U, 1U);
        vlSelfRef.__VstlTriggered.setBit(3U, 1U);
        vlSelfRef.__VstlTriggered.setBit(4U, 1U);
        vlSelfRef.__VstlTriggered.setBit(5U, 1U);
        vlSelfRef.__VstlTriggered.setBit(6U, 1U);
        vlSelfRef.__VstlTriggered.setBit(7U, 1U);
        vlSelfRef.__VstlTriggered.setBit(8U, 1U);
        vlSelfRef.__VstlTriggered.setBit(9U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0xaU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0xbU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0xcU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0xdU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0xeU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0xfU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x10U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x11U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x12U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x13U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x14U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x15U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x16U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x17U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x18U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x19U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x1aU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x1bU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x1cU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x1dU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x1eU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x1fU, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x20U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x21U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x22U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x23U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x24U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x25U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x26U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x27U, 1U);
        vlSelfRef.__VstlTriggered.setBit(0x28U, 1U);
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_top___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

VL_ATTR_COLD void Vtb_top___024root___stl_sequent__TOP__0(Vtb_top___024root* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_sequent__TOP__0(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__1(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__2(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__3(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__4(Vtb_top___024root* vlSelf);
void Vtb_top___024root___act_comb__TOP__5(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__6(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__7(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__8(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__9(Vtb_top___024root* vlSelf);
void Vtb_top___024root___act_comb__TOP__10(Vtb_top___024root* vlSelf);
void Vtb_top___024root___act_comb__TOP__11(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__12(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__13(Vtb_top___024root* vlSelf);
void Vtb_top___024root___act_comb__TOP__14(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__15(Vtb_top___024root* vlSelf);
void Vtb_top___024root___act_comb__TOP__16(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__17(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__18(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__19(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__20(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__21(Vtb_top___024root* vlSelf);

VL_ATTR_COLD void Vtb_top___024root___eval_stl(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_stl\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___stl_sequent__TOP__0(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe));
        Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe));
    }
    if ((0xfULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_sequent__TOP__0(vlSelf);
        Vtb_top_cgra_pe__A4___act_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
    }
    if ((0x7fULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__1(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe));
    }
    if ((0x38fULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__2(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe));
    }
    if ((0x1c7fULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__3(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe));
    }
    if ((0x3ffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__4(vlSelf);
    }
    if ((0x380038fULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__5(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe));
    }
    if ((0xe3ffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__6(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe));
    }
    if ((0x31c7fULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__7(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe));
    }
    if ((0xc0380038fULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__8(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe));
    }
    if ((0xffffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__9(vlSelf);
    }
    if ((0x380e3ffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__10(vlSelf);
    }
    if ((0x1cffffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__11(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe));
    }
    if ((0x1f80e3ffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__12(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe));
    }
    if ((0x1fffffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__13(vlSelf);
    }
    if ((0x7fffffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__14(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe));
    }
    if ((0xc1f80e3ffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__15(vlSelf);
    }
    if ((0x3c1f80e3ffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__16(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe));
    }
    if ((0xff9cffffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__17(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe));
    }
    if ((0x3ffffffffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__18(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe));
    }
    if ((0xfcff9cffffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__19(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe));
    }
    if ((0x1ffffffffffULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__20(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe));
        Vtb_top___024root___act_comb__TOP__21(vlSelf);
    }
}

VL_ATTR_COLD void Vtb_top___024root___stl_sequent__TOP__0(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___stl_sequent__TOP__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state)) 
                               << 2U) | (((1U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state)) 
                                          << 1U) | 
                                         (0U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state)))))))) {
        if ((0U != (((2U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state)) 
                     << 2U) | (((1U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state)) 
                                << 1U) | (0U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: cgra_control_unit.sv:94: Assertion failed in %Ntb_top.u_dut.u_cu: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state));
                VL_STOP_MT("00_src/cgra_control_unit.sv", 94, "");
            }
        }
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__ext_write 
        = ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_en) 
           & (1U == (vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_dst 
                     >> 0x1cU)));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_push 
        = ((IData)(vlSelfRef.tb_top__DOT__axi_rvalid_reg) 
           & ((8U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count)) 
              & (IData)(vlSelfRef.tb_top__DOT__axi_rready)));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_pop 
        = (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__axi_fifo_pop) 
            & ((0U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count)) 
               & (0U == (vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_dst 
                         >> 0x1cU)))) | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_fifo_pop) 
                                         & ((0U != 
                                             (vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_dst 
                                              >> 0x1cU)) 
                                            & (0U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_data[0U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank0_rdata;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_data[1U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank1_rdata;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_data[2U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank2_rdata;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_data[3U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank3_rdata;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_valid[0U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_read_reg;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_valid[1U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_read_reg;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_valid[2U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_read_reg;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_valid[3U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_read_reg;
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__len_limit_fifo 
        = ((8U < vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__read_words_remaining)
            ? 8U : vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__read_words_remaining);
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state_next 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state;
    if ((0U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state))) {
        if ((IData)((1U == (3U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl)))) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state_next = 1U;
        }
    } else if ((1U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state))) {
        if ((1U & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__auto_stop_armed) 
                     & (0x10U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__auto_stop_counter))) 
                    | ((0U != vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_timeout) 
                       & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter 
                          >= vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_timeout))) 
                   | (vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl 
                      >> 1U)))) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state_next = 2U;
        }
    } else {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state_next = 0U;
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__config_we_o 
        = ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_en) 
           & (2U == (vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_dst 
                     >> 0x1cU)));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_irq_status 
        = (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__cu_done_latch) 
            << 1U) | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__dma_done_latch));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_e 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_s 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_n 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_w 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_l 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_w 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_n 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_e 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_s 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_n 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_w 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_l 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_l 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_s 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_e 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_w 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_n 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_e 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_s 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_n 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_w 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_l 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_l 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_s 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e))
                    : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e))
                        : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_e 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s))
                : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_s 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s))
                    : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w))
                : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_w 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w))
                    : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n))
                : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_n 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n))
                    : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l))
                : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_l 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l))
                    : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s 
            = ((3U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s))
                : ((3U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e))
                : ((3U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_e 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e))
                    : ((3U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_n 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_w 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_l 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_e 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_s 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_w 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_n 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_n 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_w 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_l 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_l 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_e 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_s 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_s 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e))
                    : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e))
                        : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_e 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w))
                : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_w 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w))
                    : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n))
                : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_n 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n))
                    : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l))
                : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_l 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l))
                    : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s))
                : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_s 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s))
                    : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s 
            = ((2U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s))
                : ((2U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e))
                : ((2U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_e 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e))
                    : ((2U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_n 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_w 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_l 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_e 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s))
                    : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s))
                        : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_s 
                                          >> 0x18U)))
                            ? (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s))
                            : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s))))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_n 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w))
                : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_w 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w))
                    : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_w 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_w 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n))
                : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_n 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n))
                    : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_n 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_l 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l))
                : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_l 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l))
                    : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_l 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_e 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s))
                : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_s 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s))
                    : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s 
            = ((1U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s))
                : ((1U > (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_s 
                          >> 0x1cU)) ? (8U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s))
                    : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_s 
                                      >> 0x18U))) ? 
                       (4U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e))
                : ((1U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_e 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e))
                    : ((1U > (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_e 
                                      >> 0x18U))) ? 
                       (1U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e))
                        : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e)))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_n) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_n 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n))
                : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_n 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n))
                    : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_w) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_w 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w))
                : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_w 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w))
                    : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_l) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_l 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l))
                : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_l 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l))
                    : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_e) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_e 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e))
                : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_e 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e))
                    : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s = 0U;
    if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_s) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s 
            = ((0U < (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_s 
                      >> 0x1cU)) ? (2U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s))
                : ((0U < (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_s 
                                  >> 0x18U))) ? (4U 
                                                 | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s))
                    : (0x10U | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s))));
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__words_this_burst 
        = ((vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__len_limit_fifo 
            > VL_SHIFTR_III(32,32,32, ((IData)(0x1000U) 
                                       - (0xfffU & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__read_addr)), 2U))
            ? VL_SHIFTR_III(32,32,32, ((IData)(0x1000U) 
                                       - (0xfffU & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__read_addr)), 2U)
            : vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__len_limit_fifo);
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en 
        = ((~ (vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
               >> 2U)) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__config_we_o));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata 
        = ((0x80U & vlSelfRef.tb_top__DOT__paddr) ? 0xdeadbeefU
            : ((0x40U & vlSelfRef.tb_top__DOT__paddr)
                ? 0xdeadbeefU : ((0x20U & vlSelfRef.tb_top__DOT__paddr)
                                  ? ((0x10U & vlSelfRef.tb_top__DOT__paddr)
                                      ? ((8U & vlSelfRef.tb_top__DOT__paddr)
                                          ? 0xdeadbeefU
                                          : ((4U & vlSelfRef.tb_top__DOT__paddr)
                                              ? ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_irq_mask))
                                              : ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_irq_status))))
                                      : ((8U & vlSelfRef.tb_top__DOT__paddr)
                                          ? ((4U & vlSelfRef.tb_top__DOT__paddr)
                                              ? ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_timeout))
                                              : ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter)))
                                          : ((4U & vlSelfRef.tb_top__DOT__paddr)
                                              ? ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : 
                                                  (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__cu_done_latch) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__cu_busy))))
                                              : ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl)))))
                                  : ((0x10U & vlSelfRef.tb_top__DOT__paddr)
                                      ? ((8U & vlSelfRef.tb_top__DOT__paddr)
                                          ? 0xdeadbeefU
                                          : ((4U & vlSelfRef.tb_top__DOT__paddr)
                                              ? 0xdeadbeefU
                                              : ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_size))))
                                      : ((8U & vlSelfRef.tb_top__DOT__paddr)
                                          ? ((4U & vlSelfRef.tb_top__DOT__paddr)
                                              ? ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_dst))
                                              : ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_src)))
                                          : ((4U & vlSelfRef.tb_top__DOT__paddr)
                                              ? ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : 
                                                  (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__dma_done_latch) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__dma_busy))))
                                              : ((2U 
                                                  & vlSelfRef.tb_top__DOT__paddr)
                                                  ? 0xdeadbeefU
                                                  : 
                                                 ((1U 
                                                   & vlSelfRef.tb_top__DOT__paddr)
                                                   ? 0xdeadbeefU
                                                   : vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_n 
        = ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l))
            ? 0x10U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w))
                        ? 8U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s))
                                 ? 4U : ((1U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e))
                                          ? 2U : ((1U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_e 
        = ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l))
            ? 0x10U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w))
                        ? 8U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s))
                                 ? 4U : ((2U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e))
                                          ? 2U : ((2U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_s 
        = ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l))
            ? 0x10U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w))
                        ? 8U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s))
                                 ? 4U : ((4U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e))
                                          ? 2U : ((4U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_w 
        = ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l))
            ? 0x10U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w))
                        ? 8U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s))
                                 ? 4U : ((8U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e))
                                          ? 2U : ((8U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_l 
        = ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l))
            ? 0x10U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w))
                        ? 8U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s))
                                 ? 4U : ((0x10U & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e))
                                          ? 2U : ((0x10U 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n))
                                                   ? 1U
                                                   : 0U)))));
}
