#pragma once

#include "ScreenWithLabel.h"

class DoorWindowScreen: public ScreenWithLabel
{
public:
    static DoorWindowScreen* instance;
    lv_obj_t* slider;
    lv_obj_t* image;
    lv_obj_t* value;
    lv_obj_t* obstruction;
    DoorWindowScreen();
};