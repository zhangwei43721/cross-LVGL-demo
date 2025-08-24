cmake_minimum_required(VERSION 3.12)
project(main C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# --- 控制官方示例的编译以加快编译速度 ---
option(LV_BUILD_DEMOS "构建 LVGL demos" OFF)
option(LV_BUILD_EXAMPLES "构建 LVGL examples" OFF)

include_directories(. libs/freetype/include)

# --- 平台配置 ---
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

execute_process(COMMAND bash configure.sh ${TARGET_ARCH} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# --- 构建与链接 ---
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_executable(${PROJECT_NAME} main.c mouse_cursor_icon.c obj/myexample.c abc.c)

# --- 条件链接 ---
set(EXTRA_LIBS "")
if(LV_BUILD_DEMOS)
    list(APPEND EXTRA_LIBS lvgl::demos)
endif()
if(LV_BUILD_EXAMPLES)
    list(APPEND EXTRA_LIBS lvgl::examples)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    lvgl
    lvgl::drivers
    ${PLATFORM_LIBS}
    ${EXTRA_LIBS}
)