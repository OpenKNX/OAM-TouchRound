#include "DoorWindowScreen.h"

DoorWindowScreen* DoorWindowScreen::instance = nullptr;

DoorWindowScreen::DoorWindowScreen() 
{
    slider = lv_slider_create(screen);
    lv_obj_set_size(slider, 138, 25);
    lv_slider_set_range(slider, 0, 100);
    lv_obj_align(slider, LV_ALIGN_TOP_MID, 0, 45);  

    image = lv_img_create(screen);  
    lv_obj_align(image, LV_ALIGN_CENTER, 0, -15); 
    lv_obj_add_flag(image, LV_OBJ_FLAG_CLICKABLE); 

    obstruction = lv_img_create(screen);  
    lv_obj_align(obstruction, LV_ALIGN_CENTER, 73, -15);  

    movement = lv_img_create(screen);  
    lv_obj_align(movement, LV_ALIGN_CENTER, -73, -15);  
   
    value = lv_label_create(screen);
    lv_obj_set_width(value, LV_SIZE_CONTENT);  
    lv_obj_set_height(value, LV_SIZE_CONTENT); 
    lv_obj_set_align(value, LV_ALIGN_CENTER);
    lv_obj_align(value, LV_ALIGN_CENTER, 0, 40);  
    lv_obj_set_style_text_font(value, &Monserat40WithGermanLetters, LV_PART_MAIN | LV_STATE_DEFAULT); 
}