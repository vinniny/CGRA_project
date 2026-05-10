/* fb_paint.c — write a binary blob to /dev/mem at a physical address.
 *
 * Usage: fb_paint <pattern.bin> <phys_addr_hex> [size_bytes]
 *
 * Built against musl libc, statically linked, no runtime dependencies.
 * Uses mmap() of /dev/mem which the Zynq PetaLinux kernel allows for
 * reserved-memory regions (the framebuffer at 0x1F000000 in our DT)
 * even with CONFIG_STRICT_DEVMEM=y — that flag only blocks read/write
 * syscalls, not mmap, on those regions.
 *
 * Default size = 640 * 480 * 3 = 921600 bytes (one 24-bit RGB frame at
 * the Pynq-Z2 demo resolution).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define DEFAULT_BYTES (640u * 480u * 3u)

static int die(const char *what) {
    fprintf(stderr, "fb_paint: %s: %s\n", what, strerror(errno));
    return 1;
}

int main(int argc, char **argv) {
    if (argc < 3 || argc > 4) {
        fprintf(stderr,
            "usage: %s <pattern.bin> <phys_addr_hex> [size_bytes]\n"
            "  default size = %u bytes (640*480*3)\n",
            argv[0], DEFAULT_BYTES);
        return 2;
    }

    const char *path = argv[1];
    unsigned long phys = strtoul(argv[2], NULL, 0);
    size_t want = (argc == 4) ? strtoul(argv[3], NULL, 0) : DEFAULT_BYTES;

    /* Read the pattern file. */
    int pfd = open(path, O_RDONLY);
    if (pfd < 0) return die(path);
    struct stat st;
    if (fstat(pfd, &st) < 0) return die("fstat");
    size_t fsz = (size_t)st.st_size;
    if (fsz == 0) {
        fprintf(stderr, "fb_paint: %s is empty\n", path);
        return 1;
    }
    size_t bytes = (fsz < want) ? fsz : want;

    void *src = mmap(NULL, fsz, PROT_READ, MAP_PRIVATE, pfd, 0);
    if (src == MAP_FAILED) return die("mmap pattern");
    close(pfd);

    /* Open /dev/mem WITHOUT O_SYNC. O_SYNC forces uncached mappings on
     * ARM, which makes NEON memcpy SIGBUS on unaligned chunks. The FB
     * region is normal DDR (just reserved from the kernel allocator),
     * so cacheable mapping is correct. We msync() at the end to flush. */
    int mfd = open("/dev/mem", O_RDWR);
    if (mfd < 0) return die("/dev/mem");

    long ps = sysconf(_SC_PAGESIZE);
    unsigned long page_off = phys & (ps - 1);
    unsigned long page_base = phys - page_off;
    size_t map_len = (page_off + bytes + ps - 1) & ~((size_t)ps - 1);

    void *dst = mmap(NULL, map_len, PROT_READ | PROT_WRITE,
                     MAP_SHARED, mfd, (off_t)page_base);
    if (dst == MAP_FAILED) return die("mmap /dev/mem");

    memcpy((char *)dst + page_off, src, bytes);
    msync((char *)dst + page_off, bytes, MS_SYNC);

    munmap(src, fsz);
    munmap(dst, map_len);
    close(mfd);

    printf("fb_paint: wrote %zu bytes from %s to phys 0x%lX\n",
           bytes, path, phys);
    return 0;
}
