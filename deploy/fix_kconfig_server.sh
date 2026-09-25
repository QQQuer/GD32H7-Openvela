#!/bin/bash
# 服务器版 Kconfig 修复（与 VM 已验证流程一致）
set -e
V=/root/autodl-tmp/vela
export PATH="$V/prebuilts/kconfig-frontends/bin:$V/prebuilts/gcc/linux-x86_64/arm-none-eabi/bin:/usr/bin:/bin"
cd "$V/nuttx"

# 1. 批量修复 help 块格式（438 文件级别）
python3 << 'PYEOF'
import os, re

def fix_file(path):
    with open(path, 'r', errors='replace') as f:
        lines = f.readlines()
    out = []
    in_help = False
    changed = False
    for line in lines:
        raw = line.rstrip('\n')
        if '---help---' in raw:
            in_help = True
            out.append(line)
            continue
        if in_help:
            if re.match(r'^\s*(config|menuconfig|choice|endchoice|endmenu|if|endif|source|menu|comment)\b', raw) and not raw.startswith('\t'):
                in_help = False
                out.append(line)
                continue
            if raw == '':
                out.append('\t\n')
                changed = True
            elif raw.startswith('\t'):
                out.append(line)
            else:
                out[-1] = out[-1].rstrip('\n') + ' ' + raw.lstrip() + '\n'
                changed = True
        else:
            out.append(line)
    if changed:
        with open(path, 'w') as f:
            f.writelines(out)
    return changed

count = 0
for root, dirs, files in os.walk('.'):
    if '.git' in root:
        continue
    for fn in files:
        if fn.startswith('Kconfig') or fn == 'Kconfig':
            try:
                if fix_file(os.path.join(root, fn)):
                    count += 1
            except Exception:
                pass
print(f"fixed {count} Kconfig files")
PYEOF

# 2. arch/tricore/Kconfig 的 --help-- typo
TRICORE=arch/tricore/Kconfig
if [ -f "$TRICORE" ] && grep -q -- '--help--' "$TRICORE"; then
    sed -i 's/--help--/---help---/' "$TRICORE"
    echo "tricore Kconfig typo fixed"
fi

# 3. 清空 tricoreht / coresight Kconfig（老 kconf 不兼容）
for f in drivers/hwtracing/tricoreht/Kconfig drivers/hwtracing/coresight/Kconfig; do
    if [ -f "$f" ]; then
        : > "$f"
        echo "cleared $f"
    fi
done

# 4. lvgl osource 注释
LVGL=../apps/graphics/lvgl/Kconfig
if [ -f "$LVGL" ] && grep -q '^osource' "$LVGL"; then
    sed -i 's|^osource|# osource (disabled: submodule absent)|' "$LVGL"
    echo "disabled lvgl osource"
fi

echo "=== FIX DONE ==="
