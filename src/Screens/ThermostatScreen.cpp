#include "ThermostatScreen.h"
#include "ImageLoader.h"

ThermostatScreen* ThermostatScreen::instance = nullptr;

ThermostatScreen::ThermostatScreen() 
{
    labelMode = lv_label_create(screen);
    lv_obj_set_width(labelMode, LV_SIZE_CONTENT);  
    lv_obj_set_height(labelMode, LV_SIZE_CONTENT); 
    lv_obj_set_align(labelMode, LV_ALIGN_CENTER);
    lv_obj_align(labelMode, LV_ALIGN_TOP_MID, 0, 11); 

    labelValue = lv_label_create(screen);
    lv_obj_set_width(labelValue, LV_SIZE_CONTENT);  
    lv_obj_set_height(labelValue, LV_SIZE_CONTENT); 
    lv_obj_set_align(labelValue, LV_ALIGN_CENTER);
    lv_obj_align(labelValue, LV_ALIGN_TOP_MID, 0, 31); 

    image = lv_img_create(screen);  
    lv_obj_align(image, LV_ALIGN_CENTER, 32, -25);  

    buttonUp = lv_image_create(screen);
    lv_obj_align(buttonUp, LV_ALIGN_TOP_LEFT, 42, 73);
    ImageLoader::loadImage(buttonUp, "up.png", false, 0);

    buttonDown = lv_image_create(screen);
    lv_obj_align(buttonDown, LV_ALIGN_TOP_LEFT, 42, 132);
    ImageLoader::loadImage(buttonDown, "down.png", false, 0);

    value = lv_label_create(screen);
    lv_obj_set_width(value, LV_SIZE_CONTENT);  
    lv_obj_set_height(value, LV_SIZE_CONTENT); 
    lv_obj_set_align(value, LV_ALIGN_CENTER);
    lv_obj_align(value, LV_ALIGN_CENTER, 32, 40);  
    lv_obj_set_style_text_font(value, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT); 
}