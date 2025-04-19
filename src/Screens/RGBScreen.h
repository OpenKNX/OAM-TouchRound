#pragma once

#include "ScreenWithLabel.h"

class RGBScreen : public ScreenWithLabel
{
    void hsv_event_handler(lv_event_t* e);
public:
    static RGBScreen* instance;
    lv_obj_t* brightnessSlider;
    lv_obj_t* value;
    lv_obj_t* canvas;
    lv_obj_t* image;
    lv_obj_t* currentColor;
    lv_obj_t* hsvContainer;
    lv_style_t colorStyle;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint8_t hue = 0;
    uint8_t saturation = 0;
    uint8_t brightness = 0;
    bool isPressed = false;
    RGBScreen();

    void setRGB(uint8_t r, uint8_t g, uint8_t b);
    void updateColor();

};