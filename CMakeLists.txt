cmake_minimum_required(VERSION 3.10)
project(main LANGUAGES C CXX)

message(STATUS "交叉编译工具状态 ${CMAKE_CROSSCOMPILING}")

# --- 头文件和子目录 ---
include_directories(.)
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

# --- 输出路径 ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# --- 可执行文件定义 ---
add_executable(${PROJECT_NAME} main.c mouse_cursor_icon.c)

# --- 链接 LVGL 核心库 (所有平台都需要) ---
target_link_libraries(${PROJECT_NAME} PRIVATE lvgl lvgl::examples lvgl::demos lvgl::drivers)

if(NOT CMAKE_CROSSCOMPILING)
    # 1. 查找桌面环境需要的库
    find_package(SDL2 REQUIRED)
    find_package(Threads REQUIRED)

    # 2. 添加头文件路径
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
    
    # 3. 链接这些库
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} Threads::Threads)
    
    # 4. 打印消息，方便调试
    message(STATUS "Native build detected. Linking against SDL2 and pthreads.")
else()
    # 这段代码块只在“交叉编译”时执行
    message(STATUS "Cross-compilation detected for ARM. Skipping SDL2.")
endif()