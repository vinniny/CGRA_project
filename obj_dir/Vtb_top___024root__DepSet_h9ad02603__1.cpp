// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top___024root.h"

VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__1__2(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial__TOP__Vtiming__1__2\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    std::string __Vtask_tb_top__DOT__pass__508__msg;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__510__src;
    __Vtask_tb_top__DOT__dma_transfer__510__src = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__510__dst;
    __Vtask_tb_top__DOT__dma_transfer__510__dst = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__510__size;
    __Vtask_tb_top__DOT__dma_transfer__510__size = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__510__timeout;
    __Vtask_tb_top__DOT__dma_transfer__510__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__511__addr;
    __Vtask_tb_top__DOT__apb_write__511__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__511__data;
    __Vtask_tb_top__DOT__apb_write__511__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__512__addr;
    __Vtask_tb_top__DOT__apb_write__512__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__512__data;
    __Vtask_tb_top__DOT__apb_write__512__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__513__addr;
    __Vtask_tb_top__DOT__apb_write__513__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__513__data;
    __Vtask_tb_top__DOT__apb_write__513__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__514__addr;
    __Vtask_tb_top__DOT__apb_write__514__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__514__data;
    __Vtask_tb_top__DOT__apb_write__514__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__515__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__515__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__516__addr;
    __Vtask_tb_top__DOT__apb_read__516__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__516__data;
    __Vtask_tb_top__DOT__apb_read__516__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__517__n;
    __Vtask_tb_top__DOT__wait_cycles__517__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__517__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__517__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__518__src;
    __Vtask_tb_top__DOT__check_data__518__src = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__518__dst;
    __Vtask_tb_top__DOT__check_data__518__dst = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__518__size;
    __Vtask_tb_top__DOT__check_data__518__size = 0;
    CData/*0:0*/ __Vtask_tb_top__DOT__check_data__518__ok;
    __Vtask_tb_top__DOT__check_data__518__ok = 0;
    std::string __Vtask_tb_top__DOT__pass__519__msg;
    std::string __Vtask_tb_top__DOT__fail__520__msg;
    std::string __Vtask_tb_top__DOT__fail__520__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__521__src;
    __Vtask_tb_top__DOT__dma_transfer__521__src = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__521__dst;
    __Vtask_tb_top__DOT__dma_transfer__521__dst = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__521__size;
    __Vtask_tb_top__DOT__dma_transfer__521__size = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__521__timeout;
    __Vtask_tb_top__DOT__dma_transfer__521__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__522__addr;
    __Vtask_tb_top__DOT__apb_write__522__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__522__data;
    __Vtask_tb_top__DOT__apb_write__522__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__523__addr;
    __Vtask_tb_top__DOT__apb_write__523__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__523__data;
    __Vtask_tb_top__DOT__apb_write__523__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__524__addr;
    __Vtask_tb_top__DOT__apb_write__524__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__524__data;
    __Vtask_tb_top__DOT__apb_write__524__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__525__addr;
    __Vtask_tb_top__DOT__apb_write__525__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__525__data;
    __Vtask_tb_top__DOT__apb_write__525__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__526__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__526__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__527__addr;
    __Vtask_tb_top__DOT__apb_read__527__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__527__data;
    __Vtask_tb_top__DOT__apb_read__527__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__528__n;
    __Vtask_tb_top__DOT__wait_cycles__528__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__528__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__528__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__529__src;
    __Vtask_tb_top__DOT__check_data__529__src = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__529__dst;
    __Vtask_tb_top__DOT__check_data__529__dst = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__529__size;
    __Vtask_tb_top__DOT__check_data__529__size = 0;
    CData/*0:0*/ __Vtask_tb_top__DOT__check_data__529__ok;
    __Vtask_tb_top__DOT__check_data__529__ok = 0;
    std::string __Vtask_tb_top__DOT__pass__530__msg;
    std::string __Vtask_tb_top__DOT__fail__531__msg;
    std::string __Vtask_tb_top__DOT__fail__531__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__532__addr;
    __Vtask_tb_top__DOT__apb_write__532__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__532__data;
    __Vtask_tb_top__DOT__apb_write__532__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__533__n;
    __Vtask_tb_top__DOT__wait_cycles__533__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__533__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__533__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_check_bit__534__addr;
    __Vtask_tb_top__DOT__apb_check_bit__534__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_check_bit__534__bit_pos;
    __Vtask_tb_top__DOT__apb_check_bit__534__bit_pos = 0;
    CData/*0:0*/ __Vtask_tb_top__DOT__apb_check_bit__534__exp_val;
    __Vtask_tb_top__DOT__apb_check_bit__534__exp_val = 0;
    std::string __Vtask_tb_top__DOT__apb_check_bit__534__msg;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__535__addr;
    __Vtask_tb_top__DOT__apb_read__535__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__535__data;
    __Vtask_tb_top__DOT__apb_read__535__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__536__n;
    __Vtask_tb_top__DOT__wait_cycles__536__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__536__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__536__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__537__src;
    __Vtask_tb_top__DOT__dma_transfer__537__src = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__537__dst;
    __Vtask_tb_top__DOT__dma_transfer__537__dst = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__537__size;
    __Vtask_tb_top__DOT__dma_transfer__537__size = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__537__timeout;
    __Vtask_tb_top__DOT__dma_transfer__537__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__538__addr;
    __Vtask_tb_top__DOT__apb_write__538__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__538__data;
    __Vtask_tb_top__DOT__apb_write__538__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__539__addr;
    __Vtask_tb_top__DOT__apb_write__539__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__539__data;
    __Vtask_tb_top__DOT__apb_write__539__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__540__addr;
    __Vtask_tb_top__DOT__apb_write__540__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__540__data;
    __Vtask_tb_top__DOT__apb_write__540__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__541__addr;
    __Vtask_tb_top__DOT__apb_write__541__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__541__data;
    __Vtask_tb_top__DOT__apb_write__541__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__542__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__542__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__543__addr;
    __Vtask_tb_top__DOT__apb_read__543__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__543__data;
    __Vtask_tb_top__DOT__apb_read__543__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__544__n;
    __Vtask_tb_top__DOT__wait_cycles__544__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__544__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__544__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__545__src;
    __Vtask_tb_top__DOT__check_data__545__src = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__545__dst;
    __Vtask_tb_top__DOT__check_data__545__dst = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__545__size;
    __Vtask_tb_top__DOT__check_data__545__size = 0;
    CData/*0:0*/ __Vtask_tb_top__DOT__check_data__545__ok;
    __Vtask_tb_top__DOT__check_data__545__ok = 0;
    std::string __Vtask_tb_top__DOT__pass__546__msg;
    std::string __Vtask_tb_top__DOT__fail__547__msg;
    std::string __Vtask_tb_top__DOT__fail__547__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__548__addr;
    __Vtask_tb_top__DOT__apb_read__548__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__548__data;
    __Vtask_tb_top__DOT__apb_read__548__data = 0;
    std::string __Vtask_tb_top__DOT__pass__549__msg;
    std::string __Vtask_tb_top__DOT__fail__550__msg;
    std::string __Vtask_tb_top__DOT__fail__550__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__551__addr;
    __Vtask_tb_top__DOT__apb_write__551__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__551__data;
    __Vtask_tb_top__DOT__apb_write__551__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__552__n;
    __Vtask_tb_top__DOT__wait_cycles__552__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__552__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__552__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__553__addr;
    __Vtask_tb_top__DOT__apb_write__553__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__553__data;
    __Vtask_tb_top__DOT__apb_write__553__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__554__n;
    __Vtask_tb_top__DOT__wait_cycles__554__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__554__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__554__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    std::string __Vtask_tb_top__DOT__pass__555__msg;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__556__addr;
    __Vtask_tb_top__DOT__apb_write__556__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__556__data;
    __Vtask_tb_top__DOT__apb_write__556__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__557__n;
    __Vtask_tb_top__DOT__wait_cycles__557__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__557__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__557__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__558__addr;
    __Vtask_tb_top__DOT__apb_write__558__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__558__data;
    __Vtask_tb_top__DOT__apb_write__558__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__559__n;
    __Vtask_tb_top__DOT__wait_cycles__559__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__559__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__559__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__560__addr;
    __Vtask_tb_top__DOT__apb_write__560__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__560__data;
    __Vtask_tb_top__DOT__apb_write__560__data = 0;
    std::string __Vtask_tb_top__DOT__pass__561__msg;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__562__n;
    __Vtask_tb_top__DOT__wait_cycles__562__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__562__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__562__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    std::string __Vtask_tb_top__DOT__pass__563__msg;
    std::string __Vtask_tb_top__DOT__fail__564__msg;
    std::string __Vtask_tb_top__DOT__fail__564__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__565__src;
    __Vtask_tb_top__DOT__dma_transfer__565__src = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__565__dst;
    __Vtask_tb_top__DOT__dma_transfer__565__dst = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__565__size;
    __Vtask_tb_top__DOT__dma_transfer__565__size = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__565__timeout;
    __Vtask_tb_top__DOT__dma_transfer__565__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__566__addr;
    __Vtask_tb_top__DOT__apb_write__566__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__566__data;
    __Vtask_tb_top__DOT__apb_write__566__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__567__addr;
    __Vtask_tb_top__DOT__apb_write__567__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__567__data;
    __Vtask_tb_top__DOT__apb_write__567__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__568__addr;
    __Vtask_tb_top__DOT__apb_write__568__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__568__data;
    __Vtask_tb_top__DOT__apb_write__568__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__569__addr;
    __Vtask_tb_top__DOT__apb_write__569__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__569__data;
    __Vtask_tb_top__DOT__apb_write__569__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__570__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__570__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__571__addr;
    __Vtask_tb_top__DOT__apb_read__571__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__571__data;
    __Vtask_tb_top__DOT__apb_read__571__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__572__n;
    __Vtask_tb_top__DOT__wait_cycles__572__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__572__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__572__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__573__addr;
    __Vtask_tb_top__DOT__apb_write__573__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__573__data;
    __Vtask_tb_top__DOT__apb_write__573__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__574__n;
    __Vtask_tb_top__DOT__wait_cycles__574__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__574__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__574__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__575__src;
    __Vtask_tb_top__DOT__dma_transfer__575__src = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__575__dst;
    __Vtask_tb_top__DOT__dma_transfer__575__dst = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__575__size;
    __Vtask_tb_top__DOT__dma_transfer__575__size = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__575__timeout;
    __Vtask_tb_top__DOT__dma_transfer__575__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__576__addr;
    __Vtask_tb_top__DOT__apb_write__576__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__576__data;
    __Vtask_tb_top__DOT__apb_write__576__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__577__addr;
    __Vtask_tb_top__DOT__apb_write__577__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__577__data;
    __Vtask_tb_top__DOT__apb_write__577__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__578__addr;
    __Vtask_tb_top__DOT__apb_write__578__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__578__data;
    __Vtask_tb_top__DOT__apb_write__578__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__579__addr;
    __Vtask_tb_top__DOT__apb_write__579__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__579__data;
    __Vtask_tb_top__DOT__apb_write__579__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__580__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__580__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__581__addr;
    __Vtask_tb_top__DOT__apb_read__581__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__581__data;
    __Vtask_tb_top__DOT__apb_read__581__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__582__n;
    __Vtask_tb_top__DOT__wait_cycles__582__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__582__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__582__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__583__src;
    __Vtask_tb_top__DOT__check_data__583__src = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__583__dst;
    __Vtask_tb_top__DOT__check_data__583__dst = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__check_data__583__size;
    __Vtask_tb_top__DOT__check_data__583__size = 0;
    CData/*0:0*/ __Vtask_tb_top__DOT__check_data__583__ok;
    __Vtask_tb_top__DOT__check_data__583__ok = 0;
    std::string __Vtask_tb_top__DOT__pass__584__msg;
    std::string __Vtask_tb_top__DOT__fail__585__msg;
    std::string __Vtask_tb_top__DOT__fail__585__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__586__src;
    __Vtask_tb_top__DOT__dma_transfer__586__src = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__586__dst;
    __Vtask_tb_top__DOT__dma_transfer__586__dst = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__586__size;
    __Vtask_tb_top__DOT__dma_transfer__586__size = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__dma_transfer__586__timeout;
    __Vtask_tb_top__DOT__dma_transfer__586__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__587__addr;
    __Vtask_tb_top__DOT__apb_write__587__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__587__data;
    __Vtask_tb_top__DOT__apb_write__587__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__588__addr;
    __Vtask_tb_top__DOT__apb_write__588__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__588__data;
    __Vtask_tb_top__DOT__apb_write__588__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__589__addr;
    __Vtask_tb_top__DOT__apb_write__589__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__589__data;
    __Vtask_tb_top__DOT__apb_write__589__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__590__addr;
    __Vtask_tb_top__DOT__apb_write__590__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_write__590__data;
    __Vtask_tb_top__DOT__apb_write__590__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_dma_done__591__timeout;
    __Vtask_tb_top__DOT__wait_dma_done__591__timeout = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__592__addr;
    __Vtask_tb_top__DOT__apb_read__592__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__592__data;
    __Vtask_tb_top__DOT__apb_read__592__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__593__n;
    __Vtask_tb_top__DOT__wait_cycles__593__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__593__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__593__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__594__addr;
    __Vtask_tb_top__DOT__apb_read__594__addr = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__apb_read__594__data;
    __Vtask_tb_top__DOT__apb_read__594__data = 0;
    std::string __Vtask_tb_top__DOT__pass__595__msg;
    std::string __Vtask_tb_top__DOT__fail__596__msg;
    std::string __Vtask_tb_top__DOT__fail__596__reason;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__598__n;
    __Vtask_tb_top__DOT__wait_cycles__598__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__598__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__598__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__599__n;
    __Vtask_tb_top__DOT__wait_cycles__599__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__wait_cycles__599__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2;
    __Vtask_tb_top__DOT__wait_cycles__599__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    // Body
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel0;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n = 1U;
            const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6013509031942924224ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout);
        __Vlabel0: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_E_stress__Vstatic__i = 5U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__timeout = 0x1f4U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__size = 0x40U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__dst = 0xec40U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__src = 0x1140U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel1;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n = 1U;
            const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6013509031942924224ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout);
        __Vlabel1: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_E_stress__Vstatic__i = 6U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__timeout = 0x1f4U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__size = 0x40U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__dst = 0xec80U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__src = 0x1180U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel2;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n = 1U;
            const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6013509031942924224ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout);
        __Vlabel2: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_E_stress__Vstatic__i = 7U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__timeout = 0x1f4U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__size = 0x40U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__dst = 0xecc0U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__src = 0x11c0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel3;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n = 1U;
            const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6013509031942924224ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout);
        __Vlabel3: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_E_stress__Vstatic__i = 8U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__timeout = 0x1f4U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__size = 0x40U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__dst = 0xed00U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__src = 0x1200U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel4;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n = 1U;
            const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6013509031942924224ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout);
        __Vlabel4: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_E_stress__Vstatic__i = 9U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__timeout = 0x1f4U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__size = 0x40U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__dst = 0xed40U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__src = 0x1240U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__501__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__502__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__503__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__504__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__500__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__506__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel5;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n = 1U;
            const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6013509031942924224ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__507__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__505__timeout);
        __Vlabel5: ;
    }
    vlSelfRef.tb_top__DOT__run_suite_E_stress__Vstatic__i = 0xaU;
    __Vtask_tb_top__DOT__pass__508__msg = std::string{"E10: Burn Test (10 iter)"};
    VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__508__msg));
    vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                         + vlSelfRef.tb_top__DOT__pass_count);
    VL_WRITEF_NX("\n--- SUITE F: System Integration (10 Vectors) ---\n",0);
    __Vtask_tb_top__DOT__dma_transfer__510__timeout = 0x1f4U;
    __Vtask_tb_top__DOT__dma_transfer__510__size = 0x40U;
    __Vtask_tb_top__DOT__dma_transfer__510__dst = 0xf000U;
    __Vtask_tb_top__DOT__dma_transfer__510__src = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__511__data = __Vtask_tb_top__DOT__dma_transfer__510__src;
    __Vtask_tb_top__DOT__apb_write__511__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__511__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__511__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__512__data = __Vtask_tb_top__DOT__dma_transfer__510__dst;
    __Vtask_tb_top__DOT__apb_write__512__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__512__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__512__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__513__data = __Vtask_tb_top__DOT__dma_transfer__510__size;
    __Vtask_tb_top__DOT__apb_write__513__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__513__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__513__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__514__data = 1U;
    __Vtask_tb_top__DOT__apb_write__514__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__514__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__514__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__515__timeout 
        = __Vtask_tb_top__DOT__dma_transfer__510__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__515__timeout)) {
            __Vtask_tb_top__DOT__apb_read__516__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__516__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            __Vtask_tb_top__DOT__apb_read__516__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__516__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel6;
            }
            __Vtask_tb_top__DOT__wait_cycles__517__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__517__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__517__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__517__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__517__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__517__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__517__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__515__timeout);
        __Vlabel6: ;
    }
    __Vtask_tb_top__DOT__check_data__518__size = 0x40U;
    __Vtask_tb_top__DOT__check_data__518__dst = 0xf000U;
    __Vtask_tb_top__DOT__check_data__518__src = 0x1000U;
    __Vtask_tb_top__DOT__check_data__518__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < __Vtask_tb_top__DOT__check_data__518__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (__Vtask_tb_top__DOT__check_data__518__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (__Vtask_tb_top__DOT__check_data__518__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            __Vtask_tb_top__DOT__check_data__518__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__data_ok 
        = __Vtask_tb_top__DOT__check_data__518__ok;
    if (vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__519__msg = std::string{"F01: Input Load"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__519__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__520__reason = std::string{"mismatch"};
        __Vtask_tb_top__DOT__fail__520__msg = std::string{"F01: Input"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__520__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__520__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    __Vtask_tb_top__DOT__dma_transfer__521__timeout = 0x12cU;
    __Vtask_tb_top__DOT__dma_transfer__521__size = 0x20U;
    __Vtask_tb_top__DOT__dma_transfer__521__dst = 0xf100U;
    __Vtask_tb_top__DOT__dma_transfer__521__src = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__522__data = __Vtask_tb_top__DOT__dma_transfer__521__src;
    __Vtask_tb_top__DOT__apb_write__522__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__522__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__522__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__523__data = __Vtask_tb_top__DOT__dma_transfer__521__dst;
    __Vtask_tb_top__DOT__apb_write__523__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__523__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__523__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__524__data = __Vtask_tb_top__DOT__dma_transfer__521__size;
    __Vtask_tb_top__DOT__apb_write__524__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__524__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__524__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__525__data = 1U;
    __Vtask_tb_top__DOT__apb_write__525__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__525__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__525__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__526__timeout 
        = __Vtask_tb_top__DOT__dma_transfer__521__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__526__timeout)) {
            __Vtask_tb_top__DOT__apb_read__527__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__527__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            __Vtask_tb_top__DOT__apb_read__527__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__527__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel7;
            }
            __Vtask_tb_top__DOT__wait_cycles__528__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__528__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__528__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__528__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__528__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__528__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__528__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__526__timeout);
        __Vlabel7: ;
    }
    __Vtask_tb_top__DOT__check_data__529__size = 0x20U;
    __Vtask_tb_top__DOT__check_data__529__dst = 0xf100U;
    __Vtask_tb_top__DOT__check_data__529__src = 0x1000U;
    __Vtask_tb_top__DOT__check_data__529__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < __Vtask_tb_top__DOT__check_data__529__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (__Vtask_tb_top__DOT__check_data__529__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (__Vtask_tb_top__DOT__check_data__529__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            __Vtask_tb_top__DOT__check_data__529__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__data_ok 
        = __Vtask_tb_top__DOT__check_data__529__ok;
    if (vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__530__msg = std::string{"F02: Config Load"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__530__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__531__reason = std::string{"mismatch"};
        __Vtask_tb_top__DOT__fail__531__msg = std::string{"F02: Config"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__531__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__531__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    __Vtask_tb_top__DOT__apb_write__532__data = 1U;
    __Vtask_tb_top__DOT__apb_write__532__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__532__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__532__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_cycles__533__n = 0xaU;
    __Vtask_tb_top__DOT__wait_cycles__533__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__533__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__533__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__533__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        __Vtask_tb_top__DOT__wait_cycles__533__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__533__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_top__DOT__apb_check_bit__534__msg = 
        std::string{"F03: Compute Busy"};
    __Vtask_tb_top__DOT__apb_check_bit__534__exp_val = 1U;
    __Vtask_tb_top__DOT__apb_check_bit__534__bit_pos = 0U;
    __Vtask_tb_top__DOT__apb_check_bit__534__addr = 0x24U;
    __Vtask_tb_top__DOT__apb_read__535__addr = __Vtask_tb_top__DOT__apb_check_bit__534__addr;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         100);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__535__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         106);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         110);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    __Vtask_tb_top__DOT__apb_read__535__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__apb_check_bit__Vstatic__rd 
        = __Vtask_tb_top__DOT__apb_read__535__data;
    if (((1U & (vlSelfRef.tb_top__DOT__apb_check_bit__Vstatic__rd 
                >> (0x1fU & __Vtask_tb_top__DOT__apb_check_bit__534__bit_pos))) 
         == (IData)(__Vtask_tb_top__DOT__apb_check_bit__534__exp_val))) {
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__apb_check_bit__534__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        VL_WRITEF_NX("  [FAIL] %@ | Bit[%0d]: Exp=%b Got=%b\n",0,
                     -1,&(__Vtask_tb_top__DOT__apb_check_bit__534__msg),
                     32,__Vtask_tb_top__DOT__apb_check_bit__534__bit_pos,
                     1,(IData)(__Vtask_tb_top__DOT__apb_check_bit__534__exp_val),
                     1,(1U & (vlSelfRef.tb_top__DOT__apb_check_bit__Vstatic__rd 
                              >> (0x1fU & __Vtask_tb_top__DOT__apb_check_bit__534__bit_pos))));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    __Vtask_tb_top__DOT__wait_cycles__536__n = 0x32U;
    __Vtask_tb_top__DOT__wait_cycles__536__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__536__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__536__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__536__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        __Vtask_tb_top__DOT__wait_cycles__536__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__536__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_top__DOT__dma_transfer__537__timeout = 0x1f4U;
    __Vtask_tb_top__DOT__dma_transfer__537__size = 0x40U;
    __Vtask_tb_top__DOT__dma_transfer__537__dst = 0xf200U;
    __Vtask_tb_top__DOT__dma_transfer__537__src = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__538__data = __Vtask_tb_top__DOT__dma_transfer__537__src;
    __Vtask_tb_top__DOT__apb_write__538__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__538__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__538__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__539__data = __Vtask_tb_top__DOT__dma_transfer__537__dst;
    __Vtask_tb_top__DOT__apb_write__539__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__539__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__539__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__540__data = __Vtask_tb_top__DOT__dma_transfer__537__size;
    __Vtask_tb_top__DOT__apb_write__540__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__540__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__540__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__541__data = 1U;
    __Vtask_tb_top__DOT__apb_write__541__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__541__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__541__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__542__timeout 
        = __Vtask_tb_top__DOT__dma_transfer__537__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__542__timeout)) {
            __Vtask_tb_top__DOT__apb_read__543__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__543__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            __Vtask_tb_top__DOT__apb_read__543__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__543__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel8;
            }
            __Vtask_tb_top__DOT__wait_cycles__544__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__544__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__544__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__544__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__544__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__544__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__544__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__542__timeout);
        __Vlabel8: ;
    }
    __Vtask_tb_top__DOT__check_data__545__size = 0x40U;
    __Vtask_tb_top__DOT__check_data__545__dst = 0xf200U;
    __Vtask_tb_top__DOT__check_data__545__src = 0x1000U;
    __Vtask_tb_top__DOT__check_data__545__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < __Vtask_tb_top__DOT__check_data__545__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (__Vtask_tb_top__DOT__check_data__545__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (__Vtask_tb_top__DOT__check_data__545__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            __Vtask_tb_top__DOT__check_data__545__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__data_ok 
        = __Vtask_tb_top__DOT__check_data__545__ok;
    if (vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__546__msg = std::string{"F04: Result Offload"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__546__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__547__reason = std::string{"mismatch"};
        __Vtask_tb_top__DOT__fail__547__msg = std::string{"F04: Result"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__547__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__547__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    __Vtask_tb_top__DOT__apb_read__548__addr = 0x28U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         100);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__548__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         106);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         110);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    __Vtask_tb_top__DOT__apb_read__548__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__rd 
        = __Vtask_tb_top__DOT__apb_read__548__data;
    if ((0U < vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__rd)) {
        __Vtask_tb_top__DOT__pass__549__msg = std::string{"F05: Cycle Count > 0"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__549__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__550__reason = std::string{"still 0"};
        __Vtask_tb_top__DOT__fail__550__msg = std::string{"F05: Cycle Count"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__550__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__550__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    __Vtask_tb_top__DOT__apb_write__551__data = 1U;
    __Vtask_tb_top__DOT__apb_write__551__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__551__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__551__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_cycles__552__n = 0x14U;
    __Vtask_tb_top__DOT__wait_cycles__552__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__552__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__552__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__552__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        __Vtask_tb_top__DOT__wait_cycles__552__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__552__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_top__DOT__apb_write__553__data = 1U;
    __Vtask_tb_top__DOT__apb_write__553__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__553__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__553__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_cycles__554__n = 0x14U;
    __Vtask_tb_top__DOT__wait_cycles__554__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__554__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__554__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__554__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        __Vtask_tb_top__DOT__wait_cycles__554__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__554__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_top__DOT__pass__555__msg = std::string{"F06: Multi-Kernel"};
    VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__555__msg));
    vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                         + vlSelfRef.tb_top__DOT__pass_count);
    __Vtask_tb_top__DOT__apb_write__556__data = 1U;
    __Vtask_tb_top__DOT__apb_write__556__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__556__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__556__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_cycles__557__n = 5U;
    __Vtask_tb_top__DOT__wait_cycles__557__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__557__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__557__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__557__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        __Vtask_tb_top__DOT__wait_cycles__557__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__557__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_top__DOT__apb_write__558__data = 2U;
    __Vtask_tb_top__DOT__apb_write__558__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__558__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__558__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_cycles__559__n = 5U;
    __Vtask_tb_top__DOT__wait_cycles__559__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__559__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__559__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__559__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        __Vtask_tb_top__DOT__wait_cycles__559__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__559__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_top__DOT__apb_write__560__data = 0U;
    __Vtask_tb_top__DOT__apb_write__560__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__560__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__560__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__pass__561__msg = std::string{"F07: Partial Run + Reset"};
    VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__561__msg));
    vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                         + vlSelfRef.tb_top__DOT__pass_count);
    __Vtask_tb_top__DOT__wait_cycles__562__n = 0x32U;
    __Vtask_tb_top__DOT__wait_cycles__562__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__562__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__562__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__562__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        __Vtask_tb_top__DOT__wait_cycles__562__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__562__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    if ((1U & (((~ (IData)(vlSelfRef.tb_top__DOT__axi_awvalid)) 
                & (~ (IData)(vlSelfRef.tb_top__DOT__axi_arvalid))) 
               & (~ (IData)(vlSelfRef.tb_top__DOT__axi_wvalid))))) {
        __Vtask_tb_top__DOT__pass__563__msg = std::string{"F08: Idle Power"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__563__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__564__reason = std::string{"signals active"};
        __Vtask_tb_top__DOT__fail__564__msg = std::string{"F08: Idle Power"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__564__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__564__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    __Vtask_tb_top__DOT__dma_transfer__565__timeout = 0x12cU;
    __Vtask_tb_top__DOT__dma_transfer__565__size = 0x20U;
    __Vtask_tb_top__DOT__dma_transfer__565__dst = 0xf300U;
    __Vtask_tb_top__DOT__dma_transfer__565__src = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__566__data = __Vtask_tb_top__DOT__dma_transfer__565__src;
    __Vtask_tb_top__DOT__apb_write__566__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__566__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__566__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__567__data = __Vtask_tb_top__DOT__dma_transfer__565__dst;
    __Vtask_tb_top__DOT__apb_write__567__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__567__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__567__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__568__data = __Vtask_tb_top__DOT__dma_transfer__565__size;
    __Vtask_tb_top__DOT__apb_write__568__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__568__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__568__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__569__data = 1U;
    __Vtask_tb_top__DOT__apb_write__569__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__569__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__569__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__570__timeout 
        = __Vtask_tb_top__DOT__dma_transfer__565__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__570__timeout)) {
            __Vtask_tb_top__DOT__apb_read__571__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__571__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            __Vtask_tb_top__DOT__apb_read__571__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__571__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel9;
            }
            __Vtask_tb_top__DOT__wait_cycles__572__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__572__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__572__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__572__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__572__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__572__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__572__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__570__timeout);
        __Vlabel9: ;
    }
    __Vtask_tb_top__DOT__apb_write__573__data = 1U;
    __Vtask_tb_top__DOT__apb_write__573__addr = 0x20U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__573__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__573__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_cycles__574__n = 0x32U;
    __Vtask_tb_top__DOT__wait_cycles__574__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__574__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__574__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__574__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        __Vtask_tb_top__DOT__wait_cycles__574__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__574__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_top__DOT__dma_transfer__575__timeout = 0x12cU;
    __Vtask_tb_top__DOT__dma_transfer__575__size = 0x20U;
    __Vtask_tb_top__DOT__dma_transfer__575__dst = 0xf400U;
    __Vtask_tb_top__DOT__dma_transfer__575__src = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__576__data = __Vtask_tb_top__DOT__dma_transfer__575__src;
    __Vtask_tb_top__DOT__apb_write__576__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__576__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__576__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__577__data = __Vtask_tb_top__DOT__dma_transfer__575__dst;
    __Vtask_tb_top__DOT__apb_write__577__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__577__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__577__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__578__data = __Vtask_tb_top__DOT__dma_transfer__575__size;
    __Vtask_tb_top__DOT__apb_write__578__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__578__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__578__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__579__data = 1U;
    __Vtask_tb_top__DOT__apb_write__579__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__579__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__579__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__580__timeout 
        = __Vtask_tb_top__DOT__dma_transfer__575__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__580__timeout)) {
            __Vtask_tb_top__DOT__apb_read__581__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__581__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            __Vtask_tb_top__DOT__apb_read__581__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__581__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel10;
            }
            __Vtask_tb_top__DOT__wait_cycles__582__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__582__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__582__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__582__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__582__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__582__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__582__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__580__timeout);
        __Vlabel10: ;
    }
    __Vtask_tb_top__DOT__check_data__583__size = 0x20U;
    __Vtask_tb_top__DOT__check_data__583__dst = 0xf400U;
    __Vtask_tb_top__DOT__check_data__583__src = 0x1000U;
    __Vtask_tb_top__DOT__check_data__583__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < __Vtask_tb_top__DOT__check_data__583__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (__Vtask_tb_top__DOT__check_data__583__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (__Vtask_tb_top__DOT__check_data__583__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            __Vtask_tb_top__DOT__check_data__583__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__data_ok 
        = __Vtask_tb_top__DOT__check_data__583__ok;
    if (vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__data_ok) {
        __Vtask_tb_top__DOT__pass__584__msg = std::string{"F09: End-to-End"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__584__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__585__reason = std::string{"mismatch"};
        __Vtask_tb_top__DOT__fail__585__msg = std::string{"F09: E2E"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__585__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__585__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    __Vtask_tb_top__DOT__dma_transfer__586__timeout = 0xc8U;
    __Vtask_tb_top__DOT__dma_transfer__586__size = 0x10U;
    __Vtask_tb_top__DOT__dma_transfer__586__dst = 0xf500U;
    __Vtask_tb_top__DOT__dma_transfer__586__src = 0x1000U;
    __Vtask_tb_top__DOT__apb_write__587__data = __Vtask_tb_top__DOT__dma_transfer__586__src;
    __Vtask_tb_top__DOT__apb_write__587__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__587__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__587__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__588__data = __Vtask_tb_top__DOT__dma_transfer__586__dst;
    __Vtask_tb_top__DOT__apb_write__588__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__588__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__588__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__589__data = __Vtask_tb_top__DOT__dma_transfer__586__size;
    __Vtask_tb_top__DOT__apb_write__589__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__589__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__589__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__apb_write__590__data = 1U;
    __Vtask_tb_top__DOT__apb_write__590__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_write__590__addr;
    vlSelfRef.tb_top__DOT__pwdata = __Vtask_tb_top__DOT__apb_write__590__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    __Vtask_tb_top__DOT__wait_dma_done__591__timeout 
        = __Vtask_tb_top__DOT__dma_transfer__586__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, __Vtask_tb_top__DOT__wait_dma_done__591__timeout)) {
            __Vtask_tb_top__DOT__apb_read__592__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__592__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            __Vtask_tb_top__DOT__apb_read__592__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = __Vtask_tb_top__DOT__apb_read__592__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel11;
            }
            __Vtask_tb_top__DOT__wait_cycles__593__n = 1U;
            __Vtask_tb_top__DOT__wait_cycles__593__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
            __Vtask_tb_top__DOT__wait_cycles__593__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = __Vtask_tb_top__DOT__wait_cycles__593__n;
            while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__593__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                __Vtask_tb_top__DOT__wait_cycles__593__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (__Vtask_tb_top__DOT__wait_cycles__593__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,__Vtask_tb_top__DOT__wait_dma_done__591__timeout);
        __Vlabel11: ;
    }
    __Vtask_tb_top__DOT__apb_read__594__addr = 4U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         100);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = __Vtask_tb_top__DOT__apb_read__594__addr;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         106);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         110);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    __Vtask_tb_top__DOT__apb_read__594__data = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__rd 
        = __Vtask_tb_top__DOT__apb_read__594__data;
    if ((2U & vlSelfRef.tb_top__DOT__run_suite_F_system__Vstatic__rd)) {
        __Vtask_tb_top__DOT__pass__595__msg = std::string{"F10: IRQ Done Chain"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(__Vtask_tb_top__DOT__pass__595__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        __Vtask_tb_top__DOT__fail__596__reason = std::string{"done not set"};
        __Vtask_tb_top__DOT__fail__596__msg = std::string{"F10: IRQ Chain"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(__Vtask_tb_top__DOT__fail__596__msg),
                     -1,&(__Vtask_tb_top__DOT__fail__596__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
    }
    VL_WRITEF_NX("\n========================================================\n   SUITE G: CONSTRAINED RANDOM VERIFICATION (CRV)\n   [Strategy] Randomize Addr/Size + Random Stress + Scoreboard\n========================================================\n",0);
    vlSelfRef.tb_top__DOT__rst_n = 0U;
    __Vtask_tb_top__DOT__wait_cycles__598__n = 5U;
    __Vtask_tb_top__DOT__wait_cycles__598__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__598__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__598__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__598__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        __Vtask_tb_top__DOT__wait_cycles__598__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__598__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__rst_n = 1U;
    __Vtask_tb_top__DOT__wait_cycles__599__n = 0xaU;
    __Vtask_tb_top__DOT__wait_cycles__599__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    __Vtask_tb_top__DOT__wait_cycles__599__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
        = __Vtask_tb_top__DOT__wait_cycles__599__n;
    while (VL_LTS_III(32, 0U, __Vtask_tb_top__DOT__wait_cycles__599__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_top.clk)", 
                                                             "01_bench/include/tb_tasks.svh", 
                                                             54);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        __Vtask_tb_top__DOT__wait_cycles__599__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (__Vtask_tb_top__DOT__wait_cycles__599__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_top__DOT__init_memory__Vstatic__i = 0U;
    while (VL_GTS_III(32, 0x20000U, vlSelfRef.tb_top__DOT__init_memory__Vstatic__i)) {
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.tb_top__DOT__init_memory__Vstatic__i)] = 0U;
        vlSelfRef.tb_top__DOT__init_memory__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__init_memory__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__init_memory__Vstatic__i = 0U;
    while (VL_GTS_III(32, 0x10000U, vlSelfRef.tb_top__DOT__init_memory__Vstatic__i)) {
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(0x1000U) 
                                                + vlSelfRef.tb_top__DOT__init_memory__Vstatic__i))] 
            = (0xffU & vlSelfRef.tb_top__DOT__init_memory__Vstatic__i);
        vlSelfRef.tb_top__DOT__init_memory__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__init_memory__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count = 0U;
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count = 0U;
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 1U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #1] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel12;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel12: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #1"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 2U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #2] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel13;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel13: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #2"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 3U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #3] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel14;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel14: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #3"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 4U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #4] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel15;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel15: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #4"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 5U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #5] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel16;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel16: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
        vlSelfRef.__Vtask_tb_top__DOT__pass__618__msg = 
            std::string{"G01: CRV Batch 1-5"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__pass__618__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #5"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 6U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #6] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel17;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel17: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #6"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 7U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #7] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel18;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel18: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #7"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 8U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #8] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel19;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel19: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #8"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 9U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #9] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel20;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel20: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #9"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 0xaU;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #10] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel21;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel21: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
        vlSelfRef.__Vtask_tb_top__DOT__pass__618__msg = 
            std::string{"G01: CRV Batch 6-10"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__pass__618__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #10"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 0xbU;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #11] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel22;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel22: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #11"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 0xcU;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #12] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel23;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel23: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #12"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 0xdU;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #13] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel24;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel24: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #13"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 0xeU;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #14] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel25;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel25: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #14"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 0xfU;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #15] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel26;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel26: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
        vlSelfRef.__Vtask_tb_top__DOT__pass__618__msg = 
            std::string{"G01: CRV Batch 11-15"};
        VL_WRITEF_NX("  [PASS] %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__pass__618__msg));
        vlSelfRef.tb_top__DOT__pass_count = ((IData)(1U) 
                                             + vlSelfRef.tb_top__DOT__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #15"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 0x10U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #16] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel27;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel27: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #16"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 0x11U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x14U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(4U) + (IData)((0xcU & VL_SHIFTL_III(32,32,32, (IData)(
                                                                             VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_single_beat = ((IData)(1U) 
                                                  + vlSelfRef.tb_top__DOT__cov_single_beat);
    } else if (VL_GTS_III(32, 0x50U, vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x14U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                        VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x7cU))), 2U)));
        vlSelfRef.tb_top__DOT__cov_multi_beat = ((IData)(1U) 
                                                 + vlSelfRef.tb_top__DOT__cov_multi_beat);
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout 
            = ((IData)(0x204U) + (IData)((0x1fcU & 
                                          VL_SHIFTL_III(32,32,32, (IData)(
                                                                          VL_RANDOM_I()), 2U))));
        vlSelfRef.tb_top__DOT__cov_max_burst = ((IData)(1U) 
                                                + vlSelfRef.tb_top__DOT__cov_max_burst);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_stress__604__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9199571814962535704ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    if (VL_GTS_III(32, 0x46U, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout = 0U;
    } else if (VL_GTS_III(32, 0x5aU, vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__r)) {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(1U) + (IData)(VL_MODDIV_III(32, (IData)(
                                                               VL_RANDOM_I()), (IData)(0x1eU))));
    } else {
        vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout 
            = ((IData)(0x1fU) + (IData)(VL_MODDIV_III(32, (IData)(
                                                                  VL_RANDOM_I()), (IData)(0x32U))));
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_stress__604__Vfuncout;
    VL_WRITEF_NX("[CRV #17] Src: 0x%x | Dst: 0x%x | Size: %0# | Stress: %0d%%\n",0,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz,
                 32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress);
    if (VL_LTS_III(32, 0U, vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress)) {
        vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__stress;
        vlSelfRef.tb_top__DOT__stress_enable = 1U;
        vlSelfRef.tb_top__DOT__stress_probability = vlSelfRef.__Vtask_tb_top__DOT__enable_stress__607__prob;
        vlSelfRef.tb_top__DOT__cov_stress_cycles = 
            ((IData)(1U) + vlSelfRef.tb_top__DOT__cov_stress_cycles);
    } else {
        vlSelfRef.tb_top__DOT__stress_enable = 0U;
        vlSelfRef.tb_top__DOT__stress_probability = 0U;
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k = 0U;
    while ((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            < vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz)) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data 
            = VL_RANDOM_I();
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
            = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__rand_data;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__605__data 
               >> 0x18U);
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data = 0xdeaddeadU;
        vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr 
            = (vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
               + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr)] 
            = (0xffU & vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data);
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(1U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 8U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(2U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (0xffU & (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
                        >> 0x10U));
        vlSelfRef.tb_top__DOT__mem[(0x1ffffU & ((IData)(3U) 
                                                + vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__addr))] 
            = (vlSelfRef.__Vtask_tb_top__DOT__ram_write__606__data 
               >> 0x18U);
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k 
            = ((IData)(4U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__k);
    }
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout = 0x2710U;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__src;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr = 8U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__610__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__dst;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr = 0xcU;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__611__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__size;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr = 0x10U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__612__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data = 1U;
    vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         70);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__addr;
    vlSelfRef.tb_top__DOT__pwdata = vlSelfRef.__Vtask_tb_top__DOT__apb_write__613__data;
    vlSelfRef.tb_top__DOT__pwrite = 1U;
    vlSelfRef.tb_top__DOT__psel = 1U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         77);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__penable = 1U;
    co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_top.clk)", 
                                                         "01_bench/include/tb_tasks.svh", 
                                                         81);
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.tb_top__DOT__psel = 0U;
    vlSelfRef.tb_top__DOT__penable = 0U;
    vlSelfRef.tb_top__DOT__pwrite = 0U;
    vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout 
        = vlSelfRef.__Vtask_tb_top__DOT__dma_transfer__609__timeout;
    {
        vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i = 0U;
        while (VL_LTS_III(32, vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i, vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout)) {
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr = 4U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 100);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__paddr = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__addr;
            vlSelfRef.tb_top__DOT__pwrite = 0U;
            vlSelfRef.tb_top__DOT__psel = 1U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 106);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.tb_top__DOT__penable = 1U;
            co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_top.clk)", 
                                                                 "01_bench/include/tb_tasks.svh", 
                                                                 110);
            vlSelfRef.__Vm_traceActivity[4U] = 1U;
            vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data 
                = vlSelfRef.tb_top__DOT__u_dut__DOT__u_csr__DOT__prdata;
            vlSelfRef.tb_top__DOT__psel = 0U;
            vlSelfRef.tb_top__DOT__penable = 0U;
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status 
                = vlSelfRef.__Vtask_tb_top__DOT__apb_read__615__data;
            if ((2U & vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__status)) {
                goto __Vlabel28;
            }
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n = 1U;
            vlSelf->__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4505665759591131645ull);
            vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__n;
            while (VL_LTS_III(32, 0U, vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
                co_await vlSelfRef.__VtrigSched_hcdb04a4a__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_top.clk)", 
                                                                     "01_bench/include/tb_tasks.svh", 
                                                                     54);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
                vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                    = (vlSelfRef.__Vtask_tb_top__DOT__wait_cycles__616__tb_top__DOT__unnamedblk1_3__DOT____Vrepeat2 
                       - (IData)(1U));
            }
            vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i 
                = ((IData)(1U) + vlSelfRef.tb_top__DOT__wait_dma_done__Vstatic__i);
        }
        VL_WRITEF_NX("  [WARN] DMA timeout after %0d cycles\n",0,
                     32,vlSelfRef.__Vtask_tb_top__DOT__wait_dma_done__614__timeout);
        __Vlabel28: ;
    }
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
        = vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src;
    vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 1U;
    vlSelfRef.tb_top__DOT__check_data__Vstatic__i = 0U;
    while ((vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            < vlSelfRef.__Vtask_tb_top__DOT__check_data__617__size)) {
        if ((vlSelfRef.tb_top__DOT__mem[(0x1ffffU & 
                                         (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__dst 
                                          + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))] 
             != vlSelfRef.tb_top__DOT__mem[(0x1ffffU 
                                            & (vlSelfRef.__Vtask_tb_top__DOT__check_data__617__src 
                                               + vlSelfRef.tb_top__DOT__check_data__Vstatic__i))])) {
            vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok = 0U;
        }
        vlSelfRef.tb_top__DOT__check_data__Vstatic__i 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__check_data__Vstatic__i);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok 
        = vlSelfRef.__Vtask_tb_top__DOT__check_data__617__ok;
    if (VL_LIKELY((vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__data_ok))) {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__pass_count);
    } else {
        vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count 
            = ((IData)(1U) + vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__fail_count);
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason = 
            std::string{"Data Mismatch"};
        vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg = 
            std::string{"G01: CRV Iteration #17"};
        VL_WRITEF_NX("  [FAIL] %@ - %@\n",0,-1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__msg),
                     -1,&(vlSelfRef.__Vtask_tb_top__DOT__fail__619__reason));
        vlSelfRef.tb_top__DOT__error_count = ((IData)(1U) 
                                              + vlSelfRef.tb_top__DOT__error_count);
        VL_WRITEF_NX("      [DEBUG] Failed -> Src: 0x%x, Dst: 0x%x, Size: %0#\n",0,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst,
                     32,vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__sz);
    }
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__iter = 0x12U;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout 
        = ((IData)(0x1000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1800U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__src 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_src_addr__601__Vfuncout;
    vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout 
        = ((IData)(0x8000U) + (IData)(VL_SHIFTL_III(32,32,32, (IData)(
                                                                      VL_MODDIV_III(32, (IData)(
                                                                                VL_RANDOM_I()), (IData)(0x1c00U))), 2U)));
    vlSelfRef.tb_top__DOT__run_suite_G_crv__Vstatic__dst 
        = vlSelfRef.__Vfunc_tb_top__DOT__rand_dst_addr__602__Vfuncout;
    vlSelf->__Vfunc_tb_top__DOT__rand_size__603__r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16290736261088823266ull);
    vlSelfRef.__Vfunc_tb_top__DOT__rand_size__603__r 
        = VL_MODDIV_III(32, (IData)(VL_RANDOM_I()), (IData)(0x64U));
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
}
