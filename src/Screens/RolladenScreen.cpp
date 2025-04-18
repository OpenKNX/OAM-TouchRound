#include "RolladenScreen.h"
#include "../ImageLoader.h"


RolladenScreen* RolladenScreen::instance = nullptr;

RolladenScreen::RolladenScreen()
{
    icon = lv_img_create(screen);
    lv_obj_align(icon, LV_ALIGN_CENTER, 0, -10);  
 
    buttonUp = lv_img_create(screen);
    ImageLoader::loadImage(buttonUp, "up.png", false, false);
    lv_obj_add_flag(buttonUp, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_img_recolor_opa(buttonUp, 255, 0);
    lv_obj_set_style_img_recolor(buttonUp, lv_color_make(128, 128, 128), 0);
    lv_obj_align(buttonUp, LV_ALIGN_TOP_MID, 0, 34);  
   
    buttonDown = lv_img_create(screen);
    ImageLoader::loadImage(buttonDown, "down.png", false, false);
    lv_obj_add_flag(buttonDown, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_img_recolor_opa(buttonDown, 255, 0);
    lv_obj_set_style_img_recolor(buttonDown, lv_color_make(128, 128, 128), 0);
    lv_obj_align(buttonDown, LV_ALIGN_BOTTOM_MID, 0, -56);  

    sliderPosition = lv_slider_create(screen);
    lv_obj_set_size(sliderPosition, 20, 110);
    lv_slider_set_range(sliderPosition, 0, 100);  
    lv_obj_align(sliderPosition, LV_ALIGN_LEFT_MID, 35, -10);  

     
    value = lv_label_create(screen);
    lv_obj_set_width(value, LV_SIZE_CONTENT);
    lv_obj_set_height(value, LV_SIZE_CONTENT);
    lv_obj_set_align(value, LV_ALIGN_CENTER);
    lv_obj_align(value, LV_ALIGN_TOP_MID, 0, 13);  
    
}
