// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: Visu

#include "../ui.h"

void ui_Dimm_screen_init(void)
{
    ui_Dimm = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Dimm, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_DimmValue = lv_arc_create(ui_Dimm);
    lv_obj_set_width(ui_DimmValue, 200);
    lv_obj_set_height(ui_DimmValue, 200);
    lv_obj_set_align(ui_DimmValue, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_DimmValue, 0);
    lv_arc_set_bg_angles(ui_DimmValue, 160, 20);
    lv_arc_set_value(ui_DimmValue, 0);
    lv_obj_set_style_arc_width(ui_DimmValue, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    
    ui_DimmSwitch = lv_btn_create(ui_Dimm);
    lv_obj_set_width(ui_DimmSwitch, 100);
    lv_obj_set_height(ui_DimmSwitch, 50);
    lv_obj_set_align(ui_DimmSwitch, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DimmSwitch, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_DimmSwitch, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_DimmSwitch, lv_color_hex(0xFF7D00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_DimmSwitch, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_flag(ui_DimmSwitch, LV_OBJ_FLAG_CHECKABLE);

    ui_DimmLabelValue = lv_label_create(ui_Dimm);
    lv_obj_set_width(ui_DimmLabelValue, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DimmLabelValue, LV_SIZE_CONTENT); /// 1
    lv_obj_align(ui_DimmLabelValue, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_align(ui_DimmLabelValue, LV_ALIGN_CENTER);
  
    ui_DimmLabel = lv_label_create(ui_Dimm);
    lv_obj_set_width(ui_DimmLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DimmLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DimmLabel, 0);
    lv_obj_set_y(ui_DimmLabel, 80);
    lv_obj_set_align(ui_DimmLabel, LV_ALIGN_CENTER);
    
}

 