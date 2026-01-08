// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top__Syms.h"
#include "Vtb_top_cgra_pe__A4.h"

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_00.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_00.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__u_config_mem__DOT__rst_n = ((IData)(vlSymsp->TOP.tb_top__DOT__rst_n) 
                                                 & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__pe_reset_n));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSelfRef.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__1\n"); );
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
                                                   : vlSymsp->TOP.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank0_rdata))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__output_data
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? 0U
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
                                                    : vlSymsp->TOP.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank0_rdata))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__output_data
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? 0U
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__3(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__3\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i 
        = (((QData)((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_high_reg)) 
            << 0x20U) | (QData)((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__write_data_reg)));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_01.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_01.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0x100U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [1U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__1\n"); );
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
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? 0U
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? 0U
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__2\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__config_ram_valid = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n;
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_02.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_02.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0x200U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [2U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__1\n"); );
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
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? 0U
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? 0U
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_03.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_03.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0x300U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [3U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__1\n"); );
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
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__output_data
                                                   : 0U)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? 0U
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__output_data
                                                    : 0U)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? 0U
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_10.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_10.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.active_config 
                                       >> 0x15U)));
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0x400U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [4U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__1\n"); );
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
                                                   : vlSymsp->TOP.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank1_rdata))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__PVT__output_data
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__output_data
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
                                                    : vlSymsp->TOP.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank1_rdata))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__PVT__output_data
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__output_data
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_11.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_11.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.active_config 
                                       >> 0x15U)));
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0x500U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [5U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__1\n"); );
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
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__output_data
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__PVT__output_data
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_12.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_12.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.active_config 
                                       >> 0x15U)));
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0x600U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [6U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__1\n"); );
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
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__output_data
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__PVT__output_data
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_13.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_13.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.active_config 
                                       >> 0x15U)));
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0x700U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [7U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__1\n"); );
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
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__PVT__output_data
                                                   : 0U)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.__PVT__output_data
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__PVT__output_data
                                                    : 0U)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.__PVT__output_data
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_20.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_20.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    vlSelfRef.valid_in_s = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.active_config 
                                       >> 0x15U)));
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0x800U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [8U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__1\n"); );
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
                                                   : vlSymsp->TOP.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank2_rdata))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.__PVT__output_data
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__output_data
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
                                                    : vlSymsp->TOP.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank2_rdata))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.__PVT__output_data
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__PVT__output_data
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_21.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_21.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.active_config 
                                       >> 0x15U)));
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0x900U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [9U] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__1\n"); );
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_22.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_22.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.active_config 
                                       >> 0x15U)));
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0xa00U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xaU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_23.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_23.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.active_config 
                                       >> 0x15U)));
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0xb00U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xbU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__1\n"); );
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
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.__PVT__output_data
                                                   : 0U)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__output_data
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.__PVT__output_data
                                                    : 0U)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__PVT__output_data
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_30.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_30.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0xc00U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xcU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__1\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.valid_in_e = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.active_config 
                                       >> 0x15U)));
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.active_config 
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
                                                   : vlSymsp->TOP.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank3_rdata))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? 0U
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__PVT__output_data
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
                                                    : vlSymsp->TOP.tb_top__DOT__u_dut__DOT____Vcellout__u_tile_mem__bank3_rdata))
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__PVT__output_data
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_31.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_31.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0xd00U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xdU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__1\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.valid_in_e = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.active_config 
                                       >> 0x15U)));
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_32.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_32.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    vlSelfRef.valid_in_e = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.active_config 
                                       >> 0x15U)));
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0xe00U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xeU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__1\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.active_config 
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
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? 0U
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.__PVT__output_data)
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__PVT__output_data))
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.__PVT__output_data)
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__PVT__output_data
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

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___eval_initial__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync: instantiating width_p=         64, els_p=         16, read_write_same_addr_p=          1, harden_p=          0 (%Ntb_top.u_dut.u_array.u_tile_33.u_pe.u_config_mem.mem_inst)\n",0,
                 vlSymsp->name());
    VL_WRITEF_NX("## work.bsg_mem_1r1w_sync_synth: instantiating width_p=         64, els_p=         16 (%Ntb_top.u_dut.u_array.u_tile_33.u_pe.u_config_mem.mem_inst.synth)\n",0,
                 vlSymsp->name());
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__stall = (1U & ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__router_to_pe_ready)) 
                                    | (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)));
    vlSelfRef.ready_out = ((~ (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__dma_busy)) 
                           & (IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__router_to_pe_ready));
    vlSelfRef.__PVT__rf_we = 0U;
    vlSelfRef.__PVT__spm_we = 0U;
    if ((((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
          & (IData)(vlSelfRef.__PVT__execute_enable)) 
         & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        if ((1U & (IData)((vlSelfRef.active_config 
                           >> 5U)))) {
            vlSelfRef.__PVT__rf_we = 0U;
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 4U)))) {
            vlSelfRef.__PVT__rf_we = ((1U & (~ (IData)(
                                                       (vlSelfRef.active_config 
                                                        >> 3U)))) 
                                      && ((1U & (~ (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 2U)))) 
                                          && (1U & 
                                              (~ (IData)(
                                                         (vlSelfRef.active_config 
                                                          >> 1U))))));
        } else if ((1U & (IData)((vlSelfRef.active_config 
                                  >> 3U)))) {
            if ((1U & (IData)((vlSelfRef.active_config 
                               >> 2U)))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.active_config))) {
                        vlSelfRef.__PVT__rf_we = 0U;
                    }
                } else {
                    vlSelfRef.__PVT__rf_we = 1U;
                }
            } else {
                vlSelfRef.__PVT__rf_we = 1U;
            }
        } else {
            vlSelfRef.__PVT__rf_we = ((1U & (IData)(
                                                    (vlSelfRef.active_config 
                                                     >> 2U))) 
                                      || ((1U & (IData)(
                                                        (vlSelfRef.active_config 
                                                         >> 1U))) 
                                          || (1U & (IData)(vlSelfRef.active_config))));
        }
        if ((1U & (~ (IData)((vlSelfRef.active_config 
                              >> 5U))))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 4U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__spm_we = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__spm_mem__v0;
    __VdlyVal__spm_mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__spm_mem__v0;
    __VdlyDim0__spm_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__spm_mem__v0;
    __VdlySet__spm_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__rf_mem__v0;
    __VdlyVal__rf_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__rf_mem__v0;
    __VdlyDim0__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v0;
    __VdlySet__rf_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_mem__v1;
    __VdlySet__rf_mem__v1 = 0;
    QData/*63:0*/ __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0;
    // Body
    __VdlySet__spm_mem__v0 = 0U;
    __VdlySet__rf_mem__v0 = 0U;
    __VdlySet__rf_mem__v1 = 0U;
    __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 0U;
    if (((IData)(vlSelfRef.__PVT__spm_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        __VdlyVal__spm_mem__v0 = vlSelfRef.__PVT__spm_wdata;
        __VdlyDim0__spm_mem__v0 = (0xfU & vlSelfRef.__PVT__operand1);
        __VdlySet__spm_mem__v0 = 1U;
    }
    if (vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.__PVT__rf_we) & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            __VdlyVal__rf_mem__v0 = vlSelfRef.alu_result;
            __VdlyDim0__rf_mem__v0 = (0xfU & (IData)(
                                                     (vlSelfRef.active_config 
                                                      >> 0xeU)));
            __VdlySet__rf_mem__v0 = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
            if ((1U & (~ (IData)((vlSelfRef.active_config 
                                  >> 5U))))) {
                if ((1U & (IData)((vlSelfRef.active_config 
                                   >> 4U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 3U))))) {
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 2U))))) {
                            if ((1U & (IData)((vlSelfRef.active_config 
                                               >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                    if (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)) {
                                        vlSelfRef.__PVT__accumulator = 0ULL;
                                        vlSelfRef.__PVT__predicate_flag = 1U;
                                    } else {
                                        vlSelfRef.__PVT__accumulator 
                                            = vlSelfRef.__PVT__lif_next_v;
                                        vlSelfRef.__PVT__predicate_flag = 0U;
                                    }
                                }
                            }
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelfRef.active_config 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelfRef.active_config 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelfRef.active_config))) {
                                vlSelfRef.__PVT__accumulator = 0ULL;
                            }
                        }
                        if ((1U & (~ (IData)((vlSelfRef.active_config 
                                              >> 1U))))) {
                            if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                                vlSelfRef.__PVT__predicate_flag 
                                    = (vlSelfRef.__PVT__spm_wdata 
                                       == vlSelfRef.__PVT__operand1);
                            }
                        }
                    } else if ((1U & (IData)((vlSelfRef.active_config 
                                              >> 1U)))) {
                        vlSelfRef.__PVT__predicate_flag 
                            = ((1U & (IData)(vlSelfRef.active_config))
                                ? (vlSelfRef.__PVT__spm_wdata 
                                   < vlSelfRef.__PVT__operand1)
                                : (vlSelfRef.__PVT__spm_wdata 
                                   > vlSelfRef.__PVT__operand1));
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 2U)))) {
                    if ((1U & (~ (IData)((vlSelfRef.active_config 
                                          >> 1U))))) {
                        if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                            vlSelfRef.__PVT__accumulator 
                                = vlSelfRef.__PVT__mac_sum;
                        }
                    }
                } else if ((1U & (IData)((vlSelfRef.active_config 
                                          >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.active_config)))) {
                        vlSelfRef.__PVT__accumulator 
                            = vlSelfRef.__PVT__sub_result;
                    }
                } else if ((1U & (IData)(vlSelfRef.active_config))) {
                    vlSelfRef.__PVT__accumulator = vlSelfRef.__PVT__add_result;
                }
            }
            vlSelfRef.alu_result = ((1U & (IData)((vlSelfRef.active_config 
                                                   >> 5U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlSelfRef.active_config 
                                                            >> 4U)))
                                              ? ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 0U
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : 
                                                    (VL_GTES_IQQ(40, vlSelfRef.__PVT__lif_next_v, vlSelfRef.__PVT__op1_ext)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__operand1
                                                     : vlSelfRef.__PVT__spm_wdata))))
                                              : ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 3U)))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 0U
                                                     : vlSelfRef.__PVT__spm_wdata)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__spm_rdata
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      == vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      < vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((vlSelfRef.__PVT__spm_wdata 
                                                      > vlSelfRef.__PVT__operand1)
                                                      ? 1U
                                                      : 0U))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    VL_SHIFTRS_III(32,32,5, vlSelfRef.__PVT__spm_wdata, 
                                                                   (0x1fU 
                                                                    & vlSelfRef.__PVT__operand1))
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     << 
                                                     (0x1fU 
                                                      & vlSelfRef.__PVT__operand1)))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 2U)))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     ^ vlSelfRef.__PVT__operand1)
                                                     : 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     | vlSelfRef.__PVT__operand1))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     & vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__mac_result_sat))
                                                   : 
                                                  ((1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 1U)))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? 
                                                    (vlSelfRef.__PVT__spm_wdata 
                                                     * vlSelfRef.__PVT__operand1)
                                                     : vlSelfRef.__PVT__sub_result_sat)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.active_config))
                                                     ? vlSelfRef.__PVT__add_result_sat
                                                     : 0U))))));
        }
    } else {
        __VdlySet__rf_mem__v1 = 1U;
        vlSelfRef.__PVT__accumulator = 0ULL;
        vlSelfRef.__PVT__predicate_flag = 0U;
    }
    if (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_array__DOT__cfg_wr_en) 
         & (0xf00U == (0xf00U & vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr)))) {
        __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
        __VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 
            = (0xfU & (vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_dma__DOT__local_write_addr 
                       >> 3U));
        __VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0 = 1U;
    }
    vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r 
        = vlSymsp->TOP.tb_top__DOT__u_dut__DOT__u_cu__DOT__pc_counter;
    if (__VdlySet__rf_mem__v0) {
        vlSelfRef.__PVT__rf_mem[__VdlyDim0__rf_mem__v0] 
            = __VdlyVal__rf_mem__v0;
    }
    if (__VdlySet__rf_mem__v1) {
        vlSelfRef.__PVT__rf_mem[0U] = 0U;
        vlSelfRef.__PVT__rf_mem[1U] = 0U;
        vlSelfRef.__PVT__rf_mem[2U] = 0U;
        vlSelfRef.__PVT__rf_mem[3U] = 0U;
        vlSelfRef.__PVT__rf_mem[4U] = 0U;
        vlSelfRef.__PVT__rf_mem[5U] = 0U;
        vlSelfRef.__PVT__rf_mem[6U] = 0U;
        vlSelfRef.__PVT__rf_mem[7U] = 0U;
        vlSelfRef.__PVT__rf_mem[8U] = 0U;
        vlSelfRef.__PVT__rf_mem[9U] = 0U;
        vlSelfRef.__PVT__rf_mem[0xaU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xbU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xcU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xdU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xeU] = 0U;
        vlSelfRef.__PVT__rf_mem[0xfU] = 0U;
    }
    if (__VdlySet__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0) {
        vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__VdlyDim0__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0] 
            = __VdlyVal__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem__v0;
    }
    vlSelfRef.active_config = ((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy)
                                ? vlSymsp->TOP.tb_top__DOT__u_dut__DOT__config_frames
                               [0xfU] : vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem
                               [vlSelfRef.__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r]);
    if ((1U & (~ (IData)(vlSelfRef.__PVT__stall)))) {
        vlSelfRef.__PVT__spm_rdata = vlSelfRef.__PVT__spm_mem
            [(0xfU & vlSelfRef.__PVT__operand1)];
    }
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
    if (__VdlySet__spm_mem__v0) {
        vlSelfRef.__PVT__spm_mem[__VdlyDim0__spm_mem__v0] 
            = __VdlyVal__spm_mem__v0;
    }
    vlSelfRef.__PVT__output_payload = (0xffffU & vlSelfRef.alu_result);
    vlSelfRef.__PVT__output_data = (((IData)(vlSelfRef.__PVT__cfg_multicast) 
                                     << 0x1fU) | (((IData)(vlSelfRef.__PVT__cfg_dest_x) 
                                                   << 0x1bU) 
                                                  | (((IData)(vlSelfRef.__PVT__cfg_dest_y) 
                                                      << 0x17U) 
                                                     | (IData)(vlSelfRef.__PVT__output_payload))));
}

VL_INLINE_OPT void Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__1(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___nba_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__1\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.valid_in_n = (((IData)(vlSymsp->TOP.tb_top__DOT__u_dut__DOT__cu_busy) 
                             & (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__PVT__execute_enable)) 
                            & (IData)((vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.active_config 
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
                                                   : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__output_data))
                                           : ((1U & (IData)(
                                                            (vlSelfRef.active_config 
                                                             >> 0xbU)))
                                               ? 0U
                                               : ((1U 
                                                   & (IData)(
                                                             (vlSelfRef.active_config 
                                                              >> 0xaU)))
                                                   ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__PVT__output_data
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
                                                    : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__PVT__output_data))
                                            : ((1U 
                                                & (IData)(
                                                          (vlSelfRef.active_config 
                                                           >> 7U)))
                                                ? 0U
                                                : (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.active_config 
                                                               >> 6U)))
                                                    ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__PVT__output_data
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
