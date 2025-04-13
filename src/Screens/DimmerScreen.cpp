#include "DimmerScreen.h"

DimmerScreen* DimmerScreen::instance = nullptr;

DimmerScreen::DimmerScreen()
{
    value = lv_arc_create(screen);
    lv_obj_set_width(value, 200);
    lv_obj_set_height(value, 200);
    lv_obj_set_align(value, LV_ALIGN_CENTER);
    lv_arc_set_value(value, 0);
    lv_arc_set_bg_angles(value, 160, 20);
    lv_obj_set_style_arc_width(value, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    
    button = lv_btn_create(screen);
    lv_obj_set_width(button, 100);
    lv_obj_set_height(button, 50);
    lv_obj_set_align(button, LV_ALIGN_CENTER);
    lv_obj_add_flag(button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(button, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(button, lv_color_hex(0xFF7D00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(button, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);

    labelValue = lv_label_create(screen);
    lv_obj_set_width(labelValue, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(labelValue, LV_SIZE_CONTENT); /// 1
    lv_obj_align(labelValue, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_align(labelValue, LV_ALIGN_CENTER);
  
   
}