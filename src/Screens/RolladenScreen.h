#pragma once

#include "ScreenWithLabel.h"

class RolladenScreen: public ScreenWithLabel
{
    public:
    static RolladenScreen* instance;
    lv_obj_t* icon;
    lv_obj_t* value;
    lv_obj_t* buttonUp;
    lv_obj_t* buttonDown;
    lv_obj_t* buttonStop;
    lv_obj_t* sliderPosition;

    RolladenScreen();
};