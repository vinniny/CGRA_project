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
        
        if (valid_in_n) begin
            if (multicast_n) begin
                // Broadcast/multicast mode
                route_n_to_e = 1'b1;
                route_n_to_s = 1'b1;
                route_n_to_w = 1'b1;
                route_n_to_local = 1'b1;
            end else begin
                // Unicast XY routing
                if (dest_x_n > X_COORD) begin
                    route_n_to_e = 1'b1;
                end else if (dest_x_n < X_COORD) begin
                    route_n_to_w = 1'b1;
                end else if (dest_y_n > Y_COORD) begin
                    route_n_to_s = 1'b1;
                end else if (dest_y_n < Y_COORD) begin
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
        
        if (valid_in_e) begin
            if (multicast_e) begin
                route_e_to_n = 1'b1;
                route_e_to_s = 1'b1;
                route_e_to_w = 1'b1;
                route_e_to_local = 1'b1;
            end else begin
                if (dest_x_e > X_COORD) begin
                    route_e_to_e = 1'b1;
                end else if (dest_x_e < X_COORD) begin
                    route_e_to_w = 1'b1;
                end else if (dest_y_e > Y_COORD) begin
                    route_e_to_s = 1'b1;
                end else if (dest_y_e < Y_COORD) begin
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
        
        if (valid_in_s) begin
            if (multicast_s) begin
                route_s_to_n = 1'b1;
                route_s_to_e = 1'b1;
                route_s_to_w = 1'b1;
                route_s_to_local = 1'b1;
            end else begin
                if (dest_x_s > X_COORD) begin
                    route_s_to_e = 1'b1;
                end else if (dest_x_s < X_COORD) begin
                    route_s_to_w = 1'b1;
                end else if (dest_y_s > Y_COORD) begin
                    route_s_to_s = 1'b1;
                end else if (dest_y_s < Y_COORD) begin
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
        
        if (valid_in_w) begin
            if (multicast_w) begin
                route_w_to_n = 1'b1;
                route_w_to_e = 1'b1;
                route_w_to_s = 1'b1;
                route_w_to_local = 1'b1;
            end else begin
                if (dest_x_w > X_COORD) begin
                    route_w_to_e = 1'b1;
                end else if (dest_x_w < X_COORD) begin
                    route_w_to_w = 1'b1;
                end else if (dest_y_w > Y_COORD) begin
                    route_w_to_s = 1'b1;
                end else if (dest_y_w < Y_COORD) begin
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
        
        if (valid_in_local) begin
            if (multicast_local) begin
                route_l_to_n = 1'b1;
                route_l_to_e = 1'b1;
                route_l_to_s = 1'b1;
                route_l_to_w = 1'b1;
            end else begin
                if (dest_x_local > X_COORD) begin
                    route_l_to_e = 1'b1;
                end else if (dest_x_local < X_COORD) begin
                    route_l_to_w = 1'b1;
                end else if (dest_y_local > Y_COORD) begin
                    route_l_to_s = 1'b1;
                end else if (dest_y_local < Y_COORD) begin
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
            data_out_n = data_in_local;
            dest_x_out_n = dest_x_local;
            dest_y_out_n = dest_y_local;
            multicast_out_n = multicast_local;
            valid_out_n = valid_in_local;
        end else if (route_e_to_n) begin
            data_out_n = data_in_e;
            dest_x_out_n = dest_x_e;
            dest_y_out_n = dest_y_e;
            multicast_out_n = multicast_e;
            valid_out_n = valid_in_e;
        end else if (route_s_to_n) begin
            data_out_n = data_in_s;
            dest_x_out_n = dest_x_s;
            dest_y_out_n = dest_y_s;
            multicast_out_n = multicast_s;
            valid_out_n = valid_in_s;
        end else if (route_w_to_n) begin
            data_out_n = data_in_w;
            dest_x_out_n = dest_x_w;
            dest_y_out_n = dest_y_w;
            multicast_out_n = multicast_w;
            valid_out_n = valid_in_w;
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
            data_out_e = data_in_local;
            dest_x_out_e = dest_x_local;
            dest_y_out_e = dest_y_local;
            multicast_out_e = multicast_local;
            valid_out_e = valid_in_local;
        end else if (route_n_to_e) begin
            data_out_e = data_in_n;
            dest_x_out_e = dest_x_n;
            dest_y_out_e = dest_y_n;
            multicast_out_e = multicast_n;
            valid_out_e = valid_in_n;
        end else if (route_s_to_e) begin
            data_out_e = data_in_s;
            dest_x_out_e = dest_x_s;
            dest_y_out_e = dest_y_s;
            multicast_out_e = multicast_s;
            valid_out_e = valid_in_s;
        end else if (route_w_to_e) begin
            data_out_e = data_in_w;
            dest_x_out_e = dest_x_w;
            dest_y_out_e = dest_y_w;
            multicast_out_e = multicast_w;
            valid_out_e = valid_in_w;
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
            data_out_s = data_in_local;
            dest_x_out_s = dest_x_local;
            dest_y_out_s = dest_y_local;
            multicast_out_s = multicast_local;
            valid_out_s = valid_in_local;
        end else if (route_n_to_s) begin
            data_out_s = data_in_n;
            dest_x_out_s = dest_x_n;
            dest_y_out_s = dest_y_n;
            multicast_out_s = multicast_n;
            valid_out_s = valid_in_n;
        end else if (route_e_to_s) begin
            data_out_s = data_in_e;
            dest_x_out_s = dest_x_e;
            dest_y_out_s = dest_y_e;
            multicast_out_s = multicast_e;
            valid_out_s = valid_in_e;
        end else if (route_w_to_s) begin
            data_out_s = data_in_w;
            dest_x_out_s = dest_x_w;
            dest_y_out_s = dest_y_w;
            multicast_out_s = multicast_w;
            valid_out_s = valid_in_w;
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
            data_out_w = data_in_local;
            dest_x_out_w = dest_x_local;
            dest_y_out_w = dest_y_local;
            multicast_out_w = multicast_local;
            valid_out_w = valid_in_local;
        end else if (route_n_to_w) begin
            data_out_w = data_in_n;
            dest_x_out_w = dest_x_n;
            dest_y_out_w = dest_y_n;
            multicast_out_w = multicast_n;
            valid_out_w = valid_in_n;
        end else if (route_e_to_w) begin
            data_out_w = data_in_e;
            dest_x_out_w = dest_x_e;
            dest_y_out_w = dest_y_e;
            multicast_out_w = multicast_e;
            valid_out_w = valid_in_e;
        end else if (route_s_to_w) begin
            data_out_w = data_in_s;
            dest_x_out_w = dest_x_s;
            dest_y_out_w = dest_y_s;
            multicast_out_w = multicast_s;
            valid_out_w = valid_in_s;
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
            data_out_local = data_in_n;
            valid_out_local = valid_in_n;
        end else if (route_e_to_local) begin
            data_out_local = data_in_e;
            valid_out_local = valid_in_e;
        end else if (route_s_to_local) begin
            data_out_local = data_in_s;
            valid_out_local = valid_in_s;
        end else if (route_w_to_local) begin
            data_out_local = data_in_w;
            valid_out_local = valid_in_w;
        end else begin
            data_out_local = '0;
            valid_out_local = 1'b0;
        end
    end

endmodule
