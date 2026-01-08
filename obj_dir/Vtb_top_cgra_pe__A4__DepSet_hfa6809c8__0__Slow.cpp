// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top__Syms.h"
#include "Vtb_top_cgra_pe__A4.h"

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__u_config_mem__DOT__rst_n = ((IData)(vlSymsp->TOP.tb_top__DOT__rst_n) 
                                                 & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__pe_reset_n));
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i 
        = (((QData)((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_high_reg)) 
            << 0x20U) | (QData)((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__write_data_reg)));
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [1U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [2U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [3U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [4U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [5U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [6U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [7U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [8U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.valid_in_s = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [9U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__operand1 = ((1U & (IData)((vlSelfRef.active_config 
                                                >> 0xdU)))
                                  ? 0U : ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0xcU)))
                                           ? ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? 0U
                                                   : 
                                                  (0xffffU 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0x18U))))
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSelfRef.__PVT__spm_rdata
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__PVT__output_data
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data
                                                   : 
                                                  vlSelfRef.__PVT__rf_mem
                                                  [
                                                  (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))]))));
    vlSelfRef.__PVT__spm_wdata = ((1U & (IData)((vlSelfRef.active_config 
                                                 >> 9U)))
                                   ? 0U : ((1U & (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 8U)))
                                            ? ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? 0U
                                                    : 
                                                   (0xffffU 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 0x18U))))
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSelfRef.__PVT__spm_rdata
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__PVT__output_data
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data
                                                    : 
                                                   vlSelfRef.__PVT__rf_mem
                                                   [
                                                   (0xfU 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))]))));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
    vlSelfRef.__PVT__mult_result = VL_MULS_III(32, vlSelfRef.__PVT__spm_wdata, vlSelfRef.__PVT__operand1);
    vlSelfRef.__PVT__mult_ext = (((QData)((IData)((0xffU 
                                                   & (- (IData)(
                                                                (vlSelfRef.__PVT__mult_result 
                                                                 >> 0x1fU)))))) 
                                  << 0x20U) | (QData)((IData)(vlSelfRef.__PVT__mult_result)));
    vlSelfRef.__PVT__mac_sum = (0xffffffffffULL & (vlSelfRef.__PVT__accumulator 
                                                   + vlSelfRef.__PVT__mult_ext));
    vlSelfRef.__PVT__mac_result_sat = (VL_LTS_IQQ(40, 0x7fffffffULL, vlSelfRef.__PVT__mac_sum)
                                        ? 0x7fffffffU
                                        : (VL_GTS_IQQ(40, 0xff80000000ULL, vlSelfRef.__PVT__mac_sum)
                                            ? 0x80000000U
                                            : (IData)(vlSelfRef.__PVT__mac_sum)));
    vlSelfRef.__PVT__op0_ext = (((QData)((IData)((0xffU 
                                                  & (- (IData)(
                                                               (vlSelfRef.__PVT__spm_wdata 
                                                                >> 0x1fU)))))) 
                                 << 0x20U) | (QData)((IData)(vlSelfRef.__PVT__spm_wdata)));
    vlSelfRef.__PVT__op1_ext = (((QData)((IData)((0xffU 
                                                  & (- (IData)(
                                                               (vlSelfRef.__PVT__operand1 
                                                                >> 0x1fU)))))) 
                                 << 0x20U) | (QData)((IData)(vlSelfRef.__PVT__operand1)));
    vlSelfRef.__PVT__add_result = (0xffffffffffULL 
                                   & (vlSelfRef.__PVT__op0_ext 
                                      + vlSelfRef.__PVT__op1_ext));
    vlSelfRef.__PVT__sub_result = (0xffffffffffULL 
                                   & (vlSelfRef.__PVT__op0_ext 
                                      - vlSelfRef.__PVT__op1_ext));
    vlSelfRef.__PVT__lif_next_v = (0xffffffffffULL 
                                   & ((vlSelfRef.__PVT__accumulator 
                                       + vlSelfRef.__PVT__op0_ext) 
                                      - 0xaULL));
    vlSelfRef.__PVT__add_result_sat = (VL_LTS_IQQ(40, 0x7fffffffULL, vlSelfRef.__PVT__add_result)
                                        ? 0x7fffffffU
                                        : (VL_GTS_IQQ(40, 0xff80000000ULL, vlSelfRef.__PVT__add_result)
                                            ? 0x80000000U
                                            : (IData)(vlSelfRef.__PVT__add_result)));
    vlSelfRef.__PVT__sub_result_sat = (VL_LTS_IQQ(40, 0x7fffffffULL, vlSelfRef.__PVT__sub_result)
                                        ? 0x7fffffffU
                                        : (VL_GTS_IQQ(40, 0xff80000000ULL, vlSelfRef.__PVT__sub_result)
                                            ? 0x80000000U
                                            : (IData)(vlSelfRef.__PVT__sub_result)));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xaU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__1\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__operand1 = ((1U & (IData)((vlSelfRef.active_config 
                                                >> 0xdU)))
                                  ? 0U : ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0xcU)))
                                           ? ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? 0U
                                                   : 
                                                  (0xffffU 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0x18U))))
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSelfRef.__PVT__spm_rdata
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__output_data
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data
                                                   : 
                                                  vlSelfRef.__PVT__rf_mem
                                                  [
                                                  (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))]))));
    vlSelfRef.__PVT__spm_wdata = ((1U & (IData)((vlSelfRef.active_config 
                                                 >> 9U)))
                                   ? 0U : ((1U & (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 8U)))
                                            ? ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? 0U
                                                    : 
                                                   (0xffffU 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 0x18U))))
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSelfRef.__PVT__spm_rdata
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__output_data
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data
                                                    : 
                                                   vlSelfRef.__PVT__rf_mem
                                                   [
                                                   (0xfU 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))]))));
    vlSelfRef.__PVT__mult_result = VL_MULS_III(32, vlSelfRef.__PVT__spm_wdata, vlSelfRef.__PVT__operand1);
    vlSelfRef.__PVT__mult_ext = (((QData)((IData)((0xffU 
                                                   & (- (IData)(
                                                                (vlSelfRef.__PVT__mult_result 
                                                                 >> 0x1fU)))))) 
                                  << 0x20U) | (QData)((IData)(vlSelfRef.__PVT__mult_result)));
    vlSelfRef.__PVT__mac_sum = (0xffffffffffULL & (vlSelfRef.__PVT__accumulator 
                                                   + vlSelfRef.__PVT__mult_ext));
    vlSelfRef.__PVT__mac_result_sat = (VL_LTS_IQQ(40, 0x7fffffffULL, vlSelfRef.__PVT__mac_sum)
                                        ? 0x7fffffffU
                                        : (VL_GTS_IQQ(40, 0xff80000000ULL, vlSelfRef.__PVT__mac_sum)
                                            ? 0x80000000U
                                            : (IData)(vlSelfRef.__PVT__mac_sum)));
    vlSelfRef.__PVT__op0_ext = (((QData)((IData)((0xffU 
                                                  & (- (IData)(
                                                               (vlSelfRef.__PVT__spm_wdata 
                                                                >> 0x1fU)))))) 
                                 << 0x20U) | (QData)((IData)(vlSelfRef.__PVT__spm_wdata)));
    vlSelfRef.__PVT__op1_ext = (((QData)((IData)((0xffU 
                                                  & (- (IData)(
                                                               (vlSelfRef.__PVT__operand1 
                                                                >> 0x1fU)))))) 
                                 << 0x20U) | (QData)((IData)(vlSelfRef.__PVT__operand1)));
    vlSelfRef.__PVT__add_result = (0xffffffffffULL 
                                   & (vlSelfRef.__PVT__op0_ext 
                                      + vlSelfRef.__PVT__op1_ext));
    vlSelfRef.__PVT__sub_result = (0xffffffffffULL 
                                   & (vlSelfRef.__PVT__op0_ext 
                                      - vlSelfRef.__PVT__op1_ext));
    vlSelfRef.__PVT__lif_next_v = (0xffffffffffULL 
                                   & ((vlSelfRef.__PVT__accumulator 
                                       + vlSelfRef.__PVT__op0_ext) 
                                      - 0xaULL));
    vlSelfRef.__PVT__add_result_sat = (VL_LTS_IQQ(40, 0x7fffffffULL, vlSelfRef.__PVT__add_result)
                                        ? 0x7fffffffU
                                        : (VL_GTS_IQQ(40, 0xff80000000ULL, vlSelfRef.__PVT__add_result)
                                            ? 0x80000000U
                                            : (IData)(vlSelfRef.__PVT__add_result)));
    vlSelfRef.__PVT__sub_result_sat = (VL_LTS_IQQ(40, 0x7fffffffULL, vlSelfRef.__PVT__sub_result)
                                        ? 0x7fffffffU
                                        : (VL_GTS_IQQ(40, 0xff80000000ULL, vlSelfRef.__PVT__sub_result)
                                            ? 0x80000000U
                                            : (IData)(vlSelfRef.__PVT__sub_result)));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xbU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xcU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xdU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.valid_in_e = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__1\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__operand1 = ((1U & (IData)((vlSelfRef.active_config 
                                                >> 0xdU)))
                                  ? 0U : ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0xcU)))
                                           ? ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? 0U
                                                   : 
                                                  (0xffffU 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0x18U))))
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSelfRef.__PVT__spm_rdata
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? 0U
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data
                                                   : 
                                                  vlSelfRef.__PVT__rf_mem
                                                  [
                                                  (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))]))));
    vlSelfRef.__PVT__spm_wdata = ((1U & (IData)((vlSelfRef.active_config 
                                                 >> 9U)))
                                   ? 0U : ((1U & (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 8U)))
                                            ? ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? 0U
                                                    : 
                                                   (0xffffU 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 0x18U))))
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSelfRef.__PVT__spm_rdata
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? 0U
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data
                                                    : 
                                                   vlSelfRef.__PVT__rf_mem
                                                   [
                                                   (0xfU 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))]))));
    vlSelfRef.__PVT__mult_result = VL_MULS_III(32, vlSelfRef.__PVT__spm_wdata, vlSelfRef.__PVT__operand1);
    vlSelfRef.__PVT__mult_ext = (((QData)((IData)((0xffU 
                                                   & (- (IData)(
                                                                (vlSelfRef.__PVT__mult_result 
                                                                 >> 0x1fU)))))) 
                                  << 0x20U) | (QData)((IData)(vlSelfRef.__PVT__mult_result)));
    vlSelfRef.__PVT__mac_sum = (0xffffffffffULL & (vlSelfRef.__PVT__accumulator 
                                                   + vlSelfRef.__PVT__mult_ext));
    vlSelfRef.__PVT__mac_result_sat = (VL_LTS_IQQ(40, 0x7fffffffULL, vlSelfRef.__PVT__mac_sum)
                                        ? 0x7fffffffU
                                        : (VL_GTS_IQQ(40, 0xff80000000ULL, vlSelfRef.__PVT__mac_sum)
                                            ? 0x80000000U
                                            : (IData)(vlSelfRef.__PVT__mac_sum)));
    vlSelfRef.__PVT__op0_ext = (((QData)((IData)((0xffU 
                                                  & (- (IData)(
                                                               (vlSelfRef.__PVT__spm_wdata 
                                                                >> 0x1fU)))))) 
                                 << 0x20U) | (QData)((IData)(vlSelfRef.__PVT__spm_wdata)));
    vlSelfRef.__PVT__op1_ext = (((QData)((IData)((0xffU 
                                                  & (- (IData)(
                                                               (vlSelfRef.__PVT__operand1 
                                                                >> 0x1fU)))))) 
                                 << 0x20U) | (QData)((IData)(vlSelfRef.__PVT__operand1)));
    vlSelfRef.__PVT__add_result = (0xffffffffffULL 
                                   & (vlSelfRef.__PVT__op0_ext 
                                      + vlSelfRef.__PVT__op1_ext));
    vlSelfRef.__PVT__sub_result = (0xffffffffffULL 
                                   & (vlSelfRef.__PVT__op0_ext 
                                      - vlSelfRef.__PVT__op1_ext));
    vlSelfRef.__PVT__lif_next_v = (0xffffffffffULL 
                                   & ((vlSelfRef.__PVT__accumulator 
                                       + vlSelfRef.__PVT__op0_ext) 
                                      - 0xaULL));
    vlSelfRef.__PVT__add_result_sat = (VL_LTS_IQQ(40, 0x7fffffffULL, vlSelfRef.__PVT__add_result)
                                        ? 0x7fffffffU
                                        : (VL_GTS_IQQ(40, 0xff80000000ULL, vlSelfRef.__PVT__add_result)
                                            ? 0x80000000U
                                            : (IData)(vlSelfRef.__PVT__add_result)));
    vlSelfRef.__PVT__sub_result_sat = (VL_LTS_IQQ(40, 0x7fffffffULL, vlSelfRef.__PVT__sub_result)
                                        ? 0x7fffffffU
                                        : (VL_GTS_IQQ(40, 0xff80000000ULL, vlSelfRef.__PVT__sub_result)
                                            ? 0x80000000U
                                            : (IData)(vlSelfRef.__PVT__sub_result)));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xeU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.valid_in_e = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___stl_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xfU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    vlSelfRef.__PVT__execute_enable = (1U & ((~ (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 0x16U))) 
                                             | ((1U 
                                                 & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 0x17U)))
                                                 ? 
                                                (~ (IData)(vlSelfRef.__PVT__predicate_flag))
                                                 : (IData)(vlSelfRef.__PVT__predicate_flag))));
    vlSelfRef.__PVT__extended = (0xffffffU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0x28U)));
    vlSelfRef.__PVT__cfg_dest_x = (0xfU & vlSelfRef.__PVT__extended);
    vlSelfRef.__PVT__cfg_dest_y = (0xfU & (vlSelfRef.__PVT__extended 
                                           >> 4U));
    vlSelfRef.__PVT__cfg_multicast = (1U & (vlSelfRef.__PVT__extended 
                                            >> 8U));
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}
