cmake_minimum_required(VERSION 3.10)

project(main)

include_directories(.)

add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

set(TOOLCHAIN_DIR "/usr/local/arm/5.4.0/usr/")
set(CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/bin/arm-linux-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/bin/arm-linux-g++")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_executable(${PROJECT_NAME} main.c mouse_cursor_icon.c)
target_link_libraries(${PROJECT_NAME} PRIVATE lvgl lvgl::examples lvgl::demos lvgl::drivers)