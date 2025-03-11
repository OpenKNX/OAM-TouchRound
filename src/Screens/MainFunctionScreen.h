#pragma once

#include "ScreenWithLabel.h"

class MainFunctionScreen: public ScreenWithLabel
{
    public:
    static MainFunctionScreen* instance;
    lv_obj_t* image;
    lv_obj_t* value;
    MainFunctionScreen();
};