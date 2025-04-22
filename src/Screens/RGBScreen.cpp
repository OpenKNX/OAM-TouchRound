#include "RGBScreen.h"
#include "OpenKNX.h"

RGBScreen* RGBScreen::instance = nullptr;

RGBScreen::RGBScreen()
{
    value = lv_label_create(screen);
    lv_obj_set_width(value, LV_SIZE_CONTENT); 
    lv_obj_set_height(value, LV_SIZE_CONTENT);
    lv_obj_set_align(value, LV_ALIGN_RIGHT_MID);
    lv_obj_align(value, LV_ALIGN_RIGHT_MID, -115, -20);  
    lv_obj_set_style_text_font(value, &Monserat40WithGermanLetters, LV_PART_MAIN | LV_STATE_DEFAULT); 
  
    image = lv_img_create(screen);  
    lv_obj_align(image, LV_ALIGN_CENTER, 40, -20);  
    lv_obj_add_flag(image, LV_OBJ_FLAG_CLICKABLE);

    currentColor = lv_arc_create(screen);
    lv_obj_set_size(currentColor, 240, 240);
    lv_arc_set_range(currentColor,0, 100);
    lv_arc_set_value(currentColor, 0);
    lv_arc_set_bg_angles(currentColor, 0, 360);
    lv_obj_remove_style(currentColor, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(currentColor, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align(currentColor, LV_ALIGN_CENTER, 0, 0);
    
    lv_style_init(&colorStyle);
    lv_style_set_arc_color(&colorStyle, lv_color_make(128,128,128)); 
    lv_style_set_arc_width(&colorStyle, 10);
    lv_obj_add_style(currentColor, &colorStyle, LV_PART_MAIN);



    lv_event_cb_t _eventHandleChanged =[](lv_event_t *e) { ((RGBScreen*) lv_event_get_user_data(e))->colorChanged(e); };
  

    hueSlider = lv_slider_create(screen);
    lv_obj_set_size(hueSlider, 170, 25);
    lv_slider_set_range(hueSlider, 0, 359);
    lv_obj_align(hueSlider, LV_ALIGN_CENTER, 0, 40);  
    lv_obj_add_event_cb(hueSlider, _eventHandleChanged, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(hueSlider, _eventHandleChanged, LV_EVENT_PRESSING, this);
    lv_obj_set_style_bg_opa(hueSlider, LV_OPA_TRANSP, LV_PART_INDICATOR);

   
    brightnessSlider = lv_arc_create(screen);
    lv_obj_set_width(brightnessSlider, 220);
    lv_obj_set_height(brightnessSlider, 220);
    lv_obj_set_align(brightnessSlider, LV_ALIGN_CENTER);
    lv_arc_set_value(brightnessSlider, 0);
    lv_arc_set_bg_angles(brightnessSlider, 180, 260);
    lv_arc_set_range(brightnessSlider, 0, 100);
    lv_obj_set_style_arc_width(brightnessSlider, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_flag(brightnessSlider, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(brightnessSlider, _eventHandleChanged, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(brightnessSlider, _eventHandleChanged, LV_EVENT_PRESSING, this); 


    saturationSlider = lv_arc_create(screen);
    lv_obj_set_width(saturationSlider, 220);
    lv_obj_set_height(saturationSlider, 220);
    lv_obj_set_align(saturationSlider, LV_ALIGN_CENTER);
    lv_arc_set_value(saturationSlider, 0);
    lv_arc_set_bg_angles(saturationSlider, 290, 0);
    lv_arc_set_range(saturationSlider, 0, 100);
    lv_obj_set_style_arc_width(saturationSlider, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_flag(saturationSlider, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(saturationSlider, _eventHandleChanged, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(saturationSlider, _eventHandleChanged, LV_EVENT_PRESSING, this);


}

void RGBScreen::setRGB(uint8_t r, uint8_t g, uint8_t b) 
{
    if (isPressed) {
        return;
    }
    red = r;
    green = g;
    blue = b;
    auto lv_color_hsv_t = lv_color_rgb_to_hsv(r, g, b);
   
    updateColor();
    updateSlider(r, g, b);
}

void RGBScreen::colorChanged(lv_event_t* e)
{
    isPressed = lv_event_get_code(e) == LV_EVENT_PRESSING;
    auto hue = lv_slider_get_value(hueSlider);
    auto saturation = lv_arc_get_value(saturationSlider);
    auto brightness = lv_arc_get_value(brightnessSlider);
    auto color = lv_color_hsv_to_rgb(hue, saturation, brightness);
    red = color.red;
    green = color.green;
    blue = color.blue;

    updateColor();
}

void RGBScreen::updateSlider(uint8_t r, uint8_t g, uint8_t b)
{
    auto hsv = lv_color_rgb_to_hsv(r, g, b);
    lv_slider_set_value(hueSlider, hsv.h, LV_ANIM_OFF);
    lv_arc_set_value(saturationSlider, hsv.s);
    lv_arc_set_value(brightnessSlider, hsv.v);
}

void RGBScreen::updateColor()
{
    lv_style_set_arc_color(&colorStyle, lv_color_make(red, green, blue));
    lv_obj_add_style(currentColor, &colorStyle, LV_PART_MAIN);
}
