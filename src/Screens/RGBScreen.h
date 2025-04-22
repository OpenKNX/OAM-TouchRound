#pragma once

#include "ScreenWithLabel.h"

class RGBScreen : public ScreenWithLabel
{
    void colorChanged(lv_event_t* e);
    void updateColor();
    void updateSlider(uint8_t r, uint8_t g, uint8_t b);

public:
    static RGBScreen* instance;
    lv_style_t colorStyle;
    lv_obj_t* image;
    lv_obj_t* brightnessSlider;
    lv_obj_t* saturationSlider;
    lv_obj_t* hueSlider;
    lv_obj_t* value;
    lv_obj_t* currentColor;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    bool isPressed = false;
  
    RGBScreen();


    void setRGB(uint8_t r, uint8_t g, uint8_t b);
 

};