// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top__Syms.h"
#include "Vtb_top___024root.h"

VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__1__22(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial__TOP__Vtiming__1__22\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __Vtask_tb_top__DOT__run_cgra__3118__cycles;
    __Vtask_tb_top__DOT__run_cgra__3118__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__3119__addr;
    __Vtask_tb_top__DOT__apb_write__3119__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__3119__data;
    __Vtask_tb_top__DOT__apb_write__3119__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__3120__n;
    __Vtask_tb_top__DOT__wait_cycles__3120__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__3120__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__3120__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__3121__addr;
    __Vtask_tb_top__DOT__apb_write__3121__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__3121__data;
    __Vtask_tb_top__DOT__apb_write__3121__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__3122__n;
    __Vtask_tb_top__DOT__wait_cycles__3122__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__3122__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__3122__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__3123__addr;
    __Vtask_tb_top__DOT__apb_write__3123__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__3123__data;
    __Vtask_tb_top__DOT__apb_write__3123__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__3124__n;
    __Vtask_tb_top__DOT__wait_cycles__3124__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__3124__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__3124__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__3125__addr;
    __Vtask_tb_top__DOT__apb_write__3125__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__3125__data;
    __Vtask_tb_top__DOT__apb_write__3125__data = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__read_pe_result__3126__Vfuncout;
    __Vfunc_tb_top__DOT__read_pe_result__3126__Vfuncout = 0;
    CData/*3:0*/ __Vfunc_tb_top__DOT__read_pe_result__3126__pe_id;
    __Vfunc_tb_top__DOT__read_pe_result__3126__pe_id = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__read_pe_result__3127__Vfuncout;
    __Vfunc_tb_top__DOT__read_pe_result__3127__Vfuncout = 0;
    CData/*3:0*/ __Vfunc_tb_top__DOT__read_pe_result__3127__pe_id;
    __Vfunc_tb_top__DOT__read_pe_result__3127__pe_id = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__read_pe_result__3128__Vfuncout;
    __Vfunc_tb_top__DOT__read_pe_result__3128__Vfuncout = 0;
    CData/*3:0*/ __Vfunc_tb_top__DOT__read_pe_result__3128__pe_id;
    __Vfunc_tb_top__DOT__read_pe_result__3128__pe_id = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__read_pe_result__3129__Vfuncout;
    __Vfunc_tb_top__DOT__read_pe_result__3129__Vfuncout = 0;
    CData/*3:0*/ __Vfunc_tb_top__DOT__read_pe_result__3129__pe_id;
    __Vfunc_tb_top__DOT__read_pe_result__3129__pe_id = 0;
    std::string __Vtask_tb_top__DOT__pass__3130__msg;
    std::string __Vtask_tb_top__DOT__fail__3131__msg;
    std::string __Vtask_tb_top__DOT__fail__3131__reason;
    // Body
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel0;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel0: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel1;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel1: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 3U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 3U;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel2;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel2: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel3;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel3: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 4U;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel4;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel4: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel5;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel5: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 5U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 5U;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel6;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel6: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel7;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel7: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 6U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 6U;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel8;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel8: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel9;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel9: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 7U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 7U;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel10;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel10: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel11;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel11: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 8U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 8U;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel12;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel12: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel13;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel13: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 9U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 9U;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel14;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel14: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel15;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel15: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 0xaU;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 0xaU;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel16;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel16: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel17;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel17: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 0xbU;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 0xbU;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel18;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel18: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel19;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel19: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 0xcU;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 0xcU;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel20;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel20: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel21;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel21: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 0xdU;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 0xdU;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel22;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel22: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel23;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel23: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 0xeU;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 0xeU;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel24;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel24: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel25;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel25: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 0xfU;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0 = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id = 0xfU;
    vlSelf->__Vtask_tb_top__DOT__config_pe_safe__3098__cfg = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13487296394015209311ull);
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm = 0U;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__route;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__dst;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src1;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__src0;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__opcode;
    vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout 
        = (((QData)((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__imm)) 
            << 0x18U) | (QData)((IData)(((((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__route) 
                                           << 0x12U) 
                                          | ((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__dst) 
                                             << 0xeU)) 
                                         | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src1) 
                                             << 0xaU) 
                                            | (((IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__src0) 
                                                << 6U) 
                                               | (IData)(vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__opcode)))))));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg 
        = vlSelfRef.__Vfunc_tb_top__DOT__build_pe_config__3099__Vfuncout;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__cfg;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe_safe__3098__pe_id;
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7663349455255192545ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 343871257906778153ull);
    vlSelf->__Vtask_tb_top__DOT__config_pe__3100__data_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4271314952350918491ull);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__slot), 3U)));
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low 
        = (IData)(vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data);
    vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high 
        = (IData)((vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__config_data 
                   >> 0x20U));
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_high;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3101__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3102__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data 
        = (4U | vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3103__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3104__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3105__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3106__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9960360657750707590ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3107__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__status)) {
                goto __Vlabel26;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6042449492421994032ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3108__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3106__timeout);
        __Vlabel26: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__data_low;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__3109__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data = 0x1004U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3110__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data 
        = vlSelfRef.__Vtask_tb_top__DOT__config_pe__3100__cfg_addr_base;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3111__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data = 4U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3112__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__3113__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout = 0x64U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__3114__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10391873854542153327ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__3115__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__status)) {
                goto __Vlabel27;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17715243355070059595ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3116__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__3114__timeout);
        __Vlabel27: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n = 3U;
    vlSelf->__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3217622196196493342ull);
    vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__n;
    while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__3117__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pe = 0x10U;
    __Vtask_tb_top__DOT__run_cgra__3118__cycles = 0xaU;
    __Vtask_tb_top__DOT__apb_write__3119__data = 2U;
    __Vtask_tb_top__DOT__apb_write__3119__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__3119__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__3119__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_cycles__3120__n = 1U;
    __Vtask_tb_top__DOT__wait_cycles__3120__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__3120__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__3120__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__3120__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        __Vtask_tb_top__DOT__wait_cycles__3120__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__3120__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_top__DOT__apb_write__3121__data = 0U;
    __Vtask_tb_top__DOT__apb_write__3121__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__3121__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__3121__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_cycles__3122__n = 1U;
    __Vtask_tb_top__DOT__wait_cycles__3122__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__3122__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__3122__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__3122__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        __Vtask_tb_top__DOT__wait_cycles__3122__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__3122__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_top__DOT__apb_write__3123__data = 1U;
    __Vtask_tb_top__DOT__apb_write__3123__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__3123__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__3123__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_cycles__3124__n = __Vtask_tb_top__DOT__run_cgra__3118__cycles;
    __Vtask_tb_top__DOT__wait_cycles__3124__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__3124__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__3124__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__3124__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             31);
        __Vtask_tb_top__DOT__wait_cycles__3124__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__3124__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_top__DOT__apb_write__3125__data = 0U;
    __Vtask_tb_top__DOT__apb_write__3125__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__3125__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__3125__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt = 0U;
    __Vfunc_tb_top__DOT__read_pe_result__3126__pe_id = 0U;
    __Vfunc_tb_top__DOT__read_pe_result__3126__Vfuncout 
        = ((8U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
            ? ((4U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                ? ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.alu_result))
                : ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.alu_result)))
            : ((4U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                ? ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.alu_result))
                : ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3126__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.alu_result))));
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res 
        = __Vfunc_tb_top__DOT__read_pe_result__3126__Vfuncout;
    if (VL_LIKELY(((0xc8U == vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res)))) {
        vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt);
    } else {
        VL_WRITEF_NX("       AB03: PE0 expected 200, got %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res);
    }
    __Vfunc_tb_top__DOT__read_pe_result__3127__pe_id = 4U;
    __Vfunc_tb_top__DOT__read_pe_result__3127__Vfuncout 
        = ((8U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
            ? ((4U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                ? ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.alu_result))
                : ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.alu_result)))
            : ((4U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                ? ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.alu_result))
                : ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3127__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.alu_result))));
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res 
        = __Vfunc_tb_top__DOT__read_pe_result__3127__Vfuncout;
    if (VL_LIKELY(((0x190U == vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res)))) {
        vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt);
    } else {
        VL_WRITEF_NX("       AB03: PE4 expected 400, got %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res);
    }
    __Vfunc_tb_top__DOT__read_pe_result__3128__pe_id = 8U;
    __Vfunc_tb_top__DOT__read_pe_result__3128__Vfuncout 
        = ((8U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
            ? ((4U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                ? ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.alu_result))
                : ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.alu_result)))
            : ((4U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                ? ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.alu_result))
                : ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3128__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.alu_result))));
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res 
        = __Vfunc_tb_top__DOT__read_pe_result__3128__Vfuncout;
    if (VL_LIKELY(((0x258U == vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res)))) {
        vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt);
    } else {
        VL_WRITEF_NX("       AB03: PE8 expected 600, got %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res);
    }
    __Vfunc_tb_top__DOT__read_pe_result__3129__pe_id = 0xcU;
    __Vfunc_tb_top__DOT__read_pe_result__3129__Vfuncout 
        = ((8U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
            ? ((4U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                ? ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.alu_result))
                : ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.alu_result)))
            : ((4U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                ? ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.alu_result))
                : ((2U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                    ? ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.alu_result)
                    : ((1U & (IData)(__Vfunc_tb_top__DOT__read_pe_result__3129__pe_id))
                        ? vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.alu_result
                        : vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.alu_result))));
    vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res 
        = __Vfunc_tb_top__DOT__read_pe_result__3129__Vfuncout;
    if (VL_LIKELY(((0x320U == vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res)))) {
        vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt);
    } else {
        VL_WRITEF_NX("       AB03: PE12 expected 800, got %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__res);
    }
    if ((4U == vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt)) {
        __Vtask_tb_top__DOT__pass__3130__msg = std::string{"AB03: DMA Flood (4 corner PEs verified)"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__3130__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__3131__reason = VL_SFORMATF_N_NX("Only %0d/4 corner PEs correct",0,
                                                                   32,
                                                                   vlSelfRef.tb_top__DOT__run_suite_AB_advanced_stress__Vstatic__pass_cnt) ;
        __Vtask_tb_top__DOT__fail__3131__msg = std::string{"AB03: DMA Flood"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__3131__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__3131__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("\n[SUITE AB COMPLETE] Advanced stress tests finished.\n\n",0);
    VL_WRITEF_NX("\n\342\225\224\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\227\n\342\225\221                    COVERAGE REPORT                           \342\225\221\n\342\225\240\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\243\n",0);
    VL_WRITEF_NX("\342\225\221  Transfer Types:                                             \342\225\221\n\342\225\221    Single-beat (4-16B):     %6d hits                      \342\225\221\n\342\225\221    Multi-beat (20-512B):    %6d hits                      \342\225\221\n\342\225\221    Max-burst (516-1024B):   %6d hits                      \342\225\221\n",0,
                 32,vlSelfRef.tb_top__DOT__cov_single_beat,
                 32,vlSelfRef.tb_top__DOT__cov_multi_beat,
                 32,vlSelfRef.tb_top__DOT__cov_max_burst);
    VL_WRITEF_NX("\342\225\240\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\243\n\342\225\221  Stress & Corner Cases:                                      \342\225\221\n\342\225\221    4KB Boundary Tests:           0 hits                      \342\225\221\n\342\225\221    Stress Cycles:           %6d hits                      \342\225\221\n",0,
                 32,vlSelfRef.tb_top__DOT__cov_stress_cycles);
    VL_WRITEF_NX("\342\225\221    Reset Recovery Tests:         0 hits                      \342\225\221\n\342\225\221    Overlap Transactions:         0 hits                      \342\225\221\n\342\225\232\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\235\n\n",0);
    VL_WRITEF_NX("\n\342\225\224\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\227\n\342\225\221                   PROTOCOL STATISTICS                        \342\225\221\n\342\225\240\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\243\n",0);
    VL_WRITEF_NX("\342\225\221  AXI Transactions:                                           \342\225\221\n\342\225\221    AR (Read Address):      %6d                            \342\225\221\n\342\225\221    R  (Read Data):         %6d                            \342\225\221\n\342\225\221    AW (Write Address):     %6d                            \342\225\221\n\342\225\221    W  (Write Data):        %6d                            \342\225\221\n\342\225\221    B  (Write Response):    %6d                            \342\225\221\n",0,
                 32,vlSelfRef.tb_top__DOT__ar_txn_count,
                 32,vlSelfRef.tb_top__DOT__r_txn_count,
                 32,vlSelfRef.tb_top__DOT__aw_txn_count,
                 32,vlSelfRef.tb_top__DOT__w_txn_count,
                 32,vlSelfRef.tb_top__DOT__b_txn_count);
    VL_WRITEF_NX("\342\225\240\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\243\n\342\225\221  Protocol Errors:          %6d                            \342\225\221\n",0,
                 32,vlSelfRef.tb_top__DOT__assertion_errors);
    VL_WRITEF_NX("\342\225\232\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\235\n\n\n================================================================\n  FINAL RESULTS\n================================================================\n  PASSED: %0d\n  FAILED: %0d\n  ASSERTIONS: %0d errors\n  TOTAL:  %0d\n================================================================\n",0,
                 32,vlSelfRef.tb_top__DOT__pass_count,
                 32,vlSelfRef.tb_top__DOT__error_count,
                 32,vlSelfRef.tb_top__DOT__assertion_errors,
                 32,(vlSelfRef.tb_top__DOT__pass_count 
                     + vlSelfRef.tb_top__DOT__error_count));
    if (((0U == vlSelfRef.tb_top__DOT__error_count) 
         & (0U == vlSelfRef.tb_top__DOT__assertion_errors))) {
        VL_WRITEF_NX("\n  *** STATUS: PASSED (All Suites) - SILICON READY ***\n\n",0);
    } else {
        VL_WRITEF_NX("\n  *** STATUS: FAILED (%0d Errors) - REVIEW REQUIRED ***\n\n",0,
                     32,(vlSelfRef.tb_top__DOT__error_count 
                         + vlSelfRef.tb_top__DOT__assertion_errors));
    }
    VL_FINISH_MT("01_bench/tb_top.sv", 369, "");
}

VL_INLINE_OPT VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__2(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x1388ULL, 
                                             nullptr, 
                                             "01_bench/tb_top.sv", 
                                             31);
        vlSelfRef.tb_top__DOT__clk = (1U & (~ (IData)(vlSelfRef.tb_top__DOT__clk)));
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__act(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_top___024root___eval_triggers__act(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_triggers__act\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __Vtrigprevexpr_h598af589__0;
    __Vtrigprevexpr_h598af589__0 = 0;
    // Body
    __Vtrigprevexpr_h598af589__0 = ((IData)(vlSelfRef.tb_top__DOT__axi_bvalid_reg) 
                                    & (IData)(vlSelfRef.tb_top__DOT__axi_bready));
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.ready_out) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(1U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(2U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(3U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.ready_out) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(4U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(5U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(6U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.ready_out) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(7U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_20_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(8U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(9U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.ready_out) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0xaU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0xbU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_03_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0xcU, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.ready_out) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0xdU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0xeU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_12_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0xfU, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.ready_out) 
                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x10U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x11U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x12U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x13U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_13_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x14U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x15U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x16U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x17U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_30_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x18U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_21_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x19U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x1aU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x1bU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_22_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x1cU, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x1dU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x1eU, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_23_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x1fU, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x20U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_n_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x21U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x22U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_31_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x23U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x24U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_32_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x25U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x26U, ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__tile_33_w_ready__1)));
    vlSelfRef.__VactTriggered.setBit(0x27U, ((IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.ready_out) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__ready_out__1)));
    vlSelfRef.__VactTriggered.setBit(0x28U, ((IData)(vlSelfRef.tb_top__DOT__clk) 
                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__clk__0))));
    vlSelfRef.__VactTriggered.setBit(0x29U, ((~ (IData)(vlSelfRef.tb_top__DOT__rst_n)) 
                                             & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__rst_n__0)));
    vlSelfRef.__VactTriggered.setBit(0x2aU, ((~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__PVT__u_config_mem__DOT__rst_n)) 
                                             & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe____PVT__u_config_mem__DOT__rst_n__0)));
    vlSelfRef.__VactTriggered.setBit(0x2bU, vlSelfRef.__VdlySched.awaitingCurrentTime());
    vlSelfRef.__VactTriggered.setBit(0x2cU, ((IData)(vlSelfRef.tb_top__DOT__rst_n) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__rst_n__0)));
    vlSelfRef.__VactTriggered.setBit(0x2dU, ((IData)(vlSelfRef.tb_top__DOT__axi_arvalid) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_top__DOT__axi_arvalid__0)));
    vlSelfRef.__VactTriggered.setBit(0x2eU, ((IData)(__Vtrigprevexpr_h598af589__0) 
                                             != (IData)(vlSelfRef.__Vtrigprevexpr_h598af589__1)));
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
    vlSelfRef.__Vtrigprevexpr_h598af589__1 = __Vtrigprevexpr_h598af589__0;
    if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VactDidInit)))))) {
        vlSelfRef.__VactDidInit = 1U;
        vlSelfRef.__VactTriggered.setBit(0U, 1U);
        vlSelfRef.__VactTriggered.setBit(1U, 1U);
        vlSelfRef.__VactTriggered.setBit(2U, 1U);
        vlSelfRef.__VactTriggered.setBit(3U, 1U);
        vlSelfRef.__VactTriggered.setBit(4U, 1U);
        vlSelfRef.__VactTriggered.setBit(5U, 1U);
        vlSelfRef.__VactTriggered.setBit(6U, 1U);
        vlSelfRef.__VactTriggered.setBit(7U, 1U);
        vlSelfRef.__VactTriggered.setBit(8U, 1U);
        vlSelfRef.__VactTriggered.setBit(9U, 1U);
        vlSelfRef.__VactTriggered.setBit(0xaU, 1U);
        vlSelfRef.__VactTriggered.setBit(0xbU, 1U);
        vlSelfRef.__VactTriggered.setBit(0xcU, 1U);
        vlSelfRef.__VactTriggered.setBit(0xdU, 1U);
        vlSelfRef.__VactTriggered.setBit(0xeU, 1U);
        vlSelfRef.__VactTriggered.setBit(0xfU, 1U);
        vlSelfRef.__VactTriggered.setBit(0x10U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x11U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x12U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x13U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x14U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x15U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x16U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x17U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x18U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x19U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x1aU, 1U);
        vlSelfRef.__VactTriggered.setBit(0x1bU, 1U);
        vlSelfRef.__VactTriggered.setBit(0x1cU, 1U);
        vlSelfRef.__VactTriggered.setBit(0x1dU, 1U);
        vlSelfRef.__VactTriggered.setBit(0x1eU, 1U);
        vlSelfRef.__VactTriggered.setBit(0x1fU, 1U);
        vlSelfRef.__VactTriggered.setBit(0x20U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x21U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x22U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x23U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x24U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x25U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x26U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x27U, 1U);
        vlSelfRef.__VactTriggered.setBit(0x2cU, 1U);
        vlSelfRef.__VactTriggered.setBit(0x2dU, 1U);
        vlSelfRef.__VactTriggered.setBit(0x2eU, 1U);
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_top___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0(Vtb_top_cgra_pe__A4* vlSelf);
void Vtb_top___024root___act_comb__TOP__0(Vtb_top___024root* vlSelf);
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

void Vtb_top___024root___eval_act(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_act\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0x790000000000ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
        Vtb_top___024root___act_comb__TOP__0(vlSelf);
    }
    if ((7ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_sequent__TOP__0(vlSelf);
        Vtb_top_cgra_pe__A4___act_sequent__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe));
    }
    if ((0x3fULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__1(vlSelf);
        vlSelfRef.__Vm_traceActivity[0xbU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe));
    }
    if ((0x1c7ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__2(vlSelf);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe));
    }
    if ((0xe3fULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__3(vlSelf);
        vlSelfRef.__Vm_traceActivity[0xdU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe));
    }
    if ((0x1ffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__4(vlSelf);
    }
    if ((0x1c001c7ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__5(vlSelf);
        vlSelfRef.__Vm_traceActivity[0xeU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe));
    }
    if ((0x71ffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__6(vlSelf);
        vlSelfRef.__Vm_traceActivity[0xfU] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe));
    }
    if ((0x18e3fULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__7(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x10U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe));
    }
    if ((0x601c001c7ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__8(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x11U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe));
    }
    if ((0x7fffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__9(vlSelf);
    }
    if ((0x1c071ffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__10(vlSelf);
    }
    if ((0xe7fffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__11(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x12U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe));
    }
    if ((0xfc071ffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__12(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x13U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe));
    }
    if ((0xfffffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__13(vlSelf);
    }
    if ((0x3fffffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__14(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x14U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe));
    }
    if ((0x60fc071ffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__15(vlSelf);
    }
    if ((0x1e0fc071ffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__16(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x15U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe));
    }
    if ((0x7fce7fffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__17(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x16U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe));
    }
    if ((0x1ffffffffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__18(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x17U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe));
    }
    if ((0x7e7fce7fffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__19(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x18U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe));
    }
    if ((0xffffffffffULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtb_top___024root___act_comb__TOP__20(vlSelf);
        vlSelfRef.__Vm_traceActivity[0x19U] = 1U;
        Vtb_top_cgra_pe__A4___act_comb__TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe__0((&vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe));
        Vtb_top___024root___act_comb__TOP__21(vlSelf);
    }
}

VL_INLINE_OPT void Vtb_top___024root___act_sequent__TOP__0(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_sequent__TOP__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.ready_out)))) 
                       | (((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_w) 
                               >> 4U)) & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l) 
                                          >> 3U)) | 
                          ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l) 
                             >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_s) 
                                           >> 4U)) 
                                       | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready)))) 
                           | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l) 
                                >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_e) 
                                              >> 4U)) 
                                          | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready)))) 
                              | ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_n) 
                                     >> 4U)) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_l)))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.ready_out))))) 
                           || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_w) 
                                          >> 1U)) & 
                                      ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e) 
                                       >> 3U))) || 
                               ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e) 
                                        >> 2U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_s) 
                                                    >> 1U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready))))) 
                                || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e) 
                                            >> 1U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_e) 
                                                  >> 1U)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready))))) 
                                    || (1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_n) 
                                                  >> 1U)) 
                                              & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_e)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.ready_out))))) 
                           || ((1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_w) 
                                          >> 2U)) & 
                                      ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s) 
                                       >> 3U))) || 
                               ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s) 
                                        >> 2U) & ((~ 
                                                   ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_s) 
                                                    >> 2U)) 
                                                  | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_10_n_ready))))) 
                                || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s) 
                                            >> 1U) 
                                           & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_e) 
                                                  >> 2U)) 
                                              | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready))))) 
                                    || (1U & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__grant_n) 
                                                  >> 2U)) 
                                              & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_router__DOT__req_s)))))))))));
}

VL_INLINE_OPT void Vtb_top___024root___act_comb__TOP__1(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___act_comb__TOP__1\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_w_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_w) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_w) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_l) 
                                                   >> 3U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_w) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_s) 
                                               >> 3U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_e) 
                                                   >> 3U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready))))) 
                                       || (1U & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_n) 
                                                   >> 3U)) 
                                                 & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_w)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__router_to_pe_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_l) 
                    & ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l) 
                         >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_l) 
                                       >> 4U)) | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.ready_out)))) 
                       | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l) 
                            >> 3U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_w) 
                                          >> 4U)) | 
                                      (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_e_ready)))) 
                          | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l) 
                               >> 2U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_s) 
                                             >> 4U)) 
                                         | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready)))) 
                             | ((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l) 
                                  >> 1U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_e) 
                                                >> 4U)) 
                                            | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready)))) 
                                | ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_n) 
                                       >> 4U)) & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_l)))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_e_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_e) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_e) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_l) 
                                                   >> 1U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_w) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_s) 
                                               >> 1U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_e) 
                                                   >> 1U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready))))) 
                                       || (1U & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_n) 
                                                   >> 1U)) 
                                                 & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_e)))))))))));
    vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_01_s_ready 
        = (1U & (~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_s) 
                    & ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__b_val_s) 
                       && ((IData)((((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s) 
                                     >> 4U) & ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_l) 
                                                   >> 2U)) 
                                               | (~ (IData)(vlSymsp->TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.ready_out))))) 
                           || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s) 
                                       >> 3U) & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_w) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_00_e_ready))))) 
                               || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s) 
                                           >> 2U) & 
                                          ((~ ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_s) 
                                               >> 2U)) 
                                           | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_11_n_ready))))) 
                                   || ((1U & (((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s) 
                                               >> 1U) 
                                              & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_e) 
                                                   >> 2U)) 
                                                 | (~ (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__tile_02_w_ready))))) 
                                       || (1U & ((~ 
                                                  ((IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__grant_n) 
                                                   >> 2U)) 
                                                 & (IData)(vlSelfRef.tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_router__DOT__req_s)))))))))));
}

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
