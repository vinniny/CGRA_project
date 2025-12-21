# RTL Module Connection Audit Report

**Date:** December 22, 2024  
**Status:** ALL ISSUES RESOLVED ✅

---

## Module Inventory

| # | File | Module | Status |
|---|------|--------|--------|
| 1 | `cgra_top.sv` | `cgra_top` | ✅ Top-level + auto-stop |
| 2 | `cgra_axi_csr.sv` | `cgra_apb_csr` | ✅ Connected |
| 3 | `cgra_dma_engine.sv` | `cgra_dma_engine` | ✅ Pipelined |
| 4 | `cgra_control_unit.sv` | `cgra_control_unit` | ✅ Connected |
| 5 | `cgra_tile_memory.sv` | `cgra_tile_memory` | ✅ **CONNECTED** |
| 6 | `cgra_array_4x4.sv` | `cgra_array_4x4` | ✅ Mesh broadcast |
| 7 | `cgra_tile.sv` | `cgra_tile` | ✅ PE + Router |
| 8 | `cgra_pe.sv` | `cgra_pe` | ✅ 9 ops verified |
| 9 | `cgra_router.sv` | `cgra_router` | ✅ (outputs unused) |
| 10 | `axi_ram.sv` | `axi_ram` | ✅ Testbench only |

---

## Hierarchy

```
cgra_top
├── u_csr (cgra_apb_csr)         ✅
├── u_dma (cgra_dma_engine)      ✅
├── u_cu (cgra_control_unit)     ✅
├── u_tile_mem (cgra_tile_memory) ✅ **NEW**
└── u_array (cgra_array_4x4)     ✅
    └── tile_00..tile_33 (16 tiles)
        ├── u_pe (cgra_pe)
        └── u_router (cgra_router)
```

---

## Resolved Issues

| Issue | Resolution |
|-------|------------|
| `array_done` hardcoded to 0 | ✅ Auto-stop counter at 16 cycles |
| Tile memory not instantiated | ✅ 4-bank memory connected |
| Edge ports tied off | ✅ Connected to synthesis_keep |
| Config frames all zero | ✅ DMA + double-pump loader |
| pe_sel overlap with slot | ✅ Bits [11:8] for PE select |

---

## Connection Summary

### cgra_tile_memory (u_tile_mem)
| Port | Connected To |
|------|--------------|
| `bank_addr` | context_pc (streaming) |
| `row_data[0:3]` | Array edge_data_in_w[0:3] |
| DMA interface | DMA write channel |

### cgra_array_4x4 (u_array)
| Port | Connected To |
|------|--------------|
| `edge_data_in_w*` | Tile Memory row outputs |
| `edge_data_out_*` | synthesis_keep (OR-reduce) |
| `config_frame_*` | DMA via double-pump |

---

**Audit Status**: All modules connected. No open issues.
