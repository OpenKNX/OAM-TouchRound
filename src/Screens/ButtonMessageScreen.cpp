#include "ButtonMessageScreen.h"

ButtonMessageScreen* ButtonMessageScreen::instance = nullptr;

ButtonMessageScreen::ButtonMessageScreen()
{
    message = lv_label_create(screen);
    lv_obj_set_width(message, LV_SIZE_CONTENT);
    lv_obj_set_height(message, LV_SIZE_CONTENT); 
    lv_obj_set_align(message, LV_ALIGN_CENTER);
    lv_obj_set_style_text_align(message, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(message, LV_ALIGN_CENTER, 0, -30);  
 
    button = lv_btn_create(screen);
    lv_obj_align(button, LV_ALIGN_CENTER, 0, 40);  
    lv_obj_set_width(button, 180);
    lv_obj_set_height(button, 50);
    lv_obj_set_align(button, LV_ALIGN_CENTER);
    lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_style_bg_color(button, lv_color_hex(0xFF7D00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(button, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    buttonText = lv_label_create(button); 
    lv_obj_center(buttonText); 
}