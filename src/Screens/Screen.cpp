#include "Screen.h"

Screen::Screen()
{
    screen = lv_obj_create(NULL);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
}

void Screen::show()
{
    lv_scr_load(screen);
}

Screen::~Screen()
{
    lv_obj_del(screen);
}