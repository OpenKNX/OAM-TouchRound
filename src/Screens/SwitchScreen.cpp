#include "SwitchScreen.h"

SwitchScreen* SwitchScreen::instance = nullptr;

SwitchScreen::SwitchScreen()
{
    button = lv_btn_create(screen);
    lv_obj_set_width(button, 100);
    lv_obj_set_height(button, 50);
    lv_obj_set_align(button, LV_ALIGN_CENTER);
    lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_style_bg_color(button, lv_color_hex(0xFF7D00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(button, 255, LV_PART_MAIN | LV_STATE_CHECKED);
}
