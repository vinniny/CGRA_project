// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top__Syms.h"
#include "Vtb_top___024root.h"

VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__1__17(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial__TOP__Vtiming__1__17\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2577__addr;
    __Vtask_tb_top__DOT__apb_read__2577__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2577__data;
    __Vtask_tb_top__DOT__apb_read__2577__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2578__n;
    __Vtask_tb_top__DOT__wait_cycles__2578__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2578__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2578__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2579__addr;
    __Vtask_tb_top__DOT__ram_write__2579__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2579__data;
    __Vtask_tb_top__DOT__ram_write__2579__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2580__addr;
    __Vtask_tb_top__DOT__apb_write__2580__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2580__data;
    __Vtask_tb_top__DOT__apb_write__2580__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2581__addr;
    __Vtask_tb_top__DOT__apb_write__2581__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2581__data;
    __Vtask_tb_top__DOT__apb_write__2581__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2582__addr;
    __Vtask_tb_top__DOT__apb_write__2582__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2582__data;
    __Vtask_tb_top__DOT__apb_write__2582__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2583__addr;
    __Vtask_tb_top__DOT__apb_write__2583__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2583__data;
    __Vtask_tb_top__DOT__apb_write__2583__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2584__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2584__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2584__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2584__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2584__status;
    __Vtask_tb_top__DOT__wait_dma_done__2584__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2585__addr;
    __Vtask_tb_top__DOT__apb_read__2585__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2585__data;
    __Vtask_tb_top__DOT__apb_read__2585__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2586__n;
    __Vtask_tb_top__DOT__wait_cycles__2586__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2586__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2586__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2587__addr;
    __Vtask_tb_top__DOT__apb_write__2587__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2587__data;
    __Vtask_tb_top__DOT__apb_write__2587__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2588__addr;
    __Vtask_tb_top__DOT__apb_read__2588__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2588__data;
    __Vtask_tb_top__DOT__apb_read__2588__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2589__addr;
    __Vtask_tb_top__DOT__apb_read__2589__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2589__data;
    __Vtask_tb_top__DOT__apb_read__2589__data = 0;
    std::string __Vtask_tb_top__DOT__pass__2590__msg;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2591__addr;
    __Vtask_tb_top__DOT__apb_read__2591__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2591__data;
    __Vtask_tb_top__DOT__apb_read__2591__data = 0;
    std::string __Vtask_tb_top__DOT__pass__2592__msg;
    std::string __Vtask_tb_top__DOT__fail__2593__msg;
    std::string __Vtask_tb_top__DOT__fail__2593__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2594__addr;
    __Vtask_tb_top__DOT__apb_write__2594__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2594__data;
    __Vtask_tb_top__DOT__apb_write__2594__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2595__addr;
    __Vtask_tb_top__DOT__apb_write__2595__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2595__data;
    __Vtask_tb_top__DOT__apb_write__2595__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2596__addr;
    __Vtask_tb_top__DOT__apb_write__2596__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2596__data;
    __Vtask_tb_top__DOT__apb_write__2596__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2597__addr;
    __Vtask_tb_top__DOT__apb_write__2597__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2597__data;
    __Vtask_tb_top__DOT__apb_write__2597__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2598__addr;
    __Vtask_tb_top__DOT__apb_write__2598__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2598__data;
    __Vtask_tb_top__DOT__apb_write__2598__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2599__addr;
    __Vtask_tb_top__DOT__apb_read__2599__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2599__data;
    __Vtask_tb_top__DOT__apb_read__2599__data = 0;
    std::string __Vtask_tb_top__DOT__pass__2600__msg;
    std::string __Vtask_tb_top__DOT__pass__2601__msg;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2602__addr;
    __Vtask_tb_top__DOT__apb_read__2602__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2602__data;
    __Vtask_tb_top__DOT__apb_read__2602__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2603__addr;
    __Vtask_tb_top__DOT__apb_read__2603__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2603__data;
    __Vtask_tb_top__DOT__apb_read__2603__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2604__addr;
    __Vtask_tb_top__DOT__apb_write__2604__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2604__data;
    __Vtask_tb_top__DOT__apb_write__2604__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2605__addr;
    __Vtask_tb_top__DOT__apb_read__2605__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2605__data;
    __Vtask_tb_top__DOT__apb_read__2605__data = 0;
    std::string __Vtask_tb_top__DOT__pass__2606__msg;
    std::string __Vtask_tb_top__DOT__fail__2607__msg;
    std::string __Vtask_tb_top__DOT__fail__2607__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2608__addr;
    __Vtask_tb_top__DOT__apb_write__2608__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2608__data;
    __Vtask_tb_top__DOT__apb_write__2608__data = 0;
    CData/*1:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2609__bank;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2609__bank = 0;
    SData/*11:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2609__offset;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2609__offset = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2609__value;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2609__value = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2609__tile_addr;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2609__tile_addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2610__addr;
    __Vtask_tb_top__DOT__ram_write__2610__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2610__data;
    __Vtask_tb_top__DOT__ram_write__2610__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2611__addr;
    __Vtask_tb_top__DOT__apb_write__2611__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2611__data;
    __Vtask_tb_top__DOT__apb_write__2611__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2612__addr;
    __Vtask_tb_top__DOT__apb_write__2612__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2612__data;
    __Vtask_tb_top__DOT__apb_write__2612__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2613__addr;
    __Vtask_tb_top__DOT__apb_write__2613__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2613__data;
    __Vtask_tb_top__DOT__apb_write__2613__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2614__addr;
    __Vtask_tb_top__DOT__apb_write__2614__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2614__data;
    __Vtask_tb_top__DOT__apb_write__2614__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2615__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2615__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2615__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2615__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2615__status;
    __Vtask_tb_top__DOT__wait_dma_done__2615__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2616__addr;
    __Vtask_tb_top__DOT__apb_read__2616__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2616__data;
    __Vtask_tb_top__DOT__apb_read__2616__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2617__n;
    __Vtask_tb_top__DOT__wait_cycles__2617__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2617__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2617__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    CData/*3:0*/ __Vtask_tb_top__DOT__config_pe__2618__pe_id;
    __Vtask_tb_top__DOT__config_pe__2618__pe_id = 0;
    CData/*3:0*/ __Vtask_tb_top__DOT__config_pe__2618__slot;
    __Vtask_tb_top__DOT__config_pe__2618__slot = 0;
    QData/*63:0*/ __Vtask_tb_top__DOT__config_pe__2618__config_data;
    __Vtask_tb_top__DOT__config_pe__2618__config_data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__config_pe__2618__cfg_addr_base;
    __Vtask_tb_top__DOT__config_pe__2618__cfg_addr_base = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__config_pe__2618__data_high;
    __Vtask_tb_top__DOT__config_pe__2618__data_high = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__config_pe__2618__data_low;
    __Vtask_tb_top__DOT__config_pe__2618__data_low = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2619__addr;
    __Vtask_tb_top__DOT__ram_write__2619__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2619__data;
    __Vtask_tb_top__DOT__ram_write__2619__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2620__addr;
    __Vtask_tb_top__DOT__apb_write__2620__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2620__data;
    __Vtask_tb_top__DOT__apb_write__2620__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2621__addr;
    __Vtask_tb_top__DOT__apb_write__2621__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2621__data;
    __Vtask_tb_top__DOT__apb_write__2621__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2622__addr;
    __Vtask_tb_top__DOT__apb_write__2622__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2622__data;
    __Vtask_tb_top__DOT__apb_write__2622__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2623__addr;
    __Vtask_tb_top__DOT__apb_write__2623__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2623__data;
    __Vtask_tb_top__DOT__apb_write__2623__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2624__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2624__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2624__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2624__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2624__status;
    __Vtask_tb_top__DOT__wait_dma_done__2624__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2625__addr;
    __Vtask_tb_top__DOT__apb_read__2625__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2625__data;
    __Vtask_tb_top__DOT__apb_read__2625__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2626__n;
    __Vtask_tb_top__DOT__wait_cycles__2626__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2626__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2626__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2627__addr;
    __Vtask_tb_top__DOT__ram_write__2627__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2627__data;
    __Vtask_tb_top__DOT__ram_write__2627__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2628__addr;
    __Vtask_tb_top__DOT__apb_write__2628__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2628__data;
    __Vtask_tb_top__DOT__apb_write__2628__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2629__addr;
    __Vtask_tb_top__DOT__apb_write__2629__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2629__data;
    __Vtask_tb_top__DOT__apb_write__2629__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2630__addr;
    __Vtask_tb_top__DOT__apb_write__2630__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2630__data;
    __Vtask_tb_top__DOT__apb_write__2630__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2631__addr;
    __Vtask_tb_top__DOT__apb_write__2631__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2631__data;
    __Vtask_tb_top__DOT__apb_write__2631__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2632__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2632__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2632__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2632__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2632__status;
    __Vtask_tb_top__DOT__wait_dma_done__2632__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2633__addr;
    __Vtask_tb_top__DOT__apb_read__2633__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2633__data;
    __Vtask_tb_top__DOT__apb_read__2633__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2634__n;
    __Vtask_tb_top__DOT__wait_cycles__2634__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2634__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2634__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2635__addr;
    __Vtask_tb_top__DOT__apb_write__2635__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2635__data;
    __Vtask_tb_top__DOT__apb_write__2635__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2636__addr;
    __Vtask_tb_top__DOT__apb_read__2636__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2636__data;
    __Vtask_tb_top__DOT__apb_read__2636__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2637__addr;
    __Vtask_tb_top__DOT__apb_read__2637__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2637__data;
    __Vtask_tb_top__DOT__apb_read__2637__data = 0;
    std::string __Vtask_tb_top__DOT__fail__2638__msg;
    std::string __Vtask_tb_top__DOT__fail__2638__reason;
    CData/*1:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2639__bank;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2639__bank = 0;
    SData/*11:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2639__offset;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2639__offset = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2639__value;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2639__value = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_load_tile_bank__2639__tile_addr;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2639__tile_addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2640__addr;
    __Vtask_tb_top__DOT__ram_write__2640__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2640__data;
    __Vtask_tb_top__DOT__ram_write__2640__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2641__addr;
    __Vtask_tb_top__DOT__apb_write__2641__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2641__data;
    __Vtask_tb_top__DOT__apb_write__2641__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2642__addr;
    __Vtask_tb_top__DOT__apb_write__2642__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2642__data;
    __Vtask_tb_top__DOT__apb_write__2642__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2643__addr;
    __Vtask_tb_top__DOT__apb_write__2643__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2643__data;
    __Vtask_tb_top__DOT__apb_write__2643__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2644__addr;
    __Vtask_tb_top__DOT__apb_write__2644__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2644__data;
    __Vtask_tb_top__DOT__apb_write__2644__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2645__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2645__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2645__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2645__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2645__status;
    __Vtask_tb_top__DOT__wait_dma_done__2645__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2646__addr;
    __Vtask_tb_top__DOT__apb_read__2646__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2646__data;
    __Vtask_tb_top__DOT__apb_read__2646__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2647__n;
    __Vtask_tb_top__DOT__wait_cycles__2647__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2647__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2647__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    CData/*3:0*/ __Vtask_tb_top__DOT__config_pe__2648__pe_id;
    __Vtask_tb_top__DOT__config_pe__2648__pe_id = 0;
    CData/*3:0*/ __Vtask_tb_top__DOT__config_pe__2648__slot;
    __Vtask_tb_top__DOT__config_pe__2648__slot = 0;
    QData/*63:0*/ __Vtask_tb_top__DOT__config_pe__2648__config_data;
    __Vtask_tb_top__DOT__config_pe__2648__config_data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__config_pe__2648__cfg_addr_base;
    __Vtask_tb_top__DOT__config_pe__2648__cfg_addr_base = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__config_pe__2648__data_high;
    __Vtask_tb_top__DOT__config_pe__2648__data_high = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__config_pe__2648__data_low;
    __Vtask_tb_top__DOT__config_pe__2648__data_low = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2649__addr;
    __Vtask_tb_top__DOT__ram_write__2649__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2649__data;
    __Vtask_tb_top__DOT__ram_write__2649__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2650__addr;
    __Vtask_tb_top__DOT__apb_write__2650__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2650__data;
    __Vtask_tb_top__DOT__apb_write__2650__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2651__addr;
    __Vtask_tb_top__DOT__apb_write__2651__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2651__data;
    __Vtask_tb_top__DOT__apb_write__2651__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2652__addr;
    __Vtask_tb_top__DOT__apb_write__2652__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2652__data;
    __Vtask_tb_top__DOT__apb_write__2652__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2653__addr;
    __Vtask_tb_top__DOT__apb_write__2653__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2653__data;
    __Vtask_tb_top__DOT__apb_write__2653__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2654__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2654__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2654__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2654__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2654__status;
    __Vtask_tb_top__DOT__wait_dma_done__2654__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2655__addr;
    __Vtask_tb_top__DOT__apb_read__2655__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2655__data;
    __Vtask_tb_top__DOT__apb_read__2655__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2656__n;
    __Vtask_tb_top__DOT__wait_cycles__2656__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2656__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2656__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2657__addr;
    __Vtask_tb_top__DOT__ram_write__2657__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2657__data;
    __Vtask_tb_top__DOT__ram_write__2657__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2658__addr;
    __Vtask_tb_top__DOT__apb_write__2658__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2658__data;
    __Vtask_tb_top__DOT__apb_write__2658__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2659__addr;
    __Vtask_tb_top__DOT__apb_write__2659__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2659__data;
    __Vtask_tb_top__DOT__apb_write__2659__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2660__addr;
    __Vtask_tb_top__DOT__apb_write__2660__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2660__data;
    __Vtask_tb_top__DOT__apb_write__2660__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2661__addr;
    __Vtask_tb_top__DOT__apb_write__2661__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2661__data;
    __Vtask_tb_top__DOT__apb_write__2661__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2662__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2662__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2662__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2662__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2662__status;
    __Vtask_tb_top__DOT__wait_dma_done__2662__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2663__addr;
    __Vtask_tb_top__DOT__apb_read__2663__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2663__data;
    __Vtask_tb_top__DOT__apb_read__2663__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2664__n;
    __Vtask_tb_top__DOT__wait_cycles__2664__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2664__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2664__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2665__addr;
    __Vtask_tb_top__DOT__apb_write__2665__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2665__data;
    __Vtask_tb_top__DOT__apb_write__2665__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2666__addr;
    __Vtask_tb_top__DOT__apb_read__2666__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2666__data;
    __Vtask_tb_top__DOT__apb_read__2666__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2667__addr;
    __Vtask_tb_top__DOT__apb_read__2667__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2667__data;
    __Vtask_tb_top__DOT__apb_read__2667__data = 0;
    std::string __Vtask_tb_top__DOT__fail__2668__msg;
    std::string __Vtask_tb_top__DOT__fail__2668__reason;
    std::string __Vtask_tb_top__DOT__pass__2669__msg;
    std::string __Vtask_tb_top__DOT__fail__2670__msg;
    std::string __Vtask_tb_top__DOT__fail__2670__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2671__addr;
    __Vtask_tb_top__DOT__apb_write__2671__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2671__data;
    __Vtask_tb_top__DOT__apb_write__2671__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2673__addr;
    __Vtask_tb_top__DOT__ram_write__2673__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2673__data;
    __Vtask_tb_top__DOT__ram_write__2673__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2674__addr;
    __Vtask_tb_top__DOT__apb_write__2674__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2674__data;
    __Vtask_tb_top__DOT__apb_write__2674__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2675__addr;
    __Vtask_tb_top__DOT__apb_write__2675__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2675__data;
    __Vtask_tb_top__DOT__apb_write__2675__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2676__addr;
    __Vtask_tb_top__DOT__apb_write__2676__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2676__data;
    __Vtask_tb_top__DOT__apb_write__2676__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2677__addr;
    __Vtask_tb_top__DOT__apb_write__2677__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2677__data;
    __Vtask_tb_top__DOT__apb_write__2677__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2678__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2678__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2678__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2678__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2678__status;
    __Vtask_tb_top__DOT__wait_dma_done__2678__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2679__addr;
    __Vtask_tb_top__DOT__apb_read__2679__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2679__data;
    __Vtask_tb_top__DOT__apb_read__2679__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2680__n;
    __Vtask_tb_top__DOT__wait_cycles__2680__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2680__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2680__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2681__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2681__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2681__addr;
    __Vfunc_tb_top__DOT__ram_read__2681__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2682__msg;
    std::string __Vtask_tb_top__DOT__fail__2683__msg;
    std::string __Vtask_tb_top__DOT__fail__2683__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2684__addr;
    __Vtask_tb_top__DOT__ram_write__2684__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2684__data;
    __Vtask_tb_top__DOT__ram_write__2684__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2685__addr;
    __Vtask_tb_top__DOT__apb_write__2685__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2685__data;
    __Vtask_tb_top__DOT__apb_write__2685__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2686__addr;
    __Vtask_tb_top__DOT__apb_write__2686__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2686__data;
    __Vtask_tb_top__DOT__apb_write__2686__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2687__addr;
    __Vtask_tb_top__DOT__apb_write__2687__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2687__data;
    __Vtask_tb_top__DOT__apb_write__2687__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2688__addr;
    __Vtask_tb_top__DOT__apb_write__2688__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2688__data;
    __Vtask_tb_top__DOT__apb_write__2688__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2689__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2689__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2689__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2689__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2689__status;
    __Vtask_tb_top__DOT__wait_dma_done__2689__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2690__addr;
    __Vtask_tb_top__DOT__apb_read__2690__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2690__data;
    __Vtask_tb_top__DOT__apb_read__2690__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2691__n;
    __Vtask_tb_top__DOT__wait_cycles__2691__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2691__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2691__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2692__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2692__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2692__addr;
    __Vfunc_tb_top__DOT__ram_read__2692__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2693__msg;
    std::string __Vtask_tb_top__DOT__fail__2694__msg;
    std::string __Vtask_tb_top__DOT__fail__2694__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2695__addr;
    __Vtask_tb_top__DOT__ram_write__2695__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2695__data;
    __Vtask_tb_top__DOT__ram_write__2695__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2696__addr;
    __Vtask_tb_top__DOT__ram_write__2696__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2696__data;
    __Vtask_tb_top__DOT__ram_write__2696__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2697__addr;
    __Vtask_tb_top__DOT__ram_write__2697__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2697__data;
    __Vtask_tb_top__DOT__ram_write__2697__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2698__addr;
    __Vtask_tb_top__DOT__ram_write__2698__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2698__data;
    __Vtask_tb_top__DOT__ram_write__2698__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2699__addr;
    __Vtask_tb_top__DOT__ram_write__2699__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2699__data;
    __Vtask_tb_top__DOT__ram_write__2699__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2700__addr;
    __Vtask_tb_top__DOT__ram_write__2700__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2700__data;
    __Vtask_tb_top__DOT__ram_write__2700__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2701__addr;
    __Vtask_tb_top__DOT__ram_write__2701__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2701__data;
    __Vtask_tb_top__DOT__ram_write__2701__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2702__addr;
    __Vtask_tb_top__DOT__ram_write__2702__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2702__data;
    __Vtask_tb_top__DOT__ram_write__2702__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2703__addr;
    __Vtask_tb_top__DOT__apb_write__2703__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2703__data;
    __Vtask_tb_top__DOT__apb_write__2703__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2704__addr;
    __Vtask_tb_top__DOT__apb_write__2704__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2704__data;
    __Vtask_tb_top__DOT__apb_write__2704__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2705__addr;
    __Vtask_tb_top__DOT__apb_write__2705__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2705__data;
    __Vtask_tb_top__DOT__apb_write__2705__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2706__addr;
    __Vtask_tb_top__DOT__apb_write__2706__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2706__data;
    __Vtask_tb_top__DOT__apb_write__2706__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2707__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2707__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2707__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2707__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2707__status;
    __Vtask_tb_top__DOT__wait_dma_done__2707__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2708__addr;
    __Vtask_tb_top__DOT__apb_read__2708__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2708__data;
    __Vtask_tb_top__DOT__apb_read__2708__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2709__n;
    __Vtask_tb_top__DOT__wait_cycles__2709__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2709__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2709__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2710__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2710__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2710__addr;
    __Vfunc_tb_top__DOT__ram_read__2710__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2711__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2711__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2711__addr;
    __Vfunc_tb_top__DOT__ram_read__2711__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2712__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2712__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2712__addr;
    __Vfunc_tb_top__DOT__ram_read__2712__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2713__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2713__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2713__addr;
    __Vfunc_tb_top__DOT__ram_read__2713__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2714__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2714__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2714__addr;
    __Vfunc_tb_top__DOT__ram_read__2714__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2715__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2715__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2715__addr;
    __Vfunc_tb_top__DOT__ram_read__2715__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2716__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2716__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2716__addr;
    __Vfunc_tb_top__DOT__ram_read__2716__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2717__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2717__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2717__addr;
    __Vfunc_tb_top__DOT__ram_read__2717__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2718__msg;
    std::string __Vtask_tb_top__DOT__fail__2719__msg;
    std::string __Vtask_tb_top__DOT__fail__2719__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2720__addr;
    __Vtask_tb_top__DOT__ram_write__2720__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2720__data;
    __Vtask_tb_top__DOT__ram_write__2720__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2721__addr;
    __Vtask_tb_top__DOT__ram_write__2721__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2721__data;
    __Vtask_tb_top__DOT__ram_write__2721__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2722__addr;
    __Vtask_tb_top__DOT__ram_write__2722__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2722__data;
    __Vtask_tb_top__DOT__ram_write__2722__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2723__addr;
    __Vtask_tb_top__DOT__ram_write__2723__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2723__data;
    __Vtask_tb_top__DOT__ram_write__2723__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2724__addr;
    __Vtask_tb_top__DOT__apb_write__2724__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2724__data;
    __Vtask_tb_top__DOT__apb_write__2724__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2725__addr;
    __Vtask_tb_top__DOT__apb_write__2725__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2725__data;
    __Vtask_tb_top__DOT__apb_write__2725__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2726__addr;
    __Vtask_tb_top__DOT__apb_write__2726__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2726__data;
    __Vtask_tb_top__DOT__apb_write__2726__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2727__addr;
    __Vtask_tb_top__DOT__apb_write__2727__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2727__data;
    __Vtask_tb_top__DOT__apb_write__2727__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2728__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2728__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2728__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2728__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2728__status;
    __Vtask_tb_top__DOT__wait_dma_done__2728__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2729__addr;
    __Vtask_tb_top__DOT__apb_read__2729__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2729__data;
    __Vtask_tb_top__DOT__apb_read__2729__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2730__n;
    __Vtask_tb_top__DOT__wait_cycles__2730__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2730__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2730__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2731__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2731__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2731__addr;
    __Vfunc_tb_top__DOT__ram_read__2731__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2732__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2732__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2732__addr;
    __Vfunc_tb_top__DOT__ram_read__2732__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2733__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2733__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2733__addr;
    __Vfunc_tb_top__DOT__ram_read__2733__addr = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2734__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2734__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2734__addr;
    __Vfunc_tb_top__DOT__ram_read__2734__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2735__msg;
    std::string __Vtask_tb_top__DOT__fail__2736__msg;
    std::string __Vtask_tb_top__DOT__fail__2736__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2737__addr;
    __Vtask_tb_top__DOT__ram_write__2737__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2737__data;
    __Vtask_tb_top__DOT__ram_write__2737__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2738__addr;
    __Vtask_tb_top__DOT__ram_write__2738__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2738__data;
    __Vtask_tb_top__DOT__ram_write__2738__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2739__addr;
    __Vtask_tb_top__DOT__ram_write__2739__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2739__data;
    __Vtask_tb_top__DOT__ram_write__2739__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2740__addr;
    __Vtask_tb_top__DOT__ram_write__2740__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2740__data;
    __Vtask_tb_top__DOT__ram_write__2740__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2741__addr;
    __Vtask_tb_top__DOT__apb_write__2741__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2741__data;
    __Vtask_tb_top__DOT__apb_write__2741__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2742__addr;
    __Vtask_tb_top__DOT__apb_write__2742__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2742__data;
    __Vtask_tb_top__DOT__apb_write__2742__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2743__addr;
    __Vtask_tb_top__DOT__apb_write__2743__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2743__data;
    __Vtask_tb_top__DOT__apb_write__2743__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2744__addr;
    __Vtask_tb_top__DOT__apb_write__2744__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2744__data;
    __Vtask_tb_top__DOT__apb_write__2744__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2745__addr;
    __Vtask_tb_top__DOT__apb_read__2745__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2745__data;
    __Vtask_tb_top__DOT__apb_read__2745__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2746__addr;
    __Vtask_tb_top__DOT__apb_read__2746__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2746__data;
    __Vtask_tb_top__DOT__apb_read__2746__data = 0;
    std::string __Vtask_tb_top__DOT__fail__2747__msg;
    std::string __Vtask_tb_top__DOT__fail__2747__reason;
    std::string __Vtask_tb_top__DOT__pass__2748__msg;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2749__addr;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2749__data;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2750__addr;
    __Vtask_tb_top__DOT__apb_write__2750__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2750__data;
    __Vtask_tb_top__DOT__apb_write__2750__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2751__addr;
    __Vtask_tb_top__DOT__apb_write__2751__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2751__data;
    __Vtask_tb_top__DOT__apb_write__2751__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2752__addr;
    __Vtask_tb_top__DOT__apb_write__2752__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2752__data;
    __Vtask_tb_top__DOT__apb_write__2752__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2753__addr;
    __Vtask_tb_top__DOT__apb_write__2753__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2753__data;
    __Vtask_tb_top__DOT__apb_write__2753__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2754__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2754__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2754__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2754__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2754__status;
    __Vtask_tb_top__DOT__wait_dma_done__2754__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2755__addr;
    __Vtask_tb_top__DOT__apb_read__2755__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2755__data;
    __Vtask_tb_top__DOT__apb_read__2755__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2756__n;
    __Vtask_tb_top__DOT__wait_cycles__2756__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2756__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2756__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2757__addr;
    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2758__msg;
    std::string __Vtask_tb_top__DOT__fail__2759__msg;
    std::string __Vtask_tb_top__DOT__fail__2759__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2761__addr;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2761__data;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2762__addr;
    __Vtask_tb_top__DOT__apb_write__2762__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2762__data;
    __Vtask_tb_top__DOT__apb_write__2762__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2763__addr;
    __Vtask_tb_top__DOT__apb_write__2763__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2763__data;
    __Vtask_tb_top__DOT__apb_write__2763__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2764__addr;
    __Vtask_tb_top__DOT__apb_write__2764__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2764__data;
    __Vtask_tb_top__DOT__apb_write__2764__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2765__addr;
    __Vtask_tb_top__DOT__apb_write__2765__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2765__data;
    __Vtask_tb_top__DOT__apb_write__2765__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2766__addr;
    __Vtask_tb_top__DOT__apb_read__2766__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2766__data;
    __Vtask_tb_top__DOT__apb_read__2766__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2767__addr;
    __Vtask_tb_top__DOT__apb_read__2767__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2767__data;
    __Vtask_tb_top__DOT__apb_read__2767__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2768__addr;
    __Vtask_tb_top__DOT__apb_read__2768__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2768__data;
    __Vtask_tb_top__DOT__apb_read__2768__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2769__addr;
    __Vtask_tb_top__DOT__ram_write__2769__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2769__data;
    __Vtask_tb_top__DOT__ram_write__2769__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2770__addr;
    __Vtask_tb_top__DOT__apb_write__2770__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2770__data;
    __Vtask_tb_top__DOT__apb_write__2770__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2771__addr;
    __Vtask_tb_top__DOT__apb_write__2771__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2771__data;
    __Vtask_tb_top__DOT__apb_write__2771__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2772__addr;
    __Vtask_tb_top__DOT__apb_write__2772__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2772__data;
    __Vtask_tb_top__DOT__apb_write__2772__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2773__addr;
    __Vtask_tb_top__DOT__apb_write__2773__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2773__data;
    __Vtask_tb_top__DOT__apb_write__2773__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2774__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__2774__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2774__unnamedblk3__DOT__i;
    __Vtask_tb_top__DOT__wait_dma_done__2774__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__2774__status;
    __Vtask_tb_top__DOT__wait_dma_done__2774__status = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2775__addr;
    __Vtask_tb_top__DOT__apb_read__2775__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2775__data;
    __Vtask_tb_top__DOT__apb_read__2775__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2776__n;
    __Vtask_tb_top__DOT__wait_cycles__2776__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__2776__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__2776__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2777__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2777__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2777__addr;
    __Vfunc_tb_top__DOT__ram_read__2777__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2778__msg;
    std::string __Vtask_tb_top__DOT__fail__2779__msg;
    std::string __Vtask_tb_top__DOT__fail__2779__reason;
    std::string __Vtask_tb_top__DOT__fail__2780__msg;
    std::string __Vtask_tb_top__DOT__fail__2780__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2781__addr;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__ram_write__2781__data;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2782__addr;
    __Vtask_tb_top__DOT__apb_write__2782__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2782__data;
    __Vtask_tb_top__DOT__apb_write__2782__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2783__addr;
    __Vtask_tb_top__DOT__apb_write__2783__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2783__data;
    __Vtask_tb_top__DOT__apb_write__2783__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2784__addr;
    __Vtask_tb_top__DOT__apb_write__2784__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2784__data;
    __Vtask_tb_top__DOT__apb_write__2784__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2785__addr;
    __Vtask_tb_top__DOT__apb_write__2785__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__2785__data;
    __Vtask_tb_top__DOT__apb_write__2785__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2786__addr;
    __Vtask_tb_top__DOT__apb_read__2786__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2786__data;
    __Vtask_tb_top__DOT__apb_read__2786__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2787__addr;
    __Vtask_tb_top__DOT__apb_read__2787__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__2787__data;
    __Vtask_tb_top__DOT__apb_read__2787__data = 0;
    std::string __Vtask_tb_top__DOT__fail__2788__msg;
    std::string __Vtask_tb_top__DOT__fail__2788__reason;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout;
    __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__ram_read__2789__addr;
    __Vfunc_tb_top__DOT__ram_read__2789__addr = 0;
    std::string __Vtask_tb_top__DOT__pass__2790__msg;
    std::string __Vtask_tb_top__DOT__fail__2791__msg;
    std::string __Vtask_tb_top__DOT__fail__2791__reason;
    // Body
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2576__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2576__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2576__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2577__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2577__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2577__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2576__status 
                = __Vtask_tb_top__DOT__apb_read__2577__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2576__status)) {
                goto __Vlabel0;
            }
            __Vtask_tb_top__DOT__wait_cycles__2578__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2578__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2578__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2578__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2578__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2578__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2578__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2576__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2576__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2576__timeout);
        __Vlabel0: ;
    }
    __Vtask_tb_top__DOT__ram_write__2579__data = vlSelfRef.__Vtask_tb_top__DOT__config_pe__2570__data_low;
    __Vtask_tb_top__DOT__ram_write__2579__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2579__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2579__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2579__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2579__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2579__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2579__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2579__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2579__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2580__data = 0x1004U;
    __Vtask_tb_top__DOT__apb_write__2580__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2580__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2580__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2581__data = vlSelfRef.__Vtask_tb_top__DOT__config_pe__2570__cfg_addr_base;
    __Vtask_tb_top__DOT__apb_write__2581__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2581__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2581__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2582__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2582__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2582__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2582__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2583__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2583__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2583__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2583__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2584__timeout = 0x64U;
    __Vtask_tb_top__DOT__wait_dma_done__2584__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2584__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2584__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2584__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2584__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2585__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2585__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2585__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2584__status 
                = __Vtask_tb_top__DOT__apb_read__2585__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2584__status)) {
                goto __Vlabel1;
            }
            __Vtask_tb_top__DOT__wait_cycles__2586__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2586__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2586__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2586__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2586__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2586__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2586__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2584__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2584__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2584__timeout);
        __Vlabel1: ;
    }
    __Vtask_tb_top__DOT__apb_write__2587__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2587__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2587__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2587__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         2732);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2588__addr = 0x24U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         68);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2588__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         74);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2588__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
        = __Vtask_tb_top__DOT__apb_read__2588__data;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    while (((0U != (1U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)) 
            & VL_GTS_III(32, 0x64U, vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             2732);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2589__addr = 0x24U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             68);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2589__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             74);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2589__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
            = __Vtask_tb_top__DOT__apb_read__2589__data;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    }
    co_await vlSelfRef.__VdlySched.delay(0x493e0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         2737);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val 
        = vlSelfRef.tb_top__DOT__irq_done;
    if (vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val) {
        __Vtask_tb_top__DOT__pass__2590__msg = std::string{"Y03: CU Done IRQ Fired Correctly"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2590__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[INFO] Y03: IRQ not high, checking status...\n",0);
        __Vtask_tb_top__DOT__apb_read__2591__addr = 0x30U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             68);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2591__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             74);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2591__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
            = __Vtask_tb_top__DOT__apb_read__2591__data;
        if ((2U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)) {
            __Vtask_tb_top__DOT__pass__2592__msg = 
                std::string{"Y03: CU Done in IRQ_STATUS (IRQ logic OK)"};
            VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2592__msg));
            vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__pass_count);
        } else {
            __Vtask_tb_top__DOT__fail__2593__reason = 
                std::string{"Neither IRQ nor status bit set"};
            __Vtask_tb_top__DOT__fail__2593__msg = 
                std::string{"Y03: CU Done IRQ Missing"};
            VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,
                         &(__Vtask_tb_top__DOT__fail__2593__msg),
                         -1,&(__Vtask_tb_top__DOT__fail__2593__reason));
            vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__error_count);
        }
    }
    VL_WRITEF_NX("[Y04] Testing IRQ clears on new operation...\n",0);
    __Vtask_tb_top__DOT__apb_write__2594__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2594__addr = 0x34U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2594__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2594__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2595__data = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__2595__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2595__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2595__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2596__data = 0x10000000U;
    __Vtask_tb_top__DOT__apb_write__2596__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2596__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2596__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2597__data = 8U;
    __Vtask_tb_top__DOT__apb_write__2597__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2597__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2597__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2598__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2598__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2598__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2598__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x30d40ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         2766);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2599__addr = 0x30U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         68);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2599__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         74);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2599__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
        = __Vtask_tb_top__DOT__apb_read__2599__data;
    if (VL_UNLIKELY(((1U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)))) {
        VL_WRITEF_NX("[INFO] Y04: Status[0]=%b (transfer may have finished)\n",0,
                     1,(1U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata));
        __Vtask_tb_top__DOT__pass__2600__msg = std::string{"Y04: IRQ Status Check (fast transfer)"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2600__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__pass__2601__msg = std::string{"Y04: IRQ Status Cleared on New Start"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2601__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    }
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         2782);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2602__addr = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         68);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2602__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         74);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2602__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__dma_status 
        = __Vtask_tb_top__DOT__apb_read__2602__data;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    while (((0U != (1U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__dma_status)) 
            & VL_GTS_III(32, 0x64U, vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             2782);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2603__addr = 4U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             68);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2603__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             74);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2603__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__dma_status 
            = __Vtask_tb_top__DOT__apb_read__2603__data;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    }
    VL_WRITEF_NX("[Y05] Testing both IRQ sources enabled (mask=0x03)...\n",0);
    __Vtask_tb_top__DOT__apb_write__2604__data = 3U;
    __Vtask_tb_top__DOT__apb_write__2604__addr = 0x34U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2604__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2604__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_read__2605__addr = 0x30U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         68);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2605__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         74);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2605__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
        = __Vtask_tb_top__DOT__apb_read__2605__data;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val 
        = vlSelfRef.tb_top__DOT__irq_done;
    if (((0U != (3U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)) 
         == (IData)(vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val))) {
        __Vtask_tb_top__DOT__pass__2606__msg = std::string{"Y05: IRQ = (STATUS & MASK) Verified"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2606__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2607__reason = VL_SFORMATF_N_NX("STATUS=0x%02x, MASK=0x03, IRQ=%b",0,
                                                                   2,
                                                                   (3U 
                                                                    & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata),
                                                                   1,
                                                                   (IData)(vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val)) ;
        __Vtask_tb_top__DOT__fail__2607__msg = std::string{"Y05: IRQ Logic Mismatch"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2607__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2607__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[Y06] Testing back-to-back CU execution...\n",0);
    __Vtask_tb_top__DOT__apb_write__2608__data = 2U;
    __Vtask_tb_top__DOT__apb_write__2608__addr = 0x34U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2608__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2608__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    VL_WRITEF_NX("[Y06] Run 1: Starting CU...\n",0);
    __Vtask_tb_top__DOT__dma_load_tile_bank__2609__value = 0xaaaa5555U;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2609__offset = 0U;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2609__bank = 0U;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2609__tile_addr = 0;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2609__tile_addr 
        = (0x10000000U | (((IData)(__Vtask_tb_top__DOT__dma_load_tile_bank__2609__bank) 
                           << 0xcU) | (IData)(__Vtask_tb_top__DOT__dma_load_tile_bank__2609__offset)));
    __Vtask_tb_top__DOT__ram_write__2610__data = __Vtask_tb_top__DOT__dma_load_tile_bank__2609__value;
    __Vtask_tb_top__DOT__ram_write__2610__addr = 0x1000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2610__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2610__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2610__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2610__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2610__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2610__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2610__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2610__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2611__data = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__2611__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2611__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2612__data = __Vtask_tb_top__DOT__dma_load_tile_bank__2609__tile_addr;
    __Vtask_tb_top__DOT__apb_write__2612__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2612__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2613__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2613__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2613__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2614__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2614__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2614__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2614__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2615__timeout = 0x64U;
    __Vtask_tb_top__DOT__wait_dma_done__2615__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2615__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2615__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2615__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2615__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2616__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2616__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2616__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2615__status 
                = __Vtask_tb_top__DOT__apb_read__2616__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2615__status)) {
                goto __Vlabel2;
            }
            __Vtask_tb_top__DOT__wait_cycles__2617__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2617__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2617__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2617__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2617__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2617__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2617__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2615__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2615__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2615__timeout);
        __Vlabel2: ;
    }
    __Vtask_tb_top__DOT__config_pe__2618__config_data = 0x110ULL;
    __Vtask_tb_top__DOT__config_pe__2618__slot = 0U;
    __Vtask_tb_top__DOT__config_pe__2618__pe_id = 0U;
    __Vtask_tb_top__DOT__config_pe__2618__cfg_addr_base = 0;
    __Vtask_tb_top__DOT__config_pe__2618__data_high = 0;
    __Vtask_tb_top__DOT__config_pe__2618__data_low = 0;
    __Vtask_tb_top__DOT__config_pe__2618__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(__Vtask_tb_top__DOT__config_pe__2618__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(__Vtask_tb_top__DOT__config_pe__2618__slot), 3U)));
    __Vtask_tb_top__DOT__config_pe__2618__data_low 
        = (IData)(__Vtask_tb_top__DOT__config_pe__2618__config_data);
    __Vtask_tb_top__DOT__config_pe__2618__data_high 
        = (IData)((__Vtask_tb_top__DOT__config_pe__2618__config_data 
                   >> 0x20U));
    __Vtask_tb_top__DOT__ram_write__2619__data = __Vtask_tb_top__DOT__config_pe__2618__data_high;
    __Vtask_tb_top__DOT__ram_write__2619__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2619__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2619__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2619__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2619__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2619__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2619__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2619__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2619__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2620__data = 0x1004U;
    __Vtask_tb_top__DOT__apb_write__2620__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2620__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2620__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2621__data = (4U 
                                                  | __Vtask_tb_top__DOT__config_pe__2618__cfg_addr_base);
    __Vtask_tb_top__DOT__apb_write__2621__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2621__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2621__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2622__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2622__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2622__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2622__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2623__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2623__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2623__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2623__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2624__timeout = 0x64U;
    __Vtask_tb_top__DOT__wait_dma_done__2624__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2624__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2624__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2624__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2624__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2625__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2625__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2625__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2624__status 
                = __Vtask_tb_top__DOT__apb_read__2625__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2624__status)) {
                goto __Vlabel3;
            }
            __Vtask_tb_top__DOT__wait_cycles__2626__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2626__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2626__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2626__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2626__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2626__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2626__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2624__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2624__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2624__timeout);
        __Vlabel3: ;
    }
    __Vtask_tb_top__DOT__ram_write__2627__data = __Vtask_tb_top__DOT__config_pe__2618__data_low;
    __Vtask_tb_top__DOT__ram_write__2627__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2627__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2627__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2627__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2627__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2627__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2627__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2627__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2627__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2628__data = 0x1004U;
    __Vtask_tb_top__DOT__apb_write__2628__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2628__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2628__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2629__data = __Vtask_tb_top__DOT__config_pe__2618__cfg_addr_base;
    __Vtask_tb_top__DOT__apb_write__2629__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2629__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2629__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2630__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2630__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2630__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2630__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2631__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2631__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2631__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2631__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2632__timeout = 0x64U;
    __Vtask_tb_top__DOT__wait_dma_done__2632__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2632__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2632__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2632__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2632__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2633__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2633__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2633__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2632__status 
                = __Vtask_tb_top__DOT__apb_read__2633__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2632__status)) {
                goto __Vlabel4;
            }
            __Vtask_tb_top__DOT__wait_cycles__2634__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2634__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2634__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2634__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2634__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2634__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2634__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2632__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2632__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2632__timeout);
        __Vlabel4: ;
    }
    __Vtask_tb_top__DOT__apb_write__2635__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2635__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2635__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2635__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         2826);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2636__addr = 0x24U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         68);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2636__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         74);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2636__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
        = __Vtask_tb_top__DOT__apb_read__2636__data;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    while (((0U != (1U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)) 
            & VL_GTS_III(32, 0xc8U, vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             2826);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2637__addr = 0x24U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             68);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2637__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             74);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2637__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
            = __Vtask_tb_top__DOT__apb_read__2637__data;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    }
    if (VL_UNLIKELY((VL_LTES_III(32, 0xc8U, vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt)))) {
        __Vtask_tb_top__DOT__fail__2638__reason = std::string{"CU did not finish first run"};
        __Vtask_tb_top__DOT__fail__2638__msg = std::string{"Y06: Run 1 Timeout"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2638__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2638__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    } else if (VL_UNLIKELY(((2U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)))) {
        VL_WRITEF_NX("[Y06] Run 1: CU Done detected\n",0);
    }
    co_await vlSelfRef.__VdlySched.delay(0x30d40ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         2840);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val 
        = vlSelfRef.tb_top__DOT__irq_done;
    if (vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__irq_val) {
        VL_WRITEF_NX("[Y06] Run 1: IRQ fired correctly\n",0);
    } else {
        VL_WRITEF_NX("[INFO] Y06: Run 1 IRQ not high (may have cleared)\n",0);
    }
    VL_WRITEF_NX("[Y06] Run 2: Starting CU WITHOUT soft reset...\n",0);
    __Vtask_tb_top__DOT__dma_load_tile_bank__2639__value = 0x12345678U;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2639__offset = 0U;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2639__bank = 0U;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2639__tile_addr = 0;
    __Vtask_tb_top__DOT__dma_load_tile_bank__2639__tile_addr 
        = (0x10000000U | (((IData)(__Vtask_tb_top__DOT__dma_load_tile_bank__2639__bank) 
                           << 0xcU) | (IData)(__Vtask_tb_top__DOT__dma_load_tile_bank__2639__offset)));
    __Vtask_tb_top__DOT__ram_write__2640__data = __Vtask_tb_top__DOT__dma_load_tile_bank__2639__value;
    __Vtask_tb_top__DOT__ram_write__2640__addr = 0x1000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2640__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2640__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2640__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2640__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2640__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2640__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2640__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2640__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2641__data = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__2641__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2641__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2641__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2642__data = __Vtask_tb_top__DOT__dma_load_tile_bank__2639__tile_addr;
    __Vtask_tb_top__DOT__apb_write__2642__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2642__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2642__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2643__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2643__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2643__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2643__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2644__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2644__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2644__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2644__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2645__timeout = 0x64U;
    __Vtask_tb_top__DOT__wait_dma_done__2645__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2645__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2645__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2645__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2645__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2646__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2646__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2646__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2645__status 
                = __Vtask_tb_top__DOT__apb_read__2646__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2645__status)) {
                goto __Vlabel5;
            }
            __Vtask_tb_top__DOT__wait_cycles__2647__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2647__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2647__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2647__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2647__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2647__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2647__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2645__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2645__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2645__timeout);
        __Vlabel5: ;
    }
    __Vtask_tb_top__DOT__config_pe__2648__config_data = 0x111ULL;
    __Vtask_tb_top__DOT__config_pe__2648__slot = 0U;
    __Vtask_tb_top__DOT__config_pe__2648__pe_id = 0U;
    __Vtask_tb_top__DOT__config_pe__2648__cfg_addr_base = 0;
    __Vtask_tb_top__DOT__config_pe__2648__data_high = 0;
    __Vtask_tb_top__DOT__config_pe__2648__data_low = 0;
    __Vtask_tb_top__DOT__config_pe__2648__cfg_addr_base 
        = (0x20000000U | (VL_SHIFTL_III(32,32,32, (IData)(__Vtask_tb_top__DOT__config_pe__2648__pe_id), 8U) 
                          | VL_SHIFTL_III(32,32,32, (IData)(__Vtask_tb_top__DOT__config_pe__2648__slot), 3U)));
    __Vtask_tb_top__DOT__config_pe__2648__data_low 
        = (IData)(__Vtask_tb_top__DOT__config_pe__2648__config_data);
    __Vtask_tb_top__DOT__config_pe__2648__data_high 
        = (IData)((__Vtask_tb_top__DOT__config_pe__2648__config_data 
                   >> 0x20U));
    __Vtask_tb_top__DOT__ram_write__2649__data = __Vtask_tb_top__DOT__config_pe__2648__data_high;
    __Vtask_tb_top__DOT__ram_write__2649__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2649__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2649__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2649__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2649__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2649__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2649__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2649__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2649__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2650__data = 0x1004U;
    __Vtask_tb_top__DOT__apb_write__2650__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2650__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2650__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2651__data = (4U 
                                                  | __Vtask_tb_top__DOT__config_pe__2648__cfg_addr_base);
    __Vtask_tb_top__DOT__apb_write__2651__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2651__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2651__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2652__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2652__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2652__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2652__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2653__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2653__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2653__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2653__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2654__timeout = 0x64U;
    __Vtask_tb_top__DOT__wait_dma_done__2654__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2654__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2654__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2654__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2654__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2655__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2655__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2655__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2654__status 
                = __Vtask_tb_top__DOT__apb_read__2655__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2654__status)) {
                goto __Vlabel6;
            }
            __Vtask_tb_top__DOT__wait_cycles__2656__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2656__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2656__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2656__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2656__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2656__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2656__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2654__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2654__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2654__timeout);
        __Vlabel6: ;
    }
    __Vtask_tb_top__DOT__ram_write__2657__data = __Vtask_tb_top__DOT__config_pe__2648__data_low;
    __Vtask_tb_top__DOT__ram_write__2657__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2657__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2657__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2657__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2657__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2657__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2657__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2657__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2657__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2658__data = 0x1004U;
    __Vtask_tb_top__DOT__apb_write__2658__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2658__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2658__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2659__data = __Vtask_tb_top__DOT__config_pe__2648__cfg_addr_base;
    __Vtask_tb_top__DOT__apb_write__2659__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2659__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2659__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2660__data = 4U;
    __Vtask_tb_top__DOT__apb_write__2660__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2660__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2660__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2661__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2661__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2661__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2661__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2662__timeout = 0x64U;
    __Vtask_tb_top__DOT__wait_dma_done__2662__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2662__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2662__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2662__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2662__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2663__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2663__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2663__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2662__status 
                = __Vtask_tb_top__DOT__apb_read__2663__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2662__status)) {
                goto __Vlabel7;
            }
            __Vtask_tb_top__DOT__wait_cycles__2664__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2664__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2664__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2664__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2664__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2664__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2664__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2662__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2662__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2662__timeout);
        __Vlabel7: ;
    }
    __Vtask_tb_top__DOT__apb_write__2665__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2665__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2665__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2665__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         2862);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2666__addr = 0x24U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         68);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2666__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         74);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2666__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
        = __Vtask_tb_top__DOT__apb_read__2666__data;
    vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    while (((0U != (1U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)) 
            & VL_GTS_III(32, 0xc8U, vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             2862);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2667__addr = 0x24U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             68);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2667__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             74);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2667__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata 
            = __Vtask_tb_top__DOT__apb_read__2667__data;
        vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt);
    }
    if (VL_UNLIKELY((VL_LTES_III(32, 0xc8U, vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__timeout_cnt)))) {
        __Vtask_tb_top__DOT__fail__2668__reason = std::string{"CU did not finish second run (auto_stop not re-armed?)"};
        __Vtask_tb_top__DOT__fail__2668__msg = std::string{"Y06: Run 2 Timeout"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2668__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2668__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    } else if ((2U & vlSelfRef.tb_top__DOT__run_suite_Y_irq__Vstatic__rdata)) {
        __Vtask_tb_top__DOT__pass__2669__msg = std::string{"Y06: Back-to-Back CU Execution OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2669__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2670__reason = std::string{"CU finished but done bit not set"};
        __Vtask_tb_top__DOT__fail__2670__msg = std::string{"Y06: Run 2 No Done"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2670__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2670__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    __Vtask_tb_top__DOT__apb_write__2671__data = 0U;
    __Vtask_tb_top__DOT__apb_write__2671__addr = 0x34U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2671__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2671__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    VL_WRITEF_NX("\n[SUITE Y COMPLETE] IRQ verification finished.\n\n",0);
    VL_WRITEF_NX("\n   SUITE Z: BURST MODE REGRESSION (Bugs of the Past)\n   Target: H06 (Min Transfer), X01 (4KB Boundary), W01 (Tile Timeout)\n\n[Z01] Testing 1-byte min transfer (H06 fix)...\n",0);
    __Vtask_tb_top__DOT__ram_write__2673__data = 0xdeadbeefU;
    __Vtask_tb_top__DOT__ram_write__2673__addr = 0x1200U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2673__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2673__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2673__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2673__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2673__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2673__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2673__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2673__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2674__data = 0x1200U;
    __Vtask_tb_top__DOT__apb_write__2674__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2674__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2674__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2675__data = 0x6000U;
    __Vtask_tb_top__DOT__apb_write__2675__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2675__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2675__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2676__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2676__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2676__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2676__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2677__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2677__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2677__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2677__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2678__timeout = 0x1f4U;
    __Vtask_tb_top__DOT__wait_dma_done__2678__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2678__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2678__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2678__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2678__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2679__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2679__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2679__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2678__status 
                = __Vtask_tb_top__DOT__apb_read__2679__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2678__status)) {
                goto __Vlabel8;
            }
            __Vtask_tb_top__DOT__wait_cycles__2680__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2680__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2680__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2680__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2680__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2680__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2680__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2678__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2678__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2678__timeout);
        __Vlabel8: ;
    }
    __Vfunc_tb_top__DOT__ram_read__2681__addr = 0x6000U;
    __Vfunc_tb_top__DOT__ram_read__2681__Vfuncout = 
        (((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2681__addr))] 
           << 0x18U) | (vlSelfRef.tb_top__DOT__mem[
                        (0x1ffffU & ((IData)(2U) + __Vfunc_tb_top__DOT__ram_read__2681__addr))] 
                        << 0x10U)) | ((vlSelfRef.tb_top__DOT__mem
                                       [(0x1ffffU & 
                                         ((IData)(1U) 
                                          + __Vfunc_tb_top__DOT__ram_read__2681__addr))] 
                                       << 8U) | vlSelfRef.tb_top__DOT__mem
                                      [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2681__addr)]));
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata 
        = __Vfunc_tb_top__DOT__ram_read__2681__Vfuncout;
    if ((0xefU == (0xffU & vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata))) {
        __Vtask_tb_top__DOT__pass__2682__msg = std::string{"Z01: 1-Byte Min Transfer OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2682__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2683__reason = VL_SFORMATF_N_NX("Expected byte 0xEF, got 0x%02x",0,
                                                                   8,
                                                                   (0xffU 
                                                                    & vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata)) ;
        __Vtask_tb_top__DOT__fail__2683__msg = std::string{"Z01: 1-Byte Min Transfer"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2683__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2683__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[Z02] Testing 3-byte transfer (round-up edge case)...\n",0);
    __Vtask_tb_top__DOT__ram_write__2684__data = 0xcafe1234U;
    __Vtask_tb_top__DOT__ram_write__2684__addr = 0x1300U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2684__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2684__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2684__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2684__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2684__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2684__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2684__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2684__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2685__data = 0x1300U;
    __Vtask_tb_top__DOT__apb_write__2685__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2685__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2685__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2686__data = 0x6100U;
    __Vtask_tb_top__DOT__apb_write__2686__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2686__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2686__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2687__data = 3U;
    __Vtask_tb_top__DOT__apb_write__2687__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2687__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2687__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2688__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2688__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2688__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2688__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2689__timeout = 0x1f4U;
    __Vtask_tb_top__DOT__wait_dma_done__2689__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2689__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2689__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2689__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2689__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2690__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2690__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2690__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2689__status 
                = __Vtask_tb_top__DOT__apb_read__2690__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2689__status)) {
                goto __Vlabel9;
            }
            __Vtask_tb_top__DOT__wait_cycles__2691__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2691__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2691__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2691__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2691__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2691__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2691__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2689__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2689__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2689__timeout);
        __Vlabel9: ;
    }
    __Vfunc_tb_top__DOT__ram_read__2692__addr = 0x6100U;
    __Vfunc_tb_top__DOT__ram_read__2692__Vfuncout = 
        (((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2692__addr))] 
           << 0x18U) | (vlSelfRef.tb_top__DOT__mem[
                        (0x1ffffU & ((IData)(2U) + __Vfunc_tb_top__DOT__ram_read__2692__addr))] 
                        << 0x10U)) | ((vlSelfRef.tb_top__DOT__mem
                                       [(0x1ffffU & 
                                         ((IData)(1U) 
                                          + __Vfunc_tb_top__DOT__ram_read__2692__addr))] 
                                       << 8U) | vlSelfRef.tb_top__DOT__mem
                                      [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2692__addr)]));
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata 
        = __Vfunc_tb_top__DOT__ram_read__2692__Vfuncout;
    if ((0xfe1234U == (0xffffffU & vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata))) {
        __Vtask_tb_top__DOT__pass__2693__msg = std::string{"Z02: 3-Byte Round-up OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2693__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2694__reason = VL_SFORMATF_N_NX("Expected 0xFE1234, got 0x%06x",0,
                                                                   24,
                                                                   (0xffffffU 
                                                                    & vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__rdata)) ;
        __Vtask_tb_top__DOT__fail__2694__msg = std::string{"Z02: 3-Byte Round-up"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2694__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2694__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[Z03] Testing 4KB boundary crossing (X01 fix)...\n",0);
    __Vtask_tb_top__DOT__ram_write__2695__data = 0x11111111U;
    __Vtask_tb_top__DOT__ram_write__2695__addr = 0xff0U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2695__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2695__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2695__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2695__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2695__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2695__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2695__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2695__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2696__data = 0x22222222U;
    __Vtask_tb_top__DOT__ram_write__2696__addr = 0xff4U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2696__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2696__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2696__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2696__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2696__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2696__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2696__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2696__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2697__data = 0x33333333U;
    __Vtask_tb_top__DOT__ram_write__2697__addr = 0xff8U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2697__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2697__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2697__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2697__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2697__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2697__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2697__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2697__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2698__data = 0x44444444U;
    __Vtask_tb_top__DOT__ram_write__2698__addr = 0xffcU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2698__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2698__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2698__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2698__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2698__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2698__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2698__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2698__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2699__data = 0x55555555U;
    __Vtask_tb_top__DOT__ram_write__2699__addr = 0x1000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2699__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2699__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2699__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2699__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2699__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2699__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2699__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2699__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2700__data = 0x66666666U;
    __Vtask_tb_top__DOT__ram_write__2700__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2700__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2700__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2700__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2700__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2700__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2700__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2700__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2700__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2701__data = 0x77777777U;
    __Vtask_tb_top__DOT__ram_write__2701__addr = 0x1008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2701__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2701__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2701__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2701__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2701__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2701__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2701__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2701__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2702__data = 0x88888888U;
    __Vtask_tb_top__DOT__ram_write__2702__addr = 0x100cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2702__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2702__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2702__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2702__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2702__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2702__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2702__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2702__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2703__data = 0xff0U;
    __Vtask_tb_top__DOT__apb_write__2703__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2703__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2703__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2704__data = 0x7000U;
    __Vtask_tb_top__DOT__apb_write__2704__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2704__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2704__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2705__data = 0x20U;
    __Vtask_tb_top__DOT__apb_write__2705__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2705__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2705__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2706__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2706__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2706__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2706__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2707__timeout = 0x3e8U;
    __Vtask_tb_top__DOT__wait_dma_done__2707__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2707__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2707__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2707__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2707__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2708__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2708__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2708__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2707__status 
                = __Vtask_tb_top__DOT__apb_read__2708__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2707__status)) {
                goto __Vlabel10;
            }
            __Vtask_tb_top__DOT__wait_cycles__2709__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2709__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2709__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2709__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2709__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2709__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2709__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2707__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2707__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2707__timeout);
        __Vlabel10: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 1U;
    if ((0x11111111U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2710__addr = 0x7000U;
                    __Vfunc_tb_top__DOT__ram_read__2710__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2710__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2710__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2710__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2710__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2710__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x22222222U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2711__addr = 0x7004U;
                    __Vfunc_tb_top__DOT__ram_read__2711__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2711__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2711__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2711__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2711__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2711__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x33333333U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2712__addr = 0x7008U;
                    __Vfunc_tb_top__DOT__ram_read__2712__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2712__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2712__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2712__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2712__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2712__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x44444444U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2713__addr = 0x700cU;
                    __Vfunc_tb_top__DOT__ram_read__2713__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2713__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2713__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2713__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2713__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2713__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x55555555U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2714__addr = 0x7010U;
                    __Vfunc_tb_top__DOT__ram_read__2714__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2714__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2714__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2714__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2714__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2714__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x66666666U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2715__addr = 0x7014U;
                    __Vfunc_tb_top__DOT__ram_read__2715__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2715__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2715__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2715__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2715__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2715__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x77777777U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2716__addr = 0x7018U;
                    __Vfunc_tb_top__DOT__ram_read__2716__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2716__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2716__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2716__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2716__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2716__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0x88888888U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2717__addr = 0x701cU;
                    __Vfunc_tb_top__DOT__ram_read__2717__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2717__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2717__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2717__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2717__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2717__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if (vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__2718__msg = std::string{"Z03: 4KB Boundary Split OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2718__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2719__reason = std::string{"Data mismatch across boundary"};
        __Vtask_tb_top__DOT__fail__2719__msg = std::string{"Z03: 4KB Boundary Split"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2719__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2719__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[Z04] Testing 4KB exact alignment...\n",0);
    __Vtask_tb_top__DOT__ram_write__2720__data = 0xaaaaaaaaU;
    __Vtask_tb_top__DOT__ram_write__2720__addr = 0x1000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2720__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2720__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2720__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2720__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2720__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2720__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2720__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2720__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2721__data = 0xbbbbbbbbU;
    __Vtask_tb_top__DOT__ram_write__2721__addr = 0x1004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2721__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2721__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2721__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2721__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2721__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2721__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2721__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2721__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2722__data = 0xccccccccU;
    __Vtask_tb_top__DOT__ram_write__2722__addr = 0x1008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2722__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2722__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2722__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2722__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2722__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2722__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2722__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2722__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2723__data = 0xddddddddU;
    __Vtask_tb_top__DOT__ram_write__2723__addr = 0x100cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2723__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2723__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2723__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2723__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2723__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2723__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2723__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2723__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2724__data = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__2724__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2724__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2724__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2725__data = 0x8000U;
    __Vtask_tb_top__DOT__apb_write__2725__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2725__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2725__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2726__data = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2726__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2726__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2726__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2727__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2727__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2727__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2727__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2728__timeout = 0x1f4U;
    __Vtask_tb_top__DOT__wait_dma_done__2728__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2728__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2728__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2728__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2728__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2729__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2729__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2729__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2728__status 
                = __Vtask_tb_top__DOT__apb_read__2729__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2728__status)) {
                goto __Vlabel11;
            }
            __Vtask_tb_top__DOT__wait_cycles__2730__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2730__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2730__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2730__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2730__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2730__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2730__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2728__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2728__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2728__timeout);
        __Vlabel11: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 1U;
    if ((0xaaaaaaaaU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2731__addr = 0x8000U;
                    __Vfunc_tb_top__DOT__ram_read__2731__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2731__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2731__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2731__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2731__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2731__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0xbbbbbbbbU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2732__addr = 0x8004U;
                    __Vfunc_tb_top__DOT__ram_read__2732__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2732__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2732__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2732__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2732__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2732__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0xccccccccU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2733__addr = 0x8008U;
                    __Vfunc_tb_top__DOT__ram_read__2733__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2733__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2733__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2733__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2733__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2733__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if ((0xddddddddU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2734__addr = 0x800cU;
                    __Vfunc_tb_top__DOT__ram_read__2734__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2734__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2734__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2734__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2734__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2734__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    if (vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__2735__msg = std::string{"Z04: 4KB Exact Alignment OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2735__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2736__reason = std::string{"Data mismatch"};
        __Vtask_tb_top__DOT__fail__2736__msg = std::string{"Z04: 4KB Exact Alignment"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2736__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2736__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[Z05] Testing tile memory sustained transfer (W01 fix)...\n",0);
    __Vtask_tb_top__DOT__ram_write__2737__data = 0xf0000001U;
    __Vtask_tb_top__DOT__ram_write__2737__addr = 0x2000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2737__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2737__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2737__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2737__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2737__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2737__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2737__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2737__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2738__data = 0xf0000002U;
    __Vtask_tb_top__DOT__ram_write__2738__addr = 0x2004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2738__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2738__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2738__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2738__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2738__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2738__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2738__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2738__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2739__data = 0xf0000003U;
    __Vtask_tb_top__DOT__ram_write__2739__addr = 0x2008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2739__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2739__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2739__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2739__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2739__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2739__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2739__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2739__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__ram_write__2740__data = 0xf0000004U;
    __Vtask_tb_top__DOT__ram_write__2740__addr = 0x200cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2740__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2740__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2740__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2740__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2740__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2740__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2740__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2740__data 
           >> 0x18U);
    __Vtask_tb_top__DOT__apb_write__2741__data = 0x2000U;
    __Vtask_tb_top__DOT__apb_write__2741__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2741__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2741__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2742__data = 0x10000000U;
    __Vtask_tb_top__DOT__apb_write__2742__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2742__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2742__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2743__data = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2743__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2743__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2743__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2744__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2744__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2744__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2744__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3049);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2745__addr = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         68);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2745__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         74);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2745__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__dma_status 
        = __Vtask_tb_top__DOT__apb_read__2745__data;
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt);
    while (((0U != (1U & vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__dma_status)) 
            & VL_GTS_III(32, 0x1f4U, vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             3049);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2746__addr = 4U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             68);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2746__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             74);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2746__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__dma_status 
            = __Vtask_tb_top__DOT__apb_read__2746__data;
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt);
    }
    if (VL_LTES_III(32, 0x1f4U, vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__timeout_cnt)) {
        __Vtask_tb_top__DOT__fail__2747__reason = std::string{"DMA timeout - W01 bug may still exist"};
        __Vtask_tb_top__DOT__fail__2747__msg = std::string{"Z05: Tile Memory Sustained"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2747__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2747__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    } else {
        __Vtask_tb_top__DOT__pass__2748__msg = std::string{"Z05: Tile Memory Sustained OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2748__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    }
    VL_WRITEF_NX("[Z06] Testing max burst + boundary combined stress...\n",0);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0U;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x10000000U;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfc0U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 1U;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x10000001U;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfc4U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 2U;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x10000002U;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfc8U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 3U;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x10000003U;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfccU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 4U;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x10000004U;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfd0U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 5U;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x10000005U;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfd4U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 6U;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x10000006U;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfd8U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 7U;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x10000007U;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfdcU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 8U;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x10000008U;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfe0U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 9U;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x10000009U;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfe4U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xaU;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x1000000aU;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfe8U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xbU;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x1000000bU;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xfecU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xcU;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x1000000cU;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xff0U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xdU;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x1000000dU;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xff4U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xeU;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x1000000eU;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xff8U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xfU;
    __Vtask_tb_top__DOT__ram_write__2749__data = 0x1000000fU;
    __Vtask_tb_top__DOT__ram_write__2749__addr = 0xffcU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2749__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2749__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2749__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2749__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2749__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2750__data = 0xfc0U;
    __Vtask_tb_top__DOT__apb_write__2750__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2750__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2750__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2751__data = 0x9000U;
    __Vtask_tb_top__DOT__apb_write__2751__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2751__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2751__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2752__data = 0x40U;
    __Vtask_tb_top__DOT__apb_write__2752__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2752__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2752__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2753__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2753__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2753__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2753__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__2754__timeout = 0x5dcU;
    __Vtask_tb_top__DOT__wait_dma_done__2754__unnamedblk3__DOT__i = 0;
    __Vtask_tb_top__DOT__wait_dma_done__2754__status = 0;
    {
        __Vtask_tb_top__DOT__wait_dma_done__2754__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2754__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2754__timeout)) {
            __Vtask_tb_top__DOT__apb_read__2755__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2755__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            __Vtask_tb_top__DOT__apb_read__2755__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            __Vtask_tb_top__DOT__wait_dma_done__2754__status 
                = __Vtask_tb_top__DOT__apb_read__2755__data;
            if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2754__status)) {
                goto __Vlabel12;
            }
            __Vtask_tb_top__DOT__wait_cycles__2756__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__2756__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__2756__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__2756__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2756__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2756__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__2756__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            __Vtask_tb_top__DOT__wait_dma_done__2754__unnamedblk3__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2754__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,__Vtask_tb_top__DOT__wait_dma_done__2754__timeout);
        __Vlabel12: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 1U;
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0U;
    if ((0x10000000U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9000U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 1U;
    if ((0x10000001U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9004U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 2U;
    if ((0x10000002U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9008U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 3U;
    if ((0x10000003U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x900cU;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 4U;
    if ((0x10000004U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9010U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 5U;
    if ((0x10000005U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9014U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 6U;
    if ((0x10000006U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9018U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 7U;
    if ((0x10000007U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x901cU;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 8U;
    if ((0x10000008U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9020U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 9U;
    if ((0x10000009U != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9024U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xaU;
    if ((0x1000000aU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9028U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xbU;
    if ((0x1000000bU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x902cU;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xcU;
    if ((0x1000000cU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9030U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xdU;
    if ((0x1000000dU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9034U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xeU;
    if ((0x1000000eU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x9038U;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0xfU;
    if ((0x1000000fU != ([&]() {
                    __Vfunc_tb_top__DOT__ram_read__2757__addr = 0x903cU;
                    __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + __Vfunc_tb_top__DOT__ram_read__2757__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2757__addr)]));
                }(), __Vfunc_tb_top__DOT__ram_read__2757__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__i = 0x10U;
    if (vlSelfRef.tb_top__DOT__run_suite_Z_burst_regression__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__2758__msg = std::string{"Z06: Max Burst + Boundary OK"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2758__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__2759__reason = std::string{"Data mismatch in multi-chunk transfer"};
        __Vtask_tb_top__DOT__fail__2759__msg = std::string{"Z06: Max Burst + Boundary"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2759__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2759__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("\n[SUITE Z COMPLETE] Burst mode regression finished.\n\n",0);
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0;
    VL_WRITEF_NX("\n   SUITE AA: METASTABILITY & ROBUSTNESS\n   Target: Reset Recovery, Protocol Jitter, Data Integrity\n\n[AA01] Testing mid-transfer reset attack...\n",0);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0U;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa000000U;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 1U;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa000001U;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 2U;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa000002U;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 3U;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa000003U;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x400cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 4U;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa000004U;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4010U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 5U;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa000005U;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4014U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 6U;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa000006U;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4018U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 7U;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa000007U;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x401cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 8U;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa000008U;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4020U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 9U;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa000009U;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4024U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xaU;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa00000aU;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4028U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xbU;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa00000bU;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x402cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xcU;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa00000cU;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4030U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xdU;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa00000dU;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4034U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xeU;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa00000eU;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x4038U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xfU;
    __Vtask_tb_top__DOT__ram_write__2761__data = 0xaa00000fU;
    __Vtask_tb_top__DOT__ram_write__2761__addr = 0x403cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2761__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2761__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2761__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2761__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2761__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x10U;
    __Vtask_tb_top__DOT__apb_write__2762__data = 0x4000U;
    __Vtask_tb_top__DOT__apb_write__2762__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2762__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2762__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2763__data = 0xa000U;
    __Vtask_tb_top__DOT__apb_write__2763__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2763__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2763__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2764__data = 0x40U;
    __Vtask_tb_top__DOT__apb_write__2764__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2764__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2764__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2765__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2765__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2765__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2765__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x2710ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3137);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2766__addr = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         68);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2766__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         74);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2766__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status 
        = __Vtask_tb_top__DOT__apb_read__2766__data;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt);
    while (((~ (0U != (1U & vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status))) 
            & VL_GTS_III(32, 0x64U, vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x2710ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             3137);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2767__addr = 4U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             68);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2767__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             74);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2767__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status 
            = __Vtask_tb_top__DOT__apb_read__2767__data;
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt);
    }
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x14U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x13U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x12U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x11U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xfU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xeU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xdU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xbU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0xaU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 9U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 7U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 6U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 5U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 3U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 2U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3143);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0U;
    vlSelfRef.tb_top__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x88b8ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3147);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__rst_n = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 5U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3151);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3151);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 3U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3151);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 2U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3151);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/tb_test_suites.svh", 
                                                         3151);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__run_suite_AA_robustness__2760__tb_top__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0U;
    __Vtask_tb_top__DOT__apb_read__2768__addr = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         68);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2768__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         74);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2768__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status 
        = __Vtask_tb_top__DOT__apb_read__2768__data;
    if ((0U == (1U & vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status))) {
        __Vtask_tb_top__DOT__ram_write__2769__data = 0xdeadbeefU;
        __Vtask_tb_top__DOT__ram_write__2769__addr = 0x5000U;
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2769__addr)] 
            = (0xffU & __Vtask_tb_top__DOT__ram_write__2769__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + __Vtask_tb_top__DOT__ram_write__2769__addr))] 
            = (0xffU & (__Vtask_tb_top__DOT__ram_write__2769__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + __Vtask_tb_top__DOT__ram_write__2769__addr))] 
            = (0xffU & (__Vtask_tb_top__DOT__ram_write__2769__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + __Vtask_tb_top__DOT__ram_write__2769__addr))] 
            = (__Vtask_tb_top__DOT__ram_write__2769__data 
               >> 0x18U);
        __Vtask_tb_top__DOT__apb_write__2770__data = 0x5000U;
        __Vtask_tb_top__DOT__apb_write__2770__addr = 8U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             44);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2770__addr;
        vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2770__data;
        vlSelfRef.tb_top__DOT__pwrite = 1U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             51);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        __Vtask_tb_top__DOT__apb_write__2771__data = 0xb000U;
        __Vtask_tb_top__DOT__apb_write__2771__addr = 0xcU;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             44);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2771__addr;
        vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2771__data;
        vlSelfRef.tb_top__DOT__pwrite = 1U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             51);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        __Vtask_tb_top__DOT__apb_write__2772__data = 4U;
        __Vtask_tb_top__DOT__apb_write__2772__addr = 0x10U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             44);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2772__addr;
        vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2772__data;
        vlSelfRef.tb_top__DOT__pwrite = 1U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             51);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        __Vtask_tb_top__DOT__apb_write__2773__data = 1U;
        __Vtask_tb_top__DOT__apb_write__2773__addr = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             44);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2773__addr;
        vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2773__data;
        vlSelfRef.tb_top__DOT__pwrite = 1U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             51);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        __Vtask_tb_top__DOT__wait_dma_done__2774__timeout = 0x1f4U;
        __Vtask_tb_top__DOT__wait_dma_done__2774__unnamedblk3__DOT__i = 0;
        __Vtask_tb_top__DOT__wait_dma_done__2774__status = 0;
        {
            __Vtask_tb_top__DOT__wait_dma_done__2774__unnamedblk3__DOT__i = 0U;
            while (VL_LTS_III(32, __Vtask_tb_top__DOT__wait_dma_done__2774__unnamedblk3__DOT__i, __Vtask_tb_top__DOT__wait_dma_done__2774__timeout)) {
                __Vtask_tb_top__DOT__apb_read__2775__addr = 4U;
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     68);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2775__addr;
                vlSelfRef.tb_top__DOT__pwrite = 0U;
                vlSelfRef.tb_top__DOT__psel = 1U;
                vlSelfRef.tb_top__DOT__penable = 0U;
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     74);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                vlSelfRef.tb_top__DOT__penable = 1U;
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     77);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                __Vtask_tb_top__DOT__apb_read__2775__data 
                    = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
                vlSelfRef.tb_top__DOT__psel = 0U;
                vlSelfRef.tb_top__DOT__penable = 0U;
                __Vtask_tb_top__DOT__wait_dma_done__2774__status 
                    = __Vtask_tb_top__DOT__apb_read__2775__data;
                if ((2U & __Vtask_tb_top__DOT__wait_dma_done__2774__status)) {
                    goto __Vlabel13;
                }
                __Vtask_tb_top__DOT__wait_cycles__2776__n = 1U;
                __Vtask_tb_top__DOT__wait_cycles__2776__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
                __Vtask_tb_top__DOT__wait_cycles__2776__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = __Vtask_tb_top__DOT__wait_cycles__2776__n;
                while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__2776__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_top.clk)", 
                                                                         "01_bench/include/tb_tasks.svh", 
                                                                         31);
                    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                    __Vtask_tb_top__DOT__wait_cycles__2776__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                        = (__Vtask_tb_top__DOT__wait_cycles__2776__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                           - (IData)(1U));
                }
                __Vtask_tb_top__DOT__wait_dma_done__2774__unnamedblk3__DOT__i 
                    = ((IData)(1U) + __Vtask_tb_top__DOT__wait_dma_done__2774__unnamedblk3__DOT__i);
            }
            VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),32,__Vtask_tb_top__DOT__wait_dma_done__2774__timeout);
            __Vlabel13: ;
        }
        __Vfunc_tb_top__DOT__ram_read__2777__addr = 0xb000U;
        __Vfunc_tb_top__DOT__ram_read__2777__Vfuncout 
            = (((vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                             & ((IData)(3U) 
                                                + __Vfunc_tb_top__DOT__ram_read__2777__addr))] 
                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & ((IData)(2U) 
                                            + __Vfunc_tb_top__DOT__ram_read__2777__addr))] 
                              << 0x10U)) | ((vlSelfRef.tb_top__DOT__mem
                                             [(0x1ffffU 
                                               & ((IData)(1U) 
                                                  + __Vfunc_tb_top__DOT__ram_read__2777__addr))] 
                                             << 8U) 
                                            | vlSelfRef.tb_top__DOT__mem
                                            [(0x1ffffU 
                                              & __Vfunc_tb_top__DOT__ram_read__2777__addr)]));
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__rdata 
            = __Vfunc_tb_top__DOT__ram_read__2777__Vfuncout;
        if ((0xdeadbeefU == vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__rdata)) {
            __Vtask_tb_top__DOT__pass__2778__msg = 
                std::string{"AA01: Reset Attack Recovery OK"};
            VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2778__msg));
            vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__pass_count);
        } else {
            __Vtask_tb_top__DOT__fail__2779__reason = 
                std::string{"Recovery transfer failed - FSM corrupted"};
            __Vtask_tb_top__DOT__fail__2779__msg = 
                std::string{"AA01: Reset Attack"};
            VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,
                         &(__Vtask_tb_top__DOT__fail__2779__msg),
                         -1,&(__Vtask_tb_top__DOT__fail__2779__reason));
            vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__error_count);
        }
    } else {
        __Vtask_tb_top__DOT__fail__2780__reason = std::string{"DMA stuck busy after reset"};
        __Vtask_tb_top__DOT__fail__2780__msg = std::string{"AA01: Reset Attack"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2780__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2780__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("[AA02] Testing protocol jitter stress...\n",0);
    vlSelfRef.tb_top__DOT__stress_enable = 1U;
    vlSelfRef.tb_top__DOT__stress_probability = 0x1eU;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000000U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 1U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000001U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 2U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000002U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 3U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000003U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x600cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 4U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000004U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6010U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 5U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000005U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6014U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 6U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000006U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6018U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 7U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000007U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x601cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 8U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000008U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6020U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 9U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000009U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6024U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xaU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00000aU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6028U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xbU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00000bU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x602cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xcU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00000cU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6030U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xdU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00000dU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6034U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xeU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00000eU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6038U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xfU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00000fU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x603cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x10U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000010U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6040U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x11U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000011U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6044U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x12U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000012U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6048U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x13U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000013U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x604cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x14U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000014U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6050U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x15U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000015U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6054U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x16U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000016U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6058U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x17U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000017U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x605cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x18U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000018U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6060U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x19U;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb000019U;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6064U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1aU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00001aU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6068U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1bU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00001bU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x606cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1cU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00001cU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6070U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1dU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00001dU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6074U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1eU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00001eU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x6078U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1fU;
    __Vtask_tb_top__DOT__ram_write__2781__data = 0xbb00001fU;
    __Vtask_tb_top__DOT__ram_write__2781__addr = 0x607cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & __Vtask_tb_top__DOT__ram_write__2781__addr)] 
        = (0xffU & __Vtask_tb_top__DOT__ram_write__2781__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (0xffU & (__Vtask_tb_top__DOT__ram_write__2781__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + __Vtask_tb_top__DOT__ram_write__2781__addr))] 
        = (__Vtask_tb_top__DOT__ram_write__2781__data 
           >> 0x18U);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x20U;
    __Vtask_tb_top__DOT__apb_write__2782__data = 0x6000U;
    __Vtask_tb_top__DOT__apb_write__2782__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2782__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2782__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2783__data = 0xc000U;
    __Vtask_tb_top__DOT__apb_write__2783__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2783__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2783__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2784__data = 0x80U;
    __Vtask_tb_top__DOT__apb_write__2784__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2784__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2784__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__2785__data = 1U;
    __Vtask_tb_top__DOT__apb_write__2785__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__2785__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__2785__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                         nullptr, "01_bench/tb_test_suites.svh", 
                                         3198);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2786__addr = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         68);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2786__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         74);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    __Vtask_tb_top__DOT__apb_read__2786__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status 
        = __Vtask_tb_top__DOT__apb_read__2786__data;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt 
        = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt);
    while (((0U != (1U & vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status)) 
            & VL_GTS_III(32, 0x7d0U, vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt))) {
        co_await vlSelfRef.__VdlySched.delay(0x186a0ULL, 
                                             nullptr, 
                                             "01_bench/tb_test_suites.svh", 
                                             3198);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2787__addr = 4U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             68);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__2787__addr;
        vlSelfRef.tb_top__DOT__pwrite = 0U;
        vlSelfRef.tb_top__DOT__psel = 1U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             74);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        vlSelfRef.tb_top__DOT__penable = 1U;
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             77);
        vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
        __Vtask_tb_top__DOT__apb_read__2787__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
        vlSelfRef.tb_top__DOT__psel = 0U;
        vlSelfRef.tb_top__DOT__penable = 0U;
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__dma_status 
            = __Vtask_tb_top__DOT__apb_read__2787__data;
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt);
    }
    vlSelfRef.tb_top__DOT__stress_enable = 0U;
    if (VL_UNLIKELY((VL_LTES_III(32, 0x7d0U, vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__timeout_cnt)))) {
        __Vtask_tb_top__DOT__fail__2788__reason = std::string{"DMA deadlock under backpressure"};
        __Vtask_tb_top__DOT__fail__2788__msg = std::string{"AA02: Jitter Stress"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__2788__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__2788__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 1U;
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0U;
        if ((0xbb000000U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc000U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 1U;
        if ((0xbb000001U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc004U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 2U;
        if ((0xbb000002U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc008U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 3U;
        if ((0xbb000003U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc00cU;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 4U;
        if ((0xbb000004U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc010U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 5U;
        if ((0xbb000005U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc014U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 6U;
        if ((0xbb000006U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc018U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 7U;
        if ((0xbb000007U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc01cU;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 8U;
        if ((0xbb000008U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc020U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 9U;
        if ((0xbb000009U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc024U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xaU;
        if ((0xbb00000aU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc028U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xbU;
        if ((0xbb00000bU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc02cU;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xcU;
        if ((0xbb00000cU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc030U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xdU;
        if ((0xbb00000dU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc034U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xeU;
        if ((0xbb00000eU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc038U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0xfU;
        if ((0xbb00000fU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc03cU;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x10U;
        if ((0xbb000010U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc040U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x11U;
        if ((0xbb000011U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc044U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x12U;
        if ((0xbb000012U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc048U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x13U;
        if ((0xbb000013U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc04cU;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x14U;
        if ((0xbb000014U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc050U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x15U;
        if ((0xbb000015U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc054U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x16U;
        if ((0xbb000016U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc058U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x17U;
        if ((0xbb000017U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc05cU;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x18U;
        if ((0xbb000018U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc060U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x19U;
        if ((0xbb000019U != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc064U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1aU;
        if ((0xbb00001aU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc068U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1bU;
        if ((0xbb00001bU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc06cU;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1cU;
        if ((0xbb00001cU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc070U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1dU;
        if ((0xbb00001dU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc074U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1eU;
        if ((0xbb00001eU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc078U;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x1fU;
        if ((0xbb00001fU != ([&]() {
                        __Vfunc_tb_top__DOT__ram_read__2789__addr = 0xc07cU;
                        __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout 
                            = (((vlSelfRef.tb_top__DOT__mem
                                 [(0x1ffffU & ((IData)(3U) 
                                               + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                 << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                              [(0x1ffffU 
                                                & ((IData)(2U) 
                                                   + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.tb_top__DOT__mem
                                   [(0x1ffffU & ((IData)(1U) 
                                                 + __Vfunc_tb_top__DOT__ram_read__2789__addr))] 
                                   << 8U) | vlSelfRef.tb_top__DOT__mem
                                  [(0x1ffffU & __Vfunc_tb_top__DOT__ram_read__2789__addr)]));
                    }(), __Vfunc_tb_top__DOT__ram_read__2789__Vfuncout))) {
            vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
        }
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0x20U;
        if (vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok) {
            __Vtask_tb_top__DOT__pass__2790__msg = 
                std::string{"AA02: Jitter Stress Survived OK"};
            VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__2790__msg));
            vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__pass_count);
        } else {
            __Vtask_tb_top__DOT__fail__2791__reason = 
                std::string{"Data corruption under backpressure"};
            __Vtask_tb_top__DOT__fail__2791__msg = 
                std::string{"AA02: Jitter Stress"};
            VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,
                         &(__Vtask_tb_top__DOT__fail__2791__msg),
                         -1,&(__Vtask_tb_top__DOT__fail__2791__reason));
            vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__error_count);
        }
    }
    VL_WRITEF_NX("[AA03] Testing repeated transfer integrity...\n",0);
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 1U;
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data = 0xcc000000U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr = 0x7000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data = 0xcc000100U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr = 0x7004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data = 0xcc000200U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr = 0x7008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data = 0xcc000300U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr = 0x700cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__data = 0x7000U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__data = 0xd000U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__data = 0x10U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__timeout = 0x1f4U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i = 0;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__2800__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13637967671268624455ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__status)) {
                goto __Vlabel14;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9302594201753801568ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__timeout);
        __Vlabel14: ;
    }
    if ((0xcc000000U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr = 0xd000U;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000100U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr = 0xd004U;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000200U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr = 0xd008U;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000300U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr = 0xd00cU;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data = 0xcc000001U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr = 0x7000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data = 0xcc000101U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr = 0x7004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data = 0xcc000201U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr = 0x7008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data = 0xcc000301U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr = 0x700cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__data = 0x7000U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__data = 0xd010U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__data = 0x10U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__timeout = 0x1f4U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__2800__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13637967671268624455ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__status)) {
                goto __Vlabel15;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9302594201753801568ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__timeout);
        __Vlabel15: ;
    }
    if ((0xcc000001U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr = 0xd010U;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000101U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr = 0xd014U;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000201U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr = 0xd018U;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000301U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr = 0xd01cU;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 2U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data = 0xcc000002U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr = 0x7000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data = 0xcc000102U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr = 0x7004U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2793__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data = 0xcc000202U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr = 0x7008U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2794__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data = 0xcc000302U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr = 0x700cU;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data 
                    >> 8U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data 
                    >> 0x10U));
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__addr))] 
        = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2795__data 
           >> 0x18U);
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__data = 0x7000U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2796__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__data = 0xd020U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2797__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__data = 0x10U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2798__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         44);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__2799__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         51);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         54);
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__timeout = 0x1f4U;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i = 0;
    vlSelf->__Vtask_tb_top__DOT__wait_dma_done__2800__status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13637967671268624455ull);
    {
        vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 68);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 74);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 77);
            vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__2801__data;
            if ((2U & vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__status)) {
                goto __Vlabel16;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9302594201753801568ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     31);
                vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__2802__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i 
                = ((IData)(1U) + vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__unnamedblk3__DOT__i);
        }
        VL_WRITEF_NX("[%0t] %%Warning: tb_tasks.svh:169: %Ntb_top.wait_dma_done: [DMA] Timeout after %0d cycles\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__2800__timeout);
        __Vlabel16: ;
    }
    if ((0xcc000002U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr = 0xd020U;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2803__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000102U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr = 0xd024U;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2804__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000202U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr = 0xd028U;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2805__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    if ((0xcc000302U != ([&]() {
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr = 0xd02cU;
                    vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__Vfuncout 
                        = (((vlSelfRef.tb_top__DOT__mem
                             [(0x1ffffU & ((IData)(3U) 
                                           + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr))] 
                             << 0x18U) | (vlSelfRef.tb_top__DOT__mem
                                          [(0x1ffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr))] 
                                          << 0x10U)) 
                           | ((vlSelfRef.tb_top__DOT__mem
                               [(0x1ffffU & ((IData)(1U) 
                                             + vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr))] 
                               << 8U) | vlSelfRef.tb_top__DOT__mem
                              [(0x1ffffU & vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__addr)]));
                }(), vlSelfRef.__Vfunc_tb_top__DOT__ram_read__2806__Vfuncout))) {
        vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__data_ok = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_AA_robustness__Vstatic__i = 3U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data = 0xcc000003U;
    vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr = 0x7000U;
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr)] 
        = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data);
    vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                            + vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__addr))] 
        = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__2792__data 
                    >> 8U));
    vlSelfRef.__Vm_traceActivity[0xaU] = 1U;
}
