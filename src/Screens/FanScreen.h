#pragma once

#include "ScreenWithLabel.h"

class FanScreen: public ScreenWithLabel
{
public:
    static FanScreen* instance;
    lv_obj_t* buttonAuto;
    lv_obj_t* buttonAutoLabel;
    lv_obj_t* image;
    lv_obj_t* value;
    FanScreen();
};