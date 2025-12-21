# RTL Module Connection Audit Report

**Date:** 2024-12-21  
**Scope:** `/home/vinniny/projects/CGRA_project/00_src/`

---

## Module Inventory

### Main Modules

| # | File | Module | Status |
|---|------|--------|--------|
| 1 | `cgra_top.sv` | `cgra_top` | ✅ Top-level |
| 2 | `cgra_axi_csr.sv` | `cgra_apb_csr` | ✅ Connected |
| 3 | `cgra_dma_engine.sv` | `cgra_dma_engine` | ✅ Connected |
| 4 | `cgra_control_unit.sv` | `cgra_control_unit` | ✅ Connected |
| 5 | `cgra_array_4x4.sv` | `cgra_array_4x4` | ✅ Connected |
| 6 | `cgra_tile.sv` | `cgra_tile` | ✅ Connected (×16) |
| 7 | `cgra_pe.sv` | `cgra_pe` | ✅ Connected (in tile) |
| 8 | `cgra_router.sv` | `cgra_router` | ✅ Connected (in tile) |
| 9 | `cgra_tile_memory.sv` | `cgra_tile_memory` | ❌ **NOT INSTANTIATED** |
| 10 | `axi_ram.sv` | `axi_ram` | ⚠️ Testbench only |

### bsg_mem Library Modules

| # | File | Module | Status |
|---|------|--------|--------|
| 11 | `bsg_defines.sv` | (defines/macros) | ✅ Included (header) |
| 12 | `bsg_dff.sv` | `bsg_dff` | ✅ Used by bsg_mem_1r1w_sync_synth |
| 13 | `bsg_dff_en_bypass.sv` | `bsg_dff_en_bypass` | ✅ Used by bsg_mem_1r1w_sync_synth |
| 14 | `bsg_mem_1r1w_sync.sv` | `bsg_mem_1r1w_sync` | ✅ Used by cgra_config_mem_bsg |
| 15 | `bsg_mem_1r1w_sync_synth.sv` | `bsg_mem_1r1w_sync_synth` | ✅ Used by bsg_mem_1r1w_sync |
| 16 | `cgra_config_mem_bsg.sv` | `cgra_config_mem_bsg` | ❌ **NOT INSTANTIATED** |

---

### bsg_mem Hierarchy
```
cgra_config_mem_bsg (❌ not used)
└── bsg_mem_1r1w_sync ✅
    └── bsg_mem_1r1w_sync_synth ✅
        ├── bsg_dff ✅
        └── bsg_dff_en_bypass ✅
```

## Hierarchy Diagram

```
cgra_top
├── u_csr (cgra_apb_csr)         ✅ Connected
├── u_dma (cgra_dma_engine)      ✅ Connected
├── u_cu (cgra_control_unit)     ✅ Connected
└── u_array (cgra_array_4x4)     ✅ Connected
    ├── tile_00 (cgra_tile)
    │   ├── u_router (cgra_router)  ✅
    │   └── u_pe (cgra_pe)          ✅
    ├── tile_01 ... tile_33
    └── (16 tiles total)
```

---

## Connection Details

### ✅ cgra_apb_csr (u_csr)
| Port | Connected To | Notes |
|------|--------------|-------|
| APB interface | Top-level ports | psel, penable, pwrite, paddr, pwdata, prdata, pready |
| dma_* | u_dma | src, dst, size, start, busy, done |
| cu_* | u_cu | start, soft_reset, busy, done, cycles |
| irq | Top-level | Directly driven |

### ✅ cgra_dma_engine (u_dma)
| Port | Connected To | Notes |
|------|--------------|-------|
| cfg_* | u_csr | Configuration |
| status_* | u_csr | Status feedback |
| m_axi_* | Top-level | AXI4-Lite master |
| irq_done | **UNUSED** | Left open `()` |

### ✅ cgra_control_unit (u_cu)
| Port | Connected To | Notes |
|------|--------------|-------|
| start_i, soft_reset_i | u_csr | Control |
| busy_o, done_o, cycle_count_o | u_csr | Status |
| pe_enable, pe_reset_n | u_array | Array control |
| array_done_i | **HARDCODED** | `1'b0` (TODO in code) |

### ✅ cgra_array_4x4 (u_array)
| Port | Connected To | Notes |
|------|--------------|-------|
| config_frame_* | **HARDCODED** | All `64'd0` |
| config_valid | **HARDCODED** | `1'b1` |
| edge_*_in_* | **HARDCODED** | All `32'd0`, `1'b0` |
| edge_*_out_* | **UNUSED** | All left open `()` |

---

## ❌ NOT CONNECTED Modules

### cgra_tile_memory.sv
- **Purpose:** Row-banked shared memory (4 banks × 1KB)
- **Status:** File exists but **NOT instantiated anywhere**
- **Impact:** Each PE uses internal 256×32 scratchpad instead
- **Future Use:** Could connect to DMA for loading data into row banks

### axi_ram.sv  
- **Purpose:** AXI4-Lite memory model (128KB)
- **Status:** Only instantiated in **testbench** (`tb_top.sv`)
- **This is correct:** It's the external memory the DMA accesses

---

## Issues Found

| Severity | Issue | Location | Impact |
|----------|-------|----------|--------|
| ⚠️ Medium | `array_done` hardcoded to `1'b0` | cgra_top.sv:206 | CU never knows when array finishes |
| ⚠️ Medium | All config_frames are `64'd0` | cgra_top.sv:220-235 | PEs have no configuration |
| ⚠️ Medium | Edge ports tied off | cgra_top.sv:238-276 | No I/O to/from array |
| 📝 Info | `irq_done` from DMA unused | cgra_top.sv:158 | IRQ comes from CSR instead |
| 📝 Info | `cgra_tile_memory` not instantiated | - | Using PE scratchpads instead |

---

## Recommendations

1. **Connect `array_done`** from array to CU for proper completion signaling
2. **Add config loading** path to drive `config_frame_*` ports
3. **Integrate `cgra_tile_memory`** if shared row memory is needed
4. **Connect array edge ports** for I/O data flow
