#pragma once

#include "ScreenWithLabel.h"

class RGBScreen : public ScreenWithLabel
{
public:
    static RGBScreen* instance;
    lv_obj_t* colorPicker;
    lv_obj_t* valueSlider;
    lv_obj_t* labelValue;

    RGBScreen();
};