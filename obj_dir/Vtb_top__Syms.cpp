// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtb_top__pch.h"
#include "Vtb_top.h"
#include "Vtb_top___024root.h"
#include "Vtb_top___024unit.h"
#include "Vtb_top_cgra_pe__A4.h"

// FUNCTIONS
Vtb_top__Syms::~Vtb_top__Syms()
{
#ifdef VM_TRACE
    if (__Vm_dumping) _traceDumpClose();
#endif  // VM_TRACE
}

void Vtb_top__Syms::_traceDump() {
    const VerilatedLockGuard lock{__Vm_dumperMutex};
    __Vm_dumperp->dump(VL_TIME_Q());
}

void Vtb_top__Syms::_traceDumpOpen() {
    const VerilatedLockGuard lock{__Vm_dumperMutex};
    if (VL_UNLIKELY(!__Vm_dumperp)) {
        __Vm_dumperp = new VerilatedVcdC();
        __Vm_modelp->trace(__Vm_dumperp, 0, 0);
        const std::string dumpfile = _vm_contextp__->dumpfileCheck();
        __Vm_dumperp->open(dumpfile.c_str());
        __Vm_dumping = true;
    }
}

void Vtb_top__Syms::_traceDumpClose() {
    const VerilatedLockGuard lock{__Vm_dumperMutex};
    __Vm_dumping = false;
    VL_DO_CLEAR(delete __Vm_dumperp, __Vm_dumperp = nullptr);
}

Vtb_top__Syms::Vtb_top__Syms(VerilatedContext* contextp, const char* namep, Vtb_top* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_00.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_01.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_02.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_03.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_10.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_11.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_12.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_13.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_20.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_21.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_22.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_23.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_30.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_31.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_32.u_pe")}
    , TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe{this, Verilated::catName(namep, "tb_top.u_dut.u_array.u_tile_33.u_pe")}
{
        // Check resources
        Verilated::stackCheck(1096);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe;
    TOP.__PVT__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe = &TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_00__DOT__u_pe.__Vconfigure(true);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_01__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_02__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_03__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_10__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_11__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_12__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_13__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_20__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_21__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_22__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_23__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_30__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_31__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_32__DOT__u_pe.__Vconfigure(false);
    TOP__tb_top__DOT__u_dut__DOT__u_array__DOT__u_tile_33__DOT__u_pe.__Vconfigure(false);
}
