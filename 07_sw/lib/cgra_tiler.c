/* ===================================================================
 *  cgra_tiler.c – Im2Col + CSC conversion library implementation
 * =================================================================== */

#include "cgra_tiler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ── Im2Col (NHWC layout) ────────────────────────────────────────── */

void im2col_nhwc(const int32_t *data_im,
                 int C, int H, int W,
                 int KH, int KW,
                 int pad, int stride,
                 int32_t *data_col)
{
    int out_h = (H - KH + 2 * pad) / stride + 1;
    int out_w = (W - KW + 2 * pad) / stride + 1;
    int col_rows = KH * KW * C;
    /* data_col layout: col_rows × (out_h * out_w), row-major */

    for (int oh = 0; oh < out_h; oh++) {
        for (int ow = 0; ow < out_w; ow++) {
            int col_idx = oh * out_w + ow;   /* Column in output */
            int row = 0;
            for (int kh = 0; kh < KH; kh++) {
                for (int kw = 0; kw < KW; kw++) {
                    int ih = oh * stride - pad + kh;
                    int iw = ow * stride - pad + kw;
                    for (int c = 0; c < C; c++) {
                        int32_t val = 0;
                        if (ih >= 0 && ih < H && iw >= 0 && iw < W) {
                            /* NHWC: index = (ih * W + iw) * C + c */
                            val = data_im[(ih * W + iw) * C + c];
                        }
                        data_col[row * (out_h * out_w) + col_idx] = val;
                        row++;
                    }
                }
            }
            (void)col_rows;  /* Suppress unused warning */
        }
    }
}

/* ── 4-row tiled Im2Col ──────────────────────────────────────────── */

int im2col_4x4_tile(const int32_t *data_im,
                    int C, int H, int W,
                    int KH, int KW,
                    int pad, int stride,
                    int32_t **tiles,
                    int *n_tiles,
                    int *tile_cols)
{
    int out_h = (H - KH + 2 * pad) / stride + 1;
    int out_w = (W - KW + 2 * pad) / stride + 1;
    int total_rows = KH * KW * C;
    int total_cols = out_h * out_w;

    /* Full Im2Col into temporary buffer */
    int32_t *col = (int32_t *)calloc((size_t)total_rows * total_cols,
                                      sizeof(int32_t));
    if (!col) return -1;

    im2col_nhwc(data_im, C, H, W, KH, KW, pad, stride, col);

    /* Slice into 4-row tiles; last tile zero-padded if needed */
    int nt = (total_rows + 3) / 4;
    int32_t *tile_buf = (int32_t *)calloc((size_t)nt * 4 * total_cols,
                                           sizeof(int32_t));
    if (!tile_buf) { free(col); return -1; }

    for (int t = 0; t < nt; t++) {
        for (int r = 0; r < 4; r++) {
            int src_row = t * 4 + r;
            int32_t *dst = tile_buf + (size_t)(t * 4 + r) * total_cols;
            if (src_row < total_rows) {
                memcpy(dst,
                       col + (size_t)src_row * total_cols,
                       (size_t)total_cols * sizeof(int32_t));
            }
            /* else: remains zero from calloc */
        }
    }

    free(col);

    *tiles     = tile_buf;
    *n_tiles   = nt;
    *tile_cols = total_cols;
    return 0;
}

/* ── Dense to CSC ────────────────────────────────────────────────── */

int dense_to_csc(const int32_t *dense, int nrows, int ncols,
                 cgra_csc_t *out)
{
    if (!dense || !out || nrows <= 0 || ncols <= 0) return -1;
    memset(out, 0, sizeof(*out));

    /* Pass 1: count non-zeros per column */
    int *col_count = (int *)calloc(ncols, sizeof(int));
    if (!col_count) return -1;

    int nnz = 0;
    for (int j = 0; j < ncols; j++) {
        for (int i = 0; i < nrows; i++) {
            if (dense[i * ncols + j] != 0) {
                col_count[j]++;
                nnz++;
            }
        }
    }

    /* Allocate CSC arrays */
    int32_t *values  = (int32_t *)malloc((size_t)nnz * sizeof(int32_t));
    int     *row_idx = (int *)malloc((size_t)nnz * sizeof(int));
    int     *col_ptr = (int *)malloc((size_t)(ncols + 1) * sizeof(int));
    if (!values || !row_idx || !col_ptr) {
        free(col_count); free(values); free(row_idx); free(col_ptr);
        return -1;
    }

    /* Build col_ptr (cumulative sum of col_count) */
    col_ptr[0] = 0;
    for (int j = 0; j < ncols; j++)
        col_ptr[j + 1] = col_ptr[j] + col_count[j];

    /* Pass 2: fill values and row_idx */
    int *pos = (int *)calloc(ncols, sizeof(int));  /* Per-column write pointer */
    if (!pos) {
        free(col_count); free(values); free(row_idx); free(col_ptr);
        return -1;
    }

    for (int j = 0; j < ncols; j++) {
        for (int i = 0; i < nrows; i++) {
            int32_t v = dense[i * ncols + j];
            if (v != 0) {
                int idx = col_ptr[j] + pos[j];
                values[idx]  = v;
                row_idx[idx] = i;
                pos[j]++;
            }
        }
    }

    free(col_count);
    free(pos);

    out->values  = values;
    out->row_idx = row_idx;
    out->col_ptr = col_ptr;
    out->nrows   = nrows;
    out->ncols   = ncols;
    out->nnz     = nnz;
    return 0;
}

void csc_free(cgra_csc_t *csc)
{
    if (!csc) return;
    free(csc->values);
    free(csc->row_idx);
    free(csc->col_ptr);
    memset(csc, 0, sizeof(*csc));
}

/* ── Software SpMV (CSC) ────────────────────────────────────────── */

void csc_spmv_sw(const cgra_csc_t *csc, const int32_t *x, int32_t *y)
{
    memset(y, 0, (size_t)csc->nrows * sizeof(int32_t));

    for (int j = 0; j < csc->ncols; j++) {
        int32_t xj = x[j];
        if (xj == 0) continue;  /* Skip zero multiplications */
        for (int k = csc->col_ptr[j]; k < csc->col_ptr[j + 1]; k++) {
            y[csc->row_idx[k]] += csc->values[k] * xj;
        }
    }
}

/* ── Software MatMul (dense, for reference / validation) ─────── */

void matmul_sw(const int32_t *A, const int32_t *B, int32_t *C,
               int M, int K, int N)
{
    memset(C, 0, (size_t)M * N * sizeof(int32_t));
    for (int i = 0; i < M; i++) {
        for (int k = 0; k < K; k++) {
            int32_t a_ik = A[i * K + k];
            if (a_ik == 0) continue;
            for (int j = 0; j < N; j++) {
                C[i * N + j] += a_ik * B[k * N + j];
            }
        }
    }
}
