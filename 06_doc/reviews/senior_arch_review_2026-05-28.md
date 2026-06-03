# Senior principal-engineer architectural review — 2026-05-28

Verbatim response to the 35 questions in `senior_engineer_questions_2026-05-28`
(see chat transcript or `.handover/`). Preserved here because every paragraph
contains a non-trivial decision criterion or a citation worth keeping.

This is the canonical source-of-truth for the v3 chip design directions and
the thesis-defense methodology. If anything below conflicts with a memory
entry or a different doc, the senior review wins unless overruled by new
silicon measurement.

---

## 1. Hetero Split vs. Unified Fabric

The "CGRA-conv + NEON-FC" split is absolutely the right architectural answer,
and ironically, the TPU comparison proves your point. The TPU is not a single
unified fabric; it is a highly heterogeneous pipeline. The Matrix Multiply
Unit (MXU) is a rigid 2D systolic array that only does matrix multiplication.
Google explicitly paired it with a separate Vector Processing Unit (VPU) to
handle activations, pooling, and operations that don't map well to a 2D
spatial array.

If you try to build a unified CGRA that gracefully handles both high-reuse
Convs and zero-reuse FCs, you will end up building an FPGA. You will bloat
your PE configuration memory, over-provision your interconnect, and burn die
area on mode-switching mux logic. By splitting the workload, you are aligning
with the modern SoC design paradigm: let the spatial array do what it does
best (compute-bound loops), and let the tightly-coupled vector processor
(NEON) handle the memory-bound streaming.

## 2. Roofline vs. "Right Tool" Framing

Do not choose between them; use the Roofline model to mathematically prove
the "right tool" argument.

- For the ML Systems people: Show them the Roofline plot. Plot your Conv
  layers far to the right (Compute-Bound, high arithmetic intensity) and
  your FC layers far to the left (Memory-Bound, low arithmetic intensity).
- For the Digital Architecture people: Frame this through the lens of
  Amdahl's Law and Dark Silicon. Explain that because these two workloads
  exist in fundamentally different Roofline regimes, a monolithic
  architecture forced to accommodate both will inevitably waste silicon
  (dark area) and energy.

When you anchor "right tool for the job" to the indisputable math of the
Roofline model, it ceases to be hand-waving and becomes a rigorous
architectural derivation.

## 3. Defending "My CGRA Doesn't Do FC Efficiently"

This is highly defendable and actually demonstrates engineering maturity.
When examiners ask, "Shouldn't a thesis-quality CGRA at least try?" your
response should be: "I did try, and the models proved it was the wrong path."

You already have the ammunition: point out that you modeled FC1 v2 (the
16-PE wide compute version), and the readout overhead scaled
proportionally, yielding no net win.

A hallmark of poor accelerator design is "feature creep"—stretching a
domain-specific architecture until it becomes general-purpose. You can cite
the history of spatial architectures: whenever designers over-generalize the
routing network of a CGRA to handle irregular or memory-bound workloads,
they destroy the Area/Power/Performance advantage the CGRA had over an
embedded CPU in the first place. Admitting a negative result (FC doesn't
map well) and proposing a system-level heterogeneous fallback (NEON) is
exactly what senior hardware architects do in the industry.

## 4. Cortex-A9 NEON INT16 Benchmarks & Citations

Because Cortex-A9 is an older ARMv7-A microarchitecture, finding modern ML
papers isolating it can be tricky, but you have a few canonical anchors for
16-bit NEON performance:

- **The QNNPACK Paper** (Facebook/Meta, 2018): *QNNPACK: Open Source Library
  for Optimized Mobile Deep Learning* (Marat Dukhan). While focused heavily
  on INT8, this is the gold standard for explaining how mobile CPUs
  (including older NEON architectures) execute GEMV/GEMM operations with
  extreme efficiency. It perfectly details how NEON registers are packed to
  hide memory latency.
- **gemmlowp** (Google, 2015-present): Look at the design documents by
  Benoit Jacob for gemmlowp (Low-precision matrix multiplication). It
  provides an exhaustive breakdown of why ARM NEON vector pipelines excel
  at low-precision GEMV compared to naive C implementations.
- **ARM's Primary Engineering Source**: For a direct, mathematically clear
  anchor on 16-bit MAC latencies, cite Chris Shore's widely referenced ARM
  engineering article: *"Coding for Neon - Part 3: Matrix Multiplication"*.
  It explicitly breaks down how 16-bit fixed-point arithmetic on Cortex-A
  series NEON pipelines almost doubles performance over 32-bit floats by
  using instructions like SMULL (Signed Multiply Long) and SMLAL (Signed
  Multiply-Add Long) to accumulate in 32-bit registers before narrowing
  back to 16-bit.

## 5. Per-PE Result FIFO Depth

Your intuition is close, but it is a bit more subtle because you are
interfacing with AXI, which is notoriously non-deterministic. The depth
needs to absorb the worst-case AXI stall during a compute burst.

**The safe sizing rule is**: `Depth = (Compute Burst Size) - (Guaranteed
Drain Rate) + (Max Expected AXI Backpressure)`.

If your AXI interconnect routinely deasserts AWREADY or WREADY for 10-15
cycles while arbitrating other system traffic, a shallow FIFO will fill up
and instantly stall your PEs. On an FPGA, a depth of 16 or 32 elements is
often practically "free" if you map it to a LUTRAM (SRL32) rather than
burning a full Block RAM. Size it to cover the AXI interconnect's longest
observed stall latency.

## 6. FIFO Backpressure Semantics: Stall vs. Overflow Flag

**You must stall.** In machine learning accelerators, silent data corruption
is fatal. If an overflow flag is set and a partial sum is dropped, the
entire inference is poisoned. Software cannot practically "recover" a
dropped MAC in the middle of a tightly pipelined 2D array without resetting
and re-running the entire tile.

Real production AI chips (like the TPU or NVDLA) stall the pipeline. Yes,
this introduces the risk of deadlock if the drain path hangs, but that is a
verification problem, not an architectural one. You build robust UVM
scoreboards and deadlock-detection monitors to ensure the AXI drain path
never permanently hangs, rather than pushing the problem to the software
stack.

## 7. Readout Sweeper Policy: Round-Robin vs. Priority

**Round-Robin** (specifically, *Burst-Locked Round-Robin*) is the production-
grade choice. Pure priority schemes (drain fullest first) require comparing
the counters of all 16 FIFOs every cycle. In SystemVerilog, this generates a
massive, deep combinational logic tree that will destroy your Fmax and make
timing closure miserable.

Instead, use a Round-Robin arbiter that locks onto a FIFO until a full AXI
burst length (e.g., 4 or 8 beats) is satisfied or the FIFO empties. This
perfectly coalesces AXI bursts, guarantees fairness (preventing one PE from
starving the others), and keeps the RTL synthesis clean and fast.

## 8. Per-PE Bias Regs Abstraction

**(b) DMA-mappable bias bank in tile memory wins.**

- Option (a) using APB is too slow. The scalar writes from the host CPU
  take too many cycles and force you to route a separate APB control
  network into the datapath.
- Option (c) using an explicit opcode bloats your instruction memory and
  overcomplicates the decoder.

By memory-mapping a small bias SRAM bank and feeding it via the existing
DMA engines before the compute phase begins, you treat biases exactly like
activations or weights. It keeps the PE datapath pure, minimizes area, and
software handles it with a standard memory copy.

## 9. Wide-Readout Port: Separate AXI Master vs. SmartConnect

**Share it via the SmartConnect.** Burning dedicated PL High-Performance
(HP) ports for every datapath is unsustainable as you scale up.

The ~5 ns of arbitration latency through an AXI Interconnect/SmartConnect
only hurts you on the first beat of the transaction (the AWVALID to
AWREADY handshake). Because AXI is pipelined, once the burst starts, you
will still achieve one word per clock cycle. As long as your per-PE FIFOs
are sized correctly (as discussed in #5) to absorb that initial 5 ns
arbitration delay, the latency is completely hidden from the compute array.

## 10. Multi-Context PE Config Slot (16-Deep): Keep or Kill?

**Kill it** (or reduce it heavily) for a v3 chip. 16-deep is vestigial for
modern AI workloads. CGRAs originally used deep configuration RAMs to
handle complex, irregular control flows (like software-defined radio or
general-purpose DSP). For spatial AI (Convolutions, GEMMs), the inner loops
are highly regular.

You typically only need 3 or 4 contexts: a Prologue (load), a Steady-State
(compute loop), and an Epilogue (drain). Dropping from 16 to 4 contexts
will drastically reduce the area of your configuration registers, ease
routing congestion, and relieve the timing closure pressure on your decode
path, allowing you to clock the MACs faster.

## 11. ACP Write Traffic vs. CPU L2 Reads (The 800 MB/s Scenario)

In the worst case, the CPU will lose roughly **15% to 25% of its L2 read
bandwidth**, but the **latency impact** is what will actually throttle your
NEON FC kernel.

At 667 MHz, the PL310 L2 cache has a theoretical peak bandwidth of ~5.3
GB/s. 800 MB/s from the CGRA consumes about 15% of that raw pipe. However,
ACP writes do not just quietly enter the L2. Every ACP write forces the SCU
(Snoop Control Unit) to interrogate the Cortex-A9's L1 Data Cache tag RAMs
to ensure coherency. While the tag RAMs are duplicated to allow concurrent
snooping, a sustained 800 MB/s stream saturates the SCU's arbitration
logic. Your NEON kernel, which relies on aggressive L2 hardware prefetching
to feed its vector registers, will suffer from SCU arbitration stalls,
causing the pipeline to starve.

## 12. SCU Snoop Bottleneck on Cortex-A9

The UG1046 warning is **not** overcautious; it is a hard production reality.
The SCU was designed primarily to keep the two A9 cores coherent with each
other, not to ingest a continuous 64-bit firehose from the programmable
logic. If you stream bulk tensor data over the ACP, the SCU locks up
processing the coherent writes. We see this constantly in production when
teams try to push high-framerate video or large ML activations through the
ACP. The CPU stalls completely, unable to fetch instructions or data. The
ACP should be strictly reserved for **small, latency-sensitive control
structures** (like your SG-DMA descriptors) or tiny, highly-shared
parameter updates. For **bulk ML tensors, use the HP (High Performance)
ports directly to DDR** and manage the cache in software.

## 13. Rate-Limiting CGRA → ACP Writes

Rate-limiting is worth it if you are forced to use the ACP for medium-to-
large payloads and cannot afford to stall the CPU.

The ACP "burst budget" is defined by the SCU's shallow acceptance buffers.
The sweet spot is restricting your AXI bursts to exactly **4 or 8 beats
(32 or 64 bytes)** — which aligns perfectly with the 32-byte cache line
size — and limiting your **outstanding write transactions (AWVALID without
BVALID) to 1 or 2**. If you allow the AXI master to issue deep, 16-beat
bursts with multiple outstanding transactions, the SCU buffers fill, the
AWREADY signal drops, and the SCU prioritizes draining the ACP over
servicing the CPU's L1 misses. A slight artificial delay between 8-beat
bursts acts as a yield, allowing the A9 to slip its NEON fetches into the
L2.

## 14. Xil_DCacheInvalidateRange Scaling

The scaling is **(a) per-line constant**, but your 2.5 µs latency for 400 B
is heavily inflated by the PL310 architecture.

For 400 Bytes, you are invalidating 13 cache lines (32B each). The CP15
instructions that invalidate the L1 cache by Modified Virtual Address (MVA)
are extremely fast (a few cycles per line). **The bottleneck is the L2
cache.**

On the Zynq-7000, the PL310 L2 cache is not managed via CP15 coprocessor
instructions; it is managed via Memory-Mapped I/O (MMIO).
`Xil_DCacheInvalidateRange` function loops through the addresses, writing
them to the PL310 invalidation registers over a slow APB bridge. Worse, at
the end of the operation, Xilinx's standalone BSP executes an L2 Cache Sync
(writing to the PL310 Sync register and polling it). That APB
synchronization barrier is agonizingly slow and accounts for the bulk of
your 2.5 µs.

## 15. PMU L2 Counter Access on PL310

You must use the **L2C-310 MMIO range (0xF8F02000)**. The Cortex-A9 CP15
PMU interface only has visibility into the L1 caches, the branch
predictor, and the SCU. It is completely blind to L2 hits, misses, and
evictions.

There are two major gotchas when reading the PL310 counters from EL1
(bare-metal/kernel):

1. **TrustZone / Secure Access**: The PL310 Event Counter Control
   Registers are typically configured as Secure-access only by default.
   If your bootloader (e.g., FSBL or U-Boot) drops you into Non-Secure
   EL1, any attempt to configure or read the L2 counters will silently
   fail or cause a synchronous Data Abort. You must ensure the boot
   setup clears the relevant security restrictions for the PL310.
2. **Read Latency**: Because the registers are on the APB interconnect,
   a read takes dozens of CPU cycles. Do not read these counters inside
   the inner loop of your NEON FC kernel, or the measurement overhead
   will fundamentally alter the pipeline behavior you are trying to
   measure. Read them before the outer loop starts and immediately
   after it finishes.

## 16. Memory-Bandwidth Axis: The "Ceiling" Approach

**Do not use the measured AXI-mon throughput of your actual workload as the
roof.** That is circular logic. The roof represents the maximum capability
of the machine, while the point plotted underneath it represents the
workload. If the workload becomes the roof, your efficiency always looks
like 100%.

For a thesis, the most intellectually honest and visually powerful method
is to plot **multiple roofs (often called Ceilings)**:

1. **The Theoretical Roof (Highest)**: Plot the absolute mathematical peak
   (1.2 GB/s × 4 ports = 4.8 GB/s). Cite the Xilinx Zynq-7000 TRM.
2. **The Empirical/Achievable Roof (Lower)**: Plot the sustained achievable
   bandwidth (usually 60-80%). You generate this **not** with your ML
   kernel, but with a highly optimized, pure-streaming DMA microbenchmark
   (like a custom hardware implementation of the STREAM benchmark) that
   does nothing but saturate the AXI ports with maximum burst lengths.

When you plot your actual FC and Conv workloads, they will sit below the
Empirical Roof. The gap between the Theoretical and Empirical roofs
represents platform inefficiencies (AXI arbitration, DDR controller
overhead). The gap between the Empirical roof and your workload point
represents workload inefficiencies (your SG-DMA descriptor traversal, non-
ideal burst lengths, etc.). This allows you to visually decompose exactly
where you are losing performance.

## 17. Peak-Throughput Convention: GOPS vs. MMAC/s

You are entirely correct that this is a community clash. ML-Systems people
expect GOPS/TOPS. Digital Architecture people expect MACs/cycle or MMAC/s.

**The solution: Lead with GOPS on the axis, but define it explicitly in the
legend and the text.**

- Label your Y-axis: `Performance (GOPS)`.
- Set your flat roof at 1.6 GOPS.
- In the caption and the defense slide, explicitly state: "*Peak compute is
  800 MMAC/s (16 PEs × 50 MHz). Using the ML-industry standard convention
  of 1 MAC = 2 Operations, this yields 1.6 GOPS.*"

Do not hide the conversion. If you just say 1.6 GOPS, the architecture
professors will divide by your clock speed, get 32, look at your 16 PEs,
and interrupt your presentation to ask if you magically double-pumped your
ALUs. By explicitly stating the math upfront, you satisfy the ML folks'
desire for standard units while proving to the architecture folks that
your math is grounded.

## 18. MAC Efficiency Curve: Architectural Peak vs. Application Achievable

**The Roofline curve must be the Architectural Peak.** This is the most
critical rule of the Roofline model.

The Roofline is defined as the upper bound of what the hardware can
theoretically deliver at a given arithmetic intensity. The application-
achievable performance (which includes your setup, readout, and context-
switch overhead) is represented by the **scatter plot point** (the dot)
that you place under the roof.

If you draw the roofline using the application-achievable curve (excluding
setup/readout), you are artificially lowering the roof to make your dot
look closer to it. Committee members will instantly recognize this as
"cooking the books."

Instead, use the Architectural Peak (1.6 GOPS) as the solid roof line.
Plot your Conv workload dot close to the knee. Then, plot your FC workload
dot far to the left (low arithmetic intensity) and far below the bandwidth
roof.

**The Defense Narrative**: You then point to the massive vertical gap
between the FC dot and the roof, and you explicitly state: *"This vertical
distance represents our 87% idle time. It is driven precisely by the
readout overhead and column-serial AXI drain we discussed."* By using the
absolute peak as the roof, you turn a "bad" result (poor FC performance)
into a rigorous, scientifically diagnosed architectural bottleneck. This
is exactly what a master's or PhD committee wants to see: an engineer who
uses standard models to accurately diagnose their own system's limitations.

## 19. Smallest Credible Characterization Set

Your instinct of "1 Conv + 1 FC + 1 End-to-End" is right for the
application level, but it is missing the foundational layer. To make a
cycle model truly trustworthy to an architecture committee, you must
bridge the gap between the bare silicon and the complex neural network.

The minimum credible set requires **four pillars**, all on the same
bitstream, validated by the PMU:

1. **The Microbenchmark (The Anchor)**: A synthetic, idealized kernel
   (e.g., a pure MAC loop with data pinned in local PE registers, or a
   pure DMA streaming loop). This proves your architectural peak and
   bandwidth roofline limits are real.
2. **The Compute-Bound Kernel (1 Conv Layer)**: Proves the spatial array
   can achieve high utilization when data reuse is present.
3. **The Memory-Bound Kernel (1 FC Layer)**: Exposes the interconnect/
   readout overhead and validates your diagnosis of the bottleneck.
4. **The End-to-End Workload**: Proves you understand system-level
   orchestration, bare-metal driver overhead, and cache coherency
   penalties (ACP/L2 interactions).

If your cycle-approximate model predicts all four of these **within a
5-10% margin of error against the silicon PMU**, your model is bulletproof.

## 20. "Why MNIST and not ImageNet?"

Do not use "ImageNet wouldn't fit" (sounds like a failure) or "Same
primitives" (sounds defensive). Frame the answer strictly around your
**Target Application Domain**.

The defense is: *"ImageNet is a datacenter and high-tier mobile benchmark;
this architecture targets the Deep Embedded Edge."*

Refer to industry standards like **MLPerf Tiny**. The benchmark suite for
ultra-low-power edge devices does not use ImageNet; it uses visual wake
words, keyword spotting, and anomaly detection — workloads roughly the
size and complexity of MNIST and LPR.

State that scaling up to ImageNet would require a massive L2/L3 memory
hierarchy and DDR bandwidth that fundamentally violates the Area and
Power constraints of your target domain. **You sized the CGRA for the
workloads it was meant to run.**

## 21. Workload-Count Rule of Thumb

**Three is the magic number** in architecture papers, provided those three
demonstrate **architectural diversity**. Your three workloads are actually
a highly compelling narrative:

- **MNIST CNN**: Demonstrates heavy spatial reuse and 2D dataflows.
- **LPR INT8 OCR**: Demonstrates sequence processing, irregular memory
  accesses, and likely exposes the memory-bound FC bottlenecks you
  diagnosed.
- **Kyber-512 Barrett**: This is your ace in the hole. Demonstrating Post-
  Quantum Cryptography (modular arithmetic, irregular control flow) on an
  architecture designed primarily for ML proves the "General" in Coarse-
  Grained Reconfigurable Architecture.

When presenting, explicitly state **why** you chose these three: not to
inflate the count, but because they stress the compute array, the memory
subsystem, and the functional unit flexibility in completely different ways.

## 22. Hetero Pipeline Visualization

Show **both**, but clearly label their distinct purposes. Never present an
unvalidated pipeline as your primary result; committees have a sharp eye
for theoretical projections masquerading as silicon results.

- **Step 1 (The Validation)**: Show the **serial waterfall** (CGRA-conv →
  CPU overhead → NEON-FC). Present this as your **Measured Execution**.
  It is honest, it matches your PMU data, and it highlights the exact
  percentage of time spent in orchestration versus compute.
- **Step 2 (The System Architecture Projection)**: Flip to the next slide
  showing the **parallel timeline** (Macro-Pipelining frame N and N+1).
  Present this as **"System-Level Scaling Opportunity."** Explain that
  because the CGRA and NEON operate in decoupled memory spaces (or
  through ping-pong buffers), the architecture naturally supports macro-
  pipelining.

This approach shows the committee that you are intellectually honest about
what you actually measured, but you possess the architectural maturity to
understand how software systems would exploit your hardware at scale.

## 23. 40-bit Accumulator: Perfect (The Goldilocks Zone)

**40 bits is neither oversized nor undersized; it is the industry-standard
sweet spot** for 16-bit ML and DSP workloads.

- **Why 32-bit is fatal**: An INT16 × INT16 multiplication yields a 32-bit
  (or 31-bit signed) product. If you use a 32-bit accumulator, you have
  zero guard bits. The very first accumulation of two maximum-value
  products will overflow.
- **The Math**: To safely accumulate N products without saturation, you
  need ⌈log₂(N)⌉ guard bits. Your 40-bit accumulator provides 8 guard
  bits above the 32-bit product. This allows 2⁸ = 256 consecutive MAC
  operations before saturation is mathematically possible.
- **Why 48-bit is overkill**: While Xilinx DSP48 slices use 48 bits, in an
  edge-AI ASIC context, routing an extra 8 bits of datapath through every
  multiplexer and register in the PE burns unnecessary dynamic power and
  area. Your 40-bit choice was perfectly sized for the 25-50 MAC tiles
  you are running.

## 24. 5-Port Router: Stick to the Mesh (with one caveat)

**Do not build a true crossbar for a v3 chip.** A full crossbar's area and
power scale quadratically (O(N²)). For a 16-PE array, a 16×16 crossbar will
completely dominate your PE logic area, create massive wire-routing
congestion in the back-end physical design, and severely degrade your Fmax.

The Compromise: The 2D Mesh (N/E/S/W/Local) is the **defining, scalable
characteristic** of a CGRA.

The Next-Rev Upgrade: If unicast-with-multicast is failing your workloads,
look at **Single-Cycle Multi-Hop routing (like the HyCUBE architecture)**.
It keeps the lightweight mesh topology but adds bypass multiplexers to the
routers, allowing data to traverse multiple PEs in a single clock cycle
without stopping at intermediate registers. It gives you crossbar-like
flexibility with mesh-like area.

## 25. Tile Memory: Move to (b) 8 banks × 2048

If you are accelerating ML workloads, bandwidth is king.

Your current 4-bank setup allows for standard double-buffering (Ping-Pong
Input, Ping-Pong Output). However, in modern GEMV/GEMM workloads, you often
need to **simultaneously** fetch Weights, fetch Activations, and read/write
Partial Sums.

Moving to 8 banks of 2048 gives you **double the read/write ports** into
the fabric. You can partition this into finer-grained data streams,
allowing your DMA to fill 4 banks while the CGRA simultaneously computes
out of the other 4 without arbitrating for the same SRAM macros. The cost
is a wider memory-to-CGRA interconnect crossbar, but the utilization boost
in your compute array will easily justify the area.

## 26. 4 KB SPM per PE: The Right Trade-off for Edge

4 KB per PE is highly defensible for an edge spatial accelerator.

- If you shrink it, you become **purely memory-bound**. You will spend all
  your time and energy shuttling weights from the L2/DDR into the PE,
  destroying the energy-efficiency argument of the CGRA.
- If you enlarge it (e.g., 16 KB per PE), you have effectively built a
  **distributed SRAM array with ALUs bolted on as an afterthought**. Your
  compute density (MACs per mm²) will plummet.

Holding 2K INT16 weights allows an entire tile of a Conv or FC layer to
remain stationary while activations stream past. For a broader workload
class like MatMul, 4 KB allows for efficient 32×32 block-matrix
multiplication, which fits nicely into standard loop-tiling algorithms.

## 27. CU_PC_END Programmability: Keep the APB Write

The 30-cycle APB latency tax is an illusion. **Keep the software-
programmable PC_END.**

- **Amdahl's Law**: If your kernel is so short that 30 ARM setup cycles
  meaningfully impact your end-to-end execution time, that workload should
  not be on the CGRA in the first place. Accelerators are for bulk offload.
- **The Cost of Hard-Coding**: If you hard-code the end and rely on NOP
  padding, you are wasting precious configuration memory (Instruction
  RAM). In CGRAs, the configuration SRAM is often the largest single
  component of the PE. Forcing the compiler to pad short loops with NOPs
  wastes power (clocking the memory to fetch NOPs) and wastes area. A
  programmable loop-bound register is a clean, standard architectural
  pattern for hardware loops.

## 28. Order of Measurements: Bottom-Up (Primitives First)

**Always go Primitives-First (Bottom-Up).** If you put the end-to-end
headline number on the screen first, you immediately invite attacks. A
committee member will look at the total latency, do some mental math
regarding your clock speed, and interrupt you to ask why it seems slow
(or suspiciously fast). You will spend the next 20 minutes on the
defensive, trying to explain the microarchitectural overheads out of
order.

By going Bottom-Up, you take them on a guided derivation of the truth:

1. **The Bare Metal**: "Here is a 100% MAC utilization microbenchmark. It
   perfectly matches our simulator." (Trust in tools established.)
2. **The Memory Bound**: "Here is a pure DMA streaming benchmark. We hit
   80% of theoretical AXI bandwidth." (Platform limits established.)
3. **The Layer Breakdown**: "Here is the Conv layer hitting the compute
   roof, and the FC layer hitting the memory roof." (Architectural
   reality established.)
4. **The End-to-End**: "Therefore, when we run the full pipeline, we see
   exactly the macroscopic behavior predicted by our primitive
   measurements."

By the time you show the headline number, **it is no longer a claim to be
debated; it is the inevitable mathematical conclusion of the previous
slides.**

## 29. PMU Sampling Granularity: The Two-Pass Method

You have correctly identified the "Observer Effect" in computer
architecture. Because reading the PL310 PMU over the APB bridge takes
dozens of cycles and stalls the pipeline, per-layer sampling will actively
**perturb the very memory/compute overlap you are trying to measure.**

The production solution is the **Two-Pass Method**:

1. **The "Clean" Pass**: Instrument only the start and end of the entire
   inference. This gives you the absolute, unperturbed "Headline Latency"
   and total energy consumption.
2. **The "Instrumented" Pass**: Run the exact same workload again, but
   with PMU reads between every layer. The total time of this run will be
   noticeably longer (due to the APB read overheads and pipeline flushes).
3. **The Synthesis**: You use the Instrumented Pass *only* to calculate
   the **proportional breakdown** (e.g., "Layer 1 took 20% of the cycles,
   Layer 2 took 30%"). You then apply those percentages to the **absolute
   time** measured in the Clean Pass to generate your final pie chart.

In your thesis methodology section, **explicitly state that you used a two-
pass approach** to decouple instrumentation overhead from absolute
performance measurements. Examiners love this level of rigor.

## 30. NEON Benchmark Fairness: Avoid the Strawman Trap

**You must use the production -O2+LTO (or -O3) build for the NEON baseline.**
If you compare a custom hardware accelerator against -O1 unoptimized
software, the committee will immediately accuse you of attacking a
"strawman." The fundamental justification for building custom silicon is
that the workload cannot run fast enough on a general-purpose processor,
**even when the software is perfectly optimized.**

To prove that your CGRA (or your heterogeneous split) is actually valuable,
you must give the CPU **every possible advantage**:

- Compile the NEON kernel with the highest optimization flags.
- If you are writing the C code yourself, ensure you are actually using
  **NEON intrinsics** (or a highly tuned library like QNNPACK), not just
  relying on the compiler's auto-vectorizer, which often fails on complex
  ML loops.
- If your -O1 baremetal codebase is causing linking issues with an -O3
  NEON kernel, **isolate the NEON kernel into its own compilation unit**,
  compile it aggressively, and link it in.

When you present the data, proudly state: *"We benchmarked against a
heavily optimized, -O3 compiled NEON baseline using explicit vector
intrinsics to ensure our hardware comparison was rigorously fair."* This
completely shields you from the most common attack in accelerator defenses.

## 31. One-Fabric vs. Two-Fabrics (Universal vs. Specialized)

**Build two specialized fabrics sharing a coherent Scratchpad Memory (SPM).**

Do not build a "universal" CGRA. The history of computer architecture is
littered with the corpses of "mode-bit" architectures that tried to be
everything to everyone and ended up being large, hot, and slow.

- A spatial array (your CGRA) relies on rigid, regular dataflows to keep
  control overhead near zero.
- Sparse and FC workloads require dynamic pointer chasing, scatter/gather
  memory accesses, and complex divergence.

If you force a CGRA PE to handle dynamic sparsity, you must add integer
address-generation ALUs, deep branch-target buffers, and massive crossbars
to every single PE. You will bloat your PE area by 3×, and your Conv
layers will pay the leakage power tax for hardware they never use.

**The Industry Standard**: Look at Apple's Neural Engine, Google's Edge
TPU, or the NVDLA. They all pair a rigid 2D MAC array (for Convs/GEMMs)
with a programmable Vector/Activation engine (for FC, sparse, and non-
linearities), coupled via a high-bandwidth shared SRAM.

## 32. FP16 vs. INT16 (The Precision Crossover)

Your intuition about dynamic range is correct, but the physical cost
crossover is brutal.

- **Area/Power Cost**: An FP16 MAC requires mantissa alignment (shifters),
  a multiplier, an adder, and a massive normalization step (leading zero
  detection and more shifting). In 28nm, an **FP16 MAC is roughly 3× to 4×
  larger and more power-hungry than a pure INT16 MAC.**
- **The Real Question**: Do you even need INT16? For edge inference, the
  industry has aggressively standardized on **INT8 weights and activations
  with an INT32 accumulator.**
- **When FP16 wins**: FP16/BF16 is only required if you are doing on-
  device training/fine-tuning (where gradients require massive dynamic
  range) or running specific Transformer architectures without aggressive
  post-training quantization. For a v3 **edge inference** chip, stick to
  integer arithmetic.

## 33. ASIC Migration (What breaks when you leave the FPGA)

FPGAs hide a lot of sins. When you move to a 28nm standard-cell ASIC,
three major things will break:

1. **Distributed Memory Overhead**: On an FPGA, 16-deep configuration RAM
   per PE uses tiny LUTRAMs that are basically free. On an ASIC, SRAM
   macros have a minimum physical size and massive peripheral overhead
   (sense amps, address decoders). A 16×32b SRAM macro is incredibly
   area-inefficient. **The Delta**: You must either implement the config
   RAM using discrete flip-flops (expensive in power/area) or consolidate
   the config memory into one larger SRAM macro per column/array and
   broadcast the instructions.
2. **Wide Routing Congestion**: A 64-bit config word broadcast to 16 PEs
   creates a massive routing web. FPGAs have pre-fabricated routing
   tracks; ASICs require the synthesis tool to weave those wires over
   your logic. **The Delta**: You will likely suffer severe routing
   congestion. You must serialize the configuration loading or encode/
   compress the instructions.
3. **Clock Tree Synthesis (CTS)**: FPGAs have perfect, dedicated global
   clock networks. On an ASIC, you have to build the clock tree yourself.
   If your PEs have deeply nested clock gating or weird asynchronous
   resets, the CTS tools will fail to balance the skew.

## 34. Power Domains: Clock Gating vs. Voltage Scaling

**Per-PE Clock Gating is mandatory. Fine-grained Voltage Scaling is a
trap.**

- **Dynamic Clock Gating (ICG)**: It is incredibly cheap on an ASIC. The
  synthesis tool (e.g., Genus or Design Compiler) automatically inserts
  Integrated Clock Gating (ICG) cells. If you add an enable signal to your
  PE, the tool will turn off the clock tree to the entire PE's datapath.
  The routing complexity is negligible, and **it instantly drops dynamic
  power by 95% for idle PEs**.
- **Fine-Grained Voltage Scaling**: Having multiple voltage domains
  requires physical separation, isolation cells to prevent floating
  nodes, level shifters on every wire crossing domains, and multiple
  power grid meshes. **It will destroy your floorplan and your tape-out
  schedule.** Use a single voltage domain, but aggressively clock-gate.

## 35. The "Next Workload" Question

If you want the v3 chip to be a thesis-defining, highly relevant
architecture for the late 2020s, **optimize for GEMM (Transformer
Attention).**

- MNIST and standard CNNs are solved problems.
- Post-Quantum Crypto (NTT) is highly niche and best served by a specific
  co-processor.
- SNNs are academically interesting but have continually failed to
  displace standard ANNs in commercial edge devices due to training
  difficulties and lack of software infrastructure.
- **Transformers on the Edge**: Vision Transformers (ViTs) and small Large
  Language Models (like Llama-3-8B or MobileBERT) are moving aggressively
  to the edge. Optimizing your CGRA to handle matrix-matrix multiplication
  (GEMM), while using your secondary fabric (or ARM NEON) to handle the
  Softmax and LayerNorm functions, puts your research exactly where the
  commercial semiconductor industry is currently bleeding.
