#pragma once
#include "Screen.h"

class ScreenWithLabel: public Screen
{
public:
    lv_obj_t* label;
    ScreenWithLabel();
};