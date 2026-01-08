// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top___024root.h"

VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__1__10(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial__TOP__Vtiming__1__10\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    std::string __Vtask_tb_top__DOT__pass__2182__msg;
    std::string __Vtask_tb_top__DOT__fail__2183__msg;
    std::string __Vtask_tb_top__DOT__fail__2183__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2184__addr;
    __Vtask_tb_top__DOT__apb_write__2184__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2184__data;
    __Vtask_tb_top__DOT__apb_write__2184__data = 0;
    CData/*1:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2185__bank;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2185__bank = 0;
    SData/*11:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2185__offset;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2185__offset = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2185__value;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2185__value = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2186__addr;
    __Vtask_tb_top__DOT__ram_write__2186__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2186__data;
    __Vtask_tb_top__DOT__ram_write__2186__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2187__addr;
    __Vtask_tb_top__DOT__apb_write__2187__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2187__data;
    __Vtask_tb_top__DOT__apb_write__2187__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2188__addr;
    __Vtask_tb_top__DOT__apb_write__2188__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2188__data;
    __Vtask_tb_top__DOT__apb_write__2188__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2189__addr;
    __Vtask_tb_top__DOT__apb_write__2189__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2189__data;
    __Vtask_tb_top__DOT__apb_write__2189__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2190__addr;
    __Vtask_tb_top__DOT__apb_write__2190__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2190__data;
    __Vtask_tb_top__DOT__apb_write__2190__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2191__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2191__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2192__addr;
    __Vtask_tb_top__DOT__apb_read__2192__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2192__data;
    __Vtask_tb_top__DOT__apb_read__2192__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2193__n;
    __Vtask_tb_top__DOT__wait_cycles__2193__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2193__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2193__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    CData/*3:0*/ __Vtask_tb_top__DOT__config_pe__2194__pe_id;
    __Vtask_tb_top__DOT__config_pe__2194__pe_id = 0;
    CData/*3:0*/ __Vtask_tb_top__DOT__config_pe__2194__slot;
    __Vtask_tb_top__DOT__config_pe__2194__slot = 0;
    QData/*63:0*/ __Vtask_tb_top__DOT__config_pe__2194__config_data;
    __Vtask_tb_top__DOT__config_pe__2194__config_data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2195__addr;
    __Vtask_tb_top__DOT__ram_write__2195__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2195__data;
    __Vtask_tb_top__DOT__ram_write__2195__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2196__addr;
    __Vtask_tb_top__DOT__apb_write__2196__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2196__data;
    __Vtask_tb_top__DOT__apb_write__2196__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2197__addr;
    __Vtask_tb_top__DOT__apb_write__2197__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2197__data;
    __Vtask_tb_top__DOT__apb_write__2197__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2198__addr;
    __Vtask_tb_top__DOT__apb_write__2198__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2198__data;
    __Vtask_tb_top__DOT__apb_write__2198__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2199__addr;
    __Vtask_tb_top__DOT__apb_write__2199__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2199__data;
    __Vtask_tb_top__DOT__apb_write__2199__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2200__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2200__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2201__addr;
    __Vtask_tb_top__DOT__apb_read__2201__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2201__data;
    __Vtask_tb_top__DOT__apb_read__2201__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2202__n;
    __Vtask_tb_top__DOT__wait_cycles__2202__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2202__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2202__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2203__addr;
    __Vtask_tb_top__DOT__ram_write__2203__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2203__data;
    __Vtask_tb_top__DOT__ram_write__2203__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2204__addr;
    __Vtask_tb_top__DOT__apb_write__2204__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2204__data;
    __Vtask_tb_top__DOT__apb_write__2204__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2205__addr;
    __Vtask_tb_top__DOT__apb_write__2205__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2205__data;
    __Vtask_tb_top__DOT__apb_write__2205__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2206__addr;
    __Vtask_tb_top__DOT__apb_write__2206__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2206__data;
    __Vtask_tb_top__DOT__apb_write__2206__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2207__addr;
    __Vtask_tb_top__DOT__apb_write__2207__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2207__data;
    __Vtask_tb_top__DOT__apb_write__2207__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2208__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2208__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2209__addr;
    __Vtask_tb_top__DOT__apb_read__2209__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2209__data;
    __Vtask_tb_top__DOT__apb_read__2209__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2210__n;
    __Vtask_tb_top__DOT__wait_cycles__2210__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2210__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2210__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2211__addr;
    __Vtask_tb_top__DOT__apb_write__2211__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2211__data;
    __Vtask_tb_top__DOT__apb_write__2211__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2212__addr;
    __Vtask_tb_top__DOT__apb_read__2212__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2212__data;
    __Vtask_tb_top__DOT__apb_read__2212__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2213__addr;
    __Vtask_tb_top__DOT__apb_read__2213__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2213__data;
    __Vtask_tb_top__DOT__apb_read__2213__data = 0;
    std::string __Vtask_tb_top__DOT__fail__2214__msg;
    std::string __Vtask_tb_top__DOT__fail__2214__reason;
    CData/*1:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2215__bank;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2215__bank = 0;
    SData/*11:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2215__offset;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2215__offset = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2215__value;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2215__value = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2216__addr;
    __Vtask_tb_top__DOT__ram_write__2216__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2216__data;
    __Vtask_tb_top__DOT__ram_write__2216__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2217__addr;
    __Vtask_tb_top__DOT__apb_write__2217__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2217__data;
    __Vtask_tb_top__DOT__apb_write__2217__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2218__addr;
    __Vtask_tb_top__DOT__apb_write__2218__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2218__data;
    __Vtask_tb_top__DOT__apb_write__2218__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2219__addr;
    __Vtask_tb_top__DOT__apb_write__2219__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2219__data;
    __Vtask_tb_top__DOT__apb_write__2219__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2220__addr;
    __Vtask_tb_top__DOT__apb_write__2220__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2220__data;
    __Vtask_tb_top__DOT__apb_write__2220__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2221__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2221__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2222__addr;
    __Vtask_tb_top__DOT__apb_read__2222__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2222__data;
    __Vtask_tb_top__DOT__apb_read__2222__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2223__n;
    __Vtask_tb_top__DOT__wait_cycles__2223__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2223__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2223__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    CData/*3:0*/ __Vtask_tb_top__DOT__config_pe__2224__pe_id;
    __Vtask_tb_top__DOT__config_pe__2224__pe_id = 0;
    CData/*3:0*/ __Vtask_tb_top__DOT__config_pe__2224__slot;
    __Vtask_tb_top__DOT__config_pe__2224__slot = 0;
    QData/*63:0*/ __Vtask_tb_top__DOT__config_pe__2224__config_data;
    __Vtask_tb_top__DOT__config_pe__2224__config_data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2225__addr;
    __Vtask_tb_top__DOT__ram_write__2225__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2225__data;
    __Vtask_tb_top__DOT__ram_write__2225__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2226__addr;
    __Vtask_tb_top__DOT__apb_write__2226__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2226__data;
    __Vtask_tb_top__DOT__apb_write__2226__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2227__addr;
    __Vtask_tb_top__DOT__apb_write__2227__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2227__data;
    __Vtask_tb_top__DOT__apb_write__2227__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2228__addr;
    __Vtask_tb_top__DOT__apb_write__2228__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2228__data;
    __Vtask_tb_top__DOT__apb_write__2228__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2229__addr;
    __Vtask_tb_top__DOT__apb_write__2229__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2229__data;
    __Vtask_tb_top__DOT__apb_write__2229__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2230__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2230__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2231__addr;
    __Vtask_tb_top__DOT__apb_read__2231__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2231__data;
    __Vtask_tb_top__DOT__apb_read__2231__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2232__n;
    __Vtask_tb_top__DOT__wait_cycles__2232__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2232__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2232__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2233__addr;
    __Vtask_tb_top__DOT__ram_write__2233__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2233__data;
    __Vtask_tb_top__DOT__ram_write__2233__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2234__addr;
    __Vtask_tb_top__DOT__apb_write__2234__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2234__data;
    __Vtask_tb_top__DOT__apb_write__2234__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2235__addr;
    __Vtask_tb_top__DOT__apb_write__2235__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2235__data;
    __Vtask_tb_top__DOT__apb_write__2235__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2236__addr;
    __Vtask_tb_top__DOT__apb_write__2236__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2236__data;
    __Vtask_tb_top__DOT__apb_write__2236__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2237__addr;
    __Vtask_tb_top__DOT__apb_write__2237__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2237__data;
    __Vtask_tb_top__DOT__apb_write__2237__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2238__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2238__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2239__addr;
    __Vtask_tb_top__DOT__apb_read__2239__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2239__data;
    __Vtask_tb_top__DOT__apb_read__2239__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2240__n;
    __Vtask_tb_top__DOT__wait_cycles__2240__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2240__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2240__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2241__addr;
    __Vtask_tb_top__DOT__apb_write__2241__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2241__data;
    __Vtask_tb_top__DOT__apb_write__2241__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2242__addr;
    __Vtask_tb_top__DOT__apb_read__2242__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2242__data;
    __Vtask_tb_top__DOT__apb_read__2242__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2243__addr;
    __Vtask_tb_top__DOT__apb_read__2243__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2243__data;
    __Vtask_tb_top__DOT__apb_read__2243__data = 0;
    std::string __Vtask_tb_top__DOT__fail__2244__msg;
    std::string __Vtask_tb_top__DOT__fail__2244__reason;
    std::string __Vtask_tb_top__DOT__pass__2245__msg;
    std::string __Vtask_tb_top__DOT__fail__2246__msg;
    std::string __Vtask_tb_top__DOT__fail__2246__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2247__addr;
    __Vtask_tb_top__DOT__apb_write__2247__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2247__data;
    __Vtask_tb_top__DOT__apb_write__2247__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2249__addr;
    __Vtask_tb_top__DOT__ram_write__2249__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2249__data;
    __Vtask_tb_top__DOT__ram_write__2249__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2250__addr;
    __Vtask_tb_top__DOT__apb_write__2250__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2250__data;
    __Vtask_tb_top__DOT__apb_write__2250__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2251__addr;
    __Vtask_tb_top__DOT__apb_write__2251__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2251__data;
    __Vtask_tb_top__DOT__apb_write__2251__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2252__addr;
    __Vtask_tb_top__DOT__apb_write__2252__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2252__data;
    __Vtask_tb_top__DOT__apb_write__2252__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2253__addr;
    __Vtask_tb_top__DOT__apb_write__2253__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2253__data;
    __Vtask_tb_top__DOT__apb_write__2253__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2254__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2254__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2255__addr;
    __Vtask_tb_top__DOT__apb_read__2255__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2255__data;
    __Vtask_tb_top__DOT__apb_read__2255__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2256__n;
    __Vtask_tb_top__DOT__wait_cycles__2256__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2256__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2256__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2257__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2257__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2257__addr;
    __Vfunc_tb_top__DOT__ram_read__2257__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2258__msg;
    std::string __Vtask_tb_top__DOT__fail__2259__msg;
    std::string __Vtask_tb_top__DOT__fail__2259__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2260__addr;
    __Vtask_tb_top__DOT__ram_write__2260__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2260__data;
    __Vtask_tb_top__DOT__ram_write__2260__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2261__addr;
    __Vtask_tb_top__DOT__apb_write__2261__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2261__data;
    __Vtask_tb_top__DOT__apb_write__2261__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2262__addr;
    __Vtask_tb_top__DOT__apb_write__2262__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2262__data;
    __Vtask_tb_top__DOT__apb_write__2262__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2263__addr;
    __Vtask_tb_top__DOT__apb_write__2263__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2263__data;
    __Vtask_tb_top__DOT__apb_write__2263__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2264__addr;
    __Vtask_tb_top__DOT__apb_write__2264__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2264__data;
    __Vtask_tb_top__DOT__apb_write__2264__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2265__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2265__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2266__addr;
    __Vtask_tb_top__DOT__apb_read__2266__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2266__data;
    __Vtask_tb_top__DOT__apb_read__2266__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2267__n;
    __Vtask_tb_top__DOT__wait_cycles__2267__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2267__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2267__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2268__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2268__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2268__addr;
    __Vfunc_tb_top__DOT__ram_read__2268__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2269__msg;
    std::string __Vtask_tb_top__DOT__fail__2270__msg;
    std::string __Vtask_tb_top__DOT__fail__2270__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2271__addr;
    __Vtask_tb_top__DOT__ram_write__2271__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2271__data;
    __Vtask_tb_top__DOT__ram_write__2271__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2272__addr;
    __Vtask_tb_top__DOT__ram_write__2272__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2272__data;
    __Vtask_tb_top__DOT__ram_write__2272__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2273__addr;
    __Vtask_tb_top__DOT__ram_write__2273__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2273__data;
    __Vtask_tb_top__DOT__ram_write__2273__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2274__addr;
    __Vtask_tb_top__DOT__ram_write__2274__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2274__data;
    __Vtask_tb_top__DOT__ram_write__2274__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2275__addr;
    __Vtask_tb_top__DOT__ram_write__2275__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2275__data;
    __Vtask_tb_top__DOT__ram_write__2275__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2276__addr;
    __Vtask_tb_top__DOT__ram_write__2276__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2276__data;
    __Vtask_tb_top__DOT__ram_write__2276__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2277__addr;
    __Vtask_tb_top__DOT__ram_write__2277__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2277__data;
    __Vtask_tb_top__DOT__ram_write__2277__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2278__addr;
    __Vtask_tb_top__DOT__ram_write__2278__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2278__data;
    __Vtask_tb_top__DOT__ram_write__2278__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2279__addr;
    __Vtask_tb_top__DOT__apb_write__2279__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2279__data;
    __Vtask_tb_top__DOT__apb_write__2279__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2280__addr;
    __Vtask_tb_top__DOT__apb_write__2280__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2280__data;
    __Vtask_tb_top__DOT__apb_write__2280__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2281__addr;
    __Vtask_tb_top__DOT__apb_write__2281__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2281__data;
    __Vtask_tb_top__DOT__apb_write__2281__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2282__addr;
    __Vtask_tb_top__DOT__apb_write__2282__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2282__data;
    __Vtask_tb_top__DOT__apb_write__2282__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2283__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2283__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2284__addr;
    __Vtask_tb_top__DOT__apb_read__2284__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2284__data;
    __Vtask_tb_top__DOT__apb_read__2284__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2285__n;
    __Vtask_tb_top__DOT__wait_cycles__2285__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2285__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2285__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2286__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2286__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2286__addr;
    __Vfunc_tb_top__DOT__ram_read__2286__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2287__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2287__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2287__addr;
    __Vfunc_tb_top__DOT__ram_read__2287__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2288__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2288__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2288__addr;
    __Vfunc_tb_top__DOT__ram_read__2288__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2289__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2289__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2289__addr;
    __Vfunc_tb_top__DOT__ram_read__2289__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2290__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2290__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2290__addr;
    __Vfunc_tb_top__DOT__ram_read__2290__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2291__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2291__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2291__addr;
    __Vfunc_tb_top__DOT__ram_read__2291__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2292__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2292__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2292__addr;
    __Vfunc_tb_top__DOT__ram_read__2292__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2293__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2293__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2293__addr;
    __Vfunc_tb_top__DOT__ram_read__2293__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2294__msg;
    std::string __Vtask_tb_top__DOT__fail__2295__msg;
    std::string __Vtask_tb_top__DOT__fail__2295__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2296__addr;
    __Vtask_tb_top__DOT__ram_write__2296__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2296__data;
    __Vtask_tb_top__DOT__ram_write__2296__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2297__addr;
    __Vtask_tb_top__DOT__ram_write__2297__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2297__data;
    __Vtask_tb_top__DOT__ram_write__2297__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2298__addr;
    __Vtask_tb_top__DOT__ram_write__2298__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2298__data;
    __Vtask_tb_top__DOT__ram_write__2298__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2299__addr;
    __Vtask_tb_top__DOT__ram_write__2299__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2299__data;
    __Vtask_tb_top__DOT__ram_write__2299__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2300__addr;
    __Vtask_tb_top__DOT__apb_write__2300__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2300__data;
    __Vtask_tb_top__DOT__apb_write__2300__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2301__addr;
    __Vtask_tb_top__DOT__apb_write__2301__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2301__data;
    __Vtask_tb_top__DOT__apb_write__2301__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2302__addr;
    __Vtask_tb_top__DOT__apb_write__2302__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2302__data;
    __Vtask_tb_top__DOT__apb_write__2302__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2303__addr;
    __Vtask_tb_top__DOT__apb_write__2303__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2303__data;
    __Vtask_tb_top__DOT__apb_write__2303__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2304__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2304__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2305__addr;
    __Vtask_tb_top__DOT__apb_read__2305__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2305__data;
    __Vtask_tb_top__DOT__apb_read__2305__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2306__n;
    __Vtask_tb_top__DOT__wait_cycles__2306__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2306__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2306__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2307__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2307__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2307__addr;
    __Vfunc_tb_top__DOT__ram_read__2307__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2308__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2308__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2308__addr;
    __Vfunc_tb_top__DOT__ram_read__2308__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2309__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2309__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2309__addr;
    __Vfunc_tb_top__DOT__ram_read__2309__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2310__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2310__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2310__addr;
    __Vfunc_tb_top__DOT__ram_read__2310__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2311__msg;
    std::string __Vtask_tb_top__DOT__fail__2312__msg;
    std::string __Vtask_tb_top__DOT__fail__2312__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2313__addr;
    __Vtask_tb_top__DOT__ram_write__2313__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2313__data;
    __Vtask_tb_top__DOT__ram_write__2313__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2314__addr;
    __Vtask_tb_top__DOT__ram_write__2314__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2314__data;
    __Vtask_tb_top__DOT__ram_write__2314__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2315__addr;
    __Vtask_tb_top__DOT__ram_write__2315__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2315__data;
    __Vtask_tb_top__DOT__ram_write__2315__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2316__addr;
    __Vtask_tb_top__DOT__ram_write__2316__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2316__data;
    __Vtask_tb_top__DOT__ram_write__2316__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2317__addr;
    __Vtask_tb_top__DOT__apb_write__2317__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2317__data;
    __Vtask_tb_top__DOT__apb_write__2317__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2318__addr;
    __Vtask_tb_top__DOT__apb_write__2318__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2318__data;
    __Vtask_tb_top__DOT__apb_write__2318__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2319__addr;
    __Vtask_tb_top__DOT__apb_write__2319__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2319__data;
    __Vtask_tb_top__DOT__apb_write__2319__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2320__addr;
    __Vtask_tb_top__DOT__apb_write__2320__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2320__data;
    __Vtask_tb_top__DOT__apb_write__2320__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2321__addr;
    __Vtask_tb_top__DOT__apb_read__2321__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2321__data;
    __Vtask_tb_top__DOT__apb_read__2321__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2322__addr;
    __Vtask_tb_top__DOT__apb_read__2322__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2322__data;
    __Vtask_tb_top__DOT__apb_read__2322__data = 0;
    std::string __Vtask_tb_top__DOT__fail__2323__msg;
    std::string __Vtask_tb_top__DOT__fail__2323__reason;
    std::string __Vtask_tb_top__DOT__pass__2324__msg;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2325__addr;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2325__data;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2326__addr;
    __Vtask_tb_top__DOT__apb_write__2326__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2326__data;
    __Vtask_tb_top__DOT__apb_write__2326__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2327__addr;
    __Vtask_tb_top__DOT__apb_write__2327__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2327__data;
    __Vtask_tb_top__DOT__apb_write__2327__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2328__addr;
    __Vtask_tb_top__DOT__apb_write__2328__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2328__data;
    __Vtask_tb_top__DOT__apb_write__2328__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2329__addr;
    __Vtask_tb_top__DOT__apb_write__2329__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2329__data;
    __Vtask_tb_top__DOT__apb_write__2329__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2330__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2330__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2331__addr;
    __Vtask_tb_top__DOT__apb_read__2331__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2331__data;
    __Vtask_tb_top__DOT__apb_read__2331__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2332__n;
    __Vtask_tb_top__DOT__wait_cycles__2332__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2332__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2332__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2333__addr;
    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2334__msg;
    std::string __Vtask_tb_top__DOT__fail__2335__msg;
    std::string __Vtask_tb_top__DOT__fail__2335__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2337__addr;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2337__data;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2338__addr;
    __Vtask_tb_top__DOT__apb_write__2338__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2338__data;
    __Vtask_tb_top__DOT__apb_write__2338__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2339__addr;
    __Vtask_tb_top__DOT__apb_write__2339__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2339__data;
    __Vtask_tb_top__DOT__apb_write__2339__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2340__addr;
    __Vtask_tb_top__DOT__apb_write__2340__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2340__data;
    __Vtask_tb_top__DOT__apb_write__2340__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2341__addr;
    __Vtask_tb_top__DOT__apb_write__2341__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2341__data;
    __Vtask_tb_top__DOT__apb_write__2341__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2342__addr;
    __Vtask_tb_top__DOT__apb_read__2342__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2342__data;
    __Vtask_tb_top__DOT__apb_read__2342__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2343__addr;
    __Vtask_tb_top__DOT__apb_read__2343__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2343__data;
    __Vtask_tb_top__DOT__apb_read__2343__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2344__addr;
    __Vtask_tb_top__DOT__apb_read__2344__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2344__data;
    __Vtask_tb_top__DOT__apb_read__2344__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2345__addr;
    __Vtask_tb_top__DOT__ram_write__2345__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2345__data;
    __Vtask_tb_top__DOT__ram_write__2345__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2346__addr;
    __Vtask_tb_top__DOT__apb_write__2346__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2346__data;
    __Vtask_tb_top__DOT__apb_write__2346__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2347__addr;
    __Vtask_tb_top__DOT__apb_write__2347__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2347__data;
    __Vtask_tb_top__DOT__apb_write__2347__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2348__addr;
    __Vtask_tb_top__DOT__apb_write__2348__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2348__data;
    __Vtask_tb_top__DOT__apb_write__2348__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2349__addr;
    __Vtask_tb_top__DOT__apb_write__2349__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2349__data;
    __Vtask_tb_top__DOT__apb_write__2349__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2350__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2350__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2351__addr;
    __Vtask_tb_top__DOT__apb_read__2351__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2351__data;
    __Vtask_tb_top__DOT__apb_read__2351__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2352__n;
    __Vtask_tb_top__DOT__wait_cycles__2352__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2352__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2352__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2353__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2353__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2353__addr;
    __Vfunc_tb_top__DOT__ram_read__2353__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2354__msg;
    std::string __Vtask_tb_top__DOT__fail__2355__msg;
    std::string __Vtask_tb_top__DOT__fail__2355__reason;
    std::string __Vtask_tb_top__DOT__fail__2356__msg;
    std::string __Vtask_tb_top__DOT__fail__2356__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2357__addr;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2357__data;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2358__addr;
    __Vtask_tb_top__DOT__apb_write__2358__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2358__data;
    __Vtask_tb_top__DOT__apb_write__2358__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2359__addr;
    __Vtask_tb_top__DOT__apb_write__2359__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2359__data;
    __Vtask_tb_top__DOT__apb_write__2359__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2360__addr;
    __Vtask_tb_top__DOT__apb_write__2360__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2360__data;
    __Vtask_tb_top__DOT__apb_write__2360__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2361__addr;
    __Vtask_tb_top__DOT__apb_write__2361__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2361__data;
    __Vtask_tb_top__DOT__apb_write__2361__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2362__addr;
    __Vtask_tb_top__DOT__apb_read__2362__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2362__data;
    __Vtask_tb_top__DOT__apb_read__2362__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2363__addr;
    __Vtask_tb_top__DOT__apb_read__2363__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2363__data;
    __Vtask_tb_top__DOT__apb_read__2363__data = 0;
    std::string __Vtask_tb_top__DOT__fail__2364__msg;
    std::string __Vtask_tb_top__DOT__fail__2364__reason;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2365__addr;
    __Vfunc_tb_top__DOT__ram_read__2365__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2366__msg;
    std::string __Vtask_tb_top__DOT__fail__2367__msg;
    std::string __Vtask_tb_top__DOT__fail__2367__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2368__addr;
    __Vtask_tb_top__DOT__ram_write__2368__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2368__data;
    __Vtask_tb_top__DOT__ram_write__2368__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2369__addr;
    __Vtask_tb_top__DOT__ram_write__2369__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2369__data;
    __Vtask_tb_top__DOT__ram_write__2369__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2370__addr;
    __Vtask_tb_top__DOT__ram_write__2370__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2370__data;
    __Vtask_tb_top__DOT__ram_write__2370__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2371__addr;
    __Vtask_tb_top__DOT__ram_write__2371__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2371__data;
    __Vtask_tb_top__DOT__ram_write__2371__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2372__addr;
    __Vtask_tb_top__DOT__apb_write__2372__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2372__data;
    __Vtask_tb_top__DOT__apb_write__2372__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2373__addr;
    __Vtask_tb_top__DOT__apb_write__2373__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2373__data;
    __Vtask_tb_top__DOT__apb_write__2373__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2374__addr;
    __Vtask_tb_top__DOT__apb_write__2374__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2374__data;
    __Vtask_tb_top__DOT__apb_write__2374__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2375__addr;
    __Vtask_tb_top__DOT__apb_write__2375__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2375__data;
    __Vtask_tb_top__DOT__apb_write__2375__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2376__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2376__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2377__addr;
    __Vtask_tb_top__DOT__apb_read__2377__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2377__data;
    __Vtask_tb_top__DOT__apb_read__2377__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2378__n;
    __Vtask_tb_top__DOT__wait_cycles__2378__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2379__addr;
    __Vfunc_tb_top__DOT__ram_read__2379__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2380__addr;
    __Vfunc_tb_top__DOT__ram_read__2380__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2381__addr;
    __Vfunc_tb_top__DOT__ram_read__2381__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2382__addr;
    __Vfunc_tb_top__DOT__ram_read__2382__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2383__msg;
    std::string __Vtask_tb_top__DOT__fail__2384__msg;
    std::string __Vtask_tb_top__DOT__fail__2384__reason;
    // Body
    if (((0U != (3U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)) 
         == (IData)(vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val))) {
        __Vtask_tb_top__DOT__pass__2182__msg = std::string{"Y05: IRQ = (STATUS & MASK) Verified"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2182__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2183__reason = VL_SFORMATF_N_NX("STATUS=0x%02x, MASK=0x03, IRQ=%b",0,
                                                                   2,
                                                                   (3U 
                                                                    & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata),
                                                                   1,
                                                                   (IData)(vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val)) ;
        __Vtask_tb_top__DOT__fail__2183__msg = std::string{"Y05: IRQ Logic Mismatch"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2183__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2183__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[Y06] Testing back-to-back CU execution...\n",0);
    __Vtask_tb_top__DOT__apb_write__2184__data = 2U;
    __Vtask_tb_top__DOT__apb_write__2184__addr = 0x34U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2184__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2184__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    VL_WRITEF_NX("[Y06] Run 1: Starting CU...\n",0);
    __Vtask_tb_top__DOT__dma_load_tile_bank__2185__value = 0xaaaa5555U;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2185__offset = 0U;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2185__bank = 0U;
    vlSelfRef.tb_top__DOT__dma_load_tile_bank__Vstatic__tile_addr 
        = (0x10000000U | (((IData)(__Vtask_tb_top__DOT__dma_load_tile_bank__2185__bank) 
                           << 0xcU) | (IData)(__Vtask_tb_top__DOT__dma_load_tile_bank__2185__offset)));
    __Vtask_tb_top__DOT__ram_write__2186__data = __Vtask_tb_top__DOT__dma_load_tile_bank__2185__value;
    __Vtask_tb_top__DOT__ram_write__2186__addr = 0x1000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2186__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2186__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2186__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2186__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2186__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2186__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2186__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2186__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2187__data = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__2187__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2187__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2187__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2188__data = vlSelfRef.tb_top__DOT__dma_load_tile_bank__Vstatic__tile_addr;
    __Vtask_tb_top__DOT__apb_write__2188__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2188__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2188__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2189__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2189__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2189__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2189__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2190__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2190__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2190__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2190__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2191__timeout = 0x64U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2191__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2192__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2192__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2192__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2192__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel0;
            }
            __Vtask_tb_top__DOT__wait_cycles__2193__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2193__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2193__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2193__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2193__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2193__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2193__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2191__timeout);
        __Vlabel0: ;
    }
    __Vtask_tb_top__DOT__config_pe__2194__config_data = 0x110ULL;
    __Vtask_tb_top__DOT__config_pe__2194__slot = 0U;
    __Vtask_tb_top__DOT__config_pe__2194__pe_id = 0U;
    vlSelfRef.tb_top__DOT__config_pe__Vstatic__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(__Vtask_tb_top__DOT__config_pe__2194__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(__Vtask_tb_top__DOT__config_pe__2194__slot), 3U)));
    vlSelfRef.tb_top__DOT__config_pe__Vstatic__data_low 
        = (IData)(__Vtask_tb_top__DOT__config_pe__2194__config_data);
    vlSelfRef.tb_top__DOT__config_pe__Vstatic__data_high 
        = (IData)((__Vtask_tb_top__DOT__config_pe__2194__config_data 
                   >> 0x20U));
    __Vtask_tb_top__DOT__ram_write__2195__data = vlSelfRef.tb_top__DOT__config_pe__Vstatic__data_high;
    __Vtask_tb_top__DOT__ram_write__2195__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2195__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2195__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2195__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2195__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2195__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2195__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2195__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2195__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2196__data = 0x1004U;
    __Vtask_tb_top__DOT__apb_write__2196__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2196__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2196__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2197__data = (4U 
                                                  | vlSelfRef.tb_top__DOT__config_pe__Vstatic__cfg_addr_base);
    __Vtask_tb_top__DOT__apb_write__2197__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2197__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2197__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2198__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2198__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2198__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2198__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2199__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2199__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2199__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2199__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2200__timeout = 0x64U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2200__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2201__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2201__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2201__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2201__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel1;
            }
            __Vtask_tb_top__DOT__wait_cycles__2202__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2202__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2202__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2202__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2202__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2202__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2202__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2200__timeout);
        __Vlabel1: ;
    }
    __Vtask_tb_top__DOT__ram_write__2203__data = vlSelfRef.tb_top__DOT__config_pe__Vstatic__data_low;
    __Vtask_tb_top__DOT__ram_write__2203__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2203__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2203__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2203__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2203__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2203__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2203__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2203__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2203__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2204__data = 0x1004U;
    __Vtask_tb_top__DOT__apb_write__2204__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2204__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2204__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2205__data = vlSelfRef.tb_top__DOT__config_pe__Vstatic__cfg_addr_base;
    __Vtask_tb_top__DOT__apb_write__2205__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2205__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2205__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2206__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2206__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2206__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2206__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2207__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2207__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2207__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2207__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2208__timeout = 0x64U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2208__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2209__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2209__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2209__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2209__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel2;
            }
            __Vtask_tb_top__DOT__wait_cycles__2210__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2210__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2210__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2210__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2210__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2210__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2210__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2208__timeout);
        __Vlabel2: ;
    }
    __Vtask_tb_top__DOT__apb_write__2211__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2211__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2211__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2211__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3023);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2212__addr = 0x24U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         100);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2212__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         106);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         110);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2212__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
        = __Vtask_tb_top__DOT__apb_read__2212__data;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    while (((0U != (1U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)) 
            & VL_GTS_III(32, 0xc8U, vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             3023);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2213__addr = 0x24U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             100);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2213__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             106);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             110);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2213__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
            = __Vtask_tb_top__DOT__apb_read__2213__data;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    }
    if (VL_UNLIKELY((VL_LTES_III(32, 0xc8U, vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt)))) {
        __Vtask_tb_top__DOT__fail__2214__reason = std::string{"CU did not finish first run"};
        __Vtask_tb_top__DOT__fail__2214__msg = std::string{"Y06: Run 1 Timeout"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2214__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2214__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    } else if (VL_UNLIKELY(((2U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)))) {
        VL_WRITEF_NX("[Y06] Run 1: CU Done detected\n",0);
    }
    co_await vlSelfRef.__VdlySched.delay(0x30d40ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3037);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val 
        = vlSelfRef.tb_top__DOT__irq_done;
    if (vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val) {
        VL_WRITEF_NX("[Y06] Run 1: IRQ fired correctly\n",0);
    } else {
        VL_WRITEF_NX("[INFO] Y06: Run 1 IRQ not high (may have cleared)\n",0);
    }
    VL_WRITEF_NX("[Y06] Run 2: Starting CU WITHOUT soft reset...\n",0);
    __Vtask_tb_top__DOT__dma_load_tile_bank__2215__value = 0x12345678U;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2215__offset = 0U;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2215__bank = 0U;
    vlSelfRef.tb_top__DOT__dma_load_tile_bank__Vstatic__tile_addr 
        = (0x10000000U | (((IData)(__Vtask_tb_top__DOT__dma_load_tile_bank__2215__bank) 
                           << 0xcU) | (IData)(__Vtask_tb_top__DOT__dma_load_tile_bank__2215__offset)));
    __Vtask_tb_top__DOT__ram_write__2216__data = __Vtask_tb_top__DOT__dma_load_tile_bank__2215__value;
    __Vtask_tb_top__DOT__ram_write__2216__addr = 0x1000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2216__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2216__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2216__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2216__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2216__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2216__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2216__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2216__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2217__data = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__2217__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2217__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2217__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2218__data = vlSelfRef.tb_top__DOT__dma_load_tile_bank__Vstatic__tile_addr;
    __Vtask_tb_top__DOT__apb_write__2218__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2218__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2218__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2219__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2219__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2219__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2219__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2220__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2220__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2220__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2220__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2221__timeout = 0x64U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2221__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2222__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2222__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2222__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2222__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel3;
            }
            __Vtask_tb_top__DOT__wait_cycles__2223__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2223__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2223__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2223__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2223__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2223__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2223__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2221__timeout);
        __Vlabel3: ;
    }
    __Vtask_tb_top__DOT__config_pe__2224__config_data = 0x111ULL;
    __Vtask_tb_top__DOT__config_pe__2224__slot = 0U;
    __Vtask_tb_top__DOT__config_pe__2224__pe_id = 0U;
    vlSelfRef.tb_top__DOT__config_pe__Vstatic__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(__Vtask_tb_top__DOT__config_pe__2224__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(__Vtask_tb_top__DOT__config_pe__2224__slot), 3U)));
    vlSelfRef.tb_top__DOT__config_pe__Vstatic__data_low 
        = (IData)(__Vtask_tb_top__DOT__config_pe__2224__config_data);
    vlSelfRef.tb_top__DOT__config_pe__Vstatic__data_high 
        = (IData)((__Vtask_tb_top__DOT__config_pe__2224__config_data 
                   >> 0x20U));
    __Vtask_tb_top__DOT__ram_write__2225__data = vlSelfRef.tb_top__DOT__config_pe__Vstatic__data_high;
    __Vtask_tb_top__DOT__ram_write__2225__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2225__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2225__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2225__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2225__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2225__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2225__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2225__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2225__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2226__data = 0x1004U;
    __Vtask_tb_top__DOT__apb_write__2226__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2226__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2226__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2227__data = (4U 
                                                  | vlSelfRef.tb_top__DOT__config_pe__Vstatic__cfg_addr_base);
    __Vtask_tb_top__DOT__apb_write__2227__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2227__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2227__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2228__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2228__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2228__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2228__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2229__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2229__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2229__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2229__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2230__timeout = 0x64U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2230__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2231__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2231__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2231__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2231__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel4;
            }
            __Vtask_tb_top__DOT__wait_cycles__2232__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2232__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2232__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2232__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2232__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2232__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2232__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2230__timeout);
        __Vlabel4: ;
    }
    __Vtask_tb_top__DOT__ram_write__2233__data = vlSelfRef.tb_top__DOT__config_pe__Vstatic__data_low;
    __Vtask_tb_top__DOT__ram_write__2233__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2233__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2233__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2233__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2233__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2233__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2233__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2233__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2233__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2234__data = 0x1004U;
    __Vtask_tb_top__DOT__apb_write__2234__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2234__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2234__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2235__data = vlSelfRef.tb_top__DOT__config_pe__Vstatic__cfg_addr_base;
    __Vtask_tb_top__DOT__apb_write__2235__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2235__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2235__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2236__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2236__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2236__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2236__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2237__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2237__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2237__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2237__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2238__timeout = 0x64U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2238__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2239__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2239__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2239__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2239__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel5;
            }
            __Vtask_tb_top__DOT__wait_cycles__2240__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2240__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2240__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2240__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2240__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2240__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2240__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2238__timeout);
        __Vlabel5: ;
    }
    __Vtask_tb_top__DOT__apb_write__2241__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2241__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2241__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2241__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3059);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2242__addr = 0x24U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         100);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2242__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         106);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         110);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2242__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
        = __Vtask_tb_top__DOT__apb_read__2242__data;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    while (((0U != (1U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)) 
            & VL_GTS_III(32, 0xc8U, vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             3059);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2243__addr = 0x24U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             100);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2243__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             106);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             110);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2243__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
            = __Vtask_tb_top__DOT__apb_read__2243__data;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    }
    if (VL_UNLIKELY((VL_LTES_III(32, 0xc8U, vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt)))) {
        __Vtask_tb_top__DOT__fail__2244__reason = std::string{"CU did not finish second run (auto_stop not re-armed?)"};
        __Vtask_tb_top__DOT__fail__2244__msg = std::string{"Y06: Run 2 Timeout"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2244__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2244__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    } else if ((2U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)) {
        __Vtask_tb_top__DOT__pass__2245__msg = std::string{"Y06: Back-to-Back CU Execution OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2245__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2246__reason = std::string{"CU finished but done bit not set"};
        __Vtask_tb_top__DOT__fail__2246__msg = std::string{"Y06: Run 2 No Done"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2246__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2246__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    __Vtask_tb_top__DOT__apb_write__2247__data = 0U;
    __Vtask_tb_top__DOT__apb_write__2247__addr = 0x34U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2247__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2247__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    VL_WRITEF_NX("\n[SUITE Y COMPLETE] IRQ verification finished.\n\n",0);
    VL_WRITEF_NX("\n   SUITE Z: BURST MODE REGRESSION (Bugs of the Past)\n   Target: H06 (Min Transfer), X01 (4KB Boundary), W01 (Tile Timeout)\n\n[Z01] Testing 1-byte min transfer (H06 fix)...\n",0);
    __Vtask_tb_top__DOT__ram_write__2249__data = 0xdeadbeefU;
    __Vtask_tb_top__DOT__ram_write__2249__addr = 0x1200U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2249__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2249__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2249__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2249__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2249__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2249__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2249__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2249__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2250__data = 0x1200U;
    __Vtask_tb_top__DOT__apb_write__2250__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2250__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2250__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2251__data = 0x6000U;
    __Vtask_tb_top__DOT__apb_write__2251__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2251__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2251__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2252__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2252__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2252__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2252__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2253__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2253__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2253__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2253__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2254__timeout = 0x1f4U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2254__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2255__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2255__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2255__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2255__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel6;
            }
            __Vtask_tb_top__DOT__wait_cycles__2256__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2256__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2256__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2256__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2256__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2256__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2256__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2254__timeout);
        __Vlabel6: ;
    }
    __Vfunc_tb_top__DOT__ram_read__2257__addr = 0x6000U;
    __Vfunc_tb_top__DOT__ram_read__2257__Vfuncout = 
        (((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2257__addr))] 
           << 0x18U) | (vlSelfRef.tb_top__DOT__mem[
                        (0x1ffffU & ((IData)(2U) + __Vfunc_tb_top__DOT__ram_read__2257__addr))] 
                        << 0x10U)) | ((vlSelfRef.tb_top__DOT__mem
                                       [(0x1ffffU & 
                                         ((IData)(1U) 
                                          + __Vfunc_tb_top__DOT__ram_read__2257__addr))] 
                                       << 8U) | vlSelfRef.tb_top__DOT__mem
                                      [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2257__addr)]));
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata 
        = __Vfunc_tb_top__DOT__ram_read__2257__Vfuncout;
    if ((0xefU == (0xffU & vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata))) {
        __Vtask_tb_top__DOT__pass__2258__msg = std::string{"Z01: 1-Byte Min Transfer OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2258__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2259__reason = VL_SFORMATF_N_NX("Expected byte 0xEF, got 0x%02x",0,
                                                                   8,
                                                                   (0xffU 
                                                                    & vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata)) ;
        __Vtask_tb_top__DOT__fail__2259__msg = std::string{"Z01: 1-Byte Min Transfer"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2259__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2259__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[Z02] Testing 3-byte transfer (round-up edge case)...\n",0);
    __Vtask_tb_top__DOT__ram_write__2260__data = 0xcafe1234U;
    __Vtask_tb_top__DOT__ram_write__2260__addr = 0x1300U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2260__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2260__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2260__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2260__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2260__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2260__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2260__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2260__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2261__data = 0x1300U;
    __Vtask_tb_top__DOT__apb_write__2261__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2261__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2261__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2262__data = 0x6100U;
    __Vtask_tb_top__DOT__apb_write__2262__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2262__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2262__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2263__data = 3U;
    __Vtask_tb_top__DOT__apb_write__2263__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2263__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2263__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2264__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2264__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2264__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2264__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2265__timeout = 0x1f4U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2265__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2266__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2266__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2266__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2266__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel7;
            }
            __Vtask_tb_top__DOT__wait_cycles__2267__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2267__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2267__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2267__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2267__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2267__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2267__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2265__timeout);
        __Vlabel7: ;
    }
    __Vfunc_tb_top__DOT__ram_read__2268__addr = 0x6100U;
    __Vfunc_tb_top__DOT__ram_read__2268__Vfuncout = 
        (((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2268__addr))] 
           << 0x18U) | (vlSelfRef.tb_top__DOT__mem[
                        (0x1ffffU & ((IData)(2U) + __Vfunc_tb_top__DOT__ram_read__2268__addr))] 
                        << 0x10U)) | ((vlSelfRef.tb_top__DOT__mem
                                       [(0x1ffffU & 
                                         ((IData)(1U) 
                                          + __Vfunc_tb_top__DOT__ram_read__2268__addr))] 
                                       << 8U) | vlSelfRef.tb_top__DOT__mem
                                      [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2268__addr)]));
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata 
        = __Vfunc_tb_top__DOT__ram_read__2268__Vfuncout;
    if ((0xfe1234U == (0xffffffU & vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata))) {
        __Vtask_tb_top__DOT__pass__2269__msg = std::string{"Z02: 3-Byte Round-up OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2269__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2270__reason = VL_SFORMATF_N_NX("Expected 0xFE1234, got 0x%06x",0,
                                                                   24,
                                                                   (0xffffffU 
                                                                    & vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata)) ;
        __Vtask_tb_top__DOT__fail__2270__msg = std::string{"Z02: 3-Byte Round-up"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2270__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2270__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[Z03] Testing 4KB boundary crossing (X01 fix)...\n",0);
    __Vtask_tb_top__DOT__ram_write__2271__data = 0x11111111U;
    __Vtask_tb_top__DOT__ram_write__2271__addr = 0xff0U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2271__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2271__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2271__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2271__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2271__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2271__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2271__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2271__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2272__data = 0x22222222U;
    __Vtask_tb_top__DOT__ram_write__2272__addr = 0xff4U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2272__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2272__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2272__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2272__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2272__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2272__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2272__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2272__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2273__data = 0x33333333U;
    __Vtask_tb_top__DOT__ram_write__2273__addr = 0xff8U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2273__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2273__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2273__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2273__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2273__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2273__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2273__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2273__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2274__data = 0x44444444U;
    __Vtask_tb_top__DOT__ram_write__2274__addr = 0xffcU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2274__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2274__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2274__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2274__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2274__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2274__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2274__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2274__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2275__data = 0x55555555U;
    __Vtask_tb_top__DOT__ram_write__2275__addr = 0x1000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2275__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2275__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2275__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2275__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2275__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2275__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2275__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2275__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2276__data = 0x66666666U;
    __Vtask_tb_top__DOT__ram_write__2276__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2276__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2276__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2276__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2276__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2276__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2276__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2276__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2276__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2277__data = 0x77777777U;
    __Vtask_tb_top__DOT__ram_write__2277__addr = 0x1008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2277__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2277__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2277__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2277__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2277__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2277__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2277__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2277__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2278__data = 0x88888888U;
    __Vtask_tb_top__DOT__ram_write__2278__addr = 0x100cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2278__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2278__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2278__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2278__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2278__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2278__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2278__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2278__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2279__data = 0xff0U;
    __Vtask_tb_top__DOT__apb_write__2279__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2279__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2279__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2280__data = 0x7000U;
    __Vtask_tb_top__DOT__apb_write__2280__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2280__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2280__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2281__data = 0x20U;
    __Vtask_tb_top__DOT__apb_write__2281__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2281__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2281__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2282__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2282__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2282__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2282__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2283__timeout = 0x3e8U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2283__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2284__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2284__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2284__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2284__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel8;
            }
            __Vtask_tb_top__DOT__wait_cycles__2285__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2285__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2285__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2285__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2285__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2285__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2285__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2283__timeout);
        __Vlabel8: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 1U;
    if ((0x11111111U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2286__addr = 0x7000U;
                    __Vfunc_tb_top__DOT__ram_read__2286__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2286__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2286__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2286__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2286__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2286__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x22222222U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2287__addr = 0x7004U;
                    __Vfunc_tb_top__DOT__ram_read__2287__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2287__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2287__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2287__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2287__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2287__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x33333333U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2288__addr = 0x7008U;
                    __Vfunc_tb_top__DOT__ram_read__2288__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2288__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2288__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2288__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2288__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2288__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x44444444U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2289__addr = 0x700cU;
                    __Vfunc_tb_top__DOT__ram_read__2289__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2289__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2289__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2289__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2289__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2289__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x55555555U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2290__addr = 0x7010U;
                    __Vfunc_tb_top__DOT__ram_read__2290__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2290__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2290__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2290__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2290__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2290__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x66666666U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2291__addr = 0x7014U;
                    __Vfunc_tb_top__DOT__ram_read__2291__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2291__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2291__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2291__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2291__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2291__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x77777777U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2292__addr = 0x7018U;
                    __Vfunc_tb_top__DOT__ram_read__2292__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2292__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2292__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2292__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2292__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2292__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x88888888U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2293__addr = 0x701cU;
                    __Vfunc_tb_top__DOT__ram_read__2293__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2293__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2293__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2293__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2293__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2293__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if (vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__2294__msg = std::string{"Z03: 4KB Boundary Split OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2294__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2295__reason = std::string{"Data mismatch across boundary"};
        __Vtask_tb_top__DOT__fail__2295__msg = std::string{"Z03: 4KB Boundary Split"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2295__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2295__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[Z04] Testing 4KB exact alignment...\n",0);
    __Vtask_tb_top__DOT__ram_write__2296__data = 0xaaaaaaaaU;
    __Vtask_tb_top__DOT__ram_write__2296__addr = 0x1000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2296__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2296__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2296__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2296__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2296__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2296__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2296__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2296__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2297__data = 0xbbbbbbbbU;
    __Vtask_tb_top__DOT__ram_write__2297__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2297__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2297__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2297__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2297__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2297__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2297__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2297__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2297__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2298__data = 0xccccccccU;
    __Vtask_tb_top__DOT__ram_write__2298__addr = 0x1008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2298__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2298__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2298__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2298__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2298__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2298__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2298__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2298__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2299__data = 0xddddddddU;
    __Vtask_tb_top__DOT__ram_write__2299__addr = 0x100cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2299__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2299__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2299__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2299__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2299__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2299__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2299__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2299__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2300__data = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__2300__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2300__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2300__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2301__data = 0x8000U;
    __Vtask_tb_top__DOT__apb_write__2301__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2301__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2301__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2302__data = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2302__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2302__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2302__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2303__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2303__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2303__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2303__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2304__timeout = 0x1f4U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2304__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2305__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2305__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2305__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2305__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel9;
            }
            __Vtask_tb_top__DOT__wait_cycles__2306__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2306__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2306__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2306__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2306__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2306__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2306__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2304__timeout);
        __Vlabel9: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 1U;
    if ((0xaaaaaaaaU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2307__addr = 0x8000U;
                    __Vfunc_tb_top__DOT__ram_read__2307__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2307__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2307__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2307__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2307__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2307__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0xbbbbbbbbU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2308__addr = 0x8004U;
                    __Vfunc_tb_top__DOT__ram_read__2308__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2308__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2308__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2308__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2308__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2308__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0xccccccccU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2309__addr = 0x8008U;
                    __Vfunc_tb_top__DOT__ram_read__2309__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2309__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2309__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2309__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2309__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2309__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0xddddddddU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2310__addr = 0x800cU;
                    __Vfunc_tb_top__DOT__ram_read__2310__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2310__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2310__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2310__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2310__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2310__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if (vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__2311__msg = std::string{"Z04: 4KB Exact Alignment OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2311__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2312__reason = std::string{"Data mismatch"};
        __Vtask_tb_top__DOT__fail__2312__msg = std::string{"Z04: 4KB Exact Alignment"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2312__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2312__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[Z05] Testing tile memory sustained transfer (W01 fix)...\n",0);
    __Vtask_tb_top__DOT__ram_write__2313__data = 0xf0000001U;
    __Vtask_tb_top__DOT__ram_write__2313__addr = 0x2000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2313__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2313__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2313__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2313__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2313__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2313__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2313__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2313__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2314__data = 0xf0000002U;
    __Vtask_tb_top__DOT__ram_write__2314__addr = 0x2004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2314__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2314__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2314__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2314__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2314__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2314__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2314__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2314__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2315__data = 0xf0000003U;
    __Vtask_tb_top__DOT__ram_write__2315__addr = 0x2008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2315__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2315__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2315__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2315__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2315__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2315__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2315__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2315__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2316__data = 0xf0000004U;
    __Vtask_tb_top__DOT__ram_write__2316__addr = 0x200cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2316__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2316__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2316__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2316__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2316__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2316__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2316__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2316__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2317__data = 0x2000U;
    __Vtask_tb_top__DOT__apb_write__2317__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2317__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2317__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2318__data = 0x10000000U;
    __Vtask_tb_top__DOT__apb_write__2318__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2318__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2318__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2319__data = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2319__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2319__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2319__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2320__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2320__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2320__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2320__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3246);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2321__addr = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         100);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2321__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         106);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         110);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2321__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__dma_status 
        = __Vtask_tb_top__DOT__apb_read__2321__data;
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt);
    while (((0U != (1U & vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__dma_status)) 
            & VL_GTS_III(32, 0x1f4U, vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             3246);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2322__addr = 4U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             100);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2322__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             106);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             110);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2322__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__dma_status 
            = __Vtask_tb_top__DOT__apb_read__2322__data;
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt);
    }
    if (VL_LTES_III(32, 0x1f4U, vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt)) {
        __Vtask_tb_top__DOT__fail__2323__reason = std::string{"DMA timeout - W01 bug may still exist"};
        __Vtask_tb_top__DOT__fail__2323__msg = std::string{"Z05: Tile Memory Sustained"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2323__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2323__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    } else {
        __Vtask_tb_top__DOT__pass__2324__msg = std::string{"Z05: Tile Memory Sustained OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2324__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    }
    VL_WRITEF_NX("[Z06] Testing max burst + boundary combined stress...\n",0);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0U;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x10000000U;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfc0U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 1U;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x10000001U;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfc4U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 2U;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x10000002U;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfc8U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 3U;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x10000003U;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfccU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 4U;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x10000004U;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfd0U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 5U;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x10000005U;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfd4U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 6U;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x10000006U;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfd8U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 7U;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x10000007U;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfdcU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 8U;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x10000008U;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfe0U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 9U;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x10000009U;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfe4U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xaU;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x1000000aU;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfe8U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xbU;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x1000000bU;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xfecU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xcU;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x1000000cU;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xff0U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xdU;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x1000000dU;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xff4U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xeU;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x1000000eU;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xff8U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xfU;
    __Vtask_tb_top__DOT__ram_write__2325__data = 0x1000000fU;
    __Vtask_tb_top__DOT__ram_write__2325__addr = 0xffcU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2325__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2325__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2325__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2325__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2325__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2326__data = 0xfc0U;
    __Vtask_tb_top__DOT__apb_write__2326__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2326__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2326__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2327__data = 0x9000U;
    __Vtask_tb_top__DOT__apb_write__2327__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2327__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2327__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2328__data = 0x40U;
    __Vtask_tb_top__DOT__apb_write__2328__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2328__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2328__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2329__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2329__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2329__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2329__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2330__timeout = 0x5dcU;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2330__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2331__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2331__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2331__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2331__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel10;
            }
            __Vtask_tb_top__DOT__wait_cycles__2332__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2332__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2332__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2332__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2332__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2332__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2332__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2330__timeout);
        __Vlabel10: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 1U;
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0U;
    if ((0x10000000U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9000U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 1U;
    if ((0x10000001U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9004U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 2U;
    if ((0x10000002U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9008U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 3U;
    if ((0x10000003U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x900cU;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 4U;
    if ((0x10000004U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9010U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 5U;
    if ((0x10000005U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9014U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 6U;
    if ((0x10000006U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9018U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 7U;
    if ((0x10000007U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x901cU;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 8U;
    if ((0x10000008U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9020U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 9U;
    if ((0x10000009U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9024U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xaU;
    if ((0x1000000aU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9028U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xbU;
    if ((0x1000000bU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x902cU;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xcU;
    if ((0x1000000cU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9030U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xdU;
    if ((0x1000000dU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9034U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xeU;
    if ((0x1000000eU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x9038U;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xfU;
    if ((0x1000000fU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2333__addr = 0x903cU;
                    __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2333__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2333__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2333__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0x10U;
    if (vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__2334__msg = std::string{"Z06: Max Burst + Boundary OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2334__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2335__reason = std::string{"Data mismatch in multi-chunk transfer"};
        __Vtask_tb_top__DOT__fail__2335__msg = std::string{"Z06: Max Burst + Boundary"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2335__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2335__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("\n[SUITE Z COMPLETE] Burst mode regression finished.\n\n",0);
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0;
    VL_WRITEF_NX("\n   SUITE AA: METASTABILITY & ROBUSTNESS\n   Target: Reset Recovery, Protocol Jitter, Data Integrity\n\n[AA01] Testing mid-transfer reset attack...\n",0);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0U;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa000000U;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 1U;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa000001U;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 2U;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa000002U;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 3U;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa000003U;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x400cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 4U;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa000004U;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4010U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 5U;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa000005U;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4014U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 6U;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa000006U;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4018U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 7U;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa000007U;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x401cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 8U;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa000008U;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4020U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 9U;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa000009U;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4024U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xaU;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa00000aU;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4028U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xbU;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa00000bU;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x402cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xcU;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa00000cU;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4030U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xdU;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa00000dU;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4034U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xeU;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa00000eU;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x4038U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xfU;
    __Vtask_tb_top__DOT__ram_write__2337__data = 0xaa00000fU;
    __Vtask_tb_top__DOT__ram_write__2337__addr = 0x403cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2337__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2337__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2337__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2337__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2337__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2338__data = 0x4000U;
    __Vtask_tb_top__DOT__apb_write__2338__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2338__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2338__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2339__data = 0xa000U;
    __Vtask_tb_top__DOT__apb_write__2339__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2339__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2339__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2340__data = 0x40U;
    __Vtask_tb_top__DOT__apb_write__2340__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2340__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2340__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2341__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2341__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2341__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2341__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x2710ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3334);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2342__addr = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         100);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2342__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         106);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         110);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2342__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status 
        = __Vtask_tb_top__DOT__apb_read__2342__data;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt);
    while (((~ (0U != (1U & vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status))) 
            & VL_GTS_III(32, 0x64U, vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x2710ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             3334);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2343__addr = 4U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             100);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2343__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             106);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             110);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2343__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status 
            = __Vtask_tb_top__DOT__apb_read__2343__data;
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt);
    }
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x14U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x13U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x12U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x11U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xfU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xeU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xdU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xbU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xaU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 9U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 7U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 6U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 5U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 3U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 2U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3340);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0U;
    vlSelfRef.tb_top__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x88b8ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3344);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__rst_n = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 5U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3348);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3348);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 3U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3348);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 2U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3348);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3348);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2336__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0U;
    __Vtask_tb_top__DOT__apb_read__2344__addr = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         100);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2344__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         106);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         110);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2344__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status 
        = __Vtask_tb_top__DOT__apb_read__2344__data;
    if ((0U == (1U & vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status))) {
        __Vtask_tb_top__DOT__ram_write__2345__data = 0xdeadbeefU;
        __Vtask_tb_top__DOT__ram_write__2345__addr = 0x5000U;
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2345__addr)] 
            = (0xffU & __Vtask_tb_top__DOT__ram_write__2345__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + __Vtask_tb_top__DOT__ram_write__2345__addr))] 
            = (0xffU & (__Vtask_tb_top__DOT__ram_write__2345__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + __Vtask_tb_top__DOT__ram_write__2345__addr))] 
            = (0xffU & (__Vtask_tb_top__DOT__ram_write__2345__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + __Vtask_tb_top__DOT__ram_write__2345__addr))] 
            = (__Vtask_tb_top__DOT__ram_write__2345__data 
               >> 0x18U);
        __Vtask_tb_top__DOT__apb_write__2346__data = 0x5000U;
        __Vtask_tb_top__DOT__apb_write__2346__addr = 8U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             70);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2346__addr;
        vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2346__data;
        vlSelfRef.tb_top__DOT__pwrite = 1U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             81);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        __Vtask_tb_top__DOT__apb_write__2347__data = 0xb000U;
        __Vtask_tb_top__DOT__apb_write__2347__addr = 0xcU;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             70);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2347__addr;
        vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2347__data;
        vlSelfRef.tb_top__DOT__pwrite = 1U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             81);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        __Vtask_tb_top__DOT__apb_write__2348__data = 4U;
        __Vtask_tb_top__DOT__apb_write__2348__addr = 0x10U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             70);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2348__addr;
        vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2348__data;
        vlSelfRef.tb_top__DOT__pwrite = 1U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             81);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        __Vtask_tb_top__DOT__apb_write__2349__data = 1U;
        __Vtask_tb_top__DOT__apb_write__2349__addr = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             70);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2349__addr;
        vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2349__data;
        vlSelfRef.tb_top__DOT__pwrite = 1U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             81);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        __Vtask_tb_top__DOT__wait_dma_done__2350__timeout = 0x1f4U;
        {
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
            while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2350__timeout)) {
                __Vtask_tb_top__DOT__apb_read__2351__addr = 4U;
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     100);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2351__addr;
                vlSelfRef.tb_top__DOT__pwrite = 0U;
                vlSelfRef.tb_top__DOT__psel = 1U;
                vlSelfRef.tb_top__DOT__penable = 0U;
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     106);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                vlSelfRef.tb_top__DOT__penable = 1U;
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     110);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__apb_read__2351__data 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
                vlSelfRef.tb_top__DOT__psel = 0U;
                vlSelfRef.tb_top__DOT__penable = 0U;
                vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                    = __Vtask_tb_top__DOT__apb_read__2351__data;
                if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                    goto __Vlabel11;
                }
                __Vtask_tb_top__DOT__wait_cycles__2352__n = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2352__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
                __Vtask_tb_top__DOT__wait_cycles__2352__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = __Vtask_tb_top__DOT__wait_cycles__2352__n;
                while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2352__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_top.clk)", 
                                                                         "01_bench/include/tb_tasks.svh", 
                                                                         54);
                    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                    __Vtask_tb_top__DOT__wait_cycles__2352__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                        = (__Vtask_tb_top__DOT__wait_cycles__2352__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                           - (IData)(1U));
                }
                vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                    = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
            }
            VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                         32,__Vtask_tb_top__DOT__wait_dma_done__2350__timeout);
            __Vlabel11: ;
        }
        __Vfunc_tb_top__DOT__ram_read__2353__addr = 0xb000U;
        __Vfunc_tb_top__DOT__ram_read__2353__Vfuncout 
            = (((vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                             & ((IData)(3U) 
                                                + __Vfunc_tb_top__DOT__ram_read__2353__addr))] 
                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & ((IData)(2U) 
                                            + __Vfunc_tb_top__DOT__ram_read__2353__addr))] 
                              << 0x10U)) | ((vlSelfRef.tb_top__DOT__mem
                                             [(0x1ffffU 
                                               & ((IData)(1U) 
                                                  + __Vfunc_tb_top__DOT__ram_read__2353__addr))] 
                                             << 8U) 
                                            | vlSelfRef.tb_top__DOT__mem
                                            [(0x1ffffU 
                                              & __Vfunc_tb_top__DOT__ram_read__2353__addr)]));
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__rdata 
            = __Vfunc_tb_top__DOT__ram_read__2353__Vfuncout;
        if ((0xdeadbeefU == vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__rdata)) {
            __Vtask_tb_top__DOT__pass__2354__msg = 
                std::string{"AA01: Reset Attack Recovery OK"};
            VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2354__msg));
            vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__pass_count);
        } else {
            __Vtask_tb_top__DOT__fail__2355__reason = 
                std::string{"Recovery transfer failed - FSM corrupted"};
            __Vtask_tb_top__DOT__fail__2355__msg = 
                std::string{"AA01: Reset Attack"};
            VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,
                         &(__Vtask_tb_top__DOT__fail__2355__msg),
                         -1,&(__Vtask_tb_top__DOT__fail__2355__reason));
            vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__error_count);
        }
    } else {
        __Vtask_tb_top__DOT__fail__2356__reason = std::string{"DMA stuck busy after reset"};
        __Vtask_tb_top__DOT__fail__2356__msg = std::string{"AA01: Reset Attack"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2356__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2356__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[AA02] Testing protocol jitter stress...\n",0);
    vlSelfRef.tb_top__DOT__stress_enable = 1U;
    vlSelfRef.tb_top__DOT__stress_probability = 0x1eU;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000000U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 1U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000001U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 2U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000002U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 3U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000003U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x600cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 4U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000004U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6010U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 5U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000005U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6014U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 6U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000006U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6018U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 7U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000007U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x601cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 8U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000008U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6020U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 9U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000009U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6024U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xaU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00000aU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6028U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xbU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00000bU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x602cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xcU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00000cU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6030U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xdU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00000dU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6034U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xeU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00000eU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6038U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xfU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00000fU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x603cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x10U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000010U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6040U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x11U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000011U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6044U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x12U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000012U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6048U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x13U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000013U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x604cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x14U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000014U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6050U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x15U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000015U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6054U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x16U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000016U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6058U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x17U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000017U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x605cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x18U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000018U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6060U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x19U;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb000019U;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6064U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1aU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00001aU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6068U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1bU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00001bU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x606cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1cU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00001cU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6070U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1dU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00001dU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6074U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1eU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00001eU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x6078U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1fU;
    __Vtask_tb_top__DOT__ram_write__2357__data = 0xbb00001fU;
    __Vtask_tb_top__DOT__ram_write__2357__addr = 0x607cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2357__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2357__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2357__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2357__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2357__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x20U;
    __Vtask_tb_top__DOT__apb_write__2358__data = 0x6000U;
    __Vtask_tb_top__DOT__apb_write__2358__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2358__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2358__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2359__data = 0xc000U;
    __Vtask_tb_top__DOT__apb_write__2359__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2359__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2359__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2360__data = 0x80U;
    __Vtask_tb_top__DOT__apb_write__2360__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2360__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2360__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2361__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2361__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2361__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2361__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3395);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2362__addr = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         100);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2362__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         106);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         110);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2362__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status 
        = __Vtask_tb_top__DOT__apb_read__2362__data;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt);
    while (((0U != (1U & vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status)) 
            & VL_GTS_III(32, 0x7d0U, vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             3395);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2363__addr = 4U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             100);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2363__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             106);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             110);
        vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2363__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status 
            = __Vtask_tb_top__DOT__apb_read__2363__data;
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt);
    }
    vlSelfRef.tb_top__DOT__stress_enable = 0U;
    if (VL_UNLIKELY((VL_LTES_III(32, 0x7d0U, vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt)))) {
        __Vtask_tb_top__DOT__fail__2364__reason = std::string{"DMA deadlock under backpressure"};
        __Vtask_tb_top__DOT__fail__2364__msg = std::string{"AA02: Jitter Stress"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2364__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2364__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 1U;
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0U;
        if ((0xbb000000U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc000U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 1U;
        if ((0xbb000001U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc004U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 2U;
        if ((0xbb000002U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc008U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 3U;
        if ((0xbb000003U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc00cU;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 4U;
        if ((0xbb000004U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc010U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 5U;
        if ((0xbb000005U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc014U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 6U;
        if ((0xbb000006U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc018U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 7U;
        if ((0xbb000007U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc01cU;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 8U;
        if ((0xbb000008U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc020U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 9U;
        if ((0xbb000009U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc024U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xaU;
        if ((0xbb00000aU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc028U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xbU;
        if ((0xbb00000bU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc02cU;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xcU;
        if ((0xbb00000cU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc030U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xdU;
        if ((0xbb00000dU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc034U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xeU;
        if ((0xbb00000eU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc038U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xfU;
        if ((0xbb00000fU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc03cU;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x10U;
        if ((0xbb000010U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc040U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x11U;
        if ((0xbb000011U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc044U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x12U;
        if ((0xbb000012U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc048U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x13U;
        if ((0xbb000013U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc04cU;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x14U;
        if ((0xbb000014U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc050U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x15U;
        if ((0xbb000015U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc054U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x16U;
        if ((0xbb000016U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc058U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x17U;
        if ((0xbb000017U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc05cU;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x18U;
        if ((0xbb000018U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc060U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x19U;
        if ((0xbb000019U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc064U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1aU;
        if ((0xbb00001aU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc068U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1bU;
        if ((0xbb00001bU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc06cU;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1cU;
        if ((0xbb00001cU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc070U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1dU;
        if ((0xbb00001dU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc074U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1eU;
        if ((0xbb00001eU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc078U;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1fU;
        if ((0xbb00001fU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2365__addr = 0xc07cU;
                        __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2365__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2365__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2365__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x20U;
        if (vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok) {
            __Vtask_tb_top__DOT__pass__2366__msg = 
                std::string{"AA02: Jitter Stress Survived OK"};
            VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2366__msg));
            vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__pass_count);
        } else {
            __Vtask_tb_top__DOT__fail__2367__reason = 
                std::string{"Data corruption under backpressure"};
            __Vtask_tb_top__DOT__fail__2367__msg = 
                std::string{"AA02: Jitter Stress"};
            VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,
                         &(__Vtask_tb_top__DOT__fail__2367__msg),
                         -1,&(__Vtask_tb_top__DOT__fail__2367__reason));
            vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__error_count);
        }
    }
    VL_WRITEF_NX("[AA03] Testing repeated transfer integrity...\n",0);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 1U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0U;
    __Vtask_tb_top__DOT__ram_write__2368__data = 0xcc000000U;
    __Vtask_tb_top__DOT__ram_write__2368__addr = 0x7000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2368__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2368__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2368__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2368__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2368__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2369__data = 0xcc000100U;
    __Vtask_tb_top__DOT__ram_write__2369__addr = 0x7004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2369__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2369__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2369__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2369__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2369__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2370__data = 0xcc000200U;
    __Vtask_tb_top__DOT__ram_write__2370__addr = 0x7008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2370__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2370__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2370__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2370__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2370__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2371__data = 0xcc000300U;
    __Vtask_tb_top__DOT__ram_write__2371__addr = 0x700cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2371__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2371__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2371__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2371__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2371__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2372__data = 0x7000U;
    __Vtask_tb_top__DOT__apb_write__2372__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2372__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2372__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2373__data = 0xd000U;
    __Vtask_tb_top__DOT__apb_write__2373__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2373__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2373__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2374__data = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2374__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2374__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2374__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2375__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2375__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2375__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2375__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2376__timeout = 0x1f4U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2376__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2377__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2377__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2377__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2377__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel12;
            }
            __Vtask_tb_top__DOT__wait_cycles__2378__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2378__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2376__timeout);
        __Vlabel12: ;
    }
    if ((0xcc000000U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2379__addr = 0xd000U;
                    __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2379__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000100U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2380__addr = 0xd004U;
                    __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2380__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000200U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2381__addr = 0xd008U;
                    __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2381__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000300U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2382__addr = 0xd00cU;
                    __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2382__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 1U;
    __Vtask_tb_top__DOT__ram_write__2368__data = 0xcc000001U;
    __Vtask_tb_top__DOT__ram_write__2368__addr = 0x7000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2368__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2368__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2368__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2368__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2368__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2369__data = 0xcc000101U;
    __Vtask_tb_top__DOT__ram_write__2369__addr = 0x7004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2369__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2369__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2369__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2369__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2369__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2370__data = 0xcc000201U;
    __Vtask_tb_top__DOT__ram_write__2370__addr = 0x7008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2370__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2370__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2370__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2370__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2370__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2371__data = 0xcc000301U;
    __Vtask_tb_top__DOT__ram_write__2371__addr = 0x700cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2371__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2371__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2371__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2371__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2371__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2372__data = 0x7000U;
    __Vtask_tb_top__DOT__apb_write__2372__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2372__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2372__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2373__data = 0xd010U;
    __Vtask_tb_top__DOT__apb_write__2373__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2373__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2373__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2374__data = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2374__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2374__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2374__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2375__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2375__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2375__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2375__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2376__timeout = 0x1f4U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2376__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2377__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2377__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2377__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2377__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel13;
            }
            __Vtask_tb_top__DOT__wait_cycles__2378__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2378__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2376__timeout);
        __Vlabel13: ;
    }
    if ((0xcc000001U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2379__addr = 0xd010U;
                    __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2379__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000101U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2380__addr = 0xd014U;
                    __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2380__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000201U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2381__addr = 0xd018U;
                    __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2381__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000301U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2382__addr = 0xd01cU;
                    __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2382__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 2U;
    __Vtask_tb_top__DOT__ram_write__2368__data = 0xcc000002U;
    __Vtask_tb_top__DOT__ram_write__2368__addr = 0x7000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2368__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2368__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2368__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2368__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2368__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2369__data = 0xcc000102U;
    __Vtask_tb_top__DOT__ram_write__2369__addr = 0x7004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2369__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2369__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2369__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2369__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2369__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2370__data = 0xcc000202U;
    __Vtask_tb_top__DOT__ram_write__2370__addr = 0x7008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2370__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2370__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2370__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2370__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2370__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2371__data = 0xcc000302U;
    __Vtask_tb_top__DOT__ram_write__2371__addr = 0x700cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2371__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2371__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2371__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2371__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2371__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2372__data = 0x7000U;
    __Vtask_tb_top__DOT__apb_write__2372__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2372__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2372__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2373__data = 0xd020U;
    __Vtask_tb_top__DOT__apb_write__2373__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2373__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2373__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2374__data = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2374__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2374__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2374__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2375__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2375__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2375__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2375__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2376__timeout = 0x1f4U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2376__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2377__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2377__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2377__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2377__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel14;
            }
            __Vtask_tb_top__DOT__wait_cycles__2378__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2378__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2376__timeout);
        __Vlabel14: ;
    }
    if ((0xcc000002U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2379__addr = 0xd020U;
                    __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2379__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000102U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2380__addr = 0xd024U;
                    __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2380__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000202U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2381__addr = 0xd028U;
                    __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2381__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000302U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2382__addr = 0xd02cU;
                    __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2382__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 3U;
    __Vtask_tb_top__DOT__ram_write__2368__data = 0xcc000003U;
    __Vtask_tb_top__DOT__ram_write__2368__addr = 0x7000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2368__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2368__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2368__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2368__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2368__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2369__data = 0xcc000103U;
    __Vtask_tb_top__DOT__ram_write__2369__addr = 0x7004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2369__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2369__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2369__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2369__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2369__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2370__data = 0xcc000203U;
    __Vtask_tb_top__DOT__ram_write__2370__addr = 0x7008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2370__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2370__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2370__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2370__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2370__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2371__data = 0xcc000303U;
    __Vtask_tb_top__DOT__ram_write__2371__addr = 0x700cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2371__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2371__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2371__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2371__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2371__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2372__data = 0x7000U;
    __Vtask_tb_top__DOT__apb_write__2372__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2372__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2372__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2373__data = 0xd030U;
    __Vtask_tb_top__DOT__apb_write__2373__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2373__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2373__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2374__data = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2374__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2374__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2374__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2375__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2375__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2375__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2375__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2376__timeout = 0x1f4U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2376__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2377__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2377__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2377__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2377__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel15;
            }
            __Vtask_tb_top__DOT__wait_cycles__2378__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2378__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2376__timeout);
        __Vlabel15: ;
    }
    if ((0xcc000003U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2379__addr = 0xd030U;
                    __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2379__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000103U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2380__addr = 0xd034U;
                    __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2380__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000203U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2381__addr = 0xd038U;
                    __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2381__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000303U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2382__addr = 0xd03cU;
                    __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2382__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 4U;
    __Vtask_tb_top__DOT__ram_write__2368__data = 0xcc000004U;
    __Vtask_tb_top__DOT__ram_write__2368__addr = 0x7000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2368__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2368__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2368__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2368__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2368__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2368__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2369__data = 0xcc000104U;
    __Vtask_tb_top__DOT__ram_write__2369__addr = 0x7004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2369__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2369__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2369__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2369__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2369__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2369__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2370__data = 0xcc000204U;
    __Vtask_tb_top__DOT__ram_write__2370__addr = 0x7008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2370__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2370__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2370__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2370__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2370__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2370__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2371__data = 0xcc000304U;
    __Vtask_tb_top__DOT__ram_write__2371__addr = 0x700cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2371__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2371__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2371__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2371__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2371__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2371__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2372__data = 0x7000U;
    __Vtask_tb_top__DOT__apb_write__2372__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2372__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2372__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2373__data = 0xd040U;
    __Vtask_tb_top__DOT__apb_write__2373__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2373__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2373__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2374__data = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2374__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2374__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2374__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2375__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2375__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2375__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2375__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2376__timeout = 0x1f4U;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__2376__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2377__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2377__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2377__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__2377__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel16;
            }
            __Vtask_tb_top__DOT__wait_cycles__2378__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2378__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2378__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__2376__timeout);
        __Vlabel16: ;
    }
    if ((0xcc000004U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2379__addr = 0xd040U;
                    __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2379__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2379__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2379__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000104U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2380__addr = 0xd044U;
                    __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2380__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2380__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2380__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000204U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2381__addr = 0xd048U;
                    __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2381__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2381__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2381__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000304U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2382__addr = 0xd04cU;
                    __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2382__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2382__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2382__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 5U;
    if (vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__2383__msg = std::string{"AA03: Repeated Transfer Integrity OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2383__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2384__reason = std::string{"Data corruption after multiple transfers"};
        __Vtask_tb_top__DOT__fail__2384__msg = std::string{"AA03: Repeated Transfer"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2384__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2384__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("\n[SUITE AA COMPLETE] Metastability & robustness tests finished.\n\n",0);
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
    VL_FINISH_MT("01_bench/tb_top.sv", 357, "");
    vlSelfRef.__Vm_traceActivity[0xcU] = 1U;
}
