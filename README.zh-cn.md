*其他语言：[English](README.md)，[简体中文](README.zh-cn.md)*

## 目录

- [概述](#概述)
- [目录结构](#目录结构)
- [分支说明](#分支说明)
- [功能亮点](#功能亮点)
- [硬件支持](#硬件支持)
- [编译](#编译)
  - [键盘生产商/QMK 固件用户](#键盘生产商qmk-固件用户)
  - [开发者](#开发者)
    - [Debian GNU/Linux或Ubuntu](#debian-gnulinux-或-ubuntu)
- [烧录](#烧录)
- [社区](#社区)

## 概述

这是 [QMK](https://github.com/qmk/qmk_firmware) 固件向 CH58x 平台的移植，主要工作集中在应用层（QMK）和底层硬件之间的接合。

## 目录结构

- CherryUSB、qmk_firmware、mcuboot：子仓库，**没有修改任何代码**。

  *其中，QMK 固件应当能够随上游仓库随时更新。*
- CherryUSB_porting、mcuboot_porting：用于配置子模块并将它们添加到构建系统中的文件。
- qmk_porting：QMK 和硬件之间的接合层。
- sdk：WCH 的 SDK。

## 分支说明

- via：完成了有线键盘所需的基本移植，包括 VIA 支持。灯方面，目前支持 WS2812（SPI 和 PWM）和 AW20216S（SPI）。
- debug：如果你只是来看 QMK 的，当它是空气即可。

## 功能亮点

- 支持有线、蓝牙、无线 2.4G（无线功能暂不开放）。
- 可随 QMK 上游仓库随时更新，支持 QMK 的绝大多数功能。
- 无线低功耗。

## 硬件支持

目前只测试了 CH582M，CH582F 应当能够正常工作。

## 编译

- WCH 的工具链已经随附，当然你也可以选择使用[公版编译器](https://xpack.github.io/blog/2019/07/31/riscv-none-embed-gcc-v8-2-0-3-1-released)。请记得将它的路径手动添加到环境变量 `PATH`。
- *如果你确定要头铁，加一个全局宏定义 `INT_SOFT`，否则中断很有可能不会正常工作*。

### 键盘生产商/QMK 固件用户

Fork 我的仓库，手动将你的键盘配置文件上传到[keyboards](https://github.com/O-H-M2/qmk_port_ch582/tree/via/qmk_porting/keyboards)目录下，然后使用页面上方的 Actions 来在线编译你的固件。

*需要注意本仓库目前使用的配置文件与 QMK 的有一点轻微差异，你可以用[这个](https://github.com/O-H-M2/qmk_port_ch582/tree/via/qmk_porting/keyboards/m2wired)作为模板自行修改。*

### 开发者

推荐使用 [Visual Studio Code](https://code.visualstudio.com/)。

参照[这个](./VSCODE_DEVELOPMENT.md)搭建你的本机开发环境，也可选择 Codespace.

或参照以下步骤在 Linux 系统上构建：

#### Debian GNU/Linux 或 Ubuntu

1. 安装依赖：

```
$ sudo apt update
$ sudo apt install git cmake ccache python3 python3-click python3-cbor2 python3-intelhex
```

2. Clone 代码仓库：
```
$ git clone https://github.com/O-H-M2/qmk_port_ch582.git
$ cd qmk_port_ch582
$ git -c submodule."qmk_porting/keyboards_private".update=none submodule update --recursive --init
```

3. 创建构建目录：
```
$ mkdir build
$ cd build
```

4. 运行 `cmake` 检查依赖和生成 Makefile
```
$ cmake -DCMAKE_BUILD_TYPE=Release -Dkeyboard=ezy64 -Dkeymap=default ..
```
你可以把 `ezy64` 和 `default` 替换成你的键盘和 keymap。

5. 编译：
```
$ make -j$(nproc)
```
如果编译成功，`.uf2` and `.hex` 会在项目的最顶层目录被生成。

## 烧录

用户：不要使用除 [Bootmagic Lite](https://docs.qmk.fm/#/feature_bootmagic?id=bootmagic-lite) 以外的方式。

开发者：推荐使用 [WCH 提供的工具](http://www.wch.cn/downloads/WCHISPTool_Setup_exe.html)。

## 社区

- QQ 群： 860356332
- [Discord](https://discord.gg/kaH6eRUFZS)