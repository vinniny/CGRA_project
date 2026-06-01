# =============================================================================
# vitis_build_mnist_demo.tcl — build the MNIST per-stage CGRA demo through the
# pure Vivado→Vitis flow, from bitstreams/cgra_top.xsa. Identical Tcl on Linux
# xsct and Windows xsct.bat — this IS the reproducible recipe for the GUI host.
#
# Mirrors the Vitis Unified IDE GUI:
#   File → New → Platform Component (from cgra_top.xsa)
#   File → New → Application Component (Empty Application(C))
#   import sources, set linker/defines, Build.
#
# Usage:
#   xsct scripts/vitis_build_mnist_demo.tcl                  (Linux)
#   xsct.bat scripts\vitis_build_mnist_demo.tcl              (Windows)
#   (override workspace: set env CGRA_WS before calling)
#
# Output: $WS/mnist_demo/Debug/mnist_demo.elf  + platform with BSP+ps7_init.
#
# Demo is caches-OFF + FCLK0=50 (deterministic): expect CGRA accuracy 87/100,
# ARM-INT 94/100, CGRA-FC ~7.7x faster than ARM-INT-FC. See
# 06_doc/silicon_pillars_2026-05-29.md for the canonical Vitis numbers.
# =============================================================================
proc _env_or {n d} { if {[info exists ::env($n)]} { return $::env($n) } ; return $d }

set REPO [file normalize [file join [file dirname [info script]] ..]]
set XSA  [file join $REPO bitstreams cgra_top.xsa]
set WS   [_env_or CGRA_WS [file join [_env_or TMP /tmp] cgra_vitis_demo]]
set PLAT cgra_top
set APP  mnist_demo
set BM   [file join $REPO 07_sw baremetal]
set CNN  [file join $REPO 07_sw cnn_eval]

puts "REPO=$REPO\nXSA=$XSA\nWS=$WS"
if {![file exists $XSA]} { error "XSA not found: $XSA" }
file mkdir $WS
setws $WS

# 1. Platform from .xsa (auto BSP + ps7_init) -------------------------------
if {[catch {platform active $PLAT}]} {
    platform create -name $PLAT -hw $XSA -os standalone -proc ps7_cortexa9_0 -arch 32-bit
    platform write
}
platform generate
puts "platform ready"

# 2. Application ------------------------------------------------------------
catch {app remove -name $APP}
app create -name $APP -platform $PLAT -domain standalone_domain -template "Empty Application(C)"

# 3. Sources (flat import into src/) ----------------------------------------
set SRC [file join $WS $APP src]
file delete -force $SRC; file mkdir $SRC
foreach f {start.s demo_mnist_per_stage.c arm_fc_int_bm.c arm_cnn_int_bm.c \
           demo_mnist_weights.S demo_mnist_conv_weights.S gic.c \
           uart.h cgra.h cgra_kernels_cnn.h mnist_sweep_fixture.h \
           arm_fc_bm.h arm_cnn_int_bm.h gic.h linker_cnn.ld} {
    if {[file exists [file join $BM $f]]} {
        file copy -force [file join $BM $f] $SRC/
    } else { puts "  MISSING: $f" }
}
# 3b. cnn_eval sibling dir so the demo's "../cnn_eval/<x>" header + the weight
#     .incbin paths resolve from src/ (GCC resolves quoted includes relative to
#     the .c file; the assembler resolves .incbin via the -I added in step 4).
set CE [file join $WS $APP cnn_eval]
file delete -force $CE; file mkdir $CE
foreach f {mnist_weights_scale.h mnist_weights_spm.bin mnist_weights_conv.bin} {
    file copy -force [file join $CNN $f] $CE/
}

# 4. Config: CNN linker, defines, VFP, assembler -I for .incbin -------------
app config -name $APP -set linker-script [file join $SRC linker_cnn.ld]
app config -name $APP -add define-compiler-symbols BOARD_CGRA_ONLY
app config -name $APP -add define-compiler-symbols TWO_PASS_PMU=1
app config -name $APP -add compiler-misc {-mfpu=vfpv3 -mfloat-abi=hard -ffunction-sections -fdata-sections}
app config -name $APP -add assembler-flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I$SRC"
app config -name $APP -set build-config Debug

# 5. Build ------------------------------------------------------------------
app build -name $APP
set ELF [file join $WS $APP Debug $APP.elf]
if {![file exists $ELF]} { error "build failed: no $ELF" }
puts "=========================================================="
puts " MNIST DEMO BUILT (pure Vivado->Vitis flow)"
puts "  ELF : $ELF ([file size $ELF] bytes)"
puts "  Run : CGRA_XSA_DIR=$WS/$APP/_ide \\"
puts "        CGRA_BIT=$WS/$APP/_ide/bitstream/cgra_top.bit \\"
puts "        CGRA_ELF=$ELF \\"
puts "        xsct scripts/vitis_launch_autohw.tcl"
puts "  Expect: CGRA 87/100, ARM-INT 94/100"
puts "=========================================================="
exit
