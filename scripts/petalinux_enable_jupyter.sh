#!/bin/bash
# =============================================================================
# petalinux_enable_jupyter.sh — Enable Jupyter+numpy+OpenCV+pip in Wildfire's
# PetaLinux rootfs_config, so the resulting rootfs supports PYNQ-style dev.
#
# Usage:
#   source /home/vinniny/petalinux/2022.2/settings.sh
#   cd /home/vinniny/centos_vm/projects/CGRA_project/wildfire_plnx/zynq_plnx
#   bash /home/vinniny/centos_vm/projects/CGRA_project/scripts/petalinux_enable_jupyter.sh
#
# After this runs:
#   petalinux-build              # ~30 min with sstate-cache, hours without
#   petalinux-package --boot --fsbl --fpga ... --u-boot
#
# Then reflash SD card.
# =============================================================================
set -euo pipefail

CFG="project-spec/configs/rootfs_config"
[ -f "$CFG" ] || { echo "Run from PetaLinux project root (no $CFG found)"; exit 1; }

# Packages to enable (CONFIG_xxx=y)
PKGS=(
    # Python core + pip
    python3
    python3-pip
    python3-modules
    python3-setuptools
    python3-wheel
    python3-dev

    # Numerical / image / scientific
    python3-numpy
    python3-pillow

    # OpenCV (C library + Python bindings)
    opencv
    python3-opencv

    # Jupyter notebook + kernel
    python3-jupyter
    python3-jupyter-core
    python3-jupyter-client
    python3-jupyter-server
    python3-notebook
    python3-ipykernel
    python3-ipywidgets

    # Jupyter dependencies (mostly auto-pulled, listed for safety)
    python3-tornado
    python3-jinja2
    python3-pyzmq
    python3-traitlets
    python3-jsonschema
    python3-pygments
    python3-nbformat
    python3-nbconvert
    python3-prometheus-client

    # V4L2 / GStreamer Python bindings
    python3-pygobject
    gstreamer1.0-python

    # Editors / dev convenience
    nano
    htop
    tmux
)

echo "[i] Enabling ${#PKGS[@]} packages in $CFG"

for pkg in "${PKGS[@]}"; do
    if grep -q "^CONFIG_${pkg}=y" "$CFG"; then
        echo "  ✓ already enabled: $pkg"
        continue
    fi
    if grep -q "^# CONFIG_${pkg} is not set" "$CFG"; then
        sed -i "s|^# CONFIG_${pkg} is not set|CONFIG_${pkg}=y|" "$CFG"
        echo "  + enabled: $pkg"
    else
        # Not in current Kconfig output — append; if recipe doesn't exist,
        # build will fail with a clear error and we remove it then.
        echo "CONFIG_${pkg}=y" >> "$CFG"
        echo "  + appended (verify): $pkg"
    fi
done

echo ""
echo "[i] Done. Now run:  petalinux-build"
echo "[i] Or first:       petalinux-config -c rootfs   (to review menu)"
