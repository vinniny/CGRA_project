# CGRA SoC Block Diagram

> Render at: https://mermaid.live/

## Top-Level Architecture (Current Implementation)

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
        %% Control Path
        %% -----------------------------------------------------------------------
        subgraph CTRL_PATH["Control Path (APB)"]
            direction LR
            
            CSR["cgra_axi_csr<br/>───────────<br/>DMA_CTRL [0x00]<br/>DMA_STATUS [0x04]<br/>DMA_SRC [0x08]<br/>DMA_DST [0x0C]<br/>DMA_SIZE [0x10]<br/>CU_CTRL [0x14]"]:::control
            
            CU["cgra_control_unit<br/>─────────────<br/>FSM: IDLE → RUN<br/>→ FINISH<br/>─────────────<br/>context_pc[3:0]<br/>auto_stop"]:::control
        end
        
        %% -----------------------------------------------------------------------
        %% Pipelined DMA Engine
        %% -----------------------------------------------------------------------
        subgraph DMA_ENGINE["cgra_dma_engine (Pipelined)"]
            direction LR
            
            READ_ENG["Read Engine<br/>(Producer)<br/>──────────<br/>R_IDLE<br/>R_ADDR<br/>R_DATA<br/>R_DONE"]:::datapath
            
            FIFO["FIFO<br/>────<br/>8×32b<br/>count"]:::fifo
            
            WRITE_ENG["Write Engine<br/>(Consumer)<br/>──────────<br/>W_IDLE→WAIT<br/>→ADDR→DATA<br/>→RESP→DONE"]:::datapath
            
            READ_ENG --> FIFO --> WRITE_ENG
        end
        
        %% -----------------------------------------------------------------------
        %% Tile Memory (4-Bank Row Memory)
        %% -----------------------------------------------------------------------
        subgraph TILE_MEM["cgra_tile_memory (4 Banks)"]
            direction LR
            BANK0["Bank 0<br/>Row 0"]:::memory
            BANK1["Bank 1<br/>Row 1"]:::memory
            BANK2["Bank 2<br/>Row 2"]:::memory
            BANK3["Bank 3<br/>Row 3"]:::memory
        end
        
        %% -----------------------------------------------------------------------
        %% Compute Fabric (4x4 PE Array)
        %% -----------------------------------------------------------------------
        subgraph FABRIC["cgra_array_4x4 (Mesh Broadcast)"]
            direction TB
            
            subgraph R0["Row 0 ← Bank 0"]
                direction LR
                PE00["PE<br/>0,0"]:::compute
                PE01["PE<br/>0,1"]:::compute
                PE02["PE<br/>0,2"]:::compute
                PE03["PE<br/>0,3"]:::compute
            end
            
            subgraph R1["Row 1 ← Bank 1"]
                direction LR
                PE10["PE<br/>1,0"]:::compute
                PE11["PE<br/>1,1"]:::compute
                PE12["PE<br/>1,2"]:::compute
                PE13["PE<br/>1,3"]:::compute
            end
            
            subgraph R2["Row 2 ← Bank 2"]
                direction LR
                PE20["PE<br/>2,0"]:::compute
                PE21["PE<br/>2,1"]:::compute
                PE22["PE<br/>2,2"]:::compute
                PE23["PE<br/>2,3"]:::compute
            end
            
            subgraph R3["Row 3 ← Bank 3"]
                direction LR
                PE30["PE<br/>3,0"]:::compute
                PE31["PE<br/>3,1"]:::compute
                PE32["PE<br/>3,2"]:::compute
                PE33["PE<br/>3,3"]:::compute
            end
        end
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
    CSR -->|"start, reset"| CU
    CSR -->|"cfg_src/dst/size"| DMA_ENGINE
    CU -->|"busy, done"| CSR
    WRITE_ENG -->|"status"| CSR
    CU -->|"context_pc"| TILE_MEM
    CU -->|"pe_enable"| FABRIC
    
    TILE_MEM -->|"row_data[0]"| R0
    TILE_MEM -->|"row_data[1]"| R1
    TILE_MEM -->|"row_data[2]"| R2
    TILE_MEM -->|"row_data[3]"| R3

    %% ===========================================================================
    %% Mesh Broadcast (PE outputs → Neighbor inputs)
    %% ===========================================================================
    PE00 --> PE01 --> PE02 --> PE03
    PE10 --> PE11 --> PE12 --> PE13
    PE20 --> PE21 --> PE22 --> PE23
    PE30 --> PE31 --> PE32 --> PE33
```

---

## Data Flow Architecture

```mermaid
flowchart LR
    subgraph INPUT["Data Input"]
        DMA["DMA"]
        TILEMEM["Tile Memory<br/>(4 Banks)"]
    end
    
    subgraph COMPUTE["PE Array"]
        COL0["Column 0<br/>(Memory Input)"]
        COL1["Column 1"]
        COL2["Column 2"]
        COL3["Column 3"]
    end
    
    subgraph OUTPUT["Synthesis Keeper"]
        SYNTH["synthesis_keep<br/>(OR-reduce)"]
    end
    
    DMA -->|"Config"| TILEMEM
    TILEMEM -->|"West Edge"| COL0
    COL0 -->|"PE Broadcast"| COL1
    COL1 -->|"PE Broadcast"| COL2
    COL2 -->|"PE Broadcast"| COL3
    COL3 -->|"Edge Outputs"| SYNTH
```

---

## Each cgra_tile Contains

```mermaid
flowchart TB
    subgraph TILE["cgra_tile"]
        subgraph PE["cgra_pe"]
            RF["RF: 16×32"]
            ALU["ALU: 9 ops verified"]
            SPM["SPM: 256×32"]
            CFG["Config RAM<br/>(16 contexts)"]
        end
        ROUTER["cgra_router<br/>5-port XY<br/>(outputs unused)"]
    end
    
    CFG -->|"context_pc"| ALU
    RF --> ALU
    ALU --> SPM
    ALU -->|"alu_result"| BROADCAST
    
    BROADCAST["Broadcast<br/>to N/E/S/W"]
    
    W((W)) --> PE
    BROADCAST --> N((N))
    BROADCAST --> E((E))
    BROADCAST --> S((S))
```

---

## Key Metrics (Verified)

| Component | Spec | Verified |
|-----------|------|----------|
| PE Array | 4×4 = 16 tiles | ✅ Suite O |
| SPM per PE | 256 × 32-bit | ✅ |
| DMA FIFO | 8 × 32-bit | ✅ Suite B |
| Tile Memory | 4 banks × 4KB | ✅ Suite J |
| Test Suites | 19 (A-S) | ✅ |
| Test Vectors | **126** | ✅ |
| ISA Operations | 9 verified | ✅ Suite M |
| Mesh Broadcast | PE → Neighbors | ✅ Suite L |
| Auto-Stop | 16-cycle trigger | ✅ |

---

## Architecture Fixes Applied

| Fix | Issue | Solution |
|-----|-------|----------|
| #1 | PE N/E/S/W inputs same | Direct tile port wiring |
| #2 | Config 32→64 bit loss | Double-pump loader |
| #3 | Bank addr hardcoded | context_pc streaming |
| #4 | PE outputs disconnected | Mesh broadcast |
| #5 | pe_sel encoding overlap | Bits [11:8] not [7:4] |
