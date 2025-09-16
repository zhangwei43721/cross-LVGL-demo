# LVGL 项目模板：PC与ARM平台一键编译

本项目是一个基于 LVGL 的图形用户界面应用程序模板，其核心特性是**真正的单指令跨平台编译**。通过强大的 CMake 构建系统，开发者可以在 **PC** 和 **嵌入式 ARM Linux** 三个平台之间无缝切换编译，无需手动修改任何配置文件

这极大地简化了开发流程：您可以在 Windows 或 Linux PC 上快速进行界面设计和逻辑验证，然后使用同一套代码库，直接交叉编译到目标 ARM 平台开发版进行部署

## ⚠️ 版本兼容性说明

本项目基于 **LVGL v8.x** 版本开发（具体为 **v8.3** 系列）

LVGL v9 引入了大量不兼容的 API 变更，因此本项目的代码**无法直接与 LVGL v9 或更高版本一起编译**。在更新 UI 目录时，请务必确保您使用的是 **v8** 系列的代码

## 核心特性

*   **全自动跨平台配置**：构建系统自动检测目标平台（Windows, Linux, ARM），并**在 CMake 内部直接修改** LVGL 驱动和内核配置，无需任何外部脚本
*   **统一的源码，多平台目标**：`main.c` 中使用C语言的宏预处理指令，为不同平台选择性地编译代码，实现了“一次编写，到处编译”
*   **UI 与逻辑分离**：推荐将 SquareLine Studio 生成的 UI 代码与手写的业务逻辑代码分离，避免了 UI 更新后逻辑代码被覆盖的问题

## 跨平台实现原理

本项目的跨平台能力完全由 `CMakeLists.txt` 主导，其原理如下：

1.  **平台检测**：CMake 通过内置变量（如 `WIN32`, `UNIX`, `CMAKE_CROSSCOMPILING`）准确识别当前的目标平台
2.  **动态文件配置**：识别平台后，CMake 会：
    *   在内存中读取 `lv_drv_conf.h` 和 `lv_conf.h` 的内容
    *   使用 `string(REGEX REPLACE ...)` 命令，根据平台需求（例如为 PC/Windows 启用 `USE_SDL`，为 ARM 启用 `USE_FBDEV`）修改这些内容
    *   将修改后的内容写回原文件
    这个过程完全自动化，取代了原有的 `configure.sh` 脚本，从而实现了原生跨平台。
3.  **条件编译**：在 `main.c` 中，`#if USE_SDL ... #else ... #endif` 结构根据上一步被修改的宏，自动包含正确的驱动代码（SDL 或 Framebuffer），确保最终的可执行文件与目标平台兼容。
4.  **库链接**：CMake 会根据平台链接不同的依赖库。特别地，在交叉编译时，它会直接链接到项目内 `libs/` 目录下的 `libfreetype` 库，避免了在工具链中寻找库的问题。

## 开发工作流：UI 设计与逻辑分离

为了解决使用 SquareLine Studio 等工具时，重新生成代码会导致手动添加的逻辑被覆盖的问题，我强烈推荐采用**视图（UI）与控制（Logic）分离**的开发模式。

#### `UI/` 目录 (视图层)

*   **用途**：存放由 SquareLine Studio 等可视化工具**自动生成**的全部 UI 文件。
*   **原则**：**不要手动修改这个目录下的任何文件**。每当你在 SquareLine Studio 中更新了界面设计，就将导出的文件完全覆盖到这个目录中。

#### `obj/` 目录 (控制/逻辑层)

*   **用途**：存放所有你**手动编写**的业务逻辑代码。例如，按钮的点击事件、传感器数据的处理等。
*   **如何工作**：
    1.  在 `obj/` 目录下创建你自己的 C 文件（例如 `my_app_events.c`）。
    2.  在该文件中包含 `#include "ui.h"` 来访问所有 UI 控件对象。
    3.  编写函数来为这些 UI 控件添加事件回调和业务逻辑。
    4.  最后，在 `main.c` 的 `ui_init()` 调用之后，调用你的逻辑初始化函数。

**这样做的好处是**：你可以随时更新 `UI/` 目录，而你精心编写在 `obj/` 目录下的所有业务逻辑代码都**完好无损**。

## 如何使用

### 环境依赖

*   **通用**：
    *   `cmake` (>= 3.12)
    *   C 编译器 (GCC, MinGW, MSVC等)
*   **Windows 平台**：
    *   **MinGW-w64**。
    *   **SDL2 开发库**: 从 [libsdl.org](https://github.com/libsdl-org/SDL/releases/tag/release-2.32.10) 下载 `SDL2-devel-2.x.x-mingw.zip` (用于 MinGW) 或 `SDL2-devel-2.32.10-VC.zip` (用于 MSVC)，并解压到稳定位置。
*   **Linux PC 平台**：
    *   `build-essential`, `libsdl2-dev` (`sudo apt-get install build-essential libsdl2-dev`)
*   **ARM 平台**：
    *   ARM 交叉编译工具链（例如 `arm-linux-gcc`）。

### 编译步骤

#### 1. 为 Windows 编译

图形界面（Vscode）：
  直接在下方的cmake工具栏中选择 `x86`工具包，然后点击构建按钮即可

1.  **打开命令行** (CMD, PowerShell, 或 Git Bash)。
2.  **创建构建目录**:
    
    ```bash
    mkdir build
    cd build
    ```
3.  **运行 CMake 配置** (以 MinGW 为例):
    *   你需要告诉 CMake 在哪里找到你解压的 SDL2 库。
    *   将 `C:/path/to/SDL2_dev_lib` 替换为你的实际路径。

    ```bash
    cmake .. -G "MinGW Makefiles" -DSDL2_DIR="C:/path/to/SDL2_dev_lib"
    ```
4.  **编译**:
    ```bash
    cmake --build .
    ```
5.  **运行程序**：可执行文件将在 `bin/main.exe` 生成。

#### 2. 为 Linux PC 编译

图形界面（Vscode）：
  直接在下方的cmake工具栏中选择 `x86`工具包，然后点击构建按钮即可

```bash
# 创建并进入构建目录
mkdir -p build && cd build
# 运行 CMake 配置
cmake ..
# 编译项目
make
# 运行程序
../bin/main
```

#### 3. 为 ARM Linux 交叉编译

图形界面（Vscode）：
  直接在下方的cmake工具栏中选择 `arm`工具包，然后点击构建按钮即可。

纯命令行方式：

```bash
# 创建并进入构建目录
mkdir -p build && cd build
# 运行 CMake 并指定 ARM 工具链文件
cmake .. -DCMAKE_TOOLCHAIN_FILE=../arm.cmake
# 编译项目
make
```

> ### **✅ 重要部署说明 (ARM 平台)**
>
> 编译完成后，你需要将 `bin/main` 可执行文件部署到 ARM 开发板上。但由于程序依赖 FreeType 动态库 (`libfreetype.so`)，你**还必须**将这个库文件也部署到开发板上，否则程序运行时会提示“找不到库文件”的错误。
>
> 你可以从本项目的 `libs/freetype/lib/arm/` 目录中找到针对`GEC6818`开发版编译的 `libfreetype.so` 文件。
>
> 以下是三种推荐的部署方法：
>
> 1.  **【推荐】与可执行文件放在一起**：
>     *   将 `libfreetype.so` 文件复制到开发板上，与 `main` 可执行文件**放在同一个目录**下。
>     *   **原理**：本项目的编译配置已添加 `-rpath=.` 链接器标志，它会告诉程序在运行时，优先在自身所在的目录查找所需的库文件。这是最简单且不会污染开发板系统环境的方法。
>
> 2.  **【标准】复制到系统库目录**：
>     *   将 `libfreetype.so` 文件复制到开发板的標準庫目錄，例如 `/usr/lib` 或 `/lib`。
>       ```bash
>       # 在开发板上执行
>       cp libfreetype.so /usr/lib/
>       ```
>     *   复制后，建议运行 `ldconfig` 命令来更新系统的动态链接器缓存。
>       ```bash
>       ldconfig
>       ```
>
> 3.  **【灵活】使用环境变量**：
>     *   将 `libfreetype.so` 文件复制到开发板的任意目录（例如 `/opt/libs`）。
>     *   在运行程序前，通过设置 `LD_LIBRARY_PATH` 环境变量来告诉程序去哪里寻找这个库。
>       ```bash
>       # 在开发板上执行
>       export LD_LIBRARY_PATH=/opt/libs:$LD_LIBRARY_PATH
>       ./main
>       ```