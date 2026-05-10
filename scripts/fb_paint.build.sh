#!/bin/sh
# fb_paint.build.sh — cross-compile fb_paint.c into a static-musl ARM binary
# that runs on the PYNQ-Z2 PetaLinux target.
#
# Toolchain: arm-linux-musleabihf-cross from musl.cc (one-time download).
# Output: /tmp/fb_paint (statically-linked, ~46 KB, zero deps).
#
# Why musl-static instead of glibc-cross:
#   * Single tarball, no apt/sudo, no PetaLinux SDK rebuild.
#   * Static -> no glibc/libc.so version drift between host and target.
#   * mmap()-based, so it bypasses CONFIG_STRICT_DEVMEM (which only blocks
#     read()/write() to /dev/mem, not mmap of reserved-memory regions).

set -e

PROJ=$(cd "$(dirname "$0")/.." && pwd)
SRC="$PROJ/scripts/fb_paint.c"
OUT=/tmp/fb_paint

# One-time toolchain bootstrap. Set MUSL_TC env var to override.
TC="${MUSL_TC:-/home/vinniny/toolchains/arm-linux-musleabihf-cross}"
GCC="$TC/bin/arm-linux-musleabihf-gcc"

if [ ! -x "$GCC" ]; then
    cat <<EOF >&2
Toolchain not found at $TC.
Download once with:
    mkdir -p $(dirname "$TC") && cd $(dirname "$TC")
    curl -fLO https://musl.cc/arm-linux-musleabihf-cross.tgz
    tar xzf arm-linux-musleabihf-cross.tgz
Or set MUSL_TC=/path/to/your/toolchain and re-run this script.
EOF
    exit 1
fi

# Why -fno-tree-vectorize: musl's memcpy with autovectorization can emit
# unaligned NEON loads/stores that fault on /dev/mem when O_SYNC opens it
# uncached. We open WITHOUT O_SYNC so the cacheable path works, but we
# disable the vectorizer anyway to keep the codegen predictable.
"$GCC" -O2 -Wall -static \
    -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard \
    -fno-tree-vectorize \
    -o "$OUT" "$SRC"

ls -lh "$OUT"
file "$OUT"
echo "Built: $OUT"
echo "Deploy: scp $OUT petalinux@<board>:/tmp/"
echo "Run:    ssh petalinux@<board> 'sudo /tmp/fb_paint /path/to/pattern.bin 0x1F000000'"
