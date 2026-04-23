// cgra_dma_subsystem.sv — wraps DMA engine + SG chain controller and
// presents a single clean boundary to the rest of the system:
//   - one command interface (cfg_* + cfg_chain_*),
//   - one status_busy that covers engine + chain,
//   - one AXI4 master port.
//
// The AXI AR/R channel is shared between the engine (data transfers) and
// the chain controller (descriptor fetches) through a combinational mux
// gated by fetch_active. Arbitration is sequential-by-construction: the
// chain ctrl only asserts its AR from C_FETCH, entered from C_IDLE where
// the engine owns nothing on AR/R.

module cgra_dma_subsystem #(
    parameter DATA_WIDTH   = 32,
    parameter ADDR_WIDTH   = 32,
    parameter AXI_ID_WIDTH = 4,
    parameter FIFO_DEPTH   = 32
)(
    input  logic                    clk,
    input  logic                    rst_n,

    // Command from CSR
    input  logic [31:0]             cfg_src,
    input  logic [31:0]             cfg_dst,
    input  logic [31:0]             cfg_size,
    input  logic [31:0]             cfg_src_stride,
    input  logic [31:0]             cfg_rows,
    input  logic [31:0]             cfg_cols,
    input  logic                    cfg_start,
    input  logic                    cfg_abort,
    input  logic [31:0]             cfg_desc_head,
    input  logic                    cfg_chain_start,

    // Status to CSR
    output logic                    status_busy,
    output logic                    status_done,
    output logic                    chain_active,
    output logic [15:0]             desc_completed,
    output logic [1:0]              error_code,
    output logic                    error_valid,

    // AXI4 master (single port, internally muxed AR)
    output logic [AXI_ID_WIDTH-1:0] m_axi_awid,
    output logic [ADDR_WIDTH-1:0]   m_axi_awaddr,
    output logic [7:0]              m_axi_awlen,
    output logic [2:0]              m_axi_awsize,
    output logic [1:0]              m_axi_awburst,
    output logic                    m_axi_awvalid,
    input  logic                    m_axi_awready,
    output logic [DATA_WIDTH-1:0]   m_axi_wdata,
    output logic [DATA_WIDTH/8-1:0] m_axi_wstrb,
    output logic                    m_axi_wlast,
    output logic                    m_axi_wvalid,
    input  logic                    m_axi_wready,
    input  logic [AXI_ID_WIDTH-1:0] m_axi_bid,
    input  logic                    m_axi_bvalid,
    input  logic [1:0]              m_axi_bresp,
    output logic                    m_axi_bready,
    output logic [AXI_ID_WIDTH-1:0] m_axi_arid,
    output logic [ADDR_WIDTH-1:0]   m_axi_araddr,
    output logic [7:0]              m_axi_arlen,
    output logic [2:0]              m_axi_arsize,
    output logic [1:0]              m_axi_arburst,
    output logic                    m_axi_arvalid,
    input  logic                    m_axi_arready,
    input  logic [AXI_ID_WIDTH-1:0] m_axi_rid,
    input  logic [DATA_WIDTH-1:0]   m_axi_rdata,
    input  logic                    m_axi_rlast,
    input  logic                    m_axi_rvalid,
    input  logic [1:0]              m_axi_rresp,
    output logic                    m_axi_rready,

    // Tile memory
    output logic [11:0]             tile_addr_o,
    output logic [1:0]              tile_bank_sel_o,
    output logic                    tile_we_o,
    output logic [31:0]             tile_wdata_o,
    output logic                    tile_re_o,
    input  logic [DATA_WIDTH-1:0]   tile_rdata_i,
    input  logic                    tile_rvalid_i,

    // PE config
    output logic [31:0]             config_addr_o,
    output logic                    config_we_o,
    output logic [31:0]             config_wdata_o,

    // SPM write (DMA→SPM path)
    output logic [31:0]             spm_write_addr_o,
    output logic [31:0]             spm_write_data_o,
    output logic                    spm_write_en_o,

    // ILA debug
    output logic                    dbg_status_busy,
    output logic [2:0]              dbg_read_fsm_state,
    output logic [2:0]              dbg_write_fsm_state,
    output logic                    dbg_fifo_full,
    output logic                    dbg_fifo_empty,
    output logic [31:0]             dbg_write_words_remaining
);

    // Chain controller <-> engine command
    logic [31:0] chain_cmd_src, chain_cmd_dst, chain_cmd_size;
    logic        chain_cmd_start;
    logic        chain_fetch_active;

    // Chain controller AXI AR/R (driven; muxed below)
    logic [31:0] chain_araddr;
    logic [7:0]  chain_arlen;
    logic [2:0]  chain_arsize;
    logic [1:0]  chain_arburst;
    logic        chain_arvalid;
    logic        chain_rready;

    // Engine AXI AR/R (driven; muxed below)
    logic [AXI_ID_WIDTH-1:0] eng_arid;
    logic [31:0]             eng_araddr;
    logic [7:0]              eng_arlen;
    logic [2:0]              eng_arsize;
    logic [1:0]              eng_arburst;
    logic                    eng_arvalid;
    logic                    eng_rready;

    // Engine-side status
    logic        engine_busy;
    logic        engine_done;

    // Muxed command to engine (chain owns while chain_active)
    logic [31:0] eng_cfg_src, eng_cfg_dst, eng_cfg_size;
    logic        eng_cfg_start;
    assign eng_cfg_src   = chain_active ? chain_cmd_src   : cfg_src;
    assign eng_cfg_dst   = chain_active ? chain_cmd_dst   : cfg_dst;
    assign eng_cfg_size  = chain_active ? chain_cmd_size  : cfg_size;
    assign eng_cfg_start = chain_active ? chain_cmd_start : cfg_start;

    // AR/R channel mux (combinational; fetch_active is from a registered FSM).
    logic ar_sel_chain;
    assign ar_sel_chain = chain_fetch_active;

    assign m_axi_arid    = ar_sel_chain ? {AXI_ID_WIDTH{1'b0}} : eng_arid;
    assign m_axi_araddr  = ar_sel_chain ? chain_araddr   : eng_araddr;
    assign m_axi_arlen   = ar_sel_chain ? chain_arlen    : eng_arlen;
    assign m_axi_arsize  = ar_sel_chain ? chain_arsize   : eng_arsize;
    assign m_axi_arburst = ar_sel_chain ? chain_arburst  : eng_arburst;
    assign m_axi_arvalid = ar_sel_chain ? chain_arvalid  : eng_arvalid;
    assign m_axi_rready  = ar_sel_chain ? chain_rready   : eng_rready;

    // Combined status
    assign status_busy = engine_busy || chain_active;

    cgra_dma_engine #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .AXI_ID_WIDTH(AXI_ID_WIDTH),
        .FIFO_DEPTH(FIFO_DEPTH)
    ) u_engine (
        .clk(clk),
        .rst_n(rst_n),

        .cfg_src(eng_cfg_src),
        .cfg_dst(eng_cfg_dst),
        .cfg_size(eng_cfg_size),
        .cfg_src_stride(cfg_src_stride),
        .cfg_rows(cfg_rows),
        .cfg_cols(cfg_cols),
        .cfg_start(eng_cfg_start),
        .cfg_abort(cfg_abort),
        .status_busy(engine_busy),
        .status_done(engine_done),

        .m_axi_awid(m_axi_awid),
        .m_axi_awaddr(m_axi_awaddr),
        .m_axi_awlen(m_axi_awlen),
        .m_axi_awsize(m_axi_awsize),
        .m_axi_awburst(m_axi_awburst),
        .m_axi_awvalid(m_axi_awvalid),
        .m_axi_awready(m_axi_awready),
        .m_axi_wdata(m_axi_wdata),
        .m_axi_wstrb(m_axi_wstrb),
        .m_axi_wlast(m_axi_wlast),
        .m_axi_wvalid(m_axi_wvalid),
        .m_axi_wready(m_axi_wready),
        .m_axi_bid(m_axi_bid),
        .m_axi_bresp(m_axi_bresp),
        .m_axi_bvalid(m_axi_bvalid),
        .m_axi_bready(m_axi_bready),

        .m_axi_arid(eng_arid),
        .m_axi_araddr(eng_araddr),
        .m_axi_arlen(eng_arlen),
        .m_axi_arsize(eng_arsize),
        .m_axi_arburst(eng_arburst),
        .m_axi_arvalid(eng_arvalid),
        .m_axi_arready(m_axi_arready && !ar_sel_chain),
        .m_axi_rdata(m_axi_rdata),
        .m_axi_rlast(m_axi_rlast),
        .m_axi_rvalid(m_axi_rvalid && !ar_sel_chain),
        .m_axi_rid(m_axi_rid),
        .m_axi_rresp(m_axi_rresp),
        .m_axi_rready(eng_rready),

        .error_code(error_code),
        .error_valid(error_valid),

        .tile_addr_o(tile_addr_o),
        .tile_bank_sel_o(tile_bank_sel_o),
        .tile_we_o(tile_we_o),
        .tile_wdata_o(tile_wdata_o),
        .tile_re_o(tile_re_o),
        .tile_rdata_i(tile_rdata_i),
        .tile_rvalid_i(tile_rvalid_i),

        .config_addr_o(config_addr_o),
        .config_we_o(config_we_o),
        .config_wdata_o(config_wdata_o),

        .spm_write_addr_o(spm_write_addr_o),
        .spm_write_data_o(spm_write_data_o),
        .spm_write_en_o(spm_write_en_o),

        .dbg_status_busy(dbg_status_busy),
        .dbg_read_fsm_state(dbg_read_fsm_state),
        .dbg_write_fsm_state(dbg_write_fsm_state),
        .dbg_fifo_full(dbg_fifo_full),
        .dbg_fifo_empty(dbg_fifo_empty),
        .dbg_write_words_remaining(dbg_write_words_remaining)
    );

    assign status_done = engine_done;

    cgra_dma_chain_ctrl #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .DATA_WIDTH(DATA_WIDTH)
    ) u_chain (
        .clk(clk),
        .rst_n(rst_n),

        .desc_head_i(cfg_desc_head),
        .chain_start_i(cfg_chain_start),
        .abort_i(cfg_abort),
        .chain_active_o(chain_active),
        .desc_completed_o(desc_completed),

        .cmd_src_o(chain_cmd_src),
        .cmd_dst_o(chain_cmd_dst),
        .cmd_size_o(chain_cmd_size),
        .cmd_start_o(chain_cmd_start),
        .cmd_done_i(engine_done),
        .cmd_busy_i(engine_busy),

        .m_axi_araddr(chain_araddr),
        .m_axi_arlen(chain_arlen),
        .m_axi_arsize(chain_arsize),
        .m_axi_arburst(chain_arburst),
        .m_axi_arvalid(chain_arvalid),
        .m_axi_arready(m_axi_arready && ar_sel_chain),
        .m_axi_rdata(m_axi_rdata),
        .m_axi_rresp(m_axi_rresp),
        .m_axi_rvalid(m_axi_rvalid && ar_sel_chain),
        .m_axi_rlast(m_axi_rlast),
        .m_axi_rready(chain_rready),

        .fetch_active_o(chain_fetch_active)
    );

endmodule
