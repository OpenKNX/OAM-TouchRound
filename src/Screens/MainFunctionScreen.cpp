#include "MainFunctionScreen.h"
#include "../Images/lamp-outline.c"

MainFunctionScreen* MainFunctionScreen::instance = nullptr;

MainFunctionScreen::MainFunctionScreen() 
{
    image = lv_img_create(screen);  
    //lv_img_set_src(image, &lamp_outline);       
    lv_obj_align(image, LV_ALIGN_CENTER, 0, -65);  
  
    value = lv_label_create(screen);
    lv_obj_set_width(value, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(value, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(value, LV_ALIGN_CENTER);
    lv_obj_align(value, LV_ALIGN_CENTER, 0, 10);  
    lv_obj_set_style_text_font(value, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT); 
}