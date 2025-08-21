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
//     lv_obj_set_style_bg_color(top, lv_palette_main(LV_PALETTE_YELLOW), LV_PART_MAIN);
//     lv_obj_set_size(top, 800/3, 480/3);

//     // 底部控件
//     lv_obj_t *bottom = lv_obj_create(screen);
//     lv_obj_align(bottom, LV_ALIGN_BOTTOM_MID, 0, 0);
//     lv_obj_set_style_bg_color(bottom, lv_palette_main(LV_PALETTE_PURPLE), 0);
//     lv_obj_set_size(bottom, 800/3, 480/3);

//     // 左上角控件
//     lv_obj_t *top_left = lv_obj_create(screen);
//     lv_obj_align(top_left, LV_ALIGN_TOP_LEFT, 0, 0);
//     lv_obj_set_style_bg_color(top_left, lv_palette_main(LV_PALETTE_ORANGE), 0);
//     lv_obj_set_size(top_left, 800/3, 480/3);

//     // 右上角控件
//     lv_obj_t *top_right = lv_obj_create(screen);
//     lv_obj_align(top_right, LV_ALIGN_TOP_RIGHT, 0, 0);
//     lv_obj_set_style_bg_color(top_right, lv_palette_main(LV_PALETTE_PINK), 0);
//     lv_obj_set_size(top_right, 800/3, 480/3);

//     // 左下角控件
//     lv_obj_t *bottom_left = lv_obj_create(screen);
//     lv_obj_align(bottom_left, LV_ALIGN_BOTTOM_LEFT, 0, 0);
//     lv_obj_set_style_bg_color(bottom_left, lv_palette_main(LV_PALETTE_TEAL), 0);
//     lv_obj_set_size(bottom_left, 800/3, 480/3);

//     // 右下角控件
//     lv_obj_t *bottom_right = lv_obj_create(screen);
//     lv_obj_align(bottom_right, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
//     lv_obj_set_style_bg_color(bottom_right, lv_palette_main(LV_PALETTE_LIME), 0);
//     lv_obj_set_size(bottom_right, 800/3, 480/3);
// }


typedef struct {
    lv_align_t align;
    lv_palette_t color;
} obj_info_t;

void obj_pos(void)
{
    lv_obj_t *screen = lv_scr_act();
    
    // 定义控件信息数组
    const obj_info_t obj_infos[] = {
        {LV_ALIGN_CENTER, LV_PALETTE_RED},
        {LV_ALIGN_LEFT_MID, LV_PALETTE_BLUE},
        {LV_ALIGN_RIGHT_MID, LV_PALETTE_GREEN},
        {LV_ALIGN_TOP_MID, LV_PALETTE_YELLOW},
        {LV_ALIGN_BOTTOM_MID, LV_PALETTE_PURPLE},
        {LV_ALIGN_TOP_LEFT, LV_PALETTE_ORANGE},
        {LV_ALIGN_TOP_RIGHT, LV_PALETTE_PINK},
        {LV_ALIGN_BOTTOM_LEFT, LV_PALETTE_TEAL},
        {LV_ALIGN_BOTTOM_RIGHT, LV_PALETTE_LIME}
    };

    // 循环创建和设置控件
    for(int i = 0; i < sizeof(obj_infos)/sizeof(obj_infos[0]); i++) {
        lv_obj_t *obj = lv_obj_create(screen);
        lv_obj_align(obj, obj_infos[i].align, 0, 0);
        lv_obj_set_style_bg_color(obj, lv_palette_main(obj_infos[i].color), 0);
        lv_obj_set_size(obj, 800/3, 480/3);
    }
}


void obj_xx(void)
{

}