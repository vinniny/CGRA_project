// ==============================================================================
// CGRA ROUTER (FIXED FLOW CONTROL)
// ==============================================================================
// 1. Explicit Handshake Logic to prevent "Stuck Valid" / Looping
// 2. Correct parameter propagation for X/Y Coordinates
// ==============================================================================

module cgra_router #(
    parameter DATA_WIDTH = 32,
    parameter COORD_WIDTH = 4,
    parameter PAYLOAD_WIDTH = 16,
    parameter X_COORD = 0,
    parameter Y_COORD = 0
)(
    input  logic clk,
    input  logic rst_n,

    // North Port
    input  logic [DATA_WIDTH-1:0] data_in_n,
    input  logic                  valid_in_n,
    output logic                  ready_out_n,
    output logic [DATA_WIDTH-1:0] data_out_n,
    output logic                  valid_out_n,
    input  logic                  ready_in_n,

    // East Port
    input  logic [DATA_WIDTH-1:0] data_in_e,
    input  logic                  valid_in_e,
    output logic                  ready_out_e,
    output logic [DATA_WIDTH-1:0] data_out_e,
    output logic                  valid_out_e,
    input  logic                  ready_in_e,

    // South Port
    input  logic [DATA_WIDTH-1:0] data_in_s,
    input  logic                  valid_in_s,
    output logic                  ready_out_s,
    output logic [DATA_WIDTH-1:0] data_out_s,
    output logic                  valid_out_s,
    input  logic                  ready_in_s,

    // West Port
    input  logic [DATA_WIDTH-1:0] data_in_w,
    input  logic                  valid_in_w,
    output logic                  ready_out_w,
    output logic [DATA_WIDTH-1:0] data_out_w,
    output logic                  valid_out_w,
    input  logic                  ready_in_w,

    // Local Port
    input  logic [DATA_WIDTH-1:0] data_in_local,
    input  logic                  valid_in_local,
    output logic                  ready_out_local,
    output logic [DATA_WIDTH-1:0] data_out_local,
    output logic                  valid_out_local,
    input  logic                  ready_in_local
);

    // Internal Buffers
    logic [DATA_WIDTH-1:0] b_data_n, b_data_e, b_data_s, b_data_w, b_data_l;
    logic                  b_val_n,  b_val_e,  b_val_s,  b_val_w,  b_val_l;
    
    // Stall Signals (Computed later)
    logic stall_n, stall_e, stall_s, stall_w, stall_l;

    // =========================================================================
    // 1. INPUT BUFFER MANAGEMENT (Skid Buffers)
    // =========================================================================
    // A buffer accepts data if it is EMPTY or if it is currently STALLING=0 (moving data).
    
    // North Buffer
    assign ready_out_n = !b_val_n || !stall_n;
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            b_val_n <= 1'b0;
            b_data_n <= '0;
        end else begin
            if (ready_out_n) begin
                // Ready to accept: Load new data if valid, or clear valid if not
                b_val_n <= valid_in_n;
                if (valid_in_n) b_data_n <= data_in_n;
            end
        end
    end

    // East Buffer
    assign ready_out_e = !b_val_e || !stall_e;
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            b_val_e <= 1'b0;
            b_data_e <= '0;
        end else begin
            if (ready_out_e) begin
                b_val_e <= valid_in_e;
                if (valid_in_e) b_data_e <= data_in_e;
            end
        end
    end

    // South Buffer
    assign ready_out_s = !b_val_s || !stall_s;
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            b_val_s <= 1'b0;
            b_data_s <= '0;
        end else begin
            if (ready_out_s) begin
                b_val_s <= valid_in_s;
                if (valid_in_s) b_data_s <= data_in_s;
            end
        end
    end

    // West Buffer
    assign ready_out_w = !b_val_w || !stall_w;
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            b_val_w <= 1'b0;
            b_data_w <= '0;
        end else begin
            if (ready_out_w) begin
                b_val_w <= valid_in_w;
                if (valid_in_w) b_data_w <= data_in_w;
            end
        end
    end

    // Local Buffer
    assign ready_out_local = !b_val_l || !stall_l;
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            b_val_l <= 1'b0;
            b_data_l <= '0;
        end else begin
            if (ready_out_local) begin
                b_val_l <= valid_in_local;
                if (valid_in_local) b_data_l <= data_in_local;
            end
        end
    end

    // =========================================================================
    // 2. ROUTING LOGIC (In-Band Header Extraction)
    // =========================================================================
    // Format: [31:28 DX][27:24 DY][23:16 RSVD][15:0 PAYLOAD]
    
    logic [COORD_WIDTH-1:0] dx_n, dy_n;
    logic [COORD_WIDTH-1:0] dx_e, dy_e;
    logic [COORD_WIDTH-1:0] dx_s, dy_s;
    logic [COORD_WIDTH-1:0] dx_w, dy_w;
    logic [COORD_WIDTH-1:0] dx_l, dy_l;

    // Header Extraction
    assign dx_n = b_data_n[31:28];
    assign dy_n = b_data_n[27:24];
    assign dx_e = b_data_e[31:28];
    assign dy_e = b_data_e[27:24];
    assign dx_s = b_data_s[31:28];
    assign dy_s = b_data_s[27:24];
    assign dx_w = b_data_w[31:28];
    assign dy_w = b_data_w[27:24];
    assign dx_l = b_data_l[31:28];
    assign dy_l = b_data_l[27:24];

    // Request Vector Generation
    // req_from_X[4:0] -> {Local, West, South, East, North}
    logic [4:0] req_n, req_e, req_s, req_w, req_l;

    // Routing logic: XY routing - X first, then Y
    always_comb begin
        req_n = 5'b0;
        if (b_val_n) begin
            if      (dx_n > X_COORD) req_n[1] = 1; // East
            else if (dx_n < X_COORD) req_n[3] = 1; // West
            else if (dy_n > Y_COORD) req_n[2] = 1; // South
            else if (dy_n < Y_COORD) req_n[0] = 1; // North
            else                     req_n[4] = 1; // Local (arrived)
        end
    end

    always_comb begin
        req_e = 5'b0;
        if (b_val_e) begin
            if      (dx_e > X_COORD) req_e[1] = 1;
            else if (dx_e < X_COORD) req_e[3] = 1;
            else if (dy_e > Y_COORD) req_e[2] = 1;
            else if (dy_e < Y_COORD) req_e[0] = 1;
            else                     req_e[4] = 1;
        end
    end

    always_comb begin
        req_s = 5'b0;
        if (b_val_s) begin
            if      (dx_s > X_COORD) req_s[1] = 1;
            else if (dx_s < X_COORD) req_s[3] = 1;
            else if (dy_s > Y_COORD) req_s[2] = 1;
            else if (dy_s < Y_COORD) req_s[0] = 1;
            else                     req_s[4] = 1;
        end
    end

    always_comb begin
        req_w = 5'b0;
        if (b_val_w) begin
            if      (dx_w > X_COORD) req_w[1] = 1;
            else if (dx_w < X_COORD) req_w[3] = 1;
            else if (dy_w > Y_COORD) req_w[2] = 1;
            else if (dy_w < Y_COORD) req_w[0] = 1;
            else                     req_w[4] = 1;
        end
    end

    always_comb begin
        req_l = 5'b0;
        if (b_val_l) begin
            if      (dx_l > X_COORD) req_l[1] = 1;
            else if (dx_l < X_COORD) req_l[3] = 1;
            else if (dy_l > Y_COORD) req_l[2] = 1;
            else if (dy_l < Y_COORD) req_l[0] = 1;
            else                     req_l[4] = 1;
        end
    end

    // =========================================================================
    // 3. ARBITRATION (Fixed Priority)
    // =========================================================================
    // Transpose Requests: "Who wants Output N?"
    logic [4:0] wants_n, wants_e, wants_s, wants_w, wants_l;
    // Order in vector: {L, W, S, E, N}
    assign wants_n = {req_l[0], req_w[0], req_s[0], req_e[0], req_n[0]};
    assign wants_e = {req_l[1], req_w[1], req_s[1], req_e[1], req_n[1]};
    assign wants_s = {req_l[2], req_w[2], req_s[2], req_e[2], req_n[2]};
    assign wants_w = {req_l[3], req_w[3], req_s[3], req_e[3], req_n[3]};
    assign wants_l = {req_l[4], req_w[4], req_s[4], req_e[4], req_n[4]};

    // Grants: One-Hot vectors indicating who won
    logic [4:0] grant_n, grant_e, grant_s, grant_w, grant_l;

    // Simple Fixed Priority Arbiter (L > W > S > E > N)
    always_comb begin
        if      (wants_n[4]) grant_n = 5'b10000;
        else if (wants_n[3]) grant_n = 5'b01000;
        else if (wants_n[2]) grant_n = 5'b00100;
        else if (wants_n[1]) grant_n = 5'b00010;
        else if (wants_n[0]) grant_n = 5'b00001;
        else                 grant_n = 5'b00000;
    end

    always_comb begin
        if      (wants_e[4]) grant_e = 5'b10000;
        else if (wants_e[3]) grant_e = 5'b01000;
        else if (wants_e[2]) grant_e = 5'b00100;
        else if (wants_e[1]) grant_e = 5'b00010;
        else if (wants_e[0]) grant_e = 5'b00001;
        else                 grant_e = 5'b00000;
    end

    always_comb begin
        if      (wants_s[4]) grant_s = 5'b10000;
        else if (wants_s[3]) grant_s = 5'b01000;
        else if (wants_s[2]) grant_s = 5'b00100;
        else if (wants_s[1]) grant_s = 5'b00010;
        else if (wants_s[0]) grant_s = 5'b00001;
        else                 grant_s = 5'b00000;
    end

    always_comb begin
        if      (wants_w[4]) grant_w = 5'b10000;
        else if (wants_w[3]) grant_w = 5'b01000;
        else if (wants_w[2]) grant_w = 5'b00100;
        else if (wants_w[1]) grant_w = 5'b00010;
        else if (wants_w[0]) grant_w = 5'b00001;
        else                 grant_w = 5'b00000;
    end

    always_comb begin
        if      (wants_l[4]) grant_l = 5'b10000;
        else if (wants_l[3]) grant_l = 5'b01000;
        else if (wants_l[2]) grant_l = 5'b00100;
        else if (wants_l[1]) grant_l = 5'b00010;
        else if (wants_l[0]) grant_l = 5'b00001;
        else                 grant_l = 5'b00000;
    end

    // =========================================================================
    // 4. CROSSBAR (Data Muxing)
    // =========================================================================
    always_comb begin
        unique case (grant_n)
            5'b10000: data_out_n = b_data_l;
            5'b01000: data_out_n = b_data_w;
            5'b00100: data_out_n = b_data_s;
            5'b00010: data_out_n = b_data_e;
            5'b00001: data_out_n = b_data_n;
            default:  data_out_n = '0;
        endcase
    end
    assign valid_out_n = |grant_n;

    always_comb begin
        unique case (grant_e)
            5'b10000: data_out_e = b_data_l;
            5'b01000: data_out_e = b_data_w;
            5'b00100: data_out_e = b_data_s;
            5'b00010: data_out_e = b_data_e;
            5'b00001: data_out_e = b_data_n;
            default:  data_out_e = '0;
        endcase
    end
    assign valid_out_e = |grant_e;

    always_comb begin
        unique case (grant_s)
            5'b10000: data_out_s = b_data_l;
            5'b01000: data_out_s = b_data_w;
            5'b00100: data_out_s = b_data_s;
            5'b00010: data_out_s = b_data_e;
            5'b00001: data_out_s = b_data_n;
            default:  data_out_s = '0;
        endcase
    end
    assign valid_out_s = |grant_s;

    always_comb begin
        unique case (grant_w)
            5'b10000: data_out_w = b_data_l;
            5'b01000: data_out_w = b_data_w;
            5'b00100: data_out_w = b_data_s;
            5'b00010: data_out_w = b_data_e;
            5'b00001: data_out_w = b_data_n;
            default:  data_out_w = '0;
        endcase
    end
    assign valid_out_w = |grant_w;

    always_comb begin
        unique case (grant_l)
            5'b10000: data_out_local = b_data_l;
            5'b01000: data_out_local = b_data_w;
            5'b00100: data_out_local = b_data_s;
            5'b00010: data_out_local = b_data_e;
            5'b00001: data_out_local = b_data_n;
            default:  data_out_local = '0;
        endcase
    end
    assign valid_out_local = |grant_l;

    // =========================================================================
    // 5. STALL LOGIC (Backpressure Upstream)
    // =========================================================================
    // A buffer is stalled if it wants an output, is granted that output, 
    // but the output's downstream neighbor is NOT ready.
    // OR if it wants an output but is NOT granted (Arbitration loss).
    
    always_comb begin
        // North Buffer Stall Check
        stall_n = 0;
        if (b_val_n) begin
            if (req_n[0] && (!grant_n[0] || !ready_in_n)) stall_n = 1;
            if (req_n[1] && (!grant_e[0] || !ready_in_e)) stall_n = 1;
            if (req_n[2] && (!grant_s[0] || !ready_in_s)) stall_n = 1;
            if (req_n[3] && (!grant_w[0] || !ready_in_w)) stall_n = 1;
            if (req_n[4] && (!grant_l[0] || !ready_in_local)) stall_n = 1;
        end

        // East Buffer Stall Check
        stall_e = 0;
        if (b_val_e) begin
            if (req_e[0] && (!grant_n[1] || !ready_in_n)) stall_e = 1;
            if (req_e[1] && (!grant_e[1] || !ready_in_e)) stall_e = 1;
            if (req_e[2] && (!grant_s[1] || !ready_in_s)) stall_e = 1;
            if (req_e[3] && (!grant_w[1] || !ready_in_w)) stall_e = 1;
            if (req_e[4] && (!grant_l[1] || !ready_in_local)) stall_e = 1;
        end

        // South Buffer Stall Check
        stall_s = 0;
        if (b_val_s) begin
            if (req_s[0] && (!grant_n[2] || !ready_in_n)) stall_s = 1;
            if (req_s[1] && (!grant_e[2] || !ready_in_e)) stall_s = 1;
            if (req_s[2] && (!grant_s[2] || !ready_in_s)) stall_s = 1;
            if (req_s[3] && (!grant_w[2] || !ready_in_w)) stall_s = 1;
            if (req_s[4] && (!grant_l[2] || !ready_in_local)) stall_s = 1;
        end

        // West Buffer Stall Check
        stall_w = 0;
        if (b_val_w) begin
            if (req_w[0] && (!grant_n[3] || !ready_in_n)) stall_w = 1;
            if (req_w[1] && (!grant_e[3] || !ready_in_e)) stall_w = 1;
            if (req_w[2] && (!grant_s[3] || !ready_in_s)) stall_w = 1;
            if (req_w[3] && (!grant_w[3] || !ready_in_w)) stall_w = 1;
            if (req_w[4] && (!grant_l[3] || !ready_in_local)) stall_w = 1;
        end

        // Local Buffer Stall Check
        stall_l = 0;
        if (b_val_l) begin
            if (req_l[0] && (!grant_n[4] || !ready_in_n)) stall_l = 1;
            if (req_l[1] && (!grant_e[4] || !ready_in_e)) stall_l = 1;
            if (req_l[2] && (!grant_s[4] || !ready_in_s)) stall_l = 1;
            if (req_l[3] && (!grant_w[4] || !ready_in_w)) stall_l = 1;
            if (req_l[4] && (!grant_l[4] || !ready_in_local)) stall_l = 1;
        end
    end

endmodule
