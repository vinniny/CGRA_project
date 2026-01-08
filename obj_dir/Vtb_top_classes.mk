# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Make include file with class lists
#
# This file lists generated Verilated files, for including in higher level makefiles.
# See Vtb_top.mk for the caller.

### Switches...
# C11 constructs required?  0/1 (always on now)
VM_C11 = 1
# Timing enabled?  0/1
VM_TIMING = 1
# Coverage output mode?  0/1 (from --coverage)
VM_COVERAGE = 0
# Parallel builds?  0/1 (from --output-split)
VM_PARALLEL_BUILDS = 1
# Tracing output mode?  0/1 (from --trace-fst/--trace-saif/--trace-vcd)
VM_TRACE = 1
# Tracing output mode in FST format?  0/1 (from --trace-fst)
VM_TRACE_FST = 0
# Tracing output mode in SAIF format?  0/1 (from --trace-saif)
VM_TRACE_SAIF = 0
# Tracing output mode in VCD format?  0/1 (from --trace-vcd)
VM_TRACE_VCD = 1

### Object file lists...
# Generated module classes, fast-path, compile with highest optimization
VM_CLASSES_FAST += \
  Vtb_top \
  Vtb_top___024root__DepSet_h7f86b803__0 \
  Vtb_top___024root__DepSet_h7f86b803__1 \
  Vtb_top___024root__DepSet_h7f86b803__2 \
  Vtb_top___024root__DepSet_h7f86b803__3 \
  Vtb_top___024root__DepSet_h7f86b803__4 \
  Vtb_top___024root__DepSet_h7f86b803__5 \
  Vtb_top___024root__DepSet_h7f86b803__6 \
  Vtb_top___024root__DepSet_h7f86b803__7 \
  Vtb_top___024root__DepSet_h7f86b803__8 \
  Vtb_top___024root__DepSet_h7f86b803__9 \
  Vtb_top___024root__DepSet_h7f86b803__10 \
  Vtb_top___024root__DepSet_h7f86b803__11 \
  Vtb_top___024root__DepSet_h7f86b803__12 \
  Vtb_top___024root__DepSet_h7f86b803__13 \
  Vtb_top___024root__DepSet_h7f86b803__14 \
  Vtb_top___024root__DepSet_h7f86b803__15 \
  Vtb_top___024root__DepSet_h7f86b803__16 \
  Vtb_top___024root__DepSet_h7f86b803__17 \
  Vtb_top___024root__DepSet_h7f86b803__18 \
  Vtb_top___024root__DepSet_h7f86b803__19 \
  Vtb_top___024root__DepSet_h7f86b803__20 \
  Vtb_top___024root__DepSet_h9ad02603__0 \
  Vtb_top_cgra_pe__A4__DepSet_hfa6809c8__0 \
  Vtb_top_cgra_pe__A4__DepSet_h1526b7c8__0 \
  Vtb_top__main \

# Generated module classes, non-fast-path, compile with low/medium optimization
VM_CLASSES_SLOW += \
  Vtb_top__ConstPool_0 \
  Vtb_top___024root__Slow \
  Vtb_top___024root__DepSet_h7f86b803__0__Slow \
  Vtb_top___024root__DepSet_h9ad02603__0__Slow \
  Vtb_top___024unit__Slow \
  Vtb_top___024unit__DepSet_hba4cee98__0__Slow \
  Vtb_top_cgra_pe__A4__Slow \
  Vtb_top_cgra_pe__A4__DepSet_hfa6809c8__0__Slow \
  Vtb_top_cgra_pe__A4__DepSet_h1526b7c8__0__Slow \

# Generated support classes, fast-path, compile with highest optimization
VM_SUPPORT_FAST += \
  Vtb_top__Trace__0 \
  Vtb_top__Trace__1 \

# Generated support classes, non-fast-path, compile with low/medium optimization
VM_SUPPORT_SLOW += \
  Vtb_top__Syms \
  Vtb_top__Trace__0__Slow \
  Vtb_top__TraceDecls__0__Slow \
  Vtb_top__Trace__1__Slow \

# Global classes, need linked once per executable, fast-path, compile with highest optimization
VM_GLOBAL_FAST += \
  verilated \
  verilated_vcd_c \
  verilated_timing \
  verilated_threads \

# Global classes, need linked once per executable, non-fast-path, compile with low/medium optimization
VM_GLOBAL_SLOW += \

# Verilated -*- Makefile -*-
