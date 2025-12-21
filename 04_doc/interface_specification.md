# CGRA Architecture Interface Specification

## Address Map (Approved)

| Prefix | Range | Destination | Description |
|--------|-------|-------------|-------------|
| `0x0xxx_xxxx` | `addr[31:28]==0` | AXI Master | External DDR |
| `0x1xxx_xxxx` | `addr[31:28]==1` | Tile Memory | Internal data banks |
| `0x2xxx_xxxx` | `addr[31:28]==2` | Config Bus | PE instructions |

---

## Interface 1: cgra_tile_memory (Existing - No Changes Needed)

```systemverilog
module cgra_tile_memory #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 12,      // 4KB per bank
    parameter BANK_DEPTH = 1024,
    parameter NUM_BANKS  = 4
)(
    // DMA Write Port (Already exists!)
    input  [ADDR_WIDTH-1:0] ext_addr,
    input  [1:0]            ext_bank_sel,  // 0-3
    input                   ext_read,
    input                   ext_write,
    input  [DATA_WIDTH-1:0] ext_wdata,
    output [DATA_WIDTH-1:0] ext_rdata,
    output                  ext_valid,
    
    // Bank 0-3 Read Ports (for Array)
    input  [ADDR_WIDTH-1:0] bank0_addr, bank1_addr, bank2_addr, bank3_addr,
    input                   bank0_read, bank1_read, bank2_read, bank3_read,
    output [DATA_WIDTH-1:0] bank0_rdata, bank1_rdata, bank2_rdata, bank3_rdata,
    output                  bank0_valid, bank1_valid, bank2_valid, bank3_valid
);
```

**Decision:** Use existing interface. DMA writes via `ext_*` ports.

---

## Interface 2: cgra_config_mem_bsg (Existing - No Changes Needed)

```systemverilog
module cgra_config_mem_bsg #(
    parameter DATA_WIDTH = 64,
    parameter ADDR_WIDTH = 32,
    parameter DEPTH      = 1024
)(
    // Read Port (to PE)
    input  [ADDR_WIDTH-1:0] cfg_addr,
    input                   cfg_ren,
    output [DATA_WIDTH-1:0] cfg_rdata,
    output                  cfg_valid,
    
    // Write Port (from DMA/TB)
    input                   tb_we,
    input  [ADDR_WIDTH-1:0] tb_waddr,
    input  [DATA_WIDTH-1:0] tb_wdata
);
```

**Decision:** Use existing interface. Change from 64-bit to 32-bit for PE config.

---

## Interface 3: NEW Signals in cgra_dma_engine

### New Output Ports

```systemverilog
// Local Memory Access (to cgra_tile_memory)
output logic [11:0] tile_addr_o,
output logic [1:0]  tile_bank_sel_o,
output logic        tile_we_o,
output logic [31:0] tile_wdata_o,

// Config Memory Access (to PE config bus)
output logic [31:0] config_addr_o,
output logic        config_we_o,
output logic [31:0] config_wdata_o
```

### Address Decoding Logic

```systemverilog
// Destination decode
wire dst_is_axi    = (cfg_dst[31:28] == 4'h0);
wire dst_is_tile   = (cfg_dst[31:28] == 4'h1);
wire dst_is_config = (cfg_dst[31:28] == 4'h2);
```

---

## Interface 4: NEW Signals in cgra_control_unit

### New Output Ports

```systemverilog
output logic [PC_WIDTH-1:0] context_pc_o,  // PC_WIDTH = 4 for 16 slots
output logic                global_stall_o
```

### Parameters

```systemverilog
parameter CONTEXT_DEPTH = 16,
parameter PC_WIDTH      = $clog2(CONTEXT_DEPTH)
```

---

## Interface 5: NEW Signals in cgra_top

### Wires to Tile Memory

```systemverilog
// DMA → Tile Memory
logic [11:0] dma_tile_addr;
logic [1:0]  dma_tile_bank;
logic        dma_tile_we;
logic [31:0] dma_tile_wdata;

// Tile Memory → Array (row data)
logic [31:0] row_data [0:3];
logic        row_valid [0:3];
```

### Wires to Config Bus

```systemverilog
// DMA → Config Bus → PEs
logic [31:0] dma_cfg_addr;
logic        dma_cfg_we;
logic [31:0] dma_cfg_wdata;
```

### Wires from Control Unit

```systemverilog
logic [3:0]  context_pc;
logic        global_stall;
```

---

## Summary: Port Naming Convention

| Signal | Convention | Example |
|--------|------------|---------|
| DMA to Tile | `dma_tile_*` | `dma_tile_we` |
| DMA to Config | `dma_cfg_*` | `dma_cfg_we` |
| Row data out | `row_data[n]` | `row_data[0]` |
| Context PC | `context_pc` | 4-bit counter |
| Stall | `global_stall` | From CU |

---

## Approval Checklist

- [ ] Address map: `0x0/0x1/0x2` prefix scheme
- [ ] Tile memory: Use existing `ext_*` ports
- [ ] Config memory: Use existing `tb_*` ports for writes
- [ ] DMA outputs: `tile_*_o` and `config_*_o` naming
- [ ] Control unit: `context_pc_o` and `global_stall_o`
- [ ] Parameterized context depth (default 16)
