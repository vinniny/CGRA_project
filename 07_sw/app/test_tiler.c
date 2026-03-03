/* ===================================================================
 *  test_tiler.c – Standalone unit test for Im2Col and CSC library
 *
 *  Runs without CGRA hardware – validates software tiling logic.
 *  Build: make test_tiler
 *  Run:   ./build/test_tiler
 * =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "../lib/cgra_tiler.h"

#define PASS "\033[32mPASS\033[0m"
#define FAIL "\033[31mFAIL\033[0m"

static int tests_run = 0, tests_pass = 0;

#define CHECK(cond, msg) do { \
    tests_run++; \
    if (cond) { printf("  [%s] %s\n", PASS, msg); tests_pass++; } \
    else      { printf("  [%s] %s\n", FAIL, msg); } \
} while (0)

/* ── Test 1: Im2Col basic 4×4 image, 3×3 kernel ─────────────── */
static void test_im2col_basic(void)
{
    printf("\n--- Test: Im2Col basic (4x4, k=3, pad=1, stride=1) ---\n");

    int H = 4, W = 4, C = 1, KH = 3, KW = 3, pad = 1, stride = 1;
    int out_h = (H - KH + 2*pad)/stride + 1;  /* 4 */
    int out_w = (W - KW + 2*pad)/stride + 1;  /* 4 */
    int col_rows = KH * KW * C;  /* 9 */
    int col_cols = out_h * out_w; /* 16 */

    int32_t img[16];
    for (int i = 0; i < 16; i++) img[i] = i + 1;

    int32_t *col = (int32_t *)calloc(col_rows * col_cols, sizeof(int32_t));
    im2col_nhwc(img, C, H, W, KH, KW, pad, stride, col);

    CHECK(out_h == 4, "output height == 4");
    CHECK(out_w == 4, "output width == 4");
    CHECK(col_rows == 9, "col rows (K*K*C) == 9");

    /* Center element (1,1) should have full 3×3 neighborhood */
    /* col[:,5] = column for output position (1,1) */
    /* Top-left of 3×3 at input (0,0): values 1,2,3,5,6,7,9,10,11 */
    int32_t expected_center[] = {1, 2, 3, 5, 6, 7, 9, 10, 11};
    int match = 1;
    for (int r = 0; r < 9; r++) {
        if (col[r * col_cols + 5] != expected_center[r]) match = 0;
    }
    CHECK(match, "center patch (1,1) correct");

    /* Corner (0,0) should have zero-padding */
    CHECK(col[0 * col_cols + 0] == 0, "top-left corner has padding zeros");

    free(col);
}

/* ── Test 2: 4-row tiling ──────────────────────────────────────── */
static void test_4x4_tiling(void)
{
    printf("\n--- Test: 4-row tiling ---\n");

    int H = 4, W = 4, C = 1, KH = 3, KW = 3, pad = 1, stride = 1;
    int32_t img[16];
    for (int i = 0; i < 16; i++) img[i] = i + 1;

    int32_t *tiles = NULL;
    int n_tiles = 0, tile_cols = 0;

    int rc = im2col_4x4_tile(img, C, H, W, KH, KW, pad, stride,
                              &tiles, &n_tiles, &tile_cols);

    CHECK(rc == 0, "im2col_4x4_tile returned success");
    CHECK(n_tiles > 0, "at least 1 tile produced");
    CHECK(tile_cols == 16, "tile_cols == 16 (4×4 output)");

    int total_rows = KH * KW * C;  /* 9 */
    int expected_tiles = (total_rows + 3) / 4;  /* 3 */
    CHECK(n_tiles == expected_tiles, "n_tiles == ceil(9/4) == 3");

    /* Last tile should have zero-padded rows */
    /* Tile 2 has rows 8,9(pad),10(pad),11(pad) → only row 8 has data */
    int last_tile_data_rows = total_rows - (n_tiles - 1) * 4;  /* 1 */
    CHECK(last_tile_data_rows == 1, "last tile has 1 real row + 3 padded");

    /* Verify padding in last tile row 1 (should be all zeros) */
    int pad_row_start = ((n_tiles - 1) * 4 + 1) * tile_cols;
    int all_zero = 1;
    for (int j = 0; j < tile_cols; j++)
        if (tiles[pad_row_start + j] != 0) all_zero = 0;
    CHECK(all_zero, "last tile padded row is all zeros");

    free(tiles);
}

/* ── Test 3: Dense to CSC conversion ─────────────────────────── */
static void test_dense_to_csc(void)
{
    printf("\n--- Test: Dense to CSC ---\n");

    /* 3×4 matrix with known sparsity */
    int32_t dense[] = {
        1, 0, 2, 0,
        0, 3, 0, 4,
        5, 0, 6, 0
    };
    int nrows = 3, ncols = 4;

    cgra_csc_t csc;
    int rc = dense_to_csc(dense, nrows, ncols, &csc);

    CHECK(rc == 0, "dense_to_csc returned success");
    CHECK(csc.nrows == 3, "nrows == 3");
    CHECK(csc.ncols == 4, "ncols == 4");
    CHECK(csc.nnz == 6, "nnz == 6 (6 non-zero elements)");

    /* Verify col_ptr */
    CHECK(csc.col_ptr[0] == 0, "col_ptr[0] == 0");
    CHECK(csc.col_ptr[1] == 2, "col_ptr[1] == 2 (col 0 has 2 nnz)");
    CHECK(csc.col_ptr[2] == 3, "col_ptr[2] == 3 (col 1 has 1 nnz)");
    CHECK(csc.col_ptr[3] == 5, "col_ptr[3] == 5 (col 2 has 2 nnz)");
    CHECK(csc.col_ptr[4] == 6, "col_ptr[4] == 6 (col 3 has 1 nnz)");

    /* Verify values in column 0: (row 0, val=1) and (row 2, val=5) */
    CHECK(csc.values[0] == 1 && csc.row_idx[0] == 0, "col0: (0,1)");
    CHECK(csc.values[1] == 5 && csc.row_idx[1] == 2, "col0: (2,5)");

    csc_free(&csc);
}

/* ── Test 4: CSC SpMV ──────────────────────────────────────────── */
static void test_csc_spmv(void)
{
    printf("\n--- Test: CSC SpMV ---\n");

    int32_t dense[] = {
        1, 2, 0,
        0, 3, 4,
        5, 0, 6
    };
    int32_t x[] = {1, 2, 3};
    int32_t y[3];

    cgra_csc_t csc;
    dense_to_csc(dense, 3, 3, &csc);

    csc_spmv_sw(&csc, x, y);

    /* Expected: y = [1*1+2*2+0*3, 0*1+3*2+4*3, 5*1+0*2+6*3] = [5, 18, 23] */
    CHECK(y[0] == 5,  "y[0] == 5");
    CHECK(y[1] == 18, "y[1] == 18");
    CHECK(y[2] == 23, "y[2] == 23");

    csc_free(&csc);
}

/* ── Test 5: Dense MatMul ──────────────────────────────────────── */
static void test_matmul_sw(void)
{
    printf("\n--- Test: Software MatMul ---\n");

    /* A: 2×3, B: 3×2 */
    int32_t A[] = {1, 2, 3, 4, 5, 6};
    int32_t B[] = {7, 8, 9, 10, 11, 12};
    int32_t C[4];

    matmul_sw(A, B, C, 2, 3, 2);

    /* C = [[1*7+2*9+3*11, 1*8+2*10+3*12], [4*7+5*9+6*11, 4*8+5*10+6*12]]
     *   = [[58, 64], [139, 154]] */
    CHECK(C[0] == 58,  "C[0,0] == 58");
    CHECK(C[1] == 64,  "C[0,1] == 64");
    CHECK(C[2] == 139, "C[1,0] == 139");
    CHECK(C[3] == 154, "C[1,1] == 154");
}

/* ── Test 6: CSC sparsity percentage ─────────────────────────── */
static void test_sparsity(void)
{
    printf("\n--- Test: Sparsity calculation ---\n");

    /* All zeros → 100% sparse */
    int32_t zeros[9] = {0};
    cgra_csc_t csc;
    dense_to_csc(zeros, 3, 3, &csc);
    CHECK(csc.nnz == 0, "all-zero matrix has nnz == 0");
    csc_free(&csc);

    /* All ones → 0% sparse */
    int32_t ones[] = {1,1,1, 1,1,1, 1,1,1};
    dense_to_csc(ones, 3, 3, &csc);
    CHECK(csc.nnz == 9, "all-ones 3x3 has nnz == 9");
    csc_free(&csc);
}

/* ── Main ──────────────────────────────────────────────────────── */
int main(void)
{
    printf("========================================\n");
    printf("  CGRA Tiler Library – Unit Tests\n");
    printf("========================================\n");

    test_im2col_basic();
    test_4x4_tiling();
    test_dense_to_csc();
    test_csc_spmv();
    test_matmul_sw();
    test_sparsity();

    printf("\n========================================\n");
    printf("  Results: %d / %d passed\n", tests_pass, tests_run);
    printf("========================================\n");

    return (tests_pass == tests_run) ? 0 : 1;
}
