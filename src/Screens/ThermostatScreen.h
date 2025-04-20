#pragma once

#include "ScreenWithLabel.h"

class ThermostatScreen: public ScreenWithLabel
{
public:
    static ThermostatScreen* instance;
    lv_obj_t* labelMode;
    lv_obj_t* labelValue;
    lv_obj_t* buttonUp;
    lv_obj_t* buttonDown;
    lv_obj_t* image;
    lv_obj_t* value;

    ThermostatScreen();
};