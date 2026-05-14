// Single-bit bidirectional I2C IOBUF wrapper.
// Connects the 3 scalar pins from axi_iic_0 (sda_o/sda_t/sda_i, etc.) to a
// physical bidirectional pad. Used by fix_iic_hdmi.tcl as a Module Reference
// inside the merged Wildfire BD so the synthesized wrapper exposes inout
// I2C1_sda_io / I2C1_scl_io ports — matching the existing user XDC.
`timescale 1 ns / 1 ps
module iic_iobuf (
    input  wire dat_o,   // controller → pad (drive when t=0)
    input  wire dat_t,   // tristate enable (1 = high-Z)
    output wire dat_i,   // pad → controller (always reads pad)
    inout  wire io_pad   // bidirectional pad
);
    IOBUF iobuf_inst (
        .I  (dat_o),
        .T  (dat_t),
        .O  (dat_i),
        .IO (io_pad)
    );
endmodule
