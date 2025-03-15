#pragma once

#include "ScreenWithLabel.h"

class SwitchScreen: public ScreenWithLabel
{
    public:
    static SwitchScreen* instance;
    lv_obj_t* button;
    SwitchScreen();
};