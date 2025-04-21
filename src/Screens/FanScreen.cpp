#include "FanScreen.h"

FanScreen* FanScreen::instance = nullptr;

FanScreen::FanScreen() 
{
    buttonAuto = lv_btn_create(screen);
    lv_obj_align(buttonAuto, LV_ALIGN_CENTER, 0, -80);  
    lv_obj_set_size(buttonAuto, 90, 40);
    lv_obj_add_flag(buttonAuto, LV_OBJ_FLAG_CHECKABLE);

    buttonAutoLabel = lv_label_create(buttonAuto);
    lv_label_set_text(buttonAutoLabel, "Auto");
    lv_obj_center(buttonAutoLabel);

    image = lv_img_create(screen);  
    lv_obj_align(image, LV_ALIGN_CENTER, 0, -15);  
    lv_obj_add_flag(image, LV_OBJ_FLAG_CLICKABLE); 
  
    value = lv_label_create(screen);
    lv_obj_set_width(value, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(value, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(value, LV_ALIGN_CENTER);
    lv_obj_align(value, LV_ALIGN_CENTER, 0, 40);  
    lv_obj_set_style_text_font(value, &Monserat40WithGermanLetters, LV_PART_MAIN | LV_STATE_DEFAULT); 
}