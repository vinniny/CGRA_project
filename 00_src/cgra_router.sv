// ==============================================================================
// CGRA Router for Mesh Network
// ==============================================================================
// Implements XY routing with unicast, multicast, and broadcast support
// Routes packets between N/E/S/W directions based on destination address

module cgra_router #(
    parameter DATA_WIDTH = 16,
    parameter ADDR_WIDTH = 4,
    parameter X_COORD = 0,
    parameter Y_COORD = 0
)(
    input  logic clk,
    input  logic rst_n,
    
    // North port
    input  logic [DATA_WIDTH-1:0] data_in_n,
    input  logic [ADDR_WIDTH-1:0] dest_x_n,
    input  logic [ADDR_WIDTH-1:0] dest_y_n,
    input  logic                  multicast_n,
    input  logic                  valid_in_n,
    output logic [DATA_WIDTH-1:0] data_out_n,
    output logic [ADDR_WIDTH-1:0] dest_x_out_n,
    output logic [ADDR_WIDTH-1:0] dest_y_out_n,
    output logic                  multicast_out_n,
    output logic                  valid_out_n,
    
    // East port
    input  logic [DATA_WIDTH-1:0] data_in_e,
    input  logic [ADDR_WIDTH-1:0] dest_x_e,
    input  logic [ADDR_WIDTH-1:0] dest_y_e,
    input  logic                  multicast_e,
    input  logic                  valid_in_e,
    output logic [DATA_WIDTH-1:0] data_out_e,
    output logic [ADDR_WIDTH-1:0] dest_x_out_e,
    output logic [ADDR_WIDTH-1:0] dest_y_out_e,
    output logic                  multicast_out_e,
    output logic                  valid_out_e,
    
    // South port
    input  logic [DATA_WIDTH-1:0] data_in_s,
    input  logic [ADDR_WIDTH-1:0] dest_x_s,
    input  logic [ADDR_WIDTH-1:0] dest_y_s,
    input  logic                  multicast_s,
    input  logic                  valid_in_s,
    output logic [DATA_WIDTH-1:0] data_out_s,
    output logic [ADDR_WIDTH-1:0] dest_x_out_s,
    output logic [ADDR_WIDTH-1:0] dest_y_out_s,
    output logic                  multicast_out_s,
    output logic                  valid_out_s,
    
    // West port
    input  logic [DATA_WIDTH-1:0] data_in_w,
    input  logic [ADDR_WIDTH-1:0] dest_x_w,
    input  logic [ADDR_WIDTH-1:0] dest_y_w,
    input  logic                  multicast_w,
    input  logic                  valid_in_w,
    output logic [DATA_WIDTH-1:0] data_out_w,
    output logic [ADDR_WIDTH-1:0] dest_x_out_w,
    output logic [ADDR_WIDTH-1:0] dest_y_out_w,
    output logic                  multicast_out_w,
    output logic                  valid_out_w,
    
    // Local port (to/from PE)
    input  logic [DATA_WIDTH-1:0] data_in_local,
    input  logic [ADDR_WIDTH-1:0] dest_x_local,
    input  logic [ADDR_WIDTH-1:0] dest_y_local,
    input  logic                  multicast_local,
    input  logic                  valid_in_local,
    output logic [DATA_WIDTH-1:0] data_out_local,
    output logic                  valid_out_local
);

    // =========================================================================
    // Input Buffers (1-Stage FIFO / Pipeline Registers)
    // =========================================================================
    logic [DATA_WIDTH-1:0] buf_data_n, buf_data_e, buf_data_s, buf_data_w, buf_data_l;
    logic [ADDR_WIDTH-1:0] buf_dx_n, buf_dx_e, buf_dx_s, buf_dx_w, buf_dx_l;
    logic [ADDR_WIDTH-1:0] buf_dy_n, buf_dy_e, buf_dy_s, buf_dy_w, buf_dy_l;
    logic                  buf_mc_n, buf_mc_e, buf_mc_s, buf_mc_w, buf_mc_l;
    logic                  buf_val_n, buf_val_e, buf_val_s, buf_val_w, buf_val_l;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            {buf_val_n, buf_val_e, buf_val_s, buf_val_w, buf_val_l} <= 5'b0;
            {buf_data_n, buf_data_e, buf_data_s, buf_data_w, buf_data_l} <= '0;
            {buf_dx_n, buf_dx_e, buf_dx_s, buf_dx_w, buf_dx_l} <= '0;
            {buf_dy_n, buf_dy_e, buf_dy_s, buf_dy_w, buf_dy_l} <= '0;
            {buf_mc_n, buf_mc_e, buf_mc_s, buf_mc_w, buf_mc_l} <= 5'b0;
        end else begin
            buf_val_n <= valid_in_n; buf_data_n <= data_in_n; buf_dx_n <= dest_x_n; buf_dy_n <= dest_y_n; buf_mc_n <= multicast_n;
            buf_val_e <= valid_in_e; buf_data_e <= data_in_e; buf_dx_e <= dest_x_e; buf_dy_e <= dest_y_e; buf_mc_e <= multicast_e;
            buf_val_s <= valid_in_s; buf_data_s <= data_in_s; buf_dx_s <= dest_x_s; buf_dy_s <= dest_y_s; buf_mc_s <= multicast_s;
            buf_val_w <= valid_in_w; buf_data_w <= data_in_w; buf_dx_w <= dest_x_w; buf_dy_w <= dest_y_w; buf_mc_w <= multicast_w;
            buf_val_l <= valid_in_local; buf_data_l <= data_in_local; buf_dx_l <= dest_x_local; buf_dy_l <= dest_y_local; buf_mc_l <= multicast_local;
        end
    end

    // =========================================================================
    // XY Routing Logic
    // =========================================================================
    // Route packets first in X direction, then Y direction
    // Multicast packets are forwarded to multiple outputs
    
    logic route_n_to_n, route_n_to_e, route_n_to_s, route_n_to_w, route_n_to_local;
    logic route_e_to_n, route_e_to_e, route_e_to_s, route_e_to_w, route_e_to_local;
    logic route_s_to_n, route_s_to_e, route_s_to_s, route_s_to_w, route_s_to_local;
    logic route_w_to_n, route_w_to_e, route_w_to_s, route_w_to_w, route_w_to_local;
    logic route_l_to_n, route_l_to_e, route_l_to_s, route_l_to_w, route_l_to_local;
    
    // =========================================================================
    // North input routing
    // =========================================================================
    always_comb begin
        route_n_to_n = 1'b0;
        route_n_to_e = 1'b0;
        route_n_to_s = 1'b0;
        route_n_to_w = 1'b0;
        route_n_to_local = 1'b0;
        
        if (buf_val_n) begin
            if (buf_mc_n) begin
                // Broadcast/multicast mode
                route_n_to_e = 1'b1;
                route_n_to_s = 1'b1;
                route_n_to_w = 1'b1;
                route_n_to_local = 1'b1;
            end else begin
                // Unicast XY routing
                if (buf_dx_n > X_COORD) begin
                    route_n_to_e = 1'b1;
                end else if (buf_dx_n < X_COORD) begin
                    route_n_to_w = 1'b1;
                end else if (buf_dy_n > Y_COORD) begin
                    route_n_to_s = 1'b1;
                end else if (buf_dy_n < Y_COORD) begin
                    route_n_to_n = 1'b1;
                end else begin
                    route_n_to_local = 1'b1;
                end
            end
        end
    end
    
    // =========================================================================
    // East input routing
    // =========================================================================
    always_comb begin
        route_e_to_n = 1'b0;
        route_e_to_e = 1'b0;
        route_e_to_s = 1'b0;
        route_e_to_w = 1'b0;
        route_e_to_local = 1'b0;
        
        if (buf_val_e) begin
            if (buf_mc_e) begin
                route_e_to_n = 1'b1;
                route_e_to_s = 1'b1;
                route_e_to_w = 1'b1;
                route_e_to_local = 1'b1;
            end else begin
                if (buf_dx_e > X_COORD) begin
                    route_e_to_e = 1'b1;
                end else if (buf_dx_e < X_COORD) begin
                    route_e_to_w = 1'b1;
                end else if (buf_dy_e > Y_COORD) begin
                    route_e_to_s = 1'b1;
                end else if (buf_dy_e < Y_COORD) begin
                    route_e_to_n = 1'b1;
                end else begin
                    route_e_to_local = 1'b1;
                end
            end
        end
    end
    
    // =========================================================================
    // South input routing
    // =========================================================================
    always_comb begin
        route_s_to_n = 1'b0;
        route_s_to_e = 1'b0;
        route_s_to_s = 1'b0;
        route_s_to_w = 1'b0;
        route_s_to_local = 1'b0;
        
        if (buf_val_s) begin
            if (buf_mc_s) begin
                route_s_to_n = 1'b1;
                route_s_to_e = 1'b1;
                route_s_to_w = 1'b1;
                route_s_to_local = 1'b1;
            end else begin
                if (buf_dx_s > X_COORD) begin
                    route_s_to_e = 1'b1;
                end else if (buf_dx_s < X_COORD) begin
                    route_s_to_w = 1'b1;
                end else if (buf_dy_s > Y_COORD) begin
                    route_s_to_s = 1'b1;
                end else if (buf_dy_s < Y_COORD) begin
                    route_s_to_n = 1'b1;
                end else begin
                    route_s_to_local = 1'b1;
                end
            end
        end
    end
    
    // =========================================================================
    // West input routing
    // =========================================================================
    always_comb begin
        route_w_to_n = 1'b0;
        route_w_to_e = 1'b0;
        route_w_to_s = 1'b0;
        route_w_to_w = 1'b0;
        route_w_to_local = 1'b0;
        
        if (buf_val_w) begin
            if (buf_mc_w) begin
                route_w_to_n = 1'b1;
                route_w_to_e = 1'b1;
                route_w_to_s = 1'b1;
                route_w_to_local = 1'b1;
            end else begin
                if (buf_dx_w > X_COORD) begin
                    route_w_to_e = 1'b1;
                end else if (buf_dx_w < X_COORD) begin
                    route_w_to_w = 1'b1;
                end else if (buf_dy_w > Y_COORD) begin
                    route_w_to_s = 1'b1;
                end else if (buf_dy_w < Y_COORD) begin
                    route_w_to_n = 1'b1;
                end else begin
                    route_w_to_local = 1'b1;
                end
            end
        end
    end
    
    // =========================================================================
    // Local input routing
    // =========================================================================
    always_comb begin
        route_l_to_n = 1'b0;
        route_l_to_e = 1'b0;
        route_l_to_s = 1'b0;
        route_l_to_w = 1'b0;
        route_l_to_local = 1'b0;
        
        if (buf_val_l) begin
            if (buf_mc_l) begin
                route_l_to_n = 1'b1;
                route_l_to_e = 1'b1;
                route_l_to_s = 1'b1;
                route_l_to_w = 1'b1;
            end else begin
                if (buf_dx_l > X_COORD) begin
                    route_l_to_e = 1'b1;
                end else if (buf_dx_l < X_COORD) begin
                    route_l_to_w = 1'b1;
                end else if (buf_dy_l > Y_COORD) begin
                    route_l_to_s = 1'b1;
                end else if (buf_dy_l < Y_COORD) begin
                    route_l_to_n = 1'b1;
                end else begin
                    route_l_to_local = 1'b1;
                end
            end
        end
    end
    
    // =========================================================================
    // Output Multiplexing with Arbitration (Priority: Local > N > E > S > W)
    // =========================================================================
    
    // North output
    always_comb begin
        if (route_l_to_n) begin
            data_out_n = buf_data_l;
            dest_x_out_n = buf_dx_l;
            dest_y_out_n = buf_dy_l;
            multicast_out_n = buf_mc_l;
            valid_out_n = buf_val_l;
        end else if (route_e_to_n) begin
            data_out_n = buf_data_e;
            dest_x_out_n = buf_dx_e;
            dest_y_out_n = buf_dy_e;
            multicast_out_n = buf_mc_e;
            valid_out_n = buf_val_e;
        end else if (route_s_to_n) begin
            data_out_n = buf_data_s;
            dest_x_out_n = buf_dx_s;
            dest_y_out_n = buf_dy_s;
            multicast_out_n = buf_mc_s;
            valid_out_n = buf_val_s;
        end else if (route_w_to_n) begin
            data_out_n = buf_data_w;
            dest_x_out_n = buf_dx_w;
            dest_y_out_n = buf_dy_w;
            multicast_out_n = buf_mc_w;
            valid_out_n = buf_val_w;
        end else begin
            data_out_n = '0;
            dest_x_out_n = '0;
            dest_y_out_n = '0;
            multicast_out_n = 1'b0;
            valid_out_n = 1'b0;
        end
    end
    
    // East output
    always_comb begin
        if (route_l_to_e) begin
            data_out_e = buf_data_l;
            dest_x_out_e = buf_dx_l;
            dest_y_out_e = buf_dy_l;
            multicast_out_e = buf_mc_l;
            valid_out_e = buf_val_l;
        end else if (route_n_to_e) begin
            data_out_e = buf_data_n;
            dest_x_out_e = buf_dx_n;
            dest_y_out_e = buf_dy_n;
            multicast_out_e = buf_mc_n;
            valid_out_e = buf_val_n;
        end else if (route_s_to_e) begin
            data_out_e = buf_data_s;
            dest_x_out_e = buf_dx_s;
            dest_y_out_e = buf_dy_s;
            multicast_out_e = buf_mc_s;
            valid_out_e = buf_val_s;
        end else if (route_w_to_e) begin
            data_out_e = buf_data_w;
            dest_x_out_e = buf_dx_w;
            dest_y_out_e = buf_dy_w;
            multicast_out_e = buf_mc_w;
            valid_out_e = buf_val_w;
        end else begin
            data_out_e = '0;
            dest_x_out_e = '0;
            dest_y_out_e = '0;
            multicast_out_e = 1'b0;
            valid_out_e = 1'b0;
        end
    end
    
    // South output
    always_comb begin
        if (route_l_to_s) begin
            data_out_s = buf_data_l;
            dest_x_out_s = buf_dx_l;
            dest_y_out_s = buf_dy_l;
            multicast_out_s = buf_mc_l;
            valid_out_s = buf_val_l;
        end else if (route_n_to_s) begin
            data_out_s = buf_data_n;
            dest_x_out_s = buf_dx_n;
            dest_y_out_s = buf_dy_n;
            multicast_out_s = buf_mc_n;
            valid_out_s = buf_val_n;
        end else if (route_e_to_s) begin
            data_out_s = buf_data_e;
            dest_x_out_s = buf_dx_e;
            dest_y_out_s = buf_dy_e;
            multicast_out_s = buf_mc_e;
            valid_out_s = buf_val_e;
        end else if (route_w_to_s) begin
            data_out_s = buf_data_w;
            dest_x_out_s = buf_dx_w;
            dest_y_out_s = buf_dy_w;
            multicast_out_s = buf_mc_w;
            valid_out_s = buf_val_w;
        end else begin
            data_out_s = '0;
            dest_x_out_s = '0;
            dest_y_out_s = '0;
            multicast_out_s = 1'b0;
            valid_out_s = 1'b0;
        end
    end
    
    // West output
    always_comb begin
        if (route_l_to_w) begin
            data_out_w = buf_data_l;
            dest_x_out_w = buf_dx_l;
            dest_y_out_w = buf_dy_l;
            multicast_out_w = buf_mc_l;
            valid_out_w = buf_val_l;
        end else if (route_n_to_w) begin
            data_out_w = buf_data_n;
            dest_x_out_w = buf_dx_n;
            dest_y_out_w = buf_dy_n;
            multicast_out_w = buf_mc_n;
            valid_out_w = buf_val_n;
        end else if (route_e_to_w) begin
            data_out_w = buf_data_e;
            dest_x_out_w = buf_dx_e;
            dest_y_out_w = buf_dy_e;
            multicast_out_w = buf_mc_e;
            valid_out_w = buf_val_e;
        end else if (route_s_to_w) begin
            data_out_w = buf_data_s;
            dest_x_out_w = buf_dx_s;
            dest_y_out_w = buf_dy_s;
            multicast_out_w = buf_mc_s;
            valid_out_w = buf_val_s;
        end else begin
            data_out_w = '0;
            dest_x_out_w = '0;
            dest_y_out_w = '0;
            multicast_out_w = 1'b0;
            valid_out_w = 1'b0;
        end
    end
    
    // Local output
    always_comb begin
        if (route_n_to_local) begin
            data_out_local = buf_data_n;
            valid_out_local = buf_val_n;
        end else if (route_e_to_local) begin
            data_out_local = buf_data_e;
            valid_out_local = buf_val_e;
        end else if (route_s_to_local) begin
            data_out_local = buf_data_s;
            valid_out_local = buf_val_s;
        end else if (route_w_to_local) begin
            data_out_local = buf_data_w;
            valid_out_local = buf_val_w;
        end else begin
            data_out_local = '0;
            valid_out_local = 1'b0;
        end
    end

endmodule
