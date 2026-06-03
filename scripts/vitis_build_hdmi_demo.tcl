# vitis_build_hdmi_demo.tcl — build the LIVE dual-HDMI MNIST demo
# (demo_mnist_hdmi_bm, HDMI-in capture -> CGRA MNIST -> HDMI-out display)
# from the dual-HDMI .xsa, via the pure Vivado->Vitis flow. Identical Tcl on
# Windows xsct.bat.
#
# CRITICAL: in the HDMI BD the CGRA APB is at 0x43C10000 (NOT 0x43C00000) ->
# build with -DCGRA_BASE=0x43C10000. LIVE_INPUT enables the HDMI-in path.
proc _env_or {n d} { if {[info exists ::env($n)]} { return $::env($n) } ; return $d }
set REPO [file normalize [file join [file dirname [info script]] ..]]
set XSA  [_env_or CGRA_XSA [file join $REPO bitstreams cgra_hdmi_dual.xsa]]
# Default Vitis workspace on NATIVE WSL ext4 (NOT /tmp — that clears mid-session
# on this WSL).  Override with CGRA_WS=... if needed.
set WS   [_env_or CGRA_WS /home/vinniny/cgra_builds/vitis_ws]
set PLAT cgra_hdmi_dual
set APP  hdmi_demo
set BM   [file join $REPO 07_sw baremetal]
set CNN  [file join $REPO 07_sw cnn_eval]
set FONTDIR [file join $REPO 07_sw linux demo_mnist_hdmi]

if {![file exists $XSA]} { error "XSA not found: $XSA (run hdmi_dual_build_p2 first)" }
file mkdir $WS; setws $WS
if {[catch {platform active $PLAT}]} {
    platform create -name $PLAT -hw $XSA -os standalone -proc ps7_cortexa9_0 -arch 32-bit
    platform write
}
platform generate
puts "platform ready"
catch {app remove -name $APP}
app create -name $APP -platform $PLAT -domain standalone_domain -template "Empty Application(C)"

set SRC [file join $WS $APP src]
file delete -force $SRC; file mkdir $SRC
foreach f {start.s demo_mnist_hdmi_bm.c arm_fc_int_bm.c arm_fc_vfp_bm.c \
           arm_cnn_bm.c hdmi_bm.c fb_lib_bm.c hdmi_in_bm.c frame_to_mnist.c \
           demo_mnist_weights.S demo_mnist_conv_weights.S gic.c \
           uart.h cgra.h cgra_kernels_cnn.h cgra_kernels_cnn_opt.h \
           cgra_kernels_cnn_v2.h arm_cnn_bm.h arm_fc_bm.h frame_to_mnist.h \
           hdmi_bm.h hdmi_in_bm.h mmu_cache_bm.h fb_lib_bm.h mnist_sweep_fixture.h gic.h \
           linker_cnn.ld} {
    if {[file exists [file join $BM $f]]} { file copy -force [file join $BM $f] $SRC/ } else { puts "  MISSING(bm): $f" }
}
# font from the linux demo dir
foreach f {font5x7.c font5x7.h} {
    if {[file exists [file join $FONTDIR $f]]} { file copy -force [file join $FONTDIR $f] $SRC/ } else { puts "  MISSING(font): $f" }
}
# font sibling for fb_lib_bm.c's hardcoded "../linux/demo_mnist_hdmi/font5x7.h"
set FONTSIB [file join $WS $APP linux demo_mnist_hdmi]
file delete -force $FONTSIB; file mkdir $FONTSIB
catch {file copy -force [file join $FONTDIR font5x7.h] $FONTSIB/}  ;# .h only — .c compiles once from src/
# cnn_eval sibling for ../cnn_eval header + .incbin weight blobs
set CE [file join $WS $APP cnn_eval]
file delete -force $CE; file mkdir $CE
foreach f {mnist_weights_scale.h mnist_weights_spm.bin mnist_weights_conv.bin} {
    file copy -force [file join $CNN $f] $CE/
}
app config -name $APP -set linker-script [file join $SRC linker_cnn.ld]
app config -name $APP -add define-compiler-symbols BOARD_CGRA_ONLY
app config -name $APP -add define-compiler-symbols CGRA_BASE=0x43C10000
app config -name $APP -add define-compiler-symbols ARM_CNN_VARIANT=1
# LIVE_INPUT (HDMI-in capture) needs the richer BD (color_convert/pixel_pack/
# gpio); on the lean clean BD test HDMI-OUT first.  CGRA_LIVE=1 re-enables it.
if {[_env_or CGRA_LIVE 0] ne "0"} {
    app config -name $APP -add define-compiler-symbols LIVE_INPUT
    puts "  LIVE_INPUT enabled"
} else {
    puts "  LIVE_INPUT disabled (HDMI-OUT-only test build)"
}
# CGRA_CALIB=1: per-image FC1 delta dump (CGRA - ARM-INT64) over UART for the
# per-neuron correction table. Build WITHOUT CGRA_LIVE so sweep fixtures drive it.
if {[_env_or CGRA_CALIB 0] ne "0"} {
    app config -name $APP -add define-compiler-symbols CALIB_DUMP
    puts "  CALIB_DUMP enabled"
}
# CGRA_DCACHE=1: enable MMU + I/D-cache (mmu_cache_bm.h) — ~20-30x ARM speedup.
if {[_env_or CGRA_DCACHE 0] ne "0"} {
    app config -name $APP -add define-compiler-symbols ENABLE_DCACHE
    puts "  ENABLE_DCACHE enabled"
}
app config -name $APP -add compiler-misc {-mfpu=vfpv3 -mfloat-abi=hard -ffunction-sections -fdata-sections}
app config -name $APP -add assembler-flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I$SRC"
app config -name $APP -set build-config Debug
app build -name $APP
set ELF [file join $WS $APP Debug $APP.elf]
if {![file exists $ELF]} { error "build failed: no $ELF" }
puts "HDMI DEMO ELF: $ELF ([file size $ELF] bytes)"
puts "Run: CGRA_XSA_DIR=$WS/$APP/_ide CGRA_BIT=$WS/$APP/_ide/bitstream/*.bit CGRA_ELF=$ELF xsct scripts/vitis_launch_autohw.tcl"
exit
