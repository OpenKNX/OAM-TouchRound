#pragma once

#include "ScreenWithLabel.h"

class DateTimeScreen: public Screen
{
    public:
    static DateTimeScreen* instance;
    lv_obj_t* weekday;
    lv_obj_t* date;
    lv_obj_t* time;
    lv_obj_t* message;
    DateTimeScreen();
};