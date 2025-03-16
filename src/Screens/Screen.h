#pragma once
#include "lvgl.h"

class Screen
{
public:
    lv_obj_t *screen;

public:
    Screen();
    void show();
    virtual ~Screen();
};