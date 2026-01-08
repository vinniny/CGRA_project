// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top__Syms.h"
#include "Vtb_top___024root.h"

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__2(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__2\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.ready_out))))) 
                           || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_w)) 
                                      & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n) 
                                         >> 3U))) || 
                               ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n) 
                                        >> 2U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_s)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready))))) 
                                || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n) 
                                            >> 1U) 
                                           & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_e)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready))))) 
                                    || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_n) 
                                              & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_n)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.ready_out)))) 
                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_w) 
                               >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l) 
                                          >> 3U)) | 
                          ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l) 
                             >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_s) 
                                           >> 4U)) 
                                       | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready)))) 
                           | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l) 
                                >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_e) 
                                              >> 4U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready)))) 
                              | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_l) 
                                 & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_n) 
                                        >> 4U)) | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.ready_out))))) 
                           || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_w) 
                                          >> 2U)) & 
                                      ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s) 
                                       >> 3U))) || 
                               ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s) 
                                        >> 2U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_s) 
                                                    >> 2U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready))))) 
                                || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s) 
                                            >> 1U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_e) 
                                                  >> 2U)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready))))) 
                                    || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_s) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_n) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.ready_out))))) 
                           || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_w) 
                                          >> 1U)) & 
                                      ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e) 
                                       >> 3U))) || 
                               ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e) 
                                        >> 2U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_s) 
                                                    >> 1U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready))))) 
                                || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e) 
                                            >> 1U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_e) 
                                                  >> 1U)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready))))) 
                                    || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_e) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_n) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_s_ready)))))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__3(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__3\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_s) 
                                               >> 3U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_e) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready))))) 
                                       || (1U & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_n) 
                                                   >> 3U)) 
                                                 & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_w)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_w) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l) 
                               >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_s) 
                                             >> 4U)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready)))) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l) 
                                  >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_e) 
                                                >> 4U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready)))) 
                                | ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_n) 
                                       >> 4U)) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_l)))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_w) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_s) 
                                               >> 1U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_e) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready))))) 
                                       || (1U & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_n) 
                                                   >> 1U)) 
                                                 & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_e)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_w) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_s) 
                                               >> 2U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_e) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready))))) 
                                       || (1U & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_n) 
                                                   >> 2U)) 
                                                 & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_s)))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__4(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__4\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__ready_out_n 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_n) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n) 
                         >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_l)) 
                                   | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.ready_out)))) 
                       | (((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_w)) 
                           & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n) 
                              >> 3U)) | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n) 
                                           >> 2U) & 
                                          ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_s)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready)))) 
                                         | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n) 
                                              >> 1U) 
                                             & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_e)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready)))) 
                                            | ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_n)) 
                                               & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_n)))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__ready_out_w 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_w) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_l) 
                                       >> 3U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.ready_out)))) 
                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_w) 
                               >> 3U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w) 
                                          >> 3U)) | 
                          ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w) 
                             >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_s) 
                                           >> 3U)) 
                                       | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready)))) 
                           | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w) 
                                >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_e) 
                                              >> 3U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready)))) 
                              | ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_n) 
                                     >> 3U)) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_w)))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__5(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__5\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.ready_out))))) 
                           || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_w)) 
                                      & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n) 
                                         >> 3U))) || 
                               ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n) 
                                        >> 2U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_s)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready))))) 
                                || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n) 
                                            >> 1U) 
                                           & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_e)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready))))) 
                                    || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_n) 
                                              & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_n)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.ready_out)))) 
                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_w) 
                               >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l) 
                                          >> 3U)) | 
                          ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l) 
                             >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_s) 
                                           >> 4U)) 
                                       | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready)))) 
                           | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l) 
                                >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_e) 
                                              >> 4U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready)))) 
                              | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_l) 
                                 & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_n) 
                                        >> 4U)) | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.ready_out))))) 
                           || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_w) 
                                          >> 2U)) & 
                                      ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s) 
                                       >> 3U))) || 
                               ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s) 
                                        >> 2U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_s) 
                                                    >> 2U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready))))) 
                                || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s) 
                                            >> 1U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_e) 
                                                  >> 2U)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready))))) 
                                    || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_s) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_n) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.ready_out))))) 
                           || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_w) 
                                          >> 1U)) & 
                                      ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e) 
                                       >> 3U))) || 
                               ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e) 
                                        >> 2U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_s) 
                                                    >> 1U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready))))) 
                                || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e) 
                                            >> 1U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_e) 
                                                  >> 1U)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready))))) 
                                    || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_e) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_n) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_s_ready)))))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__6(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__6\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n) 
                                       >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_w)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n) 
                                           >> 2U) & 
                                          ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_s)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n) 
                                               >> 1U) 
                                              & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_e)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_n) 
                                                 & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_n)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_s) 
                                               >> 3U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_e) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_w) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_n) 
                                                      >> 3U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.ready_out)))) 
                       | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_w) 
                                >> 4U) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_e_ready))) 
                           & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l) 
                              >> 3U)) | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_s) 
                                               >> 4U) 
                                              & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready))) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l) 
                                             >> 2U)) 
                                         | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_e) 
                                                  >> 4U) 
                                                 & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready))) 
                                             & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l) 
                                                >> 1U)) 
                                            | ((~ (
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_n) 
                                                    >> 4U) 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_s_ready))) 
                                               & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_l)))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_w) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_s) 
                                               >> 1U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_e) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_e) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_n) 
                                                      >> 1U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_w) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_s) 
                                               >> 2U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_e) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__req_s) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__grant_n) 
                                                      >> 2U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_s_ready)))))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__7(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__7\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_s) 
                                               >> 3U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready))))) 
                                   || (1U & (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_e) 
                                                  >> 3U)) 
                                              & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w) 
                                                 >> 1U)) 
                                             | ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_n) 
                                                  >> 3U)) 
                                                & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_w)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_w) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l) 
                               >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_s) 
                                             >> 4U)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready)))) 
                             | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_e) 
                                     >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l) 
                                                >> 1U)) 
                                | ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_n) 
                                       >> 4U)) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_l)))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_w) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_s) 
                                               >> 2U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready))))) 
                                   || (1U & (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_e) 
                                                  >> 2U)) 
                                              & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s) 
                                                 >> 1U)) 
                                             | ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_n) 
                                                  >> 2U)) 
                                                & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_s)))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__8(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__8\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.ready_out))))) 
                           || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_w)) 
                                      & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n) 
                                         >> 3U))) || 
                               ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_s)) 
                                       & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n) 
                                          >> 2U))) 
                                || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n) 
                                            >> 1U) 
                                           & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_e)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready))))) 
                                    || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_n) 
                                              & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_n)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.ready_out)))) 
                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_w) 
                               >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l) 
                                          >> 3U)) | 
                          (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_s) 
                                >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l) 
                                           >> 2U)) 
                           | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l) 
                                >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_e) 
                                              >> 4U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready)))) 
                              | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_l) 
                                 & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_n) 
                                        >> 4U)) | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.ready_out))))) 
                           || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_w) 
                                          >> 1U)) & 
                                      ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e) 
                                       >> 3U))) || 
                               ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_s) 
                                           >> 1U)) 
                                       & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e) 
                                          >> 2U))) 
                                || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e) 
                                            >> 1U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_e) 
                                                  >> 1U)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready))))) 
                                    || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_e) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_n) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_s_ready)))))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__9(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__9\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__ready_out_n 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_n) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n) 
                         >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_l)) 
                                   | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n) 
                            >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_w)) 
                                      | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n) 
                               >> 2U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_s)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready)))) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n) 
                                  >> 1U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_e)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready)))) 
                                | ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_n)) 
                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_n)))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__10(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__10\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__ready_out_w 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_w) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_l) 
                                       >> 3U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.ready_out)))) 
                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_w) 
                               >> 3U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w) 
                                          >> 3U)) | 
                          ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w) 
                             >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_s) 
                                           >> 3U)) 
                                       | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready)))) 
                           | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w) 
                                >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_e) 
                                              >> 3U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready)))) 
                              | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__req_w) 
                                 & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__grant_n) 
                                        >> 3U)) | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_s_ready)))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__11(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__11\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_s) 
                                               >> 3U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_e) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_w) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_n) 
                                                      >> 3U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n) 
                                       >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_w)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n) 
                                           >> 2U) & 
                                          ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_s)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n) 
                                               >> 1U) 
                                              & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_e)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_n) 
                                                 & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_n)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.ready_out)))) 
                       | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_w) 
                                >> 4U) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_e_ready))) 
                           & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l) 
                              >> 3U)) | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_s) 
                                               >> 4U) 
                                              & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready))) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l) 
                                             >> 2U)) 
                                         | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_e) 
                                                  >> 4U) 
                                                 & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready))) 
                                             & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l) 
                                                >> 1U)) 
                                            | ((~ (
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_n) 
                                                    >> 4U) 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_s_ready))) 
                                               & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_l)))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_w) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_s) 
                                               >> 1U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_e) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_e) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_n) 
                                                      >> 1U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_w) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_s) 
                                               >> 2U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_e) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__req_s) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__grant_n) 
                                                      >> 2U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_s_ready)))))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__12(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__12\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n) 
                                       >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_w)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n) 
                                           >> 2U) & 
                                          ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_s)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n) 
                                               >> 1U) 
                                              & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_e)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_n) 
                                                 & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_n)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_s) 
                                               >> 3U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_e) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_w) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_n) 
                                                      >> 3U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.ready_out)))) 
                       | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_w) 
                                >> 4U) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_e_ready))) 
                           & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l) 
                              >> 3U)) | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_s) 
                                               >> 4U) 
                                              & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready))) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l) 
                                             >> 2U)) 
                                         | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_e) 
                                                  >> 4U) 
                                                 & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready))) 
                                             & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l) 
                                                >> 1U)) 
                                            | ((~ (
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_n) 
                                                    >> 4U) 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_s_ready))) 
                                               & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_l)))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_w) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_s) 
                                               >> 2U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_e) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_s) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_n) 
                                                      >> 2U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_w) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_s) 
                                               >> 1U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_e) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__req_e) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__grant_n) 
                                                      >> 1U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_s_ready)))))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__13(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__13\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__ready_out_n 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_n) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n) 
                         >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_l)) 
                                   | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n) 
                            >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_w)) 
                                      | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n) 
                               >> 2U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_s)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready)))) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n) 
                                  >> 1U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_e)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready)))) 
                                | ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__grant_n)) 
                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__req_n)))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__14(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__14\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_s) 
                                               >> 3U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready))))) 
                                   || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_e) 
                                                  >> 3U)) 
                                              & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w) 
                                                 >> 1U))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_w) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_n) 
                                                      >> 3U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n) 
                                       >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_w)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n) 
                                           >> 2U) & 
                                          ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_s)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready))))) 
                                   || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_e)) 
                                              & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n) 
                                                 >> 1U))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_n) 
                                                 & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_n)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_w) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l) 
                               >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_s) 
                                             >> 4U)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready)))) 
                             | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_e) 
                                     >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l) 
                                                >> 1U)) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_l) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_n) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_w) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_s) 
                                               >> 2U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready))))) 
                                   || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_e) 
                                                  >> 2U)) 
                                              & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s) 
                                                 >> 1U))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_s) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_n) 
                                                      >> 2U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__ready_out_n 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_n) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n) 
                         >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_l)) 
                                   | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n) 
                            >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_w)) 
                                      | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n) 
                               >> 2U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_s)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready)))) 
                             | (((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_e)) 
                                 & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n) 
                                    >> 1U)) | ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_n)) 
                                               & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_n)))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__ready_out_e 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_e) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_l) 
                                       >> 1U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_w) 
                                          >> 1U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e) 
                               >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_s) 
                                             >> 1U)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready)))) 
                             | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_e) 
                                     >> 1U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e) 
                                                >> 1U)) 
                                | ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__grant_n) 
                                       >> 1U)) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__req_e)))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__15(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__15\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__ready_out_w 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_w) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_l) 
                                       >> 3U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.ready_out)))) 
                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_w) 
                               >> 3U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w) 
                                          >> 3U)) | 
                          ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w) 
                             >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_s) 
                                           >> 3U)) 
                                       | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready)))) 
                           | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w) 
                                >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_e) 
                                              >> 3U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready)))) 
                              | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__req_w) 
                                 & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__grant_n) 
                                        >> 3U)) | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_s_ready)))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__16(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__16\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n) 
                                       >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_w)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_e_ready))))) 
                               || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_s)) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n) 
                                             >> 2U))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n) 
                                               >> 1U) 
                                              & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_e)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_n) 
                                                 & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_n)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_e_ready))))) 
                               || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_s) 
                                              >> 3U)) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w) 
                                             >> 2U))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_e) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_w) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_n) 
                                                      >> 3U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_w) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_e_ready)))) 
                          | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_s) 
                                  >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l) 
                                             >> 2U)) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l) 
                                  >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_e) 
                                                >> 4U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready)))) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_l) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_n) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_w) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_e_ready))))) 
                               || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_s) 
                                              >> 1U)) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e) 
                                             >> 2U))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_e) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_e) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_n) 
                                                      >> 1U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__ready_out_s 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_s) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_l) 
                                       >> 2U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.ready_out)))) 
                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_w) 
                               >> 2U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s) 
                                          >> 3U)) | 
                          (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_s) 
                                >> 2U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s) 
                                           >> 2U)) 
                           | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s) 
                                >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_e) 
                                              >> 2U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready)))) 
                              | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_s) 
                                 & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_n) 
                                        >> 2U)) | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__ready_out_w 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_w) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_l) 
                                       >> 3U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.ready_out)))) 
                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_w) 
                               >> 3U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w) 
                                          >> 3U)) | 
                          (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_s) 
                                >> 3U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w) 
                                           >> 2U)) 
                           | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w) 
                                >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_e) 
                                              >> 3U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready)))) 
                              | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__req_w) 
                                 & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__grant_n) 
                                        >> 3U)) | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_s_ready)))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__17(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__17\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n) 
                                       >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_w)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n) 
                                           >> 2U) & 
                                          ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_s)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n) 
                                               >> 1U) 
                                              & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_e)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_n) 
                                                 & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_n)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_s) 
                                               >> 3U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_e) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_w) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_n) 
                                                      >> 3U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.ready_out)))) 
                       | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_w) 
                                >> 4U) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_e_ready))) 
                           & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l) 
                              >> 3U)) | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_s) 
                                               >> 4U) 
                                              & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready))) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l) 
                                             >> 2U)) 
                                         | (((~ (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_e) 
                                                  >> 4U) 
                                                 & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready))) 
                                             & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l) 
                                                >> 1U)) 
                                            | ((~ (
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_n) 
                                                    >> 4U) 
                                                   & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_s_ready))) 
                                               & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_l)))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_w) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_s) 
                                               >> 1U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_e) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_e) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_n) 
                                                      >> 1U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_w) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_s) 
                                               >> 2U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_e) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__req_s) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__grant_n) 
                                                      >> 2U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_s_ready)))))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__18(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__18\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_s) 
                                               >> 3U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready))))) 
                                   || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_e) 
                                                  >> 3U)) 
                                              & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w) 
                                                 >> 1U))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_w) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_n) 
                                                      >> 3U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n) 
                                       >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_w)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n) 
                                           >> 2U) & 
                                          ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_s)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready))))) 
                                   || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_e)) 
                                              & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n) 
                                                 >> 1U))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_n) 
                                                 & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_n)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_w) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l) 
                               >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_s) 
                                             >> 4U)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready)))) 
                             | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_e) 
                                     >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l) 
                                                >> 1U)) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_l) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_n) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_w) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_s) 
                                               >> 2U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready))))) 
                                   || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_e) 
                                                  >> 2U)) 
                                              & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s) 
                                                 >> 1U))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_s) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_n) 
                                                      >> 2U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__ready_out_e 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_e) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_l) 
                                       >> 1U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_w) 
                                          >> 1U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e) 
                               >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_s) 
                                             >> 1U)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready)))) 
                             | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_e) 
                                     >> 1U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e) 
                                                >> 1U)) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__req_e) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__grant_n) 
                                          >> 1U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_s_ready)))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__19(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__19\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                       >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready))))) 
                               || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s)) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                             >> 2U))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                               >> 1U) 
                                              & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                                 & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready))))) 
                               || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s) 
                                              >> 3U)) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                             >> 2U))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                                      >> 3U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready)))) 
                          | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s) 
                                  >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                             >> 2U)) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                  >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e) 
                                                >> 4U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready)))) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready))))) 
                               || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s) 
                                              >> 1U)) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                             >> 2U))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready))))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                                      >> 1U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__ready_out_s 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_s) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_l) 
                                       >> 2U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_w) 
                                          >> 2U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_e_ready)))) 
                          | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_s) 
                                  >> 2U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s) 
                                             >> 2U)) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s) 
                                  >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_e) 
                                                >> 2U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready)))) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__req_s) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__grant_n) 
                                          >> 2U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_s_ready)))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__20(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__20\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_n) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_n) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                     >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                       >> 3U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready))))) 
                               || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s)) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                             >> 2U))) 
                                   || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e)) 
                                              & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                                 >> 1U))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                                 & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready))))) 
                               || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                              >> 3U)) 
                                          & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                             >> 2U))) 
                                   || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                                  >> 3U)) 
                                              & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                                 >> 1U))) 
                                       || (1U & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                                 & ((~ 
                                                     ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                                      >> 3U)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready)))) 
                          | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                  >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                             >> 2U)) 
                             | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                     >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                                >> 1U)) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__ready_out_e 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_e) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_l) 
                                       >> 1U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_w) 
                                          >> 1U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e) 
                               >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_s) 
                                             >> 1U)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready)))) 
                             | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_e) 
                                     >> 1U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e) 
                                                >> 1U)) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__req_e) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__grant_n) 
                                          >> 1U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__ready_out_s 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_s) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                       >> 2U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
                                          >> 2U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready)))) 
                          | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s) 
                                  >> 2U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                             >> 2U)) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                  >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e) 
                                                >> 2U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready)))) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                          >> 2U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready)))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__21(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__21\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__ready_out_e 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_e) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                       >> 1U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                          >> 1U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready)))) 
                          | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                  >> 1U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                             >> 2U)) 
                             | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                     >> 1U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                                >> 1U)) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                          >> 1U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__ready_out_s 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_s) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                       >> 2U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                          >> 2U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready)))) 
                          | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                  >> 2U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                             >> 2U)) 
                             | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                     >> 2U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                                >> 1U)) 
                                | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                   & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                          >> 2U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))));
}

void Vtb_top___024root___nba_sequent__TOP__0(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___nba_sequent__TOP__1(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___nba_sequent__TOP__2(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__2(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_sequent__TOP__0(Vtb_top___024root* vlSelf);
void Vtb_top___024root___nba_sequent__TOP__3(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__3(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__0(Vtb_top___024root* vlSelf);
void Vtb_top___024root___act_comb__TOP__1(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___nba_sequent__TOP__4(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___nba_comb__TOP__7(Vtb_top___024root* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);

void Vtb_top___024root___eval_nba(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_nba\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0x10000000000ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x1bU] = 1U;
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe));
        Vtb_top___024root___nba_sequent__TOP__1(vlSelf);
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__1((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe));
    }
    if ((0x30000000000ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___nba_sequent__TOP__2(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x1cU] = 1U;
    }
    if ((0x50000000000ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
        vlSelfRef.__Vm_traceActivity[0x1dU] = 1U;
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe));
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe));
    }
    if ((0x10000000007ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_sequent__TOP__0(vlSelf);
    }
    if ((0x10000000000ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___nba_sequent__TOP__3(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x1eU] = 1U;
        Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__3((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
    }
    if ((0x790000000000ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
        Vtb_top___024root___act_comb__TOP__0(vlSelf);
    }
    if ((0x1000000003fULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__1(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x1fU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe));
    }
    if ((0x100000001c7ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__2(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x20U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe));
    }
    if ((0x30000000000ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___nba_sequent__TOP__4(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x21U] = 1U;
    }
    if ((0x10000000007ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top_cgra_pe__A4___act_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
    }
    if ((0x10000000e3fULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__3(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x22U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe));
    }
    if ((0x10001c001c7ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__5(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x23U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe));
    }
    if ((0x100000071ffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__6(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x24U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe));
    }
    if ((0x30000000000ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___nba_comb__TOP__7(vlSelf);
    }
    if ((0x100000001ffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__4(vlSelf);
    }
    if ((0x10000018e3fULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__7(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x25U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe));
    }
    if ((0x10601c001c7ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__8(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x26U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe));
    }
    if ((0x10000007fffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__9(vlSelf);
    }
    if ((0x10001c071ffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__10(vlSelf);
    }
    if ((0x100000e7fffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__11(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x27U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe));
    }
    if ((0x1000fc071ffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__12(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x28U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe));
    }
    if ((0x100000fffffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__13(vlSelf);
    }
    if ((0x100003fffffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__14(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x29U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe));
    }
    if ((0x1060fc071ffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__15(vlSelf);
    }
    if ((0x11e0fc071ffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__16(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x2aU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe));
    }
    if ((0x1007fce7fffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__17(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x2bU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe));
    }
    if ((0x101ffffffffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__18(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x2cU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe));
    }
    if ((0x17e7fce7fffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__19(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x2dU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe));
    }
    if ((0x1ffffffffffULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__20(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x2eU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe));
        Vtb_top___024root___act_comb__TOP__21(vlSelf);
    }
}

extern const VlUnpacked<CData/*1:0*/, 32> Vtb_top__ConstPool__TABLE_h196aa701_0;
extern const VlUnpacked<CData/*0:0*/, 32> Vtb_top__ConstPool__TABLE_h1fea15fc_0;
extern const VlUnpacked<CData/*0:0*/, 32> Vtb_top__ConstPool__TABLE_hc6bef776_0;

VL_INLINE_OPT void Vtb_top___024root___nba_sequent__TOP__0(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___nba_sequent__TOP__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*4:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    IData/*31:0*/ __Vdly__tb_top__DOT__ar_stall_cycles;
    __Vdly__tb_top__DOT__ar_stall_cycles = 0;
    CData/*4:0*/ __Vdly__tb_top__DOT__u_dut__DOT__auto_stop_counter;
    __Vdly__tb_top__DOT__u_dut__DOT__auto_stop_counter = 0;
    CData/*2:0*/ __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr;
    __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr = 0;
    CData/*0:0*/ __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active;
    __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active = 0;
    CData/*0:0*/ __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started;
    __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started = 0;
    IData/*31:0*/ __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count;
    __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count = 0;
    IData/*31:0*/ __Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter;
    __Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter = 0;
    CData/*7:0*/ __VdlyVal__tb_top__DOT__mem__v0;
    __VdlyVal__tb_top__DOT__mem__v0 = 0;
    IData/*16:0*/ __VdlyDim0__tb_top__DOT__mem__v0;
    __VdlyDim0__tb_top__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__mem__v0;
    __VdlySet__tb_top__DOT__mem__v0 = 0;
    CData/*7:0*/ __VdlyVal__tb_top__DOT__mem__v1;
    __VdlyVal__tb_top__DOT__mem__v1 = 0;
    IData/*16:0*/ __VdlyDim0__tb_top__DOT__mem__v1;
    __VdlyDim0__tb_top__DOT__mem__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__mem__v1;
    __VdlySet__tb_top__DOT__mem__v1 = 0;
    CData/*7:0*/ __VdlyVal__tb_top__DOT__mem__v2;
    __VdlyVal__tb_top__DOT__mem__v2 = 0;
    IData/*16:0*/ __VdlyDim0__tb_top__DOT__mem__v2;
    __VdlyDim0__tb_top__DOT__mem__v2 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__mem__v2;
    __VdlySet__tb_top__DOT__mem__v2 = 0;
    CData/*7:0*/ __VdlyVal__tb_top__DOT__mem__v3;
    __VdlyVal__tb_top__DOT__mem__v3 = 0;
    IData/*16:0*/ __VdlyDim0__tb_top__DOT__mem__v3;
    __VdlyDim0__tb_top__DOT__mem__v3 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__mem__v3;
    __VdlySet__tb_top__DOT__mem__v3 = 0;
    QData/*63:0*/ __VdlyVal__tb_top__DOT__u_dut__DOT__config_frames__v0;
    __VdlyVal__tb_top__DOT__u_dut__DOT__config_frames__v0 = 0;
    CData/*3:0*/ __VdlyDim0__tb_top__DOT__u_dut__DOT__config_frames__v0;
    __VdlyDim0__tb_top__DOT__u_dut__DOT__config_frames__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__u_dut__DOT__config_frames__v0;
    __VdlySet__tb_top__DOT__u_dut__DOT__config_frames__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__u_dut__DOT__config_frames__v1;
    __VdlySet__tb_top__DOT__u_dut__DOT__config_frames__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0;
    __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0 = 0;
    SData/*9:0*/ __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0;
    __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0 = 0;
    SData/*9:0*/ __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v1;
    __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v1;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0;
    __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0 = 0;
    SData/*9:0*/ __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0;
    __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0 = 0;
    SData/*9:0*/ __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v1;
    __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v1;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0;
    __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0 = 0;
    SData/*9:0*/ __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0;
    __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0 = 0;
    SData/*9:0*/ __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v1;
    __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v1;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0;
    __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0 = 0;
    SData/*9:0*/ __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0;
    __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0 = 0;
    SData/*9:0*/ __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v1;
    __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v1;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v1 = 0;
    // Body
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl;
    __Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter;
    __Vdly__tb_top__DOT__u_dut__DOT__auto_stop_counter 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__auto_stop_counter;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__r_ptr 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__r_ptr;
    __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count;
    __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr;
    vlSelfRef.__VdlySet__tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_mem__v0 = 0U;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__count 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__r_state 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__r_state;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__current_burst_len 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__current_burst_len;
    vlSelfRef.__Vdly__tb_top__DOT__axi_arvalid = vlSelfRef.tb_top__DOT__axi_arvalid;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__read_addr 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__read_addr;
    vlSelfRef.__Vdly__tb_top__DOT__axi_rready = vlSelfRef.tb_top__DOT__axi_rready;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__read_words_remaining 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__read_words_remaining;
    __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active;
    __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__w_state 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_state;
    vlSelfRef.__Vdly__tb_top__DOT__axi_awvalid = vlSelfRef.tb_top__DOT__axi_awvalid;
    vlSelfRef.__Vdly__tb_top__DOT__axi_wvalid = vlSelfRef.tb_top__DOT__axi_wvalid;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__write_words_remaining 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__write_words_remaining;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__write_addr 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__write_addr;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0 = 0U;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v1 = 0U;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0 = 0U;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v1 = 0U;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0 = 0U;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v1 = 0U;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0 = 0U;
    __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v1 = 0U;
    vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__dma_busy 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__dma_busy;
    __VdlySet__tb_top__DOT__mem__v0 = 0U;
    __VdlySet__tb_top__DOT__mem__v1 = 0U;
    __VdlySet__tb_top__DOT__mem__v2 = 0U;
    __VdlySet__tb_top__DOT__mem__v3 = 0U;
    __Vdly__tb_top__DOT__ar_stall_cycles = vlSelfRef.tb_top__DOT__ar_stall_cycles;
    __VdlySet__tb_top__DOT__u_dut__DOT__config_frames__v0 = 0U;
    __VdlySet__tb_top__DOT__u_dut__DOT__config_frames__v1 = 0U;
    vlSelfRef.tb_top__DOT__cycle_count = ((IData)(1U) 
                                          + vlSelfRef.tb_top__DOT__cycle_count);
    if ((1U & (~ (IData)(vlSelfRef.tb_top__DOT__rst_n)))) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__unnamedblk1__DOT__i = 0x10U;
    }
    if (vlSelfRef.tb_top__DOT__rst_n) {
        if ((((IData)(vlSelfRef.tb_top__DOT__psel) 
              & (IData)(vlSelfRef.tb_top__DOT__penable)) 
             & (IData)(vlSelfRef.tb_top__DOT__pwrite))) {
            if ((0U == (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl 
                    = vlSelfRef.tb_top__DOT__pwdata;
            }
            if ((0U != (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                if ((8U != (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                    if ((0xcU != (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                        if ((0x10U != (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                            if ((0x20U == (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                                vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl 
                                    = vlSelfRef.tb_top__DOT__pwdata;
                            }
                        }
                    }
                }
            }
        } else {
            if ((1U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl)) {
                vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl 
                    = (0xfffffffeU & vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl);
            }
            if ((1U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl)) {
                vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl 
                    = (0xfffffffeU & vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl);
            }
        }
        if (((0U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state)) 
             & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl)) {
            __Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter = 0U;
        } else if ((1U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state))) {
            __Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter);
        }
        if ((2U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl)) {
            __Vdly__tb_top__DOT__u_dut__DOT__auto_stop_counter = 0U;
        } else if ((1U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl)) {
            __Vdly__tb_top__DOT__u_dut__DOT__auto_stop_counter = 0U;
        } else if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__pe_enable) 
                    & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__auto_stop_armed))) {
            __Vdly__tb_top__DOT__u_dut__DOT__auto_stop_counter 
                = (0x1fU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__auto_stop_counter)));
        }
        if ((1U & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl 
                   & (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__dma_busy))))) {
            vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__r_ptr = 0U;
        } else if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_pop) {
            vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__r_ptr 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__r_ptr)));
        }
    } else {
        vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl = 0U;
        vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl = 0U;
        __Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter = 0U;
        __Vdly__tb_top__DOT__u_dut__DOT__auto_stop_counter = 0U;
        vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__r_ptr = 0U;
    }
    if (vlSelfRef.tb_top__DOT__rst_n) {
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__dma_busy) {
            __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count);
            if (VL_UNLIKELY((VL_LTS_III(32, 0x186a0U, vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count)))) {
                VL_WRITEF_NX("[%0t] %%Error: cgra_dma_engine.sv:554: Assertion failed in %Ntb_top.u_dut.u_dma: [DMA ASSERT] FSM Deadlock - busy stuck for 100000+ cycles!\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name());
                VL_STOP_MT("00_src/cgra_dma_engine.sv", 554, "");
            }
        } else {
            __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count = 0U;
        }
        if (VL_UNLIKELY(((((IData)(vlSelfRef.tb_top__DOT__axi_rvalid_reg) 
                           & (IData)(vlSelfRef.tb_top__DOT__axi_rready)) 
                          & (8U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count)))))) {
            VL_WRITEF_NX("[%0t] %%Error: cgra_dma_engine.sv:562: Assertion failed in %Ntb_top.u_dut.u_dma: [DMA ASSERT] CRITICAL: FIFO Overflow - push when full!\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name());
            VL_STOP_MT("00_src/cgra_dma_engine.sv", 562, "");
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_pop) 
                          & (0U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count)))))) {
            VL_WRITEF_NX("[%0t] %%Error: cgra_dma_engine.sv:569: Assertion failed in %Ntb_top.u_dut.u_dma: [DMA ASSERT] CRITICAL: FIFO Underflow - pop when empty!\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name());
            VL_STOP_MT("00_src/cgra_dma_engine.sv", 569, "");
        }
        if (VL_UNLIKELY(((8U < (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count))))) {
            VL_WRITEF_NX("[%0t] %%Error: cgra_dma_engine.sv:574: Assertion failed in %Ntb_top.u_dut.u_dma: [DMA ASSERT] FIFO count exceeded depth: %0# > 8\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),4,(IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count));
            VL_STOP_MT("00_src/cgra_dma_engine.sv", 574, "");
        }
        if (VL_UNLIKELY((((((0U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__r_state)) 
                            & (1U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__r_state))) 
                           & (2U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__r_state))) 
                          & (3U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__r_state)))))) {
            VL_WRITEF_NX("[%0t] %%Error: cgra_dma_engine.sv:580: Assertion failed in %Ntb_top.u_dut.u_dma: [DMA ASSERT] Read FSM in invalid state: %0#\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__r_state));
            VL_STOP_MT("00_src/cgra_dma_engine.sv", 580, "");
        }
        if (VL_UNLIKELY((((((((0U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_state)) 
                              & (1U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_state))) 
                             & (2U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_state))) 
                            & (3U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_state))) 
                           & (4U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_state))) 
                          & (5U != (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_state)))))) {
            VL_WRITEF_NX("[%0t] %%Error: cgra_dma_engine.sv:586: Assertion failed in %Ntb_top.u_dut.u_dma: [DMA ASSERT] Write FSM in invalid state: %0#\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),3,(IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_state));
            VL_STOP_MT("00_src/cgra_dma_engine.sv", 586, "");
        }
    } else {
        __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count = 0U;
    }
    if (((IData)(vlSelfRef.tb_top__DOT__axi_wvalid) 
         & (IData)(vlSelfRef.tb_top__DOT__axi_wready_reg))) {
        vlSelfRef.tb_top__DOT__unnamedblk6__DOT__target_addr 
            = (((IData)(vlSelfRef.tb_top__DOT__axi_awvalid) 
                & (IData)(vlSelfRef.tb_top__DOT__axi_awready_reg))
                ? vlSelfRef.tb_top__DOT__axi_awaddr
                : vlSelfRef.tb_top__DOT__axi_waddr_latch);
        if ((1U & (IData)(vlSelfRef.tb_top__DOT__axi_wstrb))) {
            __VdlyVal__tb_top__DOT__mem__v0 = (0xffU 
                                               & vlSelfRef.tb_top__DOT__axi_wdata);
            __VdlyDim0__tb_top__DOT__mem__v0 = (0x1ffffU 
                                                & vlSelfRef.tb_top__DOT__unnamedblk6__DOT__target_addr);
            __VdlySet__tb_top__DOT__mem__v0 = 1U;
        }
        if ((2U & (IData)(vlSelfRef.tb_top__DOT__axi_wstrb))) {
            __VdlyVal__tb_top__DOT__mem__v1 = (0xffU 
                                               & (vlSelfRef.tb_top__DOT__axi_wdata 
                                                  >> 8U));
            __VdlyDim0__tb_top__DOT__mem__v1 = (0x1ffffU 
                                                & ((IData)(1U) 
                                                   + vlSelfRef.tb_top__DOT__unnamedblk6__DOT__target_addr));
            __VdlySet__tb_top__DOT__mem__v1 = 1U;
        }
        if ((4U & (IData)(vlSelfRef.tb_top__DOT__axi_wstrb))) {
            __VdlyVal__tb_top__DOT__mem__v2 = (0xffU 
                                               & (vlSelfRef.tb_top__DOT__axi_wdata 
                                                  >> 0x10U));
            __VdlyDim0__tb_top__DOT__mem__v2 = (0x1ffffU 
                                                & ((IData)(2U) 
                                                   + vlSelfRef.tb_top__DOT__unnamedblk6__DOT__target_addr));
            __VdlySet__tb_top__DOT__mem__v2 = 1U;
        }
        if ((8U & (IData)(vlSelfRef.tb_top__DOT__axi_wstrb))) {
            __VdlyVal__tb_top__DOT__mem__v3 = (vlSelfRef.tb_top__DOT__axi_wdata 
                                               >> 0x18U);
            __VdlyDim0__tb_top__DOT__mem__v3 = (0x1ffffU 
                                                & ((IData)(3U) 
                                                   + vlSelfRef.tb_top__DOT__unnamedblk6__DOT__target_addr));
            __VdlySet__tb_top__DOT__mem__v3 = 1U;
        }
    }
    if (vlSelfRef.tb_top__DOT__rst_n) {
        if ((1U & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl 
                   & (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__dma_busy))))) {
            __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr = 0U;
            vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__count = 0U;
        } else {
            if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_push) {
                vlSelfRef.__VdlyVal__tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_mem__v0 
                    = (((vlSelfRef.tb_top__DOT__mem
                         [(0x1ffffU & ((IData)(3U) 
                                       + vlSelfRef.tb_top__DOT__r_addr_reg))] 
                         << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                      [(0x1ffffU & 
                                        ((IData)(2U) 
                                         + vlSelfRef.tb_top__DOT__r_addr_reg))] 
                                      << 0x10U)) | 
                       ((vlSelfRef.tb_top__DOT__mem
                         [(0x1ffffU & ((IData)(1U) 
                                       + vlSelfRef.tb_top__DOT__r_addr_reg))] 
                         << 8U) | vlSelfRef.tb_top__DOT__mem
                        [(0x1ffffU & vlSelfRef.tb_top__DOT__r_addr_reg)]));
                vlSelfRef.__VdlyDim0__tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_mem__v0 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr;
                vlSelfRef.__VdlySet__tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_mem__v0 = 1U;
                __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr 
                    = (7U & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr)));
            }
            if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_push) 
                 & (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_pop)))) {
                vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__count 
                    = (0xfU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count)));
            } else if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_pop) 
                        & (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_push)))) {
                vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__count 
                    = (0xfU & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count) 
                               - (IData)(1U)));
            }
        }
        if ((2U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl)) {
            vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter = 0U;
        } else if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__pe_enable) 
                    & (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__dma_busy)))) {
            vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter 
                = ((0xfU == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter))
                    ? 0U : (0xfU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter))));
        }
        if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__ext_write) 
             & (0U == (0x3000U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
            if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__ext_write) 
                 & (0U == (0x3000U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
                __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__write_data_reg;
                __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0 
                    = (0x3ffU & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr);
                __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0 = 1U;
            } else {
                __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v1 
                    = (0x3ffU & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter));
                __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v1 = 1U;
            }
        }
        if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__ext_write) 
             & (0x1000U == (0x3000U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
            if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__ext_write) 
                 & (0x1000U == (0x3000U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
                __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__write_data_reg;
                __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0 
                    = (0x3ffU & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr);
                __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0 = 1U;
            } else {
                __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v1 
                    = (0x3ffU & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter));
                __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v1 = 1U;
            }
        }
        if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__ext_write) 
             & (0x2000U == (0x3000U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
            if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__ext_write) 
                 & (0x2000U == (0x3000U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
                __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__write_data_reg;
                __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0 
                    = (0x3ffU & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr);
                __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0 = 1U;
            } else {
                __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v1 
                    = (0x3ffU & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter));
                __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v1 = 1U;
            }
        }
        if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__ext_write) 
             & (0x3000U == (0x3000U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
            if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__ext_write) 
                 & (0x3000U == (0x3000U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
                __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__write_data_reg;
                __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0 
                    = (0x3ffU & vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr);
                __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0 = 1U;
            } else {
                __VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v1 
                    = (0x3ffU & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter));
                __VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v1 = 1U;
            }
        }
    } else {
        __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr = 0U;
        vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__count = 0U;
        vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter = 0U;
    }
    if (vlSelfRef.tb_top__DOT__rst_n) {
        if (((IData)(vlSelfRef.tb_top__DOT__ar_pending) 
             & (~ (IData)(vlSelfRef.tb_top__DOT__axi_arready_reg)))) {
            if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.tb_top__DOT__axi_arvalid)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_protocol_checkers.svh:45: Assertion failed in %Ntb_top: [AXI] ARVALID dropped before ARREADY @ %0t\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9);
                vlSelfRef.tb_top__DOT__assertion_errors 
                    = ((IData)(1U) + vlSelfRef.tb_top__DOT__assertion_errors);
                VL_STOP_MT("01_bench/include/tb_protocol_checkers.svh", 45, "");
            }
            if (VL_UNLIKELY(((vlSelfRef.tb_top__DOT__axi_araddr 
                              != vlSelfRef.tb_top__DOT__ar_addr_lock)))) {
                vlSelfRef.tb_top__DOT__assertion_errors 
                    = ((IData)(1U) + vlSelfRef.tb_top__DOT__assertion_errors);
                VL_WRITEF_NX("[%0t] %%Error: tb_protocol_checkers.svh:49: Assertion failed in %Ntb_top: [AXI] ARADDR unstable: was 0x%x, now 0x%x @ %0t\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),32,
                             vlSelfRef.tb_top__DOT__ar_addr_lock,
                             32,vlSelfRef.tb_top__DOT__axi_araddr,
                             64,VL_TIME_UNITED_Q(1000),
                             -9);
                VL_STOP_MT("01_bench/include/tb_protocol_checkers.svh", 49, "");
            }
            __Vdly__tb_top__DOT__ar_stall_cycles = 
                ((IData)(1U) + vlSelfRef.tb_top__DOT__ar_stall_cycles);
            if (VL_UNLIKELY((VL_LTES_III(32, 0x3e8U, vlSelfRef.tb_top__DOT__ar_stall_cycles)))) {
                VL_WRITEF_NX("[%0t] %%Warning: tb_protocol_checkers.svh:55: %Ntb_top: [AXI] AR channel stalled for %0d cycles\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),32,
                             vlSelfRef.tb_top__DOT__ar_stall_cycles);
            }
        }
        if (((IData)(vlSelfRef.tb_top__DOT__axi_rvalid_reg) 
             & (IData)(vlSelfRef.tb_top__DOT__axi_rready))) {
            vlSelfRef.tb_top__DOT__r_txn_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__r_txn_count);
        }
        if (((IData)(vlSelfRef.tb_top__DOT__axi_bvalid_reg) 
             & (IData)(vlSelfRef.tb_top__DOT__axi_bready))) {
            vlSelfRef.tb_top__DOT__b_txn_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__b_txn_count);
        }
        if ((((IData)(vlSelfRef.tb_top__DOT__axi_arvalid) 
              & (~ (IData)(vlSelfRef.tb_top__DOT__axi_arready_reg))) 
             & (~ (IData)(vlSelfRef.tb_top__DOT__ar_pending)))) {
            vlSelfRef.tb_top__DOT__ar_pending = 1U;
            vlSelfRef.tb_top__DOT__ar_addr_lock = vlSelfRef.tb_top__DOT__axi_araddr;
            __Vdly__tb_top__DOT__ar_stall_cycles = 0U;
        } else if (((IData)(vlSelfRef.tb_top__DOT__axi_arvalid) 
                    & (IData)(vlSelfRef.tb_top__DOT__axi_arready_reg))) {
            vlSelfRef.tb_top__DOT__ar_txn_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_top__DOT__ar_txn_count);
            vlSelfRef.tb_top__DOT__ar_pending = 0U;
            __Vdly__tb_top__DOT__ar_stall_cycles = 0U;
        }
        if (((IData)(vlSelfRef.tb_top__DOT__aw_pending) 
             & (~ (IData)(vlSelfRef.tb_top__DOT__axi_awready_reg)))) {
            if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.tb_top__DOT__axi_awvalid)))))) {
                vlSelfRef.tb_top__DOT__assertion_errors 
                    = ((IData)(1U) + vlSelfRef.tb_top__DOT__assertion_errors);
                VL_WRITEF_NX("[%0t] %%Error: tb_protocol_checkers.svh:74: Assertion failed in %Ntb_top: [AXI] AWVALID dropped before AWREADY @ %0t\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9);
                VL_STOP_MT("01_bench/include/tb_protocol_checkers.svh", 74, "");
            }
            vlSelfRef.tb_top__DOT__aw_stall_cycles 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__aw_stall_cycles);
            if (VL_UNLIKELY(((vlSelfRef.tb_top__DOT__axi_awaddr 
                              != vlSelfRef.tb_top__DOT__aw_addr_lock)))) {
                vlSelfRef.tb_top__DOT__assertion_errors 
                    = ((IData)(1U) + vlSelfRef.tb_top__DOT__assertion_errors);
                VL_WRITEF_NX("[%0t] %%Error: tb_protocol_checkers.svh:78: Assertion failed in %Ntb_top: [AXI] AWADDR unstable @ %0t\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9);
                VL_STOP_MT("01_bench/include/tb_protocol_checkers.svh", 78, "");
            }
        }
        if ((((IData)(vlSelfRef.tb_top__DOT__axi_awvalid) 
              & (~ (IData)(vlSelfRef.tb_top__DOT__axi_awready_reg))) 
             & (~ (IData)(vlSelfRef.tb_top__DOT__aw_pending)))) {
            vlSelfRef.tb_top__DOT__aw_stall_cycles = 0U;
            vlSelfRef.tb_top__DOT__aw_pending = 1U;
            vlSelfRef.tb_top__DOT__aw_addr_lock = vlSelfRef.tb_top__DOT__axi_awaddr;
        } else if (((IData)(vlSelfRef.tb_top__DOT__axi_awvalid) 
                    & (IData)(vlSelfRef.tb_top__DOT__axi_awready_reg))) {
            vlSelfRef.tb_top__DOT__aw_txn_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_top__DOT__aw_txn_count);
            vlSelfRef.tb_top__DOT__aw_stall_cycles = 0U;
            vlSelfRef.tb_top__DOT__aw_pending = 0U;
        }
        if (((IData)(vlSelfRef.tb_top__DOT__w_pending) 
             & (~ (IData)(vlSelfRef.tb_top__DOT__axi_wready_reg)))) {
            if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.tb_top__DOT__axi_wvalid)))))) {
                vlSelfRef.tb_top__DOT__assertion_errors 
                    = ((IData)(1U) + vlSelfRef.tb_top__DOT__assertion_errors);
                VL_WRITEF_NX("[%0t] %%Error: tb_protocol_checkers.svh:99: Assertion failed in %Ntb_top: [AXI] WVALID dropped before WREADY @ %0t\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9);
                VL_STOP_MT("01_bench/include/tb_protocol_checkers.svh", 99, "");
            }
            vlSelfRef.tb_top__DOT__w_stall_cycles = 
                ((IData)(1U) + vlSelfRef.tb_top__DOT__w_stall_cycles);
            if (VL_UNLIKELY(((vlSelfRef.tb_top__DOT__axi_wdata 
                              != vlSelfRef.tb_top__DOT__w_data_lock)))) {
                vlSelfRef.tb_top__DOT__assertion_errors 
                    = ((IData)(1U) + vlSelfRef.tb_top__DOT__assertion_errors);
                VL_WRITEF_NX("[%0t] %%Error: tb_protocol_checkers.svh:103: Assertion failed in %Ntb_top: [AXI] WDATA unstable @ %0t\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),64,
                             VL_TIME_UNITED_Q(1000),
                             -9);
                VL_STOP_MT("01_bench/include/tb_protocol_checkers.svh", 103, "");
            }
        }
        if ((((IData)(vlSelfRef.tb_top__DOT__axi_wvalid) 
              & (~ (IData)(vlSelfRef.tb_top__DOT__axi_wready_reg))) 
             & (~ (IData)(vlSelfRef.tb_top__DOT__w_pending)))) {
            vlSelfRef.tb_top__DOT__w_stall_cycles = 0U;
            vlSelfRef.tb_top__DOT__w_pending = 1U;
            vlSelfRef.tb_top__DOT__w_data_lock = vlSelfRef.tb_top__DOT__axi_wdata;
        } else if (((IData)(vlSelfRef.tb_top__DOT__axi_wvalid) 
                    & (IData)(vlSelfRef.tb_top__DOT__axi_wready_reg))) {
            vlSelfRef.tb_top__DOT__w_txn_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__w_txn_count);
            vlSelfRef.tb_top__DOT__w_stall_cycles = 0U;
            vlSelfRef.tb_top__DOT__w_pending = 0U;
        }
    } else if ((1U & (~ (IData)(vlSelfRef.tb_top__DOT__rst_n)))) {
        vlSelfRef.tb_top__DOT__aw_stall_cycles = 0U;
        vlSelfRef.tb_top__DOT__w_stall_cycles = 0U;
        vlSelfRef.tb_top__DOT__ar_pending = 0U;
        vlSelfRef.tb_top__DOT__aw_pending = 0U;
        vlSelfRef.tb_top__DOT__w_pending = 0U;
        __Vdly__tb_top__DOT__ar_stall_cycles = 0U;
    }
    if ((1U & (~ (IData)(vlSelfRef.tb_top__DOT__rst_n)))) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__dma_tile_rdata = 0U;
        vlSelfRef.tb_top__DOT__axi_wstrb = 0xfU;
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__ext_read_reg = 0U;
    vlSelfRef.tb_top__DOT__u_dut__DOT__pe_reset_n = 
        ((1U & (~ (IData)(vlSelfRef.tb_top__DOT__rst_n))) 
         || (1U & (~ (vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl 
                      >> 1U))));
    vlSelfRef.tb_top__DOT__irq_done = ((IData)(vlSelfRef.tb_top__DOT__rst_n) 
                                       && (0U != (vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_irq_status 
                                                  & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_irq_mask)));
    if ((1U & (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n)))) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_l = 0U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__ready_out_e) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_e = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__ready_out_s) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_s = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.valid_in_e) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__ready_out_e) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_e = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__ready_out_s) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_s = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.valid_in_e) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.valid_in_e) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.valid_in_e) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__ready_out_e) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_e = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__ready_out_s) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_s = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.valid_in_s) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.valid_in_e) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__ready_out_n) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_n = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__ready_out_e) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_e = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__ready_out_s) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_s = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__ready_out_w) {
            if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_read_reg) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_w 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank3_rdata;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.valid_in_e) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.valid_in_e) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.valid_in_e) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__ready_out_n) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_n = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__ready_out_w) {
            if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_read_reg) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_w 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank2_rdata;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.valid_in_s) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__ready_out_n) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_n = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_w 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_n = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_n 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__output_data;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_n = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__ready_out_w) {
            if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_read_reg) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_w 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank1_rdata;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__ready_out_n) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_n = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__ready_out_w) {
            if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_read_reg) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_w = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_w 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank0_rdata;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_w = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__router_to_pe_ready) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_l = 0U;
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_e_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_e 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_e = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_e = 0U;
            }
        }
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_s_ready) {
            if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.valid_in_n) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_s 
                    = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__output_data;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_s = 1U;
            } else {
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_s = 0U;
            }
        }
    } else {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_n = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_l = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_w = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_data_s = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_e = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_s = 0U;
    }
    __Vtableidx1 = ((((4U & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl 
                             << 2U)) | (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__cu_done) 
                                         << 1U) | (1U 
                                                   & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl))) 
                     << 2U) | (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__dma_done) 
                                << 1U) | (IData)(vlSelfRef.tb_top__DOT__rst_n)));
    if ((1U & Vtb_top__ConstPool__TABLE_h196aa701_0
         [__Vtableidx1])) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__dma_done_latch 
            = Vtb_top__ConstPool__TABLE_h1fea15fc_0
            [__Vtableidx1];
    }
    if ((2U & Vtb_top__ConstPool__TABLE_h196aa701_0
         [__Vtableidx1])) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__cu_done_latch 
            = Vtb_top__ConstPool__TABLE_hc6bef776_0
            [__Vtableidx1];
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__cu_busy = ((IData)(vlSelfRef.tb_top__DOT__rst_n) 
                                                  && (1U 
                                                      == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state)));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter 
        = __Vdly__tb_top__DOT__u_dut__DOT__u_cu__DOT__cycle_counter;
    vlSelfRef.tb_top__DOT__u_dut__DOT__auto_stop_counter 
        = __Vdly__tb_top__DOT__u_dut__DOT__auto_stop_counter;
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count 
        = __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__busy_cycle_count;
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr 
        = __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__w_ptr;
    if (__VdlySet__tb_top__DOT__mem__v0) {
        vlSelfRef.tb_top__DOT__mem[__VdlyDim0__tb_top__DOT__mem__v0] 
            = __VdlyVal__tb_top__DOT__mem__v0;
    }
    if (__VdlySet__tb_top__DOT__mem__v1) {
        vlSelfRef.tb_top__DOT__mem[__VdlyDim0__tb_top__DOT__mem__v1] 
            = __VdlyVal__tb_top__DOT__mem__v1;
    }
    if (__VdlySet__tb_top__DOT__mem__v2) {
        vlSelfRef.tb_top__DOT__mem[__VdlyDim0__tb_top__DOT__mem__v2] 
            = __VdlyVal__tb_top__DOT__mem__v2;
    }
    if (__VdlySet__tb_top__DOT__mem__v3) {
        vlSelfRef.tb_top__DOT__mem[__VdlyDim0__tb_top__DOT__mem__v3] 
            = __VdlyVal__tb_top__DOT__mem__v3;
    }
    vlSelfRef.tb_top__DOT__ar_stall_cycles = __Vdly__tb_top__DOT__ar_stall_cycles;
    if (vlSelfRef.tb_top__DOT__rst_n) {
        if (vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) {
            __VdlyVal__tb_top__DOT__u_dut__DOT__config_frames__v0 
                = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
            __VdlyDim0__tb_top__DOT__u_dut__DOT__config_frames__v0 
                = (0xfU & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                           >> 8U));
            __VdlySet__tb_top__DOT__u_dut__DOT__config_frames__v0 = 1U;
        }
    } else {
        __VdlySet__tb_top__DOT__u_dut__DOT__config_frames__v1 = 1U;
    }
    if (__VdlySet__tb_top__DOT__u_dut__DOT__config_frames__v0) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[__VdlyDim0__tb_top__DOT__u_dut__DOT__config_frames__v0] 
            = __VdlyVal__tb_top__DOT__u_dut__DOT__config_frames__v0;
    }
    if (__VdlySet__tb_top__DOT__u_dut__DOT__config_frames__v1) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[0U] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[1U] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[2U] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[3U] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[4U] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[5U] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[6U] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[7U] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[8U] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[9U] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[0xaU] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[0xbU] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[0xcU] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[0xdU] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[0xeU] = 0ULL;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_frames[0xfU] = 0ULL;
    }
    vlSelfRef.tb_top__DOT__u_dut__DOT__pe_enable = 
        ((IData)(vlSelfRef.tb_top__DOT__rst_n) && (1U 
                                                   == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state)));
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
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_irq_status 
        = (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__cu_done_latch) 
            << 1U) | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__dma_done_latch));
    vlSelfRef.tb_top__DOT__u_dut__DOT__cu_done = ((IData)(vlSelfRef.tb_top__DOT__rst_n) 
                                                  && (2U 
                                                      == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state)));
    if (vlSelfRef.tb_top__DOT__rst_n) {
        if ((((IData)(vlSelfRef.tb_top__DOT__psel) 
              & (IData)(vlSelfRef.tb_top__DOT__penable)) 
             & (IData)(vlSelfRef.tb_top__DOT__pwrite))) {
            if ((0U != (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                if ((8U != (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                    if ((0xcU != (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                        if ((0x10U != (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                            if ((0x20U != (0xffU & vlSelfRef.tb_top__DOT__paddr))) {
                                if ((0x2cU == (0xffU 
                                               & vlSelfRef.tb_top__DOT__paddr))) {
                                    vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_timeout 
                                        = vlSelfRef.tb_top__DOT__pwdata;
                                }
                                if ((0x2cU != (0xffU 
                                               & vlSelfRef.tb_top__DOT__paddr))) {
                                    if ((0x34U == (0xffU 
                                                   & vlSelfRef.tb_top__DOT__paddr))) {
                                        vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_irq_mask 
                                            = vlSelfRef.tb_top__DOT__pwdata;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__config_we_o) 
             & (vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                >> 2U))) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__config_high_reg 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__write_data_reg;
        }
        if ((2U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl)) {
            vlSelfRef.tb_top__DOT__u_dut__DOT__auto_stop_armed = 0U;
            __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active = 0U;
            __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started = 0U;
            vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__dma_busy = 0U;
            vlSelfRef.tb_top__DOT__u_dut__DOT__dma_done = 0U;
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__irq_done = 0U;
        } else {
            if ((1U & vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_ctrl)) {
                vlSelfRef.tb_top__DOT__u_dut__DOT__auto_stop_armed = 1U;
            }
            vlSelfRef.tb_top__DOT__u_dut__DOT__dma_done = 0U;
            vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__irq_done = 0U;
            if (((vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_ctrl 
                  & (0U != vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_dma_size)) 
                 & (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__dma_busy)))) {
                __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active = 1U;
                __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started = 0U;
                vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__dma_busy = 1U;
            } else if (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active) 
                        & (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started)))) {
                __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started = 1U;
            } else if ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active) 
                         & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started)) 
                        & ((0U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__r_state)) 
                           & ((0U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__w_state)) 
                              & (0U == (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__count)))))) {
                __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active = 0U;
                __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started = 0U;
                vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__dma_busy = 0U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__dma_done = 1U;
                vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__irq_done = 1U;
            }
        }
        vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank3_rdata 
            = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem
            [(0x3ffU & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter))];
        vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank2_rdata 
            = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem
            [(0x3ffU & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter))];
        vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank1_rdata 
            = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem
            [(0x3ffU & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter))];
        vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank0_rdata 
            = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem
            [(0x3ffU & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter))];
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state 
            = vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state_next;
    } else {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_cu_timeout = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__config_high_reg = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__auto_stop_armed = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__reg_irq_mask = 0U;
        __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active = 0U;
        __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started = 0U;
        vlSelfRef.__Vdly__tb_top__DOT__u_dut__DOT__dma_busy = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__dma_done = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__irq_done = 0U;
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_cu__DOT__state = 0U;
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
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_read_reg 
        = vlSelfRef.tb_top__DOT__rst_n;
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
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_read_reg 
        = vlSelfRef.tb_top__DOT__rst_n;
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
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_read_reg 
        = vlSelfRef.tb_top__DOT__rst_n;
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
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_read_reg 
        = vlSelfRef.tb_top__DOT__rst_n;
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
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active 
        = __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_active;
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started 
        = __Vdly__tb_top__DOT__u_dut__DOT__u_dma__DOT__transfer_started;
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
    if (__VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem[__VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0] 
            = __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v0;
    }
    if (__VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v1) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem[__VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_mem__v1] = 0U;
    }
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
    if (__VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem[__VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0] 
            = __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v0;
    }
    if (__VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v1) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem[__VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_mem__v1] = 0U;
    }
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
    if (__VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem[__VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0] 
            = __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v0;
    }
    if (__VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v1) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem[__VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_mem__v1] = 0U;
    }
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
    if (__VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem[__VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0] 
            = __VdlyVal__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v0;
    }
    if (__VdlySet__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v1) {
        vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem[__VdlyDim0__tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_mem__v1] = 0U;
    }
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
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_valid[3U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank3_read_reg;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_data[3U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank3_rdata;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_valid[2U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank2_read_reg;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_data[2U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank2_rdata;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_valid[1U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank1_read_reg;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_data[1U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank1_rdata;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_valid[0U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT__u_tile_mem__DOT__bank0_read_reg;
    vlSelfRef.tb_top__DOT__u_dut__DOT__row_data[0U] 
        = vlSelfRef.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank0_rdata;
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
}
