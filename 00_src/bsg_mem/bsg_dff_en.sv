// ==============================================================================
// bsg_dff_en - D Flip-Flop with Clock Enable
// ==============================================================================
// Missing from BSG library subset. Required by bsg_dff_en_bypass.
// Implements standard DFF with enable: data_o updates only when en_i is high.
// ==============================================================================

`include "bsg_defines.sv"

module bsg_dff_en #(parameter `BSG_INV_PARAM(width_p)
                    , parameter harden_p = 0
                    , parameter strength_p = 1
                    )
   (input              clk_i
    , input            en_i
    , input  [width_p-1:0] data_i
    , output [width_p-1:0] data_o
    );

   reg [width_p-1:0] data_r;

   assign data_o = data_r;

   always @(posedge clk_i)
     if (en_i)
       data_r <= data_i;

endmodule

`BSG_ABSTRACT_MODULE(bsg_dff_en)
