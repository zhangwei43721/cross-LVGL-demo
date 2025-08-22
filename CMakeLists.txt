cmake_minimum_required(VERSION 3.10)
project(main C)

# --- 基本设置 ---
set(CMAKE_C_STANDARD 99)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
include_directories(.) # For lv_conf.h, lv_drv_conf.h

# --- 平台检测与配置 ---
if(CMAKE_CROSSCOMPILING OR CMAKE_SYSTEM_PROCESSOR MATCHES "arm|aarch64" OR CMAKE_C_COMPILER MATCHES "arm-linux-")
    message(STATUS "目标架构: ARM (交叉编译)")
    set(TARGET_ARCH "arm")
    set(PLATFORM_LIBS pthread)
else()
    message(STATUS "目标架构: PC (本地编译)")
    set(TARGET_ARCH "pc")
    find_package(SDL2 REQUIRED)
    find_package(Threads REQUIRED)
    set(PLATFORM_LIBS ${SDL2_LIBRARIES} Threads::Threads)
endif()

# 运行脚本来修改 lv_drv_conf.h
execute_process(
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/configure.sh ${TARGET_ARCH}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE script_result
)
if(NOT script_result EQUAL 0)
    message(FATAL_ERROR "为 ${TARGET_ARCH} 配置 lv_drv_conf.h 失败")
endif()


# --- 添加子目录 ---
# 因为头文件已在 /usr/local/include，编译 lvgl 会自动找到
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)


# --- 构建主程序 ---
add_executable(${PROJECT_NAME} main.c mouse_cursor_icon.c  obj/myexample.c abc.c)

# --- 链接库 ---
# 链接顺序至关重要。
target_link_libraries(${PROJECT_NAME} PRIVATE
    lvgl
    lvgl::drivers
    lvgl::demos
    lvgl::examples
    ${PLATFORM_LIBS}
    m
    # 我们不再需要在这里手动链接 freetype，因为下一步会从 lvgl 传递依赖
)

# --- 为VSCode创建一个运行目标 ---
add_custom_target(run
    COMMAND ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

message(STATUS "项目配置完成! 目标平台: ${TARGET_ARCH}")