#!/bin/bash
# 服务器：完整干净编译（修 kconfig lib + 全流程）
set -o pipefail
V=/root/autodl-tmp/vela
export PATH="$V/prebuilts/kconfig-frontends/bin:$V/prebuilts/gcc/linux-x86_64/arm-none-eabi/bin:/usr/bin:/bin"
export LD_LIBRARY_PATH="$V/prebuilts/kconfig-frontends/lib:$LD_LIBRARY_PATH"
cd "$V/nuttx"

echo "=== 0. 验证 kconfig-conf 可用 ==="
kconfig-conf --help > /dev/null 2>&1 && echo "kconfig-conf OK" || echo "kconfig-conf FAIL"

echo "=== 1. 彻底 distclean ==="
make distclean > /dev/null 2>&1
rm -f .config nuttx.bin nuttx.hex
ls .config 2>/dev/null || echo "无 .config（干净）"

echo "=== 2. configure ==="
./tools/configure.sh ../vendor/gigadevice/boards/gd32h7/gd32h759imt6/configs/nsh 2>&1 | tail -2
echo "configure rc=$?"

echo "=== 3. olddefconfig ==="
make olddefconfig 2>&1 | tail -3
echo "olddefconfig rc=${PIPESTATUS[0]}"

echo "=== 4. 关键配置检查 ==="
grep -E '^CONFIG_ARCH_CHIP=|^CONFIG_ARCH_CORTEXM7=|^CONFIG_ARCH_ARMV7M=|^CONFIG_ARCH_SUBDIR|^CONFIG_GD32H759IMT6_GT911=' .config
echo "ARCH 行数: $(grep -c 'CONFIG_ARCH' .config)"

echo "=== 5. make -j128 (start $(date +%T)) ==="
make -j128 2>&1 | tail -30
echo "make rc=${PIPESTATUS[0]} (end $(date +%T))"

echo "=== 6. 产物 ==="
ls -la nuttx.bin nuttx.hex 2>/dev/null
echo "=== DONE ==="
