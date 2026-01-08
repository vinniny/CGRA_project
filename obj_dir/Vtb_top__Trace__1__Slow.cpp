// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtb_top__Syms.h"


VL_ATTR_COLD void Vtb_top___024root__trace_full_0_sub_1(Vtb_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_full_0_sub_1\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);

    // Body
    bufp->fullBit(oldp+2915,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_n) 
                              && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                            >> 4U) 
                                           & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l)) 
                                              | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out))))) 
                                  || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                              >> 3U) 
                                             & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready))))) 
                                      || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s)) 
                                                 & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                                    >> 2U))) 
                                          || ((1U & 
                                               (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                                 >> 1U) 
                                                & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e)) 
                                                   | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready))))) 
                                              || (1U 
                                                  & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                                     & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n)) 
                                                        | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready))))))))))));
    bufp->fullBit(oldp+2916,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_e) 
                              && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                            >> 4U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                                  >> 1U)) 
                                              | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out))))) 
                                  || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                              >> 3U) 
                                             & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
                                                  >> 1U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready))))) 
                                      || ((1U & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s) 
                                                   >> 1U)) 
                                                 & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                                    >> 2U))) 
                                          || ((1U & 
                                               (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                                 >> 1U) 
                                                & ((~ 
                                                    ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e) 
                                                     >> 1U)) 
                                                   | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready))))) 
                                              || (1U 
                                                  & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                                     & ((~ 
                                                         ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                                          >> 1U)) 
                                                        | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready))))))))))));
    bufp->fullBit(oldp+2917,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_s) 
                              & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                   >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                                 >> 2U)) 
                                             | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out)))) 
                                 | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                      >> 3U) & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
                                                  >> 2U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready)))) 
                                    | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s) 
                                            >> 2U)) 
                                        & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                           >> 2U)) 
                                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                            >> 1U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e) 
                                                  >> 2U)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready)))) 
                                          | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                             & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                                  >> 2U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready)))))))))));
    bufp->fullBit(oldp+2918,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_w) 
                              && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                            >> 4U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                                  >> 3U)) 
                                              | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out))))) 
                                  || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                              >> 3U) 
                                             & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
                                                  >> 3U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready))))) 
                                      || ((1U & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s) 
                                                   >> 3U)) 
                                                 & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                                    >> 2U))) 
                                          || ((1U & 
                                               (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                                 >> 1U) 
                                                & ((~ 
                                                    ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e) 
                                                     >> 3U)) 
                                                   | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready))))) 
                                              || (1U 
                                                  & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                                     & ((~ 
                                                         ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                                          >> 3U)) 
                                                        | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready))))))))))));
    bufp->fullBit(oldp+2919,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_l) 
                              & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                   >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                                 >> 4U)) 
                                             | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out)))) 
                                 | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                      >> 3U) & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
                                                  >> 4U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready)))) 
                                    | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s) 
                                            >> 4U)) 
                                        & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                           >> 2U)) 
                                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                            >> 1U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e) 
                                                  >> 4U)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready)))) 
                                          | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                             & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                                  >> 4U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready)))))))))));
    bufp->fullBit(oldp+2920,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_n) 
                              && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                            >> 4U) 
                                           & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l)) 
                                              | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out))))) 
                                  || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                              >> 3U) 
                                             & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready))))) 
                                      || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s)) 
                                                 & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                                    >> 2U))) 
                                          || ((1U & 
                                               ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e)) 
                                                & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                                   >> 1U))) 
                                              || (1U 
                                                  & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                                     & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n)) 
                                                        | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready))))))))))));
    bufp->fullBit(oldp+2921,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_e) 
                              & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                   >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                                 >> 1U)) 
                                             | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out)))) 
                                 | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                      >> 3U) & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                                  >> 1U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready)))) 
                                    | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                            >> 1U)) 
                                        & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                           >> 2U)) 
                                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                               >> 1U)) 
                                           & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                              >> 1U)) 
                                          | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                             & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                                  >> 1U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))));
    bufp->fullBit(oldp+2922,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_s) 
                              & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                   >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                                 >> 2U)) 
                                             | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out)))) 
                                 | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                      >> 3U) & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                                  >> 2U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready)))) 
                                    | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                            >> 2U)) 
                                        & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                           >> 2U)) 
                                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                               >> 2U)) 
                                           & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                              >> 1U)) 
                                          | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                             & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                                  >> 2U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))));
    bufp->fullBit(oldp+2923,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_w) 
                              && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                            >> 4U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                                  >> 3U)) 
                                              | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out))))) 
                                  || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                              >> 3U) 
                                             & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                                  >> 3U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready))))) 
                                      || ((1U & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                                   >> 3U)) 
                                                 & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                                    >> 2U))) 
                                          || ((1U & 
                                               ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                                  >> 3U)) 
                                                & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                                   >> 1U))) 
                                              || (1U 
                                                  & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                                     & ((~ 
                                                         ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                                          >> 3U)) 
                                                        | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready))))))))))));
    bufp->fullBit(oldp+2924,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_l) 
                              & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                   >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                                 >> 4U)) 
                                             | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out)))) 
                                 | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                      >> 3U) & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                                  >> 4U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready)))) 
                                    | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                            >> 4U)) 
                                        & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                           >> 2U)) 
                                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                               >> 4U)) 
                                           & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                              >> 1U)) 
                                          | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                             & ((~ 
                                                 ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                                  >> 4U)) 
                                                | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))));
    bufp->fullIData(oldp+2925,((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__dma_done_latch) 
                                 << 1U) | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__dma_busy))),32);
    bufp->fullBit(oldp+2926,(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_push));
    bufp->fullBit(oldp+2927,(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__stall));
    bufp->fullBit(oldp+2928,(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__spm_we));
    bufp->fullBit(oldp+2929,(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__rf_we));
    bufp->fullBit(oldp+2930,((1U & (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n)))));
}
