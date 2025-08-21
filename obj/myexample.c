#include "head.h"

/**
 * @brief 设置对象位置函数
 * @details 该函数用于设置对象在场景中的位置坐标
 */
// void obj_pos(void)
// {
//     lv_obj_t *screen = lv_scr_act();

//     // 中间控件
//     lv_obj_t *cen = lv_obj_create(screen);
//     lv_obj_align(cen, LV_ALIGN_CENTER, 0, 0);
//     lv_obj_set_style_bg_color(cen, lv_palette_main(LV_PALETTE_RED), 0);
//     lv_obj_set_size(cen, 800/3, 480/3);

//     // 左侧控件
//     lv_obj_t *left = lv_obj_create(screen);
//     lv_obj_align(left, LV_ALIGN_LEFT_MID, 0, 0);
//     lv_obj_set_style_bg_color(left, lv_palette_main(LV_PALETTE_BLUE), 0);
//     lv_obj_set_size(left, 800/3, 480/3);

//     // 右侧控件
//     lv_obj_t *right = lv_obj_create(screen);
//     lv_obj_align(right, LV_ALIGN_RIGHT_MID, 0, 0);
//     lv_obj_set_style_bg_color(right, lv_palette_main(LV_PALETTE_GREEN), 0);
//     lv_obj_set_size(right, 800/3, 480/3);

//     // 顶部控件
//     lv_obj_t *top = lv_obj_create(screen);
//     lv_obj_align(top, LV_ALIGN_TOP_MID, 0, 0);
//     lv_obj_set_style_bg_color(top, lv_palette_main(LV_PALETTE_YELLOW),
//     LV_PART_MAIN); lv_obj_set_size(top, 800/3, 480/3);

//     // 底部控件
//     lv_obj_t *bottom = lv_obj_create(screen);
//     lv_obj_align(bottom, LV_ALIGN_BOTTOM_MID, 0, 0);
//     lv_obj_set_style_bg_color(bottom, lv_palette_main(LV_PALETTE_PURPLE), 0);
//     lv_obj_set_size(bottom, 800/3, 480/3);

//     // 左上角控件
//     lv_obj_t *top_left = lv_obj_create(screen);
//     lv_obj_align(top_left, LV_ALIGN_TOP_LEFT, 0, 0);
//     lv_obj_set_style_bg_color(top_left, lv_palette_main(LV_PALETTE_ORANGE),
//     0); lv_obj_set_size(top_left, 800/3, 480/3);

//     // 右上角控件
//     lv_obj_t *top_right = lv_obj_create(screen);
//     lv_obj_align(top_right, LV_ALIGN_TOP_RIGHT, 0, 0);
//     lv_obj_set_style_bg_color(top_right, lv_palette_main(LV_PALETTE_PINK),
//     0); lv_obj_set_size(top_right, 800/3, 480/3);

//     // 左下角控件
//     lv_obj_t *bottom_left = lv_obj_create(screen);
//     lv_obj_align(bottom_left, LV_ALIGN_BOTTOM_LEFT, 0, 0);
//     lv_obj_set_style_bg_color(bottom_left, lv_palette_main(LV_PALETTE_TEAL),
//     0); lv_obj_set_size(bottom_left, 800/3, 480/3);

//     // 右下角控件
//     lv_obj_t *bottom_right = lv_obj_create(screen);
//     lv_obj_align(bottom_right, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
//     lv_obj_set_style_bg_color(bottom_right, lv_palette_main(LV_PALETTE_LIME),
//     0); lv_obj_set_size(bottom_right, 800/3, 480/3);
// }

/**
 * @brief 对象信息结构体
 * @details 该结构体用于存储LVGL对象的对齐方式和颜色信息
 */
typedef struct {
  lv_align_t align;   /**< 对象对齐方式 */
  lv_palette_t color; /**< 对象颜色调色板 */
} obj_info_t;

/**
 * @brief 显示九宫格颜色
 */
void obj_pos1(void) {
  lv_obj_t *screen = lv_scr_act();  // 获取当前活动屏幕

  // 定义控件信息数组
  const obj_info_t obj_infos[] = {// 定义了位置和颜色
                                  {LV_ALIGN_CENTER, LV_PALETTE_RED},
                                  {LV_ALIGN_LEFT_MID, LV_PALETTE_BLUE},
                                  {LV_ALIGN_RIGHT_MID, LV_PALETTE_GREEN},
                                  {LV_ALIGN_TOP_MID, LV_PALETTE_YELLOW},
                                  {LV_ALIGN_BOTTOM_MID, LV_PALETTE_PURPLE},
                                  {LV_ALIGN_TOP_LEFT, LV_PALETTE_ORANGE},
                                  {LV_ALIGN_TOP_RIGHT, LV_PALETTE_PINK},
                                  {LV_ALIGN_BOTTOM_LEFT, LV_PALETTE_TEAL},
                                  {LV_ALIGN_BOTTOM_RIGHT, LV_PALETTE_LIME}};

  // 循环创建和设置控件
  for (int i = 0; i < sizeof(obj_infos) / sizeof(obj_infos[0]); i++) {
    lv_obj_t *obj = lv_obj_create(screen);        // 获取屏幕对象
    lv_obj_align(obj, obj_infos[i].align, 0, 0);  // 设置对象位置
    lv_obj_set_style_bg_color(obj, lv_palette_main(obj_infos[i].color),
                              0);            // 根据数组中的颜色设置对象背景色
    lv_obj_set_size(obj, 800 / 3, 480 / 3);  // 设置对象大小
  }
}

/**
 * @brief 创建对象位置2的函数
 * @details 该函数用于创建第二个对象位置布局（当前为空函数）
 */
void obj_pos2(void) { 
  lv_obj_t *screen = lv_scr_act(); // 获取当前活动屏幕

}

/**
 * @brief 对象相关操作函数
 * @details 该函数用于执行对象相关的操作（当前为空函数）
 */
void obj_xx(void) {}
