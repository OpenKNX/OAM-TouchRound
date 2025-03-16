#include "MessageScreen.h"

MessageScreen* MessageScreen::instance = nullptr;

MessageScreen::MessageScreen()
{
    message = lv_label_create(screen);
    lv_obj_set_width(message, LV_SIZE_CONTENT);
    lv_obj_set_height(message, LV_SIZE_CONTENT); 
    lv_obj_set_align(message, LV_ALIGN_CENTER);
    lv_obj_set_style_text_align(message, LV_TEXT_ALIGN_CENTER, 0);
}