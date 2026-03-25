/* ===================================================================
 *  dump_cgra_hex.c – CGRA $readmemh Hex Dump Utility
 *
 *  Generates three SystemVerilog $readmemh-compatible files capturing
 *  the exact data that lpr_cgra_accel.c would DMA into the CGRA for
 *  group 0 of one character inference (synthetic image 0, seed 0xCAFEBABE).
 *
 *  No hardware dependency — runs on any Linux (x86 or ARM).
 *
 *  Outputs (written to OUTPUT_DIR, default ../01_bench/):
 *    config.mem  – 64-bit PE config words; 256 entries per chunk × 61 chunks
 *    image.mem   – 32-bit tile input words; 16 entries per chunk × 61 chunks
 *    golden.mem  – 4 × 32-bit raw accumulators for group 0 (pre-dequant)
 *
 *  Usage:
 *    ./dump_cgra_hex                    # writes to ../01_bench/
 *    ./dump_cgra_hex /path/to/outdir/   # writes to specified directory
 * =================================================================== */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <sys/stat.h>

#include "../lib/lpr_golden.h"

/* ── CGRA Architecture Constants (must match lpr_cgra_accel.c) ───── */

#define CGRA_ROWS           4
#define CGRA_COLS           4
#define CGRA_NUM_PES        (CGRA_ROWS * CGRA_COLS)
#define CONTEXT_DEPTH       16
#define DRAIN_CYCLES        3
#define MAC_PER_RUN         (CONTEXT_DEPTH - DRAIN_CYCLES)   /* 13 */

/* PE ISA */
#define OP_NOP              0
#define OP_MAC              4
#define OP_PASS0            16

#define SRC_WEST            4
#define SRC_IMM             6

#define ROUTE_EAST          0x4u

/* DMA buffer sizing */
#define CFG_BUF_WORDS       (CGRA_NUM_PES * CONTEXT_DEPTH * 2)  /* 512 */
#define CFG_BUF_BYTES       (CFG_BUF_WORDS * sizeof(uint32_t))  /* 2048 */

/* Quantization */
#define QUANT_SCALE         256
#define QUANT_SHIFT         8

/* ── PE 64-bit Config Word Builder ───────────────────────────────── */

static inline uint64_t pe_config(uint8_t op, uint8_t src0, uint8_t src1,
                                 uint8_t dst, uint8_t route, int16_t imm)
{
    uint64_t w = 0;
    w |= (uint64_t)(op    & 0x3F);
    w |= (uint64_t)(src0  & 0x0F) << 6;
    w |= (uint64_t)(src1  & 0x0F) << 10;
    w |= (uint64_t)(dst   & 0x0F) << 14;
    w |= (uint64_t)(route & 0x0F) << 18;
    w |= (uint64_t)((uint16_t)imm) << 24;
    return w;
}

/* ── Config Buffer Builder (identical to lpr_cgra_accel.c) ──────── */

static void build_fc_config(uint32_t *buf,
                            const int32_t wt[4][MAC_PER_RUN],
                            int mac_count)
{
    memset(buf, 0, CFG_BUF_BYTES);

    for (int pe = 0; pe < CGRA_NUM_PES; pe++) {
        int row = pe / CGRA_COLS;
        int col = pe % CGRA_COLS;

        for (int ctx = 0; ctx < CONTEXT_DEPTH; ctx++) {
            uint64_t cw;

            if (col == 0) {
                if (ctx < mac_count)
                    cw = pe_config(OP_MAC, SRC_WEST, SRC_IMM, 0,
                                   ROUTE_EAST, (int16_t)wt[row][ctx]);
                else
                    cw = pe_config(OP_NOP, 0, 0, 0, ROUTE_EAST, 0);
            } else {
                if (ctx >= mac_count)
                    cw = pe_config(OP_PASS0, SRC_WEST, 0, 0, ROUTE_EAST, 0);
                else
                    cw = pe_config(OP_NOP, 0, 0, 0, ROUTE_EAST, 0);
            }

            int idx = (pe * CONTEXT_DEPTH + ctx) * 2;
            buf[idx + 0] = (uint32_t)(cw >> 32);
            buf[idx + 1] = (uint32_t)(cw & 0xFFFFFFFFu);
        }
    }
}

/* ── Quantization (identical to lpr_cgra_accel.c) ────────────────── */

static inline int32_t quantize_act(float x)
{
    int32_t q = (int32_t)roundf(x * QUANT_SCALE);
    if (q >  32767) q =  32767;
    if (q < -32768) q = -32768;
    return q;
}

static inline int32_t quantize_wt(float x)
{
    int32_t q = (int32_t)roundf(x);
    if (q >  127) q =  127;
    if (q < -128) q = -128;
    return q;
}

static void quantize_activations(const int32_t *in, int32_t *out, int n)
{
    for (int i = 0; i < n; i++)
        out[i] = quantize_act((float)in[i]);
}

static void quantize_weight_matrix(const int32_t *in, int32_t *out, int n)
{
    for (int i = 0; i < n; i++)
        out[i] = quantize_wt((float)in[i]);
}

/* ── Test Image Generator (identical to lpr_cgra_accel.c) ────────── */

static void gen_test_image(int32_t *img, int idx)
{
    uint32_t rng = (uint32_t)(idx * 2654435761u + 1);
    int n = GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C;
    for (int i = 0; i < n; i++) {
        rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
        img[i] = (int32_t)(rng & 0xFF);
    }
}

/* ── Main ────────────────────────────────────────────────────────── */

int main(int argc, char *argv[])
{
    const char *out_dir = (argc > 1) ? argv[1] : "../01_bench/";

    printf("========================================\n");
    printf("  CGRA Hex Dump Utility\n");
    printf("  Group 0, Image 0, Seed 0xCAFEBABE\n");
    printf("  Output dir: %s\n", out_dir);
    printf("========================================\n\n");

    /* ── Ensure output directory exists ──────────────────────────── */
    {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "mkdir -p %s", out_dir);
        if (system(cmd) != 0)
            fprintf(stderr, "Warning: mkdir -p %s failed\n", out_dir);
    }

    /* ── Allocate and initialize weights ─────────────────────────── */
    GoldenWeights *gw   = (GoldenWeights *)malloc(sizeof(GoldenWeights));
    GoldenContext *gctx = (GoldenContext *)calloc(1, sizeof(GoldenContext));
    if (!gw || !gctx) { fprintf(stderr, "malloc failed\n"); return 1; }

    golden_weights_init_synthetic(gw, 0xCAFEBABE);
    golden_context_init(gctx, NULL, NULL);

    /* ── Allocate FC buffers ──────────────────────────────────────── */
    const int fc_in  = GOLDEN_FC_IN;    /* 784 */
    const int fc_out = GOLDEN_FC_OUT;   /* 30  */

    int32_t *fc_w_q     = (int32_t *)malloc(fc_in * fc_out * sizeof(int32_t));
    int32_t *fc_input_q = (int32_t *)calloc(fc_in, sizeof(int32_t));
    int32_t *input_img  = (int32_t *)calloc(GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C,
                                            sizeof(int32_t));
    uint32_t *cfg_buf   = (uint32_t *)malloc(CFG_BUF_BYTES);

    if (!fc_w_q || !fc_input_q || !input_img || !cfg_buf) {
        fprintf(stderr, "malloc failed\n"); return 1;
    }

    /* ── Generate image 0 + run ARM CNN layers ───────────────────── */
    gen_test_image(input_img, 0);

    golden_conv2d_relu(input_img, gctx->conv1_out,
                       gw->conv1_w, gw->conv1_b,
                       GOLDEN_IN_H, GOLDEN_IN_W,
                       GOLDEN_IN_C, GOLDEN_CONV1_OUT_CH,
                       GOLDEN_CONV1_KH, GOLDEN_CONV1_KW,
                       GOLDEN_CONV1_PAD, GOLDEN_CONV1_STRIDE);

    golden_maxpool_2x2(gctx->conv1_out, gctx->pool1_out,
                       GOLDEN_IN_H, GOLDEN_IN_W, GOLDEN_CONV1_OUT_CH);

    golden_conv2d_relu(gctx->pool1_out, gctx->conv2_out,
                       gw->conv2_w, gw->conv2_b,
                       GOLDEN_POOL1_H, GOLDEN_POOL1_W,
                       GOLDEN_CONV2_IN_CH, GOLDEN_CONV2_OUT_CH,
                       GOLDEN_CONV2_KH, GOLDEN_CONV2_KW,
                       GOLDEN_CONV2_PAD, GOLDEN_CONV2_STRIDE);

    golden_maxpool_2x2(gctx->conv2_out, gctx->pool2_out,
                       GOLDEN_POOL1_H, GOLDEN_POOL1_W, GOLDEN_CONV2_OUT_CH);

    /* ── Quantize FC inputs and weights ──────────────────────────── */
    quantize_activations(gctx->pool2_out, fc_input_q, fc_in);
    quantize_weight_matrix(gw->fc_w, fc_w_q, fc_in * fc_out);

    printf("[QUANT] FC activations: %d INT16 values (Q8.8)\n", fc_in);
    printf("[QUANT] FC weights:     %dx%d INT8\n", fc_in, fc_out);

    /* ── Open output files ───────────────────────────────────────── */
    char path_cfg[512], path_img[512], path_gld[512];
    snprintf(path_cfg, sizeof(path_cfg), "%sconfig.mem", out_dir);
    snprintf(path_img, sizeof(path_img), "%simage.mem",  out_dir);
    snprintf(path_gld, sizeof(path_gld), "%sgolden.mem", out_dir);

    FILE *f_cfg = fopen(path_cfg, "w");
    FILE *f_img = fopen(path_img, "w");
    FILE *f_gld = fopen(path_gld, "w");

    if (!f_cfg || !f_img || !f_gld) {
        fprintf(stderr, "Failed to open output files in %s\n", out_dir);
        return 1;
    }

    /* ── config.mem header ───────────────────────────────────────── */
    fprintf(f_cfg,
        "// config.mem — CGRA PE config words for FC group 0\n"
        "// Image 0, seed 0xCAFEBABE, 61 chunks, 256 words/chunk\n"
        "// Word width: 64-bit  ($readmemh into reg [63:0] mem[0:15615])\n"
        "// Layout: 16 PEs × 16 contexts, PE order col-major (PE=row*4+col)\n"
        "// Each ctx entry: [63:0] = full 64-bit PE config word\n"
        "//   [5:0]=opcode [9:6]=src0 [13:10]=src1 [17:14]=dst\n"
        "//   [21:18]=route [39:24]=imm16 (INT8 weight in MAC ctx)\n"
        "//\n");

    /* ── image.mem header ────────────────────────────────────────── */
    fprintf(f_img,
        "// image.mem — CGRA tile memory input for FC group 0\n"
        "// Image 0, seed 0xCAFEBABE, 61 chunks, 16 words/chunk\n"
        "// Word width: 32-bit  ($readmemh into reg [31:0] mem[0:975])\n"
        "// All 4 tile banks receive identical data (same fc_input_q slice)\n"
        "// Address ctx within bank = context_pc (0-15)\n"
        "//\n");

    /* ── golden.mem header ───────────────────────────────────────── */
    fprintf(f_gld,
        "// golden.mem — CGRA expected raw accumulators for FC group 0\n"
        "// Image 0, seed 0xCAFEBABE\n"
        "// Word width: 32-bit  ($readmemh into reg [31:0] mem[0:3])\n"
        "// Values are pre-dequant (no >>8) and pre-bias: raw Σ(act*wt)\n"
        "// Row 0 → class 0 ('1'), Row 1 → class 1 ('2'), etc.\n"
        "//\n");

    /* ── Group 0 chunk loop ──────────────────────────────────────── */
    int n_chunks = (fc_in + MAC_PER_RUN - 1) / MAC_PER_RUN;  /* 61 */

    printf("\n[DUMP] Writing group 0, %d chunks ...\n", n_chunks);

    for (int k = 0; k < n_chunks; k++) {
        int base  = k * MAC_PER_RUN;
        int count = (base + MAC_PER_RUN <= fc_in)
                  ? MAC_PER_RUN : fc_in - base;

        /* ── Build chunk_wt for g=0 (oidx = row 0-3) ─────────────── */
        int32_t chunk_wt[CGRA_ROWS][MAC_PER_RUN];
        memset(chunk_wt, 0, sizeof(chunk_wt));
        for (int r = 0; r < CGRA_ROWS; r++) {
            int oidx = r;   /* g=0, so output class = row index */
            for (int c = 0; c < count; c++)
                chunk_wt[r][c] = fc_w_q[(base + c) * fc_out + oidx];
        }

        /* ── Build config buffer ──────────────────────────────────── */
        build_fc_config(cfg_buf, chunk_wt, count);

        /* ── Write config.mem ─────────────────────────────────────── */
        fprintf(f_cfg, "// --- chunk %d  base=%d  count=%d ---\n",
                k, base, count);
        fprintf(f_cfg, "@%04X\n", k * 256);

        for (int i = 0; i < CGRA_NUM_PES * CONTEXT_DEPTH; i++) {
            /* Reconstruct 64-bit from [hi, lo] pair */
            uint64_t word64 = ((uint64_t)cfg_buf[i * 2] << 32)
                            | (uint64_t)cfg_buf[i * 2 + 1];
            int pe  = i / CONTEXT_DEPTH;
            int ctx = i % CONTEXT_DEPTH;
            fprintf(f_cfg, "%016llX  // PE%02d ctx%02d\n",
                    (unsigned long long)word64, pe, ctx);
        }
        fprintf(f_cfg, "\n");

        /* ── Write image.mem ──────────────────────────────────────── */
        fprintf(f_img, "// --- chunk %d  base=%d  count=%d ---\n",
                k, base, count);
        fprintf(f_img, "@%04X\n", k * 16);

        for (int c = 0; c < CONTEXT_DEPTH; c++) {
            int si = base + c;
            int32_t val = (c < count && si < fc_in) ? fc_input_q[si] : 0;
            fprintf(f_img, "%08X  // ctx%02d  input_q[%d]=%d\n",
                    (uint32_t)val, c, si, val);
        }
        fprintf(f_img, "\n");
    }

    /* ── Compute golden.mem: raw accumulators for g=0 ────────────── */
    int64_t acc[CGRA_ROWS] = {0, 0, 0, 0};

    for (int i = 0; i < fc_in; i++) {
        for (int r = 0; r < CGRA_ROWS; r++) {
            int oidx = r;   /* g=0 */
            acc[r] += (int64_t)fc_input_q[i] * (int64_t)fc_w_q[i * fc_out + oidx];
        }
    }

    for (int r = 0; r < CGRA_ROWS; r++) {
        uint32_t raw = (uint32_t)(int32_t)acc[r];
        fprintf(f_gld, "%08X  // row%d class%d ('%c')  raw=%lld  >>8=%lld\n",
                raw, r, r, VN_CHAR_MAP[r],
                (long long)acc[r],
                (long long)(acc[r] >> QUANT_SHIFT));
    }

    fclose(f_cfg);
    fclose(f_img);
    fclose(f_gld);

    /* ── Summary ─────────────────────────────────────────────────── */
    printf("\n[DONE] Files written:\n");
    printf("  %s\n", path_cfg);
    printf("    %d chunks × 256 entries = %d config words (64-bit)\n",
           n_chunks, n_chunks * 256);
    printf("  %s\n", path_img);
    printf("    %d chunks × 16 entries = %d tile words (32-bit)\n",
           n_chunks, n_chunks * 16);
    printf("  %s\n", path_gld);
    printf("    4 raw accumulators for group 0 (classes 0-3)\n");

    printf("\n[GOLDEN] Group 0 raw accumulators (pre-dequant):\n");
    for (int r = 0; r < CGRA_ROWS; r++) {
        printf("  Row %d  class %d ('%c') : raw=%-12lld  >>8=%lld\n",
               r, r, VN_CHAR_MAP[r],
               (long long)acc[r],
               (long long)(acc[r] >> QUANT_SHIFT));
    }

    printf("\n[SV] $readmemh usage example:\n");
    printf("  reg [63:0] config_ram [0:%d];\n", n_chunks * 256 - 1);
    printf("  reg [31:0] tile_ram   [0:%d];\n", n_chunks * 16  - 1);
    printf("  reg [31:0] expected   [0:3];\n");
    printf("  initial begin\n");
    printf("    $readmemh(\"config.mem\", config_ram);\n");
    printf("    $readmemh(\"image.mem\",  tile_ram);\n");
    printf("    $readmemh(\"golden.mem\", expected);\n");
    printf("  end\n");

    free(gw);        free(gctx);
    free(fc_w_q);    free(fc_input_q);
    free(input_img); free(cfg_buf);

    return 0;
}
