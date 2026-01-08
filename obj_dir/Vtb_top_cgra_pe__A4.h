// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_top.h for the primary calling header

#ifndef VERILATED_VTB_TOP_CGRA_PE__A4_H_
#define VERILATED_VTB_TOP_CGRA_PE__A4_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_top_cgra_pe__A4 final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(config_valid,0,0);
    VL_IN8(context_pc,3,0);
    VL_IN8(global_stall,0,0);
    VL_IN8(cfg_wr_addr,3,0);
    VL_IN8(cfg_wr_en,0,0);
    VL_IN8(valid_in_n,0,0);
    VL_IN8(valid_in_e,0,0);
    VL_IN8(valid_in_s,0,0);
    VL_IN8(valid_in_w,0,0);
    VL_OUT8(valid_out_n,0,0);
    VL_OUT8(__PVT__valid_out_e,0,0);
    VL_OUT8(__PVT__valid_out_s,0,0);
    VL_OUT8(__PVT__valid_out_w,0,0);
    VL_OUT8(valid_out_local,0,0);
    VL_IN8(ready_in,0,0);
    VL_OUT8(ready_out,0,0);
    CData/*3:0*/ __PVT__cfg_dest_x;
    CData/*3:0*/ __PVT__cfg_dest_y;
    CData/*0:0*/ __PVT__cfg_multicast;
    CData/*0:0*/ __PVT__config_ram_valid;
    CData/*0:0*/ __PVT__stall;
    CData/*0:0*/ __PVT__spm_we;
    CData/*0:0*/ __PVT__rf_we;
    CData/*0:0*/ __PVT__predicate_flag;
    CData/*0:0*/ __PVT__execute_enable;
    CData/*0:0*/ __PVT__u_config_mem__DOT__rst_n;
    CData/*3:0*/ __PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r;
    SData/*15:0*/ __PVT__output_payload;
    VL_IN(data_in_n,31,0);
    VL_IN(data_in_e,31,0);
    VL_IN(data_in_s,31,0);
    VL_IN(data_in_w,31,0);
    VL_OUT(data_out_n,31,0);
    VL_OUT(__PVT__data_out_e,31,0);
    VL_OUT(__PVT__data_out_s,31,0);
    VL_OUT(__PVT__data_out_w,31,0);
    VL_OUT(data_out_local,31,0);
    IData/*23:0*/ __PVT__extended;
    IData/*31:0*/ __PVT__spm_rdata;
    IData/*31:0*/ __PVT__spm_wdata;
    IData/*31:0*/ __PVT__operand1;
    IData/*31:0*/ alu_result;
    IData/*31:0*/ __PVT__mult_result;
    IData/*31:0*/ __PVT__add_result_sat;
    IData/*31:0*/ __PVT__sub_result_sat;
    IData/*31:0*/ __PVT__mac_result_sat;
    IData/*31:0*/ __PVT__output_data;
    VL_IN64(config_frame,63,0);
    VL_IN64(cfg_wr_data,63,0);
    QData/*63:0*/ active_config;
    QData/*39:0*/ __PVT__accumulator;
    QData/*39:0*/ __PVT__op0_ext;
    QData/*39:0*/ __PVT__op1_ext;
    QData/*39:0*/ __PVT__mult_ext;
    QData/*39:0*/ __PVT__lif_next_v;
    QData/*39:0*/ __PVT__add_result;
    QData/*39:0*/ __PVT__sub_result;
    QData/*39:0*/ __PVT__mac_sum;
    QData/*63:0*/ __PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i;
    VlUnpacked<IData/*31:0*/, 256> __PVT__spm_mem;
    VlUnpacked<IData/*31:0*/, 16> __PVT__rf_mem;
    VlUnpacked<QData/*63:0*/, 16> __PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem;

    // INTERNAL VARIABLES
    Vtb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtb_top_cgra_pe__A4(Vtb_top__Syms* symsp, const char* v__name);
    ~Vtb_top_cgra_pe__A4();
    VL_UNCOPYABLE(Vtb_top_cgra_pe__A4);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
