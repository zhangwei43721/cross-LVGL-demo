# LVGL 项目模板：轻松实现跨平台编译

本项目是一个基于 LVGL 的图形用户界面应用程序模板，其核心特性是**一键式跨平台编译**。通过内置的 **<u>CMake</u>** 和 Shell 脚本，开发者可以轻松地将同一个项目编译到 **Linux PC** 和 **嵌入式 ARM Linux** 平台，无需手动修改任何配置文件。

这极大地简化了开发流程：您可以在 PC 上快速进行界面设计和逻辑验证，然后无缝切换到目标 ARM 平台进行部署和测试。

## 核心特性

*   **自动化跨平台配置**：通过 `configure.sh` 脚本和 CMake 变量，自动调整 LVGL 的驱动、内核配置以及代码的条件编译，以适应不同平台。
*   **统一的源码，多平台目标**：`main.c` 中使用C语言的宏预处理指令，为不同平台选择性地编译代码，实现了“一次编写，到处编译”。
*   **CMake 构建系统**：使用现代化的 CMake 管理项目，自动检测编译环境（本地编译或交叉编译），并链接相应的库。
*   **UI 与逻辑分离**：推荐将 SquareLine Studio 生成的 UI 代码与手写的业务逻辑代码分离，避免了 UI 更新后逻辑代码被覆盖的问题。

## 项目结构解析

```
.
├── CMakeLists.txt      # 主 CMake 配置文件，管理整个项目的构建
├── configure.sh        # 跨平台配置的核心脚本
├── arm.cmake           # ARM 平台交叉编译工具链配置文件
├── build/              # 编译输出目录
├── bin/                # 最终生成的可执行文件目录
├── lvgl/               # LVGL 核心库
├── lv_drivers/         # LVGL 驱动库
├── UI/                 # ✅ SquareLine Studio 生成的 UI 代码（视图层）
├── obj/                # ✅ 用户自定义的业务逻辑代码（控制层）
├── main.c              # 应用程序主入口
└── ...
```

## 跨平台实现原理

本项目的跨平台能力主要通过以下三个部分协同工作实现：

1.  **`CMakeLists.txt` (构建系统)**：
    *   通过 `CMAKE_CROSSCOMPILING` 变量判断当前是在为本地 PC 编译还是在为 ARM 平台进行交叉编译。
    *   根据判断结果，选择链接不同的库（PC 平台链接 `SDL2`，ARM 平台链接 `pthread` 等）。
    *   在配置阶段，它会调用 `configure.sh` 脚本，并传入当前的目标平台（`pc` 或 `arm`）作为参数。

2.  **`configure.sh` (配置文件修改器)**：
    *   这个脚本接收来自 CMake 的平台参数。
    *   它会动态修改 `lv_drv_conf.h` 和 `lv_conf.h` 这两个关键配置文件。例如，为 PC 平台启用 `USE_SDL` 宏，为 ARM 平台启用 `USE_FBDEV` 和 `USE_EVDEV` 宏。

3.  **`main.c` (条件编译)**：
    *   在 `main.c` 的代码中，我使用了 C 语言的预处理指令（`#if USE_SDL ... #else ... #endif`）来包裹平台相关的代码。
    *   当为 **PC** 编译时，`USE_SDL` 为 `1`，因此只有 SDL 相关的头文件和初始化代码会被编译进去。
    *   当为 **ARM** 编译时，`USE_SDL` 为 `0`，因此只有 Framebuffer 和 evdev 相关的代码会被编译。
    *   这使得同一份 `main.c` 源码能够无缝适应不同的底层硬件抽象层（HAL），而无需修改任何业务逻辑。

## 开发工作流：UI 设计与逻辑分离

为了解决使用 SquareLine Studio 等工具时，重新生成代码会导致手动添加的逻辑被覆盖的问题，我强烈推荐采用**视图（UI）与控制（Logic）分离**的开发模式。

#### `UI/` 目录 (视图层)

*   **用途**：存放由 SquareLine Studio 等可视化工具**自动生成**的全部 UI 文件（例如 `ui.c`, `ui.h`, `screens/`, `components/` 等）。
*   **原则**：**不要手动修改这个目录下的任何文件**。把它当作一个只读的库。每当你在 SquareLine Studio 中更新了界面设计，就将导出的文件完全覆盖到这个目录中。

#### `obj/` 目录 (控制/逻辑层)

*   **用途**：存放所有你**手动编写**的业务逻辑代码。例如，按钮的点击事件、传感器数据的处理、与后台的通信等。
*   **如何工作**：
    1.  在 `obj/` 目录下创建你自己的 C 文件，例如 `my_app_events.c`。
    2.  在 `my_app_events.c` 中，包含由 UI 工具生成的头文件，如 `#include "ui.h"`。这样你就可以访问到所有的 UI 控件对象（例如 `ui_Main_Screen`, `ui_Login_Button`）。
    3.  编写函数来为这些 UI 控件添加事件回调和业务逻辑。

#### 示例：

假设你在 SquareLine Studio 中创建了一个名为 `ui_SendButton` 的按钮。

1.  **UI 层**：SquareLine Studio 会在 `UI/` 目录中生成 `ui_SendButton` 对象的定义。

2.  **逻辑层**：在 `obj/my_app_events.c` 中，你可以这样写：
    ```c
    #include "ui.h" // 引用 UI 对象
    #include <stdio.h>
    
    // 按钮点击事件的回调函数
    static void send_button_event_handler(lv_event_t * e)
    {
        // lv_event_code_t code = lv_event_get_code(e); // 获取事件码
        printf("发送按钮被点击了!\n");
        // 在这里添加发送数据的逻辑...
    }
    
    // 一个用于初始化所有逻辑的函数
    void setup_application_logic(void)
    {
        // 将回调函数绑定到 UI 按钮的点击事件上
        if(ui_SendButton) { // 确保对象已创建
            lv_obj_add_event_cb(ui_SendButton, send_button_event_handler, LV_EVENT_CLICKED, NULL);
        }
    }
    ```

3.  **整合**：最后，在 `main.c` 中，在调用 `ui_init()` 之后，再调用你的逻辑初始化函数。
    ```c
    #include "obj/head.h" // 假设 head.h 中包含了你的逻辑函数声明
    #include "ui.h"
    
    int main(void)
    {
        // ... 其他初始化 ...
        lv_init();
        hal_init();
    
        ui_init(); // 初始化由 SquareLine Studio 生成的 UI
        setup_application_logic(); // 绑定你的业务逻辑
    
        while(1) {
            // ...
        }
    }
    ```

**这样做的好处是**：你可以随时在 SquareLine Studio 中修改 UI 布局、增删控件，然后重新导出并覆盖 `UI/` 目录，而你精心编写在 `obj/` 目录下的所有业务逻辑代码都**完好无损**。

## 如何使用

### 环境依赖

*   **通用**：
    *   `cmake` (>= 3.12)
    *   `gcc` / `g++`
*   **PC (Linux) 平台**：
    *   `libsdl2-dev`
*   **ARM 平台**：
    *   ARM 交叉编译工具链（例如 `arm-linux-gcc`），并确保其路径已正确配置在 `arm.cmake` 文件中。

### 编译步骤

#### 1. 为 PC (Linux) 编译 (用于快速开发和预览)

```bash
# 创建一个构建目录
mkdir -p build
cd build

# 运行 CMake 配置 (它会自动选择 PC 平台)
cmake ..

# 编译项目
make

# 运行程序
../bin/main
```

#### 2. 为 ARM Linux 交叉编译 (用于部署到目标设备)

```bash
# 推荐清理之前的构建缓存
rm -rf build/*  # 或者新建一个目录
cd build

# 运行 CMake 并指定 ARM 工具链文件
cmake .. -DCMAKE_TOOLCHAIN_FILE=../arm.cmake

# 编译项目
make

# 编译完成后，将生成的可执行文件 ../bin/main 部署到您的 ARM 开发板上运行