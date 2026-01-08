// ==============================================================================
// sim_main.cpp - Verilator 5.x C++ Wrapper with VerilatedContext
// ==============================================================================
// This is the proper Verilator 5.x timing-mode wrapper.
// The SystemVerilog manages clock generation (`always #5 clk...`).
// C++ acts as the event scheduler, advancing time and evaluating the model.
//
// Features:
//   - VCD tracing via +trace
//   - Real-time performance benchmarking
// ==============================================================================

#include <memory>
#include <iostream>
#include <chrono>
#include "verilated.h"
#include "Vtb_top.h"
#include "verilated_vcd_c.h"

int main(int argc, char** argv) {
    // ========================================================================
    // 1. Context and Instance Setup
    // ========================================================================
    const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
    contextp->commandArgs(argc, argv);
    contextp->debug(0);
    contextp->randReset(2);       // Initialize random seed
    contextp->traceEverOn(true);  // Enable tracing capability

    const std::unique_ptr<Vtb_top> top{new Vtb_top{contextp.get(), "TOP"}};

    // ========================================================================
    // 2. Trace Setup (optional, enabled via +trace)
    // ========================================================================
    VerilatedVcdC* tfp = nullptr;
    const char* flag = contextp->commandArgsPlusMatch("trace");
    if (flag && 0 == strcmp(flag, "+trace")) {
        tfp = new VerilatedVcdC;
        top->trace(tfp, 99);  // Trace 99 levels of hierarchy
        tfp->open("cgra_sim.vcd");
        std::cout << "[SIM] VCD tracing enabled: cgra_sim.vcd" << std::endl;
    }

    // ========================================================================
    // 3. Simulation Loop (Timing-Driven) with Benchmarking
    // ========================================================================
    // In --timing mode, we do NOT toggle clock here.
    // SystemVerilog handles all timing via `always #5 clk...`.
    // We just pump the event loop and advance time.
    
    std::cout << "[SIM] Starting Verilator simulation..." << std::endl;
    
    // Performance benchmarking
    auto start_time = std::chrono::high_resolution_clock::now();
    unsigned long sim_cycles = 0;
    unsigned long last_report_cycles = 0;
    auto last_report_time = start_time;
    
    while (!contextp->gotFinish()) {
        contextp->timeInc(1);  // Advance time by 1 unit (1ns with timescale 1ns/1ps)
        top->eval();           // Evaluate model at this time
        sim_cycles++;

        if (tfp) tfp->dump(contextp->time());
        
        // Flush log every 1000 cycles for CI visibility
        if (sim_cycles % 1000 == 0) {
            std::cout << std::flush;
        }
        
        // Progress report every 10M cycles (only if running long simulations)
        if (sim_cycles - last_report_cycles >= 10000000) {
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> interval = now - last_report_time;
            double interval_khz = (sim_cycles - last_report_cycles) / interval.count() / 1000.0;
            std::cout << "[PERF] " << sim_cycles / 1000000 << "M cycles @ " 
                      << interval_khz << " kHz" << std::endl;
            last_report_cycles = sim_cycles;
            last_report_time = now;
        }
    }

    // ========================================================================
    // 4. Final Performance Report
    // ========================================================================
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_time = end_time - start_time;
    double sim_khz = (sim_cycles / total_time.count()) / 1000.0;
    
    std::cout << std::endl;
    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                  SIMULATION PERFORMANCE                       ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  Total sim cycles:    " << sim_cycles << std::endl;
    std::cout << "║  Wall clock time:     " << total_time.count() << " sec" << std::endl;
    std::cout << "║  Simulation speed:    " << sim_khz << " kHz" << std::endl;
    std::cout << "║  Equiv real time:     " << (sim_cycles / 1000.0) << " us @ 100MHz" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
    
    std::cout << "[SIM] Simulation finished at time " << contextp->time() << std::endl;
    
    if (tfp) {
        tfp->close();
        delete tfp;
    }
    
    // Check for fatal errors from the simulation
    if (contextp->gotError()) {
        std::cout << "[SIM] Simulation ended with errors!" << std::endl;
        return 1;
    }
    
    return 0;
}
