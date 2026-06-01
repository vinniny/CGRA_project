set REPO /home/vinniny/centos_vm/projects/CGRA_project
set BM   $REPO/07_sw/baremetal
set WS   /tmp/vitis_proof
set XSA  $REPO/bitstreams/cgra_top.xsa
set APP  mnist_perstage
setws $WS
if {[catch {platform active cgra_top}]} {
    platform create -name cgra_top -hw $XSA -os standalone -proc ps7_cortexa9_0 -arch 32-bit
    platform write
}
platform generate
puts "platform ready"
catch {app remove -name $APP}
app create -name $APP -platform cgra_top -domain standalone_domain -template "Empty Application(C)"
set SRC $WS/$APP/src
file delete -force $SRC; file mkdir $SRC
foreach f {start.s demo_mnist_per_stage.c arm_fc_int_bm.c arm_cnn_int_bm.c demo_mnist_weights.S demo_mnist_conv_weights.S gic.c uart.h cgra.h cgra_kernels_cnn.h mnist_sweep_fixture.h arm_fc_bm.h arm_cnn_int_bm.h gic.h linker_cnn.ld} {
    if {[file exists $BM/$f]} { file copy -force $BM/$f $SRC/ } else { puts "MISSING $f" }
}
set CE $WS/$APP/cnn_eval
file delete -force $CE; file mkdir $CE
foreach f {mnist_weights_scale.h mnist_weights_spm.bin mnist_weights_conv.bin} {
    file copy -force $REPO/07_sw/cnn_eval/$f $CE/
}
app config -name $APP -set linker-script $SRC/linker_cnn.ld
app config -name $APP -add define-compiler-symbols BOARD_CGRA_ONLY
app config -name $APP -add define-compiler-symbols TWO_PASS_PMU=1
app config -name $APP -add compiler-misc {-mfpu=vfpv3 -mfloat-abi=hard -ffunction-sections -fdata-sections}
app config -name $APP -add assembler-flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I$SRC"
app config -name $APP -set build-config Debug
app build -name $APP
set ELF $WS/$APP/Debug/$APP.elf
puts "ELF_EXISTS=[file exists $ELF] SIZE=[expr {[file exists $ELF] ? [file size $ELF] : 0}]"
