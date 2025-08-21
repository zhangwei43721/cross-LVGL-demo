#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include <unistd.h>

// 包含驱动配置文件，这样我们就可以直接使用 USE_SDL 等宏
#include "lv_drv_conf.h"

// 根据 lv_drv_conf.h 中的 USE_SDL 宏来包含不同的头文件
#if USE_SDL
    /* ========================= */
    /*     PC/SDL 平台头文件      */
    /* ========================= */
    #include "lv_drivers/sdl/sdl.h"
#else
    /* ================================ */
    /*     ARM/Framebuffer 平台头文件     */
    /* ================================ */
    #include "lv_drivers/display/fbdev.h"
    #include "lv_drivers/indev/evdev.h"
    #include <sys/time.h>
    uint32_t custom_tick_get(void); // 函数声明
#endif

#define DISP_BUF_SIZE (128 * 1024)

int main(void)
{
    /* LVGL 内核初始化 */
    lv_init();

#if USE_SDL
    /* ========================= */
    /*     PC/SDL 平台初始化      */
    /* ========================= */

    sdl_init();

    /* 创建一个 LVGL 显示缓冲区 */
    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf[SDL_HOR_RES * 10];
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, SDL_HOR_RES * 10);

    /* 创建一个 LVGL 显示驱动 */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = sdl_display_flush; // 现在可以被正确找到了
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    lv_disp_drv_register(&disp_drv);

    /* 创建输入设备驱动 (鼠标) */
    static lv_indev_drv_t indev_drv_mouse;
    lv_indev_drv_init(&indev_drv_mouse);
    indev_drv_mouse.type = LV_INDEV_TYPE_POINTER;
    indev_drv_mouse.read_cb = sdl_mouse_read; // 现在可以被正确找到了
    lv_indev_drv_register(&indev_drv_mouse);

#else
    /* ================================ */
    /*     ARM/Framebuffer 平台初始化     */
    /* ================================ */

    fbdev_init();

    static lv_color_t buf[DISP_BUF_SIZE];
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 800;
    disp_drv.ver_res    = 480;
    lv_disp_drv_register(&disp_drv);

    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1);
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;
    indev_drv_1.read_cb = evdev_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

    LV_IMG_DECLARE(mouse_cursor_icon)
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act());
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);
    lv_indev_set_cursor(mouse_indev, cursor_obj);
#endif

    /* UI 代码 (平台通用) */
    lv_demo_widgets();

    /* 主循环 (处理 LVGL 任务) */
    while(1) {
        lv_timer_handler();
        usleep(5000); // 5ms
    }

    return 0;
}

#if !USE_SDL
/* ARM/fbdev 平台 tick 获取函数实现 */
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
#endif