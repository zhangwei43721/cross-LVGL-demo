cmake_minimum_required(VERSION 3.10)
project(main C)

# --- 基本设置 ---
set(CMAKE_C_STANDARD 99)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
include_directories(.) # 包含根目录以找到 lv_conf.h 和 lv_drv_conf.h

# --- 平台检测与配置 ---
if(CMAKE_CROSSCOMPILING AND (CMAKE_SYSTEM_PROCESSOR MATCHES "arm|aarch64"))
    message(STATUS "目标架构: ARM (交叉编译)")
    set(TARGET_ARCH "arm")
    set(PLATFORM_LIBS pthread) # ARM平台链接pthread
else()
    message(STATUS "目标架构: PC (本地编译)")
    set(TARGET_ARCH "pc")
    find_package(SDL2 REQUIRED)
    find_package(Threads REQUIRED)
    set(PLATFORM_LIBS ${SDL2_LIBRARIES} Threads::Threads) # PC平台链接SDL2和pthreads
endif()

# --- 自动执行配置脚本 ---
# 根据检测到的 TARGET_ARCH，运行脚本来修改 lv_drv_conf.h
# 这是配置的唯一来源
execute_process(
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/configure.sh ${TARGET_ARCH}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE script_result
)
if(NOT script_result EQUAL 0)
    message(FATAL_ERROR "为 ${TARGET_ARCH} 配置 lv_drv_conf.h 失败")
endif()


# --- 添加子目录 ---
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)


# --- 构建主程序 ---
add_executable(${PROJECT_NAME} main.c mouse_cursor_icon.c)

# 链接所有需要的库
target_link_libraries(${PROJECT_NAME} PRIVATE
    lvgl
    lvgl::drivers
    lvgl::demos      # 链接 LVGL 的 demos 库
    # lvgl::examples   # 链接 LVGL 的 examples 库
    ${PLATFORM_LIBS} # 链接平台特定的库
    m                # 链接数学库
)

# --- 为VSCode创建一个运行目标 ---
add_custom_target(run
    COMMAND ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

message(STATUS "项目配置完成! 目标平台: ${TARGET_ARCH}")