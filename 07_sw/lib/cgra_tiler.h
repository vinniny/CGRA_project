/* ===================================================================
 *  cgra_tiler.h – Im2Col + CSC conversion library for CGRA LPR demo
 *
 *  Provides:
 *    1.  im2col_nhwc()     – Standard Im2Col for convolution layers
 *    2.  im2col_4x4_tile() – Tile-aware Im2Col producing 4-row chunks
 *                            matched to the 4×4 CGRA west-edge input
 *    3.  dense_to_csc()    – Dense matrix → Compressed Sparse Column
 *    4.  csc_free()        – Release CSC buffers
 *    5.  csc_spmv_sw()     – Software SpMV (for validation / fallback)
 * =================================================================== */

#ifndef CGRA_TILER_H
#define CGRA_TILER_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Im2Col ──────────────────────────────────────────────────────── */

/**
 * im2col_nhwc – Full NHWC Im2Col transform.
 *
 * Converts a 2-D feature map (H × W × C) with a kernel (KH × KW)
 * into a column matrix suitable for GEMM-based convolution:
 *
 *   out_rows = (H - KH + 2*pad) / stride + 1
 *   out_cols = (W - KW + 2*pad) / stride + 1
 *   col rows = KH * KW * C
 *   col cols = out_rows * out_cols
 *
 * @param data_im   Input feature map, NHWC layout (int32).
 * @param C         Number of input channels.
 * @param H         Input height.
 * @param W         Input width.
 * @param KH        Kernel height.
 * @param KW        Kernel width.
 * @param pad       Zero-padding on each side.
 * @param stride    Convolution stride.
 * @param data_col  Output column buffer (caller-allocated).
 *                  Size: KH*KW*C × out_rows*out_cols int32 values.
 */
void im2col_nhwc(const int32_t *data_im,
                 int C, int H, int W,
                 int KH, int KW,
                 int pad, int stride,
                 int32_t *data_col);

/**
 * im2col_4x4_tile – Produce 4-row tiles for CGRA west-edge streaming.
 *
 * Wraps im2col_nhwc then slices the column matrix into 4-row strips
 * (matching the 4 west-edge inputs of the 4×4 CGRA array).
 *
 * @param data_im   Input feature map.
 * @param C, H, W   Channel, height, width.
 * @param KH, KW    Kernel size.
 * @param pad, stride  Convolution parameters.
 * @param tiles     Output: pointer set to heap-allocated tile array.
 *                  Each tile is 4 × tile_cols int32 values, row-major.
 * @param n_tiles   Output: number of 4-row tiles produced.
 * @param tile_cols Output: number of columns per tile.
 * Returns 0 on success, -1 on allocation failure.
 *
 * Caller must free(*tiles) when done.
 */
int im2col_4x4_tile(const int32_t *data_im,
                    int C, int H, int W,
                    int KH, int KW,
                    int pad, int stride,
                    int32_t **tiles,
                    int *n_tiles,
                    int *tile_cols);

/* ── Compressed Sparse Column (CSC) ─────────────────────────────── */

/**
 * CSC format:
 *   values[nnz]      – Non-zero values.
 *   row_idx[nnz]     – Row index of each non-zero.
 *   col_ptr[ncols+1] – Start offset in values[] for each column.
 */
typedef struct {
    int32_t  *values;
    int      *row_idx;
    int      *col_ptr;
    int       nrows;
    int       ncols;
    int       nnz;
} cgra_csc_t;

/**
 * dense_to_csc – Convert a dense row-major matrix to CSC format.
 *
 * @param dense   Row-major matrix, nrows × ncols.
 * @param nrows   Number of rows.
 * @param ncols   Number of columns.
 * @param out     Pointer to CSC descriptor (filled on success).
 * Returns 0 on success, -1 on allocation failure.
 */
int dense_to_csc(const int32_t *dense, int nrows, int ncols,
                 cgra_csc_t *out);

/**
 * csc_free – Release all buffers inside a CSC descriptor.
 */
void csc_free(cgra_csc_t *csc);

/**
 * csc_spmv_sw – Software sparse matrix-vector multiply (CSC).
 *
 * y[nrows] = A_csc * x[ncols]
 *
 * @param csc  CSC matrix descriptor.
 * @param x    Dense input vector, length = csc->ncols.
 * @param y    Dense output vector, length = csc->nrows (zeroed first).
 */
void csc_spmv_sw(const cgra_csc_t *csc, const int32_t *x, int32_t *y);

/* ── Utility ─────────────────────────────────────────────────────── */

/**
 * matmul_sw – Software dense matrix multiply C = A × B.
 *
 * A: M×K, B: K×N, C: M×N.  All row-major int32.
 */
void matmul_sw(const int32_t *A, const int32_t *B, int32_t *C,
               int M, int K, int N);

#ifdef __cplusplus
}
#endif

#endif /* CGRA_TILER_H */
