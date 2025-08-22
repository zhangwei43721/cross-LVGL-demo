#include "head.h"
#include <stdio.h>

// 事件回调函数
static void button_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);              // 获取事件代码
  lv_obj_t *label = (lv_obj_t *)lv_event_get_user_data(e);  // 获取用户数据

  if (code == LV_EVENT_CLICKED) {  // 判断是点击事件
    printf("被点击\n");
    lv_label_set_text(label, "clicked");
  }
}
static lv_style_t style_btn_green;
void obj_pos1(void) {
  // 创建基础面板
  lv_obj_t *parent_screen = lv_scr_act();          // 获取当前屏幕
  lv_obj_t *panel = lv_obj_create(parent_screen);  // 创建一个面板
  lv_obj_set_size(panel, 200, 200);                // 设置面板大小
  lv_obj_center(panel);                            // 将面板居中
  // 在面创建一个标签
  lv_obj_t *label = lv_label_create(panel);      // 创建一个标签
  lv_label_set_text(label, "Hello, World!");     // 设置标签文本
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);  // 标签顶部中对齐，并向下偏移20
  // 创建一个按钮,父对象是panel
  lv_obj_t *btn = lv_btn_create(panel);
  lv_obj_center(btn);  // 将按钮居中

  // 给按钮创建一个标签作为按钮的文本
  lv_obj_t *btn_label = lv_label_create(btn);
  lv_label_set_text(btn_label, "click me");
  lv_obj_center(btn_label);  // 将文字标签居中

  // 添加事件回调
  lv_obj_add_event_cb(btn, button_event_handler, LV_EVENT_CLICKED, label);
}

// 其他函数暂时不动
void obj_pos2(void) {}
void obj_xx(void) {}