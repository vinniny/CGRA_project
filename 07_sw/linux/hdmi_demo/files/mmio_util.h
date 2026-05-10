#ifndef MMIO_UTIL_H
#define MMIO_UTIL_H

#include <stdint.h>
#include <stddef.h>

int mmio_map_uio_by_name(const char *wanted_name,
                         const char *fallback_dev,
                         size_t expected_map_size,
                         volatile uint8_t **base_out,
                         size_t *map_size_out,
                         int *fd_out);

int mmio_map_physical(uint64_t phys_addr,
                      size_t map_size,
                      volatile uint8_t **base_out,
                      int *fd_out);

void mmio_unmap(volatile uint8_t *base, size_t map_size, int fd);

static inline uint32_t mmio_read32(volatile uint8_t *base, uint32_t offset)
{
    return *(volatile uint32_t *)(base + offset);
}

static inline void mmio_write32(volatile uint8_t *base, uint32_t offset, uint32_t value)
{
    *(volatile uint32_t *)(base + offset) = value;
}

#endif
