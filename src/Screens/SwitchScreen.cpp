#include "SwitchScreen.h"

SwitchScreen* SwitchScreen::instance = nullptr;

SwitchScreen::SwitchScreen()
{
    image = lv_img_create(screen);     
    lv_obj_align(image, LV_ALIGN_CENTER, 0, -32);  
    lv_obj_add_flag(image, LV_OBJ_FLAG_CLICKABLE); 

    value = lv_label_create(screen);
    lv_obj_set_width(value, LV_SIZE_CONTENT); 
    lv_obj_set_height(value, LV_SIZE_CONTENT); 
    lv_obj_set_align(value, LV_ALIGN_CENTER);
    lv_obj_align(value, LV_ALIGN_CENTER, 0, 34);  
    lv_obj_set_style_text_font(value, &Monserat40WithGermanLetters, LV_PART_MAIN | LV_STATE_DEFAULT); 
}
  