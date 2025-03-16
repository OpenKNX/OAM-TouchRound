#pragma once

#include "ScreenWithLabel.h"

class DimmerScreen: public ScreenWithLabel
{
    public:
    static DimmerScreen* instance;
    lv_obj_t* value;
    lv_obj_t* labelValue;
    lv_obj_t* button;


    DimmerScreen();
};