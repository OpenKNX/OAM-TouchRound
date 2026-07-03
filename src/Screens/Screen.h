#pragma once
#include "lvgl.h"

class Screen
{
    static bool _showBackground;
    static lv_color_t _backgroundColor;
public:
    lv_obj_t *screen;

protected:
    virtual bool useCustomBackgroundColor();
    virtual lv_color_t customBackgroundColor();
    void updateBackgroundColor();
 
public:
    static void setBackgroundColor(lv_color_t color);
    static void removeBackgroundColor();
    Screen();
    void show();
    virtual ~Screen();
};