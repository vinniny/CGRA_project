// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top_cgra_pe__A4.h"

VL_ATTR_COLD void Vtb_top_cgra_pe__A4___ctor_var_reset(Vtb_top_cgra_pe__A4* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtb_top_cgra_pe__A4___ctor_var_reset\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->config_frame = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10644866441308515918ull);
    vlSelf->config_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5256005406248715760ull);
    vlSelf->context_pc = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12481894802662481718ull);
    vlSelf->global_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9627833799363577374ull);
    vlSelf->cfg_wr_addr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 365765126414468489ull);
    vlSelf->cfg_wr_data = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10851778048589922656ull);
    vlSelf->cfg_wr_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2274196239682917382ull);
    vlSelf->data_in_n = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9370456554827385468ull);
    vlSelf->data_in_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17857377296211746779ull);
    vlSelf->data_in_s = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14911477262062962880ull);
    vlSelf->data_in_w = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15495666129397604370ull);
    vlSelf->valid_in_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15941450344945871743ull);
    vlSelf->valid_in_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9191086637658097863ull);
    vlSelf->valid_in_s = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13616641403901824744ull);
    vlSelf->valid_in_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4941640464738391657ull);
    vlSelf->data_out_n = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7107859155880955395ull);
    vlSelf->__PVT__data_out_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7422265183116498401ull);
    vlSelf->__PVT__data_out_s = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9566963611603006653ull);
    vlSelf->__PVT__data_out_w = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15724850036240103635ull);
    vlSelf->valid_out_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16629166547909169418ull);
    vlSelf->__PVT__valid_out_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6678847125953892341ull);
    vlSelf->__PVT__valid_out_s = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8771115282498607155ull);
    vlSelf->__PVT__valid_out_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6249509148640075341ull);
    vlSelf->data_out_local = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1024074449505996461ull);
    vlSelf->valid_out_local = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6126485611079768419ull);
    vlSelf->ready_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5285755476734430966ull);
    vlSelf->ready_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7479542285155168376ull);
    vlSelf->__PVT__extended = VL_SCOPED_RAND_RESET_I(24, __VscopeHash, 2445047661334265767ull);
    vlSelf->__PVT__cfg_dest_x = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3038743616668895533ull);
    vlSelf->__PVT__cfg_dest_y = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 16477355760276106793ull);
    vlSelf->__PVT__cfg_multicast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9488896705901665031ull);
    vlSelf->active_config = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 18000356192242038064ull);
    vlSelf->__PVT__config_ram_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3860365495845722157ull);
    vlSelf->__PVT__stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7179230919112499263ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->__PVT__spm_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 268090855935482861ull);
    }
    vlSelf->__PVT__spm_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13462338558019830485ull);
    vlSelf->__PVT__spm_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6330575300706817340ull);
    vlSelf->__PVT__spm_we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6057642474997530762ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->__PVT__rf_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4939632407280341397ull);
    }
    vlSelf->__PVT__rf_we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 761358256631926358ull);
    vlSelf->__PVT__operand1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 395903887735977689ull);
    vlSelf->alu_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15326351562492354909ull);
    vlSelf->__PVT__accumulator = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 635851360026796673ull);
    vlSelf->__PVT__predicate_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1066432305184093288ull);
    vlSelf->__PVT__op0_ext = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 7362835444103466834ull);
    vlSelf->__PVT__op1_ext = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 14609643387401794452ull);
    vlSelf->__PVT__mult_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10482412645216897151ull);
    vlSelf->__PVT__mult_ext = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 14720300005928601336ull);
    vlSelf->__PVT__lif_next_v = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 17832644187327846930ull);
    vlSelf->__PVT__add_result = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 10075498720355937314ull);
    vlSelf->__PVT__sub_result = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 2847108627631169984ull);
    vlSelf->__PVT__add_result_sat = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6219245629531477406ull);
    vlSelf->__PVT__sub_result_sat = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6717792137912176169ull);
    vlSelf->__PVT__mac_result_sat = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10552817871542896840ull);
    vlSelf->__PVT__mac_sum = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 4660975986014779437ull);
    vlSelf->__PVT__execute_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3250807417824677536ull);
    vlSelf->__PVT__output_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7032170951333504304ull);
    vlSelf->__PVT__output_payload = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12625376342735861593ull);
    vlSelf->__PVT__u_config_mem__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5883172482383956271ull);
    vlSelf->__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__w_data_i = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1919481538999607445ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8919871114462811842ull);
    }
    vlSelf->__PVT__u_config_mem__DOT__mem_inst__DOT__synth__DOT__nz__DOT__r_addr_r = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 16063548433036299738ull);
}
