/* =============================================================================
 * mmu_cache_bm.h — minimal MMU + L1 cache bring-up for Cortex-A9 (Zynq).
 *
 * Caches were OFF (start.s sets only VBAR + VFP), so EVERY load/store hit DDR
 * (~330 cyc/MAC measured). Enabling I/D-caches is worth ~20-30x.
 *
 * Coherency by construction: 1 MB section table marking ALL DMA-shared windows
 * Non-Cacheable — CGRA DMA staging (0x001-0x002), HDMI-OUT FB + HDMI-IN ring
 * (0x100-0x12F). CPU-only regions are write-back cacheable. Peripherals Device.
 * ============================================================================= */
#ifndef MMU_CACHE_BM_H
#define MMU_CACHE_BM_H
#include <stdint.h>

#define SEC_WB     0x00015C0Eu
#define SEC_NC     0x00014C02u
#define SEC_DEV    0x00000C06u

static uint32_t __attribute__((aligned(16384))) mmu_l1_table[4096];

static inline void mmu_cache_enable(void)
{
    for (uint32_t s = 0; s < 4096u; s++) {
        uint32_t base = s << 20, attr;
        if (s == 0)                   attr = SEC_WB;
        else if (s <= 2)              attr = SEC_NC;
        else if (s < 0x100u)          attr = SEC_WB;
        else if (s <= 0x12Fu)         attr = SEC_NC;
        else if (s < 0x400u)          attr = SEC_WB;
        else                          attr = SEC_DEV;
        mmu_l1_table[s] = base | attr;
    }
    uint32_t ttbr = (uint32_t)mmu_l1_table | 0x59u;
    asm volatile("mcr p15,0,%0,c2,c0,0" :: "r"(ttbr));
    asm volatile("mcr p15,0,%0,c3,c0,0" :: "r"(1));
    uint32_t z = 0;
    asm volatile("mcr p15,0,%0,c8,c7,0" :: "r"(z));
    asm volatile("mcr p15,0,%0,c7,c5,0" :: "r"(z));
    uint32_t s = 0, l = 0;
    for (s = 0; s < 256u; s++)
        for (l = 0; l < 4u; l++) {
            uint32_t sw = (l << 30) | (s << 5);
            asm volatile("mcr p15,0,%0,c7,c6,2" :: "r"(sw));
        }
    asm volatile("dsb sy");
    uint32_t v;
    asm volatile("mrc p15,0,%0,c1,c0,0" : "=r"(v));
    v |= (1u << 0) | (1u << 2) | (1u << 12);
    asm volatile("mcr p15,0,%0,c1,c0,0" :: "r"(v));
    asm volatile("dsb sy"); asm volatile("isb");
}

/* Clean entire L1 D-cache (set/way) — after CPU-initialized DDR (weights,
 * SG chains) before first CGRA DMA reads. */
static inline void cache_clean_all(void)
{
    for (uint32_t s = 0; s < 256u; s++)
        for (uint32_t w = 0; w < 4u; w++) {
            uint32_t sw = (w << 30) | (s << 5);
            asm volatile("mcr p15,0,%0,c7,c10,2" :: "r"(sw));
        }
    asm volatile("dsb sy");
}

static inline void cache_clean_range(const void *p, uint32_t bytes)
{
    uintptr_t a = (uintptr_t)p & ~31u, e = (uintptr_t)p + bytes;
    for (; a < e; a += 32) asm volatile("mcr p15,0,%0,c7,c10,1" :: "r"(a));
    asm volatile("dsb sy");
}

static inline void cache_inval_range(const void *p, uint32_t bytes)
{
    uintptr_t a = (uintptr_t)p & ~31u, e = (uintptr_t)p + bytes;
    for (; a < e; a += 32) asm volatile("mcr p15,0,%0,c7,c6,1" :: "r"(a));
    asm volatile("dsb sy");
}
#endif
