#include "Screen.h"

Screen::Screen()
{
    screen = lv_obj_create(NULL);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
}

bool Screen::_showBackground = false;
lv_color_t Screen::_backgroundColor = lv_color_black();

void Screen::setBackgroundColor(lv_color_t color)
{
    _backgroundColor = color;
    _showBackground = true;
}

void Screen::removeBackgroundColor()
{
    _showBackground = false;
}

bool Screen::useCustomBackgroundColor()
{
    return false;
}

lv_color_t Screen::customBackgroundColor()
{
    return lv_color_black();
}

void Screen::show()
{
    updateBackgroundColor();
    lv_scr_load(screen);
}

void Screen::updateBackgroundColor()
{
    if (useCustomBackgroundColor())
    {
        lv_obj_set_style_bg_color(screen, customBackgroundColor(), 0);
    }
    else if (_showBackground)
        lv_obj_set_style_bg_color(screen, _backgroundColor, 0);
    else
        lv_theme_apply(screen);
}

Screen::~Screen()
{
    lv_obj_del(screen);
}

