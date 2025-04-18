#pragma once

#include "ScreenWithLabel.h"

class RGBScreen : public ScreenWithLabel
{
    void hsv_event_handler(lv_event_t* e);
public:
    static RGBScreen* instance;
    lv_obj_t* colorPicker;
    lv_obj_t* valueSlider;
    lv_obj_t* value;
    lv_obj_t* canvas;
    lv_obj_t* image;

    bool hasNewColor = false;
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    RGBScreen();
};