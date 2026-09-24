# GD32H7-Openvela 新机器完整编译操作说明

> 适用：在**另一台全新的 Ubuntu 电脑**上，从 `https://github.com/QQQuer/GD32H7-Openvela.git` 拉取代码后，完整编译出可烧录固件。
> 已实测通过（两个环境）：
> - 模拟评委环境（本地 VM）`make -j4` → nuttx.bin 591772B，flash 28.22%
> - **128 核云服务器全量 clean 编译 `make -j128` → nuttx.bin 591824B，flash 28.22%**（2026-09-24 实测，43 秒完成）
> 本说明按服务器实测修正，包含 kconfig 工具动态库加载步骤。

---

## 0. 前置条件

- Ubuntu 20.04 / 22.04（64 位），建议 100GB 以上磁盘
- 网络可访问 GitHub（国内建议配置代理，或使用 gitee 镜像 manifest）

## 1. 安装依赖与 repo 工具

```bash
sudo apt update
sudo apt install -y git python3 build-essential libncurses5-dev \
    libssl-dev unzip wget curl

# 安装 repo 工具（清华镜像，避免 GitHub 超时）
mkdir -p ~/bin
curl -s https://mirrors.tuna.tsinghua.edu.cn/git/git-repo/repo > ~/bin/repo
chmod a+x ~/bin/repo
export PATH=~/bin:$PATH
```

## 2. 拉取 openvela SDK（官方 manifest，赛题分支）

> GitHub 在国内可能超时。**推荐直接使用 gitee 官方镜像**（已实测：gitee.com/open-vela 有 dev-ai-contest-2026 分支，约 1GB/分钟，10 分钟拉完）。

```bash
mkdir -p ~/vela && cd ~/vela

# 方式 1（推荐）：gitee 官方镜像
repo init -u https://gitee.com/open-vela/manifests.git \
    -b dev-ai-contest-2026 -m openvela.xml \
    --repo-url=https://mirrors.tuna.tsinghua.edu.cn/git/git-repo/ --git-lfs

# 方式 2：GitHub 官方（网络好的话）
# repo init -u https://github.com/open-vela/manifests.git \
#     -b dev-ai-contest-2026 -m openvela.xml \
#     --repo-url=https://mirrors.tuna.tsinghua.edu.cn/git/git-repo/ --git-lfs

# 同步（默认组）
repo sync -c -j16

# 检查交叉工具链是否拉下来（manifest 中 arm-none-eabi 属 notdefault 组）
ls prebuilts/gcc/linux-x86_64/arm-none-eabi/bin/arm-none-eabi-gcc
# 如果上面报错（没有工具链），补拉 linux 平台工具链：
repo sync -c -j8 -g notdefault,platform-linux
```

> ⚠️ 同步时若报 `prebuilts_gcc_linux_tricore` checkout 失败，**可忽略**——那是 TC 单片机（Tricore）工具链，与 GD32H7 无关。
> ⚠️ 若 sync 因网络中途中断导致 `nuttx/` 工作树不完整（如 `arch/arm/src/` 顶层文件缺失），在 `/root/vela` 下执行 `repo sync -c -j16 nuttx` 重拉 nuttx 即可（不要删 `.repo`）。

完成后目录结构：

```
~/vela/
├── nuttx/          # 内核源码（dev-ai-contest-2026 分支）
├── apps/           # 应用仓
├── vendor/         # 板级 vendor（含 gigadevice，但只有 gd32f4！）
├── prebuilts/      # 交叉工具链、kconfig 工具等
└── build.sh        # 官方构建脚本
```

> ⚠️ 官方 SDK **不自带 GD32H7 芯片层与板卡层**（只有 gd32f4），必须执行下一步复制，否则无法编译。

## 3. 拉取本仓库（增量补丁 + 完整芯片层/板卡层）

```bash
cd ~/vela
git clone https://github.com/QQQuer/GD32H7-Openvela.git
cd GD32H7-Openvela
git checkout main
```

## 4. 应用增量到 SDK（按 README 映射表整体复制）

```bash
cd ~/vela
SRC=GD32H7-Openvela

# ① 完整 GD32H7 芯片层（45 个文件：start/irq/serial/rcu/lowputc/timerisr/hardware）
cp -r $SRC/board/contest_board/nuttx/arch/arm/src/gd32h7xx nuttx/arch/arm/src/

# ② 完整板卡层（30 个文件：src/configs/scripts/include，含 defconfig）
mkdir -p vendor/gigadevice/boards/gd32h7
cp -r $SRC/board/contest_board/vendor/gigadevice/boards/gd32h7/gd32h759imt6 \
      vendor/gigadevice/boards/gd32h7/

# ③ GUI 应用
cp -r $SRC/app/gui apps/examples/gui

# ④ GT911 / LCD / LED 示例
cp -r $SRC/app/gt911_demo apps/examples/gt911
cp -r $SRC/app/lcd_demo  apps/examples/lcd
mkdir -p apps/examples/leds
cp $SRC/app/leds_demo/leds_main.c apps/examples/leds/
```

## 5. 编译

### 方式 A：NuttX 传统构建（推荐，两套环境均已实测通过）

```bash
cd ~/vela
export PATH=$PWD/prebuilts/gcc/linux-x86_64/arm-none-eabi/bin:$PATH

# ⚠️ 关键：kconfig 工具是动态链接，必须把库目录加入 LD_LIBRARY_PATH，
# 否则 configure 阶段报 "error while loading shared libraries: libkconfig-parser-4.11.0.so"
export LD_LIBRARY_PATH=$PWD/prebuilts/kconfig-frontends/lib:$LD_LIBRARY_PATH

cd nuttx
./tools/configure.sh ../vendor/gigadevice/boards/gd32h7/gd32h759imt6/configs/nsh
make -j4        # 服务器实测 128 核约 43 秒；普通 4 核约 10~15 分钟
```

> 如果 SDK 里没有 `prebuilts/kconfig-frontends/`（某些版本不随默认组拉取），
> 执行 `repo sync -c -j8 -g notdefault,platform-linux` 补拉；仍没有就先运行方式 B 一次（build.sh 会自动编译 kconfig-frontends）。

### 方式 B：openvela build.sh（官方脚本，自动编译 kconfig 工具）

```bash
cd ~/vela
./build.sh vendor/gigadevice/boards/gd32h7/gd32h759imt6/configs/nsh -j4
```

### 产物

```
nuttx/nuttx.bin   （约 591KB，flash 占用 28.2%，sram 4.5%）
nuttx/nuttx.hex
```

> 若 `make olddefconfig` 阶段报 Kconfig 语法错（help 格式 / osource / tricoreht），
> 说明 kconfig 工具版本与 SDK 不匹配，请改走方式 B（build.sh 会从源码自动编译匹配版本的 kconfig-frontends），
> 或把 SDK 的 `nuttx` 换成仓库 `firmware/` 内附带的完整内核目录（含修复）。
> 若报 "No rule to make target 'arm_cache.c'"，说明 `.config` 未正确生成导致 ARCH_SUBDIR 为空——重跑
> `make distclean && ./tools/configure.sh ... && make olddefconfig && make`（确保 LD_LIBRARY_PATH 已设置）。

## 6. 烧录与运行

1. 板卡 BOOT0=1 进入 ISP 模式，串口连接（57600 8E1）
2. 使用 GD32 All In One Programmer，烧录 `nuttx/nuttx.bin` 到 `0x08000000`
3. 烧完拨回 BOOT0=0，上电，串口 115200 进 NSH：
   - `gui` — 启动可视化系统（触摸校准后进入主界面四入口）
   - `leds` / `gt911` / `lcd` — 对应示例

## 7. 不想编译？直接用现成固件

仓库 `firmware/nuttx_v92.bin`（591412B）即为最终验证固件，可跳过 2~5 直接烧录。
