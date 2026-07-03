#include "ScreenWithLabel.h"

ScreenWithLabel::ScreenWithLabel()
{
    label = lv_label_create(screen);
    lv_obj_set_width(label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(label, 0);
    lv_obj_set_y(label, 80);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
}