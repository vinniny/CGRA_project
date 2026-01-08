// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtb_top__Syms.h"


void Vtb_top___024root__trace_chg_0_sub_1(Vtb_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_chg_0_sub_1\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 2915);

    // Body
    bufp->chgBit(oldp+0,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_n) 
                          && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                        >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l)) 
                                                  | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out))))) 
                              || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                          >> 3U) & 
                                         ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready))))) 
                                  || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s)) 
                                             & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                                >> 2U))) 
                                      || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                                  >> 1U) 
                                                 & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e)) 
                                                    | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready))))) 
                                          || (1U & 
                                              ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_n) 
                                               & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready))))))))))));
    bufp->chgBit(oldp+1,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_e) 
                          && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                        >> 4U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                                    >> 1U)) 
                                                  | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out))))) 
                              || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                          >> 3U) & 
                                         ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
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
                                          || (1U & 
                                              ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_e) 
                                               & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                                    >> 1U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready))))))))))));
    bufp->chgBit(oldp+2,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_s) 
                          & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                               >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                             >> 2U)) 
                                         | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out)))) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                  >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
                                                >> 2U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready)))) 
                                | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s) 
                                        >> 2U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                                   >> 2U)) 
                                   | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                        >> 1U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e) 
                                                    >> 2U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready)))) 
                                      | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_s) 
                                         & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                                >> 2U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready)))))))))));
    bufp->chgBit(oldp+3,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_w) 
                          && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                        >> 4U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                                    >> 3U)) 
                                                  | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out))))) 
                              || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                          >> 3U) & 
                                         ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
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
                                          || (1U & 
                                              ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_w) 
                                               & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                                    >> 3U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready))))))))))));
    bufp->chgBit(oldp+4,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__b_val_l) 
                          & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                               >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_l) 
                                             >> 4U)) 
                                         | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out)))) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                  >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_w) 
                                                >> 4U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_e_ready)))) 
                                | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_s) 
                                        >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                                   >> 2U)) 
                                   | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                        >> 1U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_e) 
                                                    >> 4U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready)))) 
                                      | ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__req_l) 
                                         & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_router__DOT__grant_n) 
                                                >> 4U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_s_ready)))))))))));
    bufp->chgBit(oldp+5,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_n) 
                          && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                        >> 4U) & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l)) 
                                                  | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out))))) 
                              || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                          >> 3U) & 
                                         ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready))))) 
                                  || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s)) 
                                             & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                                >> 2U))) 
                                      || ((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e)) 
                                                 & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                                    >> 1U))) 
                                          || (1U & 
                                              ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_n) 
                                               & ((~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready))))))))))));
    bufp->chgBit(oldp+6,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_e) 
                          & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                               >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                             >> 1U)) 
                                         | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out)))) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                  >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                                >> 1U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready)))) 
                                | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                        >> 1U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                                   >> 2U)) 
                                   | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                           >> 1U)) 
                                       & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                          >> 1U)) | 
                                      ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_e) 
                                       & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                              >> 1U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))));
    bufp->chgBit(oldp+7,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_s) 
                          & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                               >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                             >> 2U)) 
                                         | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out)))) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                  >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                                >> 2U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready)))) 
                                | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                        >> 2U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                                   >> 2U)) 
                                   | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                           >> 2U)) 
                                       & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                          >> 1U)) | 
                                      ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_s) 
                                       & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                              >> 2U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))));
    bufp->chgBit(oldp+8,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_w) 
                          && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                        >> 4U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                                    >> 3U)) 
                                                  | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out))))) 
                              || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                          >> 3U) & 
                                         ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                              >> 3U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready))))) 
                                  || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                                 >> 3U)) 
                                             & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                                >> 2U))) 
                                      || ((1U & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                                   >> 3U)) 
                                                 & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                                    >> 1U))) 
                                          || (1U & 
                                              ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_w) 
                                               & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                                    >> 3U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready))))))))))));
    bufp->chgBit(oldp+9,(((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__b_val_l) 
                          & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                               >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_l) 
                                             >> 4U)) 
                                         | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out)))) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                  >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_w) 
                                                >> 4U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_e_ready)))) 
                                | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_s) 
                                        >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                                   >> 2U)) 
                                   | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_e) 
                                           >> 4U)) 
                                       & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                          >> 1U)) | 
                                      ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__req_l) 
                                       & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_router__DOT__grant_n) 
                                              >> 4U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_s_ready)))))))))));
    bufp->chgIData(oldp+10,((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__dma_done_latch) 
                              << 1U) | (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__dma_busy))),32);
    bufp->chgBit(oldp+11,(vlSelfRef.tb_top__DOT__u_dut__DOT__u_dma__DOT__fifo_push));
    bufp->chgBit(oldp+12,(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__stall));
    bufp->chgBit(oldp+13,(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__spm_we));
    bufp->chgBit(oldp+14,(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__rf_we));
    bufp->chgBit(oldp+15,((1U & (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n)))));
}

void Vtb_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_cleanup\n"); );
    // Init
    Vtb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_top___024root*>(voidSelf);

    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;

    // Body
    vlSymsp->__Vm_activity = false;
    IData/*31:0*/ __Vilp1;
    __Vilp1 = 0U;
    while ((__Vilp1 <= 0x2eU)) {
        vlSymsp->TOP.__Vm_traceActivity[__Vilp1] = 0U;
        __Vilp1 = ((IData)(1U) + __Vilp1);
    }
}
