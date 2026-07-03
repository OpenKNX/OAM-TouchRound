#include "MessageScreen.h"

IMessageScreen* IMessageScreen::instance = nullptr;

MessageScreen::MessageScreen()
{
    _message = lv_label_create(screen);
    lv_obj_set_width(_message, LV_SIZE_CONTENT);
    lv_obj_set_height(_message, LV_SIZE_CONTENT);
    lv_obj_set_align(_message, LV_ALIGN_CENTER);
    lv_obj_set_style_text_align(_message, LV_TEXT_ALIGN_CENTER, 0);
}

void MessageScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void MessageScreen::SetMessageText(const char* text)
{
    lv_label_set_text(_message, text);
}

void MessageScreen::Show()
{
    show();
}