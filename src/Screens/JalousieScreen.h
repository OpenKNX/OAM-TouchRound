#pragma once

#include "RolladenScreen.h"


class JalousieScreen: public RolladenScreen
{
    public:
    static JalousieScreen* instance;

    lv_obj_t* sliderSlat;

    JalousieScreen();
};