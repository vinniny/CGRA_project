# =============================================================================
# vitis_build_demo.tcl — Vitis 2025.1 xsct batch script to build a bare-metal
# demo from one of the 3 .xsa files.
#
# Mirrors what the Vitis Unified IDE does via GUI clicks:
#   - File -> New -> Platform Component (from .xsa)
#   - File -> New -> Application Component
#   - drop in source files
#   - Build
#
# Runs on Linux xsct or Windows xsct.bat -- identical Tcl. Tested on Linux
# 2026-05-25 via /tools/Xilinx/2025.1/Vitis/bin/xsct against
# bitstreams/cgra_vtpg_ila.xsa -- produces demo_vtpg_test.elf (45 336 B).
#
# Usage examples:
#
#   # Default: build demo_vtpg against cgra_vtpg_ila.xsa
#   xsct scripts/vitis_build_demo.tcl
#
#   # Custom demo + .xsa
#   CGRA_XSA=bitstreams/cgra_rebuilt_from_base.xsa \
#   CGRA_DEMO=cgra_test  CGRA_DEMO_SRCS="start.s main.c gic.c" \
#   xsct scripts/vitis_build_demo.tcl
#
# Output:
#   $CGRA_WS/<plat>/                              <- platform (BSP, ps7_init.c)
#   $CGRA_WS/<app>/Debug/<app>.elf                <- the bare-metal ELF
# =============================================================================

proc _env_or {name def} {
    if {[info exists ::env($name)]} { return $::env($name) }
    return $def
}

set REPO    [file normalize [file dirname [info script]]/..]
set XSA     [_env_or CGRA_XSA      $REPO/bitstreams/cgra_vtpg_ila.xsa]
set WS      [_env_or CGRA_WS       /tmp/cgra_vitis_ws]
set APP     [_env_or CGRA_DEMO     demo_vtpg]
set SRCS    [_env_or CGRA_DEMO_SRCS "start.s demo_vtpg.c hdmi_in_bm.c hdmi_in_bm.h vtpg.h gic.c gic.h uart.h linker.ld"]
set LINKER  [_env_or CGRA_LINKER   linker.ld]
set EXTRA   [_env_or CGRA_EXTRA_CFLAGS ""]
set PLAT    [file rootname [file tail $XSA]]

puts "==========================================================="
puts " VITIS xsct BUILD"
puts "==========================================================="
puts "  XSA      : $XSA"
puts "  Workspace: $WS"
puts "  Platform : $PLAT"
puts "  App      : $APP"
puts "  Sources  : $SRCS"
puts "==========================================================="

if {![file exists $XSA]} { error "XSA not found: $XSA" }
file mkdir $WS
setws $WS

# ----- 1. Platform from .xsa ----------------------------------------------
puts "\n=== 1. platform create ==="
if {[catch {platform active $PLAT}]} {
    platform create -name $PLAT -hw $XSA \
                    -os standalone -proc ps7_cortexa9_0 -arch 32-bit
    platform write
    puts "  platform $PLAT created"
} else {
    puts "  platform $PLAT already exists -- reusing"
}
platform generate
puts "  BSP generated"

# ----- 2. Application ------------------------------------------------------
puts "\n=== 2. app create ==="
if {[catch {app config -name $APP list}]} {
    # Template name in Vitis 2025.1 is "Empty Application(C)" -- NO space
    # before the paren. Different from earlier Vitis versions.
    app create -name     $APP \
               -platform $PLAT \
               -domain   standalone_domain \
               -template "Empty Application(C)"
    puts "  app $APP created"
} else {
    puts "  app $APP exists -- reusing"
}

# ----- 3. Source files ----------------------------------------------------
puts "\n=== 3. import sources ==="
set BAREMETAL $REPO/07_sw/baremetal
set APP_SRC $WS/$APP/src
file delete -force $APP_SRC
file mkdir $APP_SRC
foreach f $SRCS {
    set path $BAREMETAL/$f
    if {[file exists $path]} {
        file copy -force $path $APP_SRC/
        puts "    + $f"
    } else {
        puts "    MISSING: $path"
    }
}

# ----- 4. App config ------------------------------------------------------
puts "\n=== 4. app config ==="
app config -name $APP -set linker-script $APP_SRC/$LINKER
app config -name $APP -add define-compiler-symbols BOARD_CGRA_ONLY
if {$EXTRA ne ""} {
    foreach sym [split $EXTRA " "] {
        if {[string match "-D*" $sym]} {
            app config -name $APP -add define-compiler-symbols [string range $sym 2 end]
        }
    }
}
app config -name $APP -add compiler-misc {-mfpu=vfpv3 -mfloat-abi=hard}
# Vitis 2025.1 invokes the assembler for .s files WITHOUT inheriting
# -mcpu/-mfpu from compiler-misc -- ARMv7 ISB/VFP/WFI then fail. Set the
# flags explicitly via assembler-flags (not assembler-misc -- that's the
# wrong key name in 2025.1).
app config -name $APP -add assembler-flags {-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard}
app config -name $APP -set build-config Debug
puts "  config set: linker-script, BOARD_CGRA_ONLY, VFP flags (compiler + assembler)"

# ----- 5. Build -----------------------------------------------------------
puts "\n=== 5. app build ==="
app build -name $APP

set ELF $WS/$APP/Debug/${APP}.elf
if {![file exists $ELF]} {
    error "Build did not produce $ELF"
}

puts ""
puts "==========================================================="
puts " VITIS BUILD COMPLETE"
puts "==========================================================="
puts "  ELF       : $ELF"
puts "  ELF size  : [file size $ELF] bytes"
puts ""
puts " To deploy:"
puts "  Vitis IDE: Run -> Run Configurations -> Single Application Debug"
puts "             -> point at \$ELF, target setup: Reset, Program FPGA,"
puts "                Run ps7_init, Run ps7_post_config all = YES"
puts "  xsct:      connect; targets -set 2 (the ARM); source ps7_init.tcl;"
puts "             ps7_init; ps7_post_config; dow \$ELF; con"
puts "==========================================================="
exit 0
