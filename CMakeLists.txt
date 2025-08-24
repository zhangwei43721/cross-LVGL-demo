cmake_minimum_required(VERSION 3.12)
project(main C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# 全局头文件路径
include_directories(. libs/freetype/include)

# --- 平台配置 (检测、设置路径、定义库列表) ---
if(CMAKE_CROSSCOMPILING)
    set(TARGET_ARCH "arm")
    set(PLATFORM_LIBS pthread freetype m)
else() # PC
    set(TARGET_ARCH "pc")
    find_package(SDL2 REQUIRED)
    find_package(Threads REQUIRED)
    set(PLATFORM_LIBS SDL2::SDL2 Threads::Threads freetype m)
endif()

link_directories("libs/freetype/lib/${TARGET_ARCH}")

# 运行配置脚本
execute_process(COMMAND bash configure.sh ${TARGET_ARCH} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# --- 构建与链接 ---
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_executable(${PROJECT_NAME} main.c mouse_cursor_icon.c obj/myexample.c abc.c)

target_link_libraries(${PROJECT_NAME} PRIVATE
    lvgl
    lvgl::drivers
    ${PLATFORM_LIBS}
)