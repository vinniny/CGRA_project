/* =============================================================================
 * bm_string.c — Freestanding memset/memcpy/memmove for bare-metal targets.
 *
 * GCC silently emits calls to memset/memcpy when compiling array zero-init
 * (`int32_t arr[N] = {0};`) and certain struct copies even under -nostdlib
 * -ffreestanding. The freestanding spec only guarantees the *type* visibility,
 * not the runtime symbols. Provide the few that the v2 MNIST demo needs.
 * ============================================================================= */
#include <stddef.h>

void *memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    unsigned char  v = (unsigned char)c;
    while (n--) *p++ = v;
    return s;
}

void *memcpy(void *dst, const void *src, size_t n) {
    unsigned char       *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    while (n--) *d++ = *s++;
    return dst;
}

void *memmove(void *dst, const void *src, size_t n) {
    unsigned char       *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    if (d < s || d >= s + n) {
        while (n--) *d++ = *s++;
    } else {
        d += n;
        s += n;
        while (n--) *--d = *--s;
    }
    return dst;
}
