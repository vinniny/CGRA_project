# CGRA SoC Block Diagram

> Updated: December 2024 | 141/141 Tests Passed | Silicon Ready

---

## Top-Level Architecture

```mermaid
flowchart TB
    %% ===========================================================================
    %% Styling
    %% ===========================================================================
    classDef external fill:#e1f5fe,stroke:#0288d1,stroke-width:2px
    classDef control fill:#fff3e0,stroke:#ff9800,stroke-width:2px
    classDef datapath fill:#e8f5e9,stroke:#4caf50,stroke-width:2px
    classDef memory fill:#fce4ec,stroke:#e91e63,stroke-width:2px
    classDef compute fill:#ede7f6,stroke:#673ab7,stroke-width:2px
    classDef fifo fill:#e3f2fd,stroke:#2196f3,stroke-width:2px

    %% ===========================================================================
    %% External Interfaces
    %% ===========================================================================
    HOST[/"Host CPU<br/>(ARM Cortex-A9)"/]:::external
    DDR[("axi_ram<br/>128KB")]:::external

    %% ===========================================================================
    %% CGRA Top Module
    %% ===========================================================================
    subgraph TOP["cgra_top"]
        direction TB
        
        %% -----------------------------------------------------------------------
        %% Control Path (APB CSR + Control Unit)
        %% -----------------------------------------------------------------------
        subgraph CTRL_PATH["Control Path"]
            direction LR
            
            CSR["cgra_axi_csr<br/>─────────────<br/>0x00 DMA_CTRL<br/>0x04 DMA_STATUS<br/>0x08 DMA_SRC<br/>0x0C DMA_DST<br/>0x10 DMA_SIZE<br/>─────────────<br/>0x20 CU_CTRL<br/>0x24 CU_STATUS<br/>0x28 CU_CYCLES<br/>0x2C CU_TIMEOUT ✨<br/>─────────────<br/>0x30 IRQ_STATUS<br/>0x34 IRQ_MASK"]:::control
            
            CU["cgra_control_unit<br/>─────────────<br/>FSM States:<br/>IDLE → RUN<br/>→ FINISH<br/>─────────────<br/>context_pc[3:0]<br/>auto_stop timer<br/>max_cycles ✨"]:::control
        end
        
        %% -----------------------------------------------------------------------
        %% Pipelined DMA Engine (Producer-Consumer)
        %% -----------------------------------------------------------------------
        subgraph DMA_ENGINE["cgra_dma_engine"]
            direction LR
            
            READ_ENG["Read Engine<br/>(Producer)<br/>──────────<br/>R_IDLE<br/>R_ADDR<br/>R_DATA<br/>R_DONE"]:::datapath
            
            FIFO["FIFO<br/>────<br/>8×32b"]:::fifo
            
            WRITE_ENG["Write Engine<br/>(Consumer)<br/>──────────<br/>W_IDLE<br/>W_WAIT<br/>W_ADDR<br/>W_DATA<br/>W_RESP<br/>W_DONE"]:::datapath
            
            CFG_PATH["Config Path<br/>──────────<br/>Double-Pump<br/>Hi→Lo→64b"]:::datapath
            
            READ_ENG --> FIFO --> WRITE_ENG
            WRITE_ENG --> CFG_PATH
        end
        
        %% -----------------------------------------------------------------------
        %% Tile Memory (4-Bank Row Memory)
        %% -----------------------------------------------------------------------
        subgraph TILE_MEM["cgra_tile_memory (16KB)"]
            direction TB
            BANK0["Bank 0 (4KB)<br/>→ Row 0"]:::memory
            BANK1["Bank 1 (4KB)<br/>→ Row 1"]:::memory
            BANK2["Bank 2 (4KB)<br/>→ Row 2"]:::memory
            BANK3["Bank 3 (4KB)<br/>→ Row 3"]:::memory
        end
        
        %% -----------------------------------------------------------------------
        %% Compute Fabric (4x4 PE Array with Mesh Broadcast)
        %% -----------------------------------------------------------------------
        subgraph FABRIC["cgra_array_4x4 — Mesh Broadcast"]
            direction TB
            
            subgraph R0["Row 0"]
                direction LR
                PE00["PE<br/>0,0"]:::compute
                PE01["PE<br/>0,1"]:::compute
                PE02["PE<br/>0,2"]:::compute
                PE03["PE<br/>0,3"]:::compute
            end
            
            subgraph R1["Row 1"]
                direction LR
                PE10["PE<br/>1,0"]:::compute
                PE11["PE<br/>1,1"]:::compute
                PE12["PE<br/>1,2"]:::compute
                PE13["PE<br/>1,3"]:::compute
            end
            
            subgraph R2["Row 2"]
                direction LR
                PE20["PE<br/>2,0"]:::compute
                PE21["PE<br/>2,1"]:::compute
                PE22["PE<br/>2,2"]:::compute
                PE23["PE<br/>2,3"]:::compute
            end
            
            subgraph R3["Row 3"]
                direction LR
                PE30["PE<br/>3,0"]:::compute
                PE31["PE<br/>3,1"]:::compute
                PE32["PE<br/>3,2"]:::compute
                PE33["PE<br/>3,3"]:::compute
            end
        end
        
        SYNTH["synthesis_keep<br/>(OR-reduce edges)"]:::external
    end

    %% ===========================================================================
    %% External Connections
    %% ===========================================================================
    HOST ===|"APB Slave"| CSR
    READ_ENG ===|"AXI AR/R"| DDR
    WRITE_ENG ===|"AXI AW/W/B"| DDR

    %% ===========================================================================
    %% Internal Connections
    %% ===========================================================================
    CSR -->|"start, reset, timeout"| CU
    CSR -->|"cfg_src/dst/size"| DMA_ENGINE
    CU -->|"busy, done, cycles"| CSR
    
    CU -->|"context_pc"| TILE_MEM
    CU -->|"pe_enable"| FABRIC
    CFG_PATH -->|"64-bit config"| FABRIC
    
    BANK0 -->|"row_data[0]"| R0
    BANK1 -->|"row_data[1]"| R1
    BANK2 -->|"row_data[2]"| R2
    BANK3 -->|"row_data[3]"| R3

    %% Mesh Broadcast (horizontal data flow)
    PE00 --> PE01 --> PE02 --> PE03
    PE10 --> PE11 --> PE12 --> PE13
    PE20 --> PE21 --> PE22 --> PE23
    PE30 --> PE31 --> PE32 --> PE33
    
    PE03 --> SYNTH
    PE13 --> SYNTH
    PE23 --> SYNTH
    PE33 --> SYNTH
```

---

## Processing Element (cgra_pe)

```mermaid
flowchart TB
    subgraph PE["cgra_pe — 19 Operations"]
        direction TB
        
        subgraph CFG["Configuration"]
            CFG_RAM["Config RAM<br/>16 slots × 64-bit"]
            PC["context_pc<br/>[3:0]"]
        end
        
        subgraph DATA["Data Path"]
            RF["Register File<br/>16 × 32-bit"]
            SPM["Scratchpad<br/>256 × 32-bit"]
            MUX0["src0_sel"]
            MUX1["src1_sel"]
        end
        
        subgraph ALU["ALU/MAC"]
            direction LR
            OPS["ADD SUB MUL MAC<br/>AND OR XOR<br/>SHL SHR (0-31) ✨<br/>CMP_GT CMP_LT CMP_EQ<br/>LOAD/STORE SPM<br/>ACC_CLR PASS0 PASS1<br/>LIF (neuromorphic)"]
            ACC["Accumulator<br/>40-bit"]
        end
        
        OUT["Broadcast<br/>→ N/E/S/W"]
    end
    
    %% Inputs
    W((West)) --> MUX0
    N((North)) --> MUX0
    E((East)) --> MUX1
    S((South)) --> MUX1
    
    PC --> CFG_RAM
    CFG_RAM --> MUX0
    CFG_RAM --> MUX1
    RF --> MUX0
    RF --> MUX1
    SPM --> MUX0
    
    MUX0 --> ALU
    MUX1 --> ALU
    ALU --> ACC
    ALU --> RF
    ALU --> SPM
    ALU --> OUT
```

---

## Data Flow (West → East Streaming)

```mermaid
flowchart LR
    subgraph INPUT["Data Input"]
        DMA["DMA Engine"]
        TILE["Tile Memory<br/>4 Banks"]
    end
    
    subgraph ARRAY["PE Array (4×4)"]
        COL0["Col 0<br/>(West Edge)"]
        COL1["Col 1"]
        COL2["Col 2"]
        COL3["Col 3<br/>(East Edge)"]
    end
    
    subgraph OUTPUT["Output"]
        SYNTH["synthesis_keep"]
    end
    
    DMA -->|"Write to banks"| TILE
    TILE -->|"Bank 0-3<br/>via West edge"| COL0
    COL0 -->|"Broadcast"| COL1
    COL1 -->|"Broadcast"| COL2
    COL2 -->|"Broadcast"| COL3
    COL3 -->|"Edge outputs"| SYNTH
```

---

## Key Metrics

| Component | Specification | Verified |
|-----------|---------------|----------|
| PE Array | 4×4 = 16 tiles | ✅ Suite O |
| SPM per PE | 256 × 32-bit | ✅ Suite T |
| Register File | 16 × 32-bit | ✅ |
| DMA FIFO | 8 × 32-bit | ✅ Suite B |
| Tile Memory | 4 banks × 4KB = 16KB | ✅ Suite J |
| Test Suites | **23** (A-V, Q1-Q2) | ✅ |
| Test Vectors | **141** | ✅ |
| ISA Operations | **19 verified** | ✅ Suite T,U,V |
| Barrel Shifter | 5-bit (0-31) | ✅ Suite Q2 ✨ |
| Mesh Broadcast | PE → 4 neighbors | ✅ Suite L |
| Auto-Stop | Programmable timeout | ✅ CSR 0x2C |
| Neuromorphic | LIF neuron | ✅ Suite V |

---

## APB Register Map

| Offset | Name | Access | Description |
|--------|------|--------|-------------|
| 0x00 | DMA_CTRL | RW | [0] Start (auto-clear) |
| 0x04 | DMA_STATUS | RO | [0] Busy, [1] Done |
| 0x08 | DMA_SRC | RW | Source address |
| 0x0C | DMA_DST | RW | Destination address |
| 0x10 | DMA_SIZE | RW | Transfer size (bytes) |
| 0x20 | CU_CTRL | RW | [0] Start, [1] Soft Reset |
| 0x24 | CU_STATUS | RO | [0] Busy, [1] Done |
| 0x28 | CU_CYCLES | RO | Cycle counter |
| **0x2C** | **CU_TIMEOUT** | **RW** | **Max cycles (0 = no limit)** ✨ |
| 0x30 | IRQ_STATUS | RO | [0] DMA Done, [1] CU Done |
| 0x34 | IRQ_MASK | RW | IRQ enable mask |

---

## ISA Summary (19 Operations)

| Op | Name | Operation | Test |
|----|------|-----------|------|
| 0 | NOP | No operation | M |
| 1 | ADD | A + B (saturating) | M, Q |
| 2 | SUB | A - B (saturating) | M, N |
| 3 | MUL | A × B | M |
| 4 | MAC | Acc += A × B | T |
| 5 | AND | A & B | K, M |
| 6 | OR | A \| B | K, M |
| 7 | XOR | A ^ B | K, M |
| 8 | SHL | A << B[4:0] | Q2 ✨ |
| 9 | SHR | A >>> B[4:0] (arith) | Q2 ✨ |
| 10 | CMP_GT | (A > B) ? 1 : 0 | T |
| 11 | CMP_LT | (A < B) ? 1 : 0 | T, U |
| 12 | CMP_EQ | (A == B) ? 1 : 0 | P |
| 13 | LOAD_SPM | Load from scratchpad | T |
| 14 | STORE_SPM | Store to scratchpad | T |
| 15 | ACC_CLR | Clear accumulator | T, V |
| 16 | PASS0 | Pass operand 0 | T |
| 17 | PASS1 | Pass operand 1 | T |
| 18 | LIF | Leaky Integrate-Fire | V |

---

## Architecture Fixes Applied

| Fix | Issue | Solution |
|-----|-------|----------|
| #1 | PE N/E/S/W inputs identical | Direct tile port wiring |
| #2 | Config 32→64 bit data loss | Double-pump protocol |
| #3 | Bank address hardcoded | context_pc streaming |
| #4 | PE outputs disconnected | Mesh broadcast |
| #5 | PE_SEL encoding overlap | Bits [11:8] decode |
| #6 | Auto-stop fixed at 16 | **Programmable timeout** ✨ |
| #7 | Shift mask [3:0] | **5-bit [4:0] + arithmetic SHR** ✨ |
