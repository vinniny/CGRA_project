%% ==============================================================================
%% CGRA Top-Level Block Diagram
%% ==============================================================================
%% Render at: https://mermaid.live/
%% ==============================================================================

flowchart TB
    %% ===========================================================================
    %% Styling
    %% ===========================================================================
    classDef external fill:#e1f5fe,stroke:#0288d1,stroke-width:2px
    classDef control fill:#fff3e0,stroke:#ff9800,stroke-width:2px
    classDef datapath fill:#e8f5e9,stroke:#4caf50,stroke-width:2px
    classDef memory fill:#fce4ec,stroke:#e91e63,stroke-width:2px
    classDef compute fill:#ede7f6,stroke:#673ab7,stroke-width:2px

    %% ===========================================================================
    %% External Interfaces
    %% ===========================================================================
    HOST[/"Host CPU<br/>(ARM Cortex-A9)"/]:::external
    DDR[("DDR3<br/>SDRAM")]:::external
    CFG_MEM[("Config<br/>Memory")]:::external

    %% ===========================================================================
    %% CGRA Top Module
    %% ===========================================================================
    subgraph TOP["cgra_top"]
        direction TB
        
        %% -----------------------------------------------------------------------
        %% Control Path
        %% -----------------------------------------------------------------------
        subgraph CTRL_PATH["Control Path"]
            direction LR
            
            CSR["cgra_axi_csr<br/>───────────<br/>CTRL [0x00]<br/>STATUS [0x04]<br/>BITSTR_ADDR [0x08]<br/>JOB_DESC [0x18]<br/>IRQ_MASK [0x24]"]:::control
            
            CU["cgra_control_unit<br/>─────────────<br/>FSM: IDLE - WAIT_CFG<br/>- EXEC_RUN - COMPLETE<br/>─────────────<br/>perf_cycles<br/>perf_stalls"]:::control
            
            IRQ["IRQ<br/>Gen"]:::control
        end
        
        %% -----------------------------------------------------------------------
        %% Data Path
        %% -----------------------------------------------------------------------
        subgraph DATA_PATH["Data Path"]
            direction LR
            
            LOADER["cgra_config_loader<br/>──────────────<br/>Bank0 / Bank1<br/>Double Buffer<br/>16 x 64-bit frames"]:::datapath
            
            DMA["cgra_dma_engine<br/>────────────<br/>AXI4 Master<br/>Burst: 16 beats<br/>Descriptor-based"]:::datapath
            
            TMEM["cgra_tile_memory<br/>─────────────<br/>4 Banks x 1KB<br/>Bank per Row<br/>DMA Port"]:::memory
        end
        
        %% -----------------------------------------------------------------------
        %% Compute Fabric
        %% -----------------------------------------------------------------------
        subgraph FABRIC["cgra_array_4x4 - 16 PEs"]
            direction LR
            
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
    end

    %% ===========================================================================
    %% External Connections
    %% ===========================================================================
    HOST ===|"AXI4-Lite Slave<br/>───────────<br/>aw: addr, valid, ready<br/>w: data[31:0], strb, valid<br/>b: resp, valid, ready<br/>ar: addr, valid, ready<br/>r: data[31:0], resp, valid"| CSR
    
    DMA ===|"AXI4 Master<br/>──────────<br/>aw: id, addr, len, burst<br/>w: data[31:0], last<br/>b: id, resp<br/>ar: id, addr, len, burst<br/>r: id, data[31:0], last"| DDR
    
    LOADER ===|"Config Read<br/>────────<br/>addr[31:0]<br/>read, valid<br/>rdata[63:0]"| CFG_MEM

    %% ===========================================================================
    %% Internal Connections
    %% ===========================================================================
    
    %% CSR <-> Control Unit
    CSR -->|"start, reset,<br/>cfg_start"| CU
    CSR -->|"bitstream_addr,<br/>bitstream_size"| CU
    CU -->|"busy, done,<br/>error, cfg_done"| CSR
    CU -->|"perf_cycles,<br/>perf_stalls"| CSR
    
    %% Control Unit -> Loader/DMA
    CU -->|"cfg_load_start,<br/>swap_buffers"| LOADER
    LOADER -->|"load_done,<br/>load_error"| CU
    
    CU -->|"dma_trigger"| DMA
    DMA -->|"busy, done,<br/>error"| CU
    
    %% Control Unit -> Fabric
    CU -->|"enable, reset,<br/>timestep[15:0]"| FABRIC
    
    %% Loader -> Fabric
    LOADER ==>|"config_frame[0:15]<br/>[63:0] x 16<br/>config_valid"| FABRIC
    
    %% DMA <-> Tile Memory
    DMA <-->|"addr[31:0], r/w<br/>wdata/rdata[31:0]"| TMEM
    
    %% IRQ
    CU --> IRQ
    DMA --> IRQ
    CSR -->|"irq_mask[2:0]"| IRQ
    IRQ ==>|"irq"| HOST

    %% ===========================================================================
    %% Mesh Interconnect (Horizontal)
    %% ===========================================================================
    PE00 <--> PE01
    PE01 <--> PE02
    PE02 <--> PE03
    PE10 <--> PE11
    PE11 <--> PE12
    PE12 <--> PE13
    PE20 <--> PE21
    PE21 <--> PE22
    PE22 <--> PE23
    PE30 <--> PE31
    PE31 <--> PE32
    PE32 <--> PE33
    
    %% Mesh Interconnect (Vertical)
    PE00 <--> PE10
    PE01 <--> PE11
    PE02 <--> PE12
    PE03 <--> PE13
    PE10 <--> PE20
    PE11 <--> PE21
    PE12 <--> PE22
    PE13 <--> PE23
    PE20 <--> PE30
    PE21 <--> PE31
    PE22 <--> PE32
    PE23 <--> PE33
