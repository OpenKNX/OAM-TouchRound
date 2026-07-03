#include "DateTimeScreen.h"

IDateTimeScreen* IDateTimeScreen::instance = nullptr;

DateTimeScreen::DateTimeScreen()
{
    lv_obj_add_event_cb(screen, OnScreenPressed, LV_EVENT_PRESSED, this);

    _weekday = lv_label_create(screen);
    lv_obj_set_width(_weekday, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(_weekday, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(_weekday, 0);
    lv_obj_set_y(_weekday, -60);
    lv_obj_set_align(_weekday, LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(_weekday, &FONT_MEDIUM, LV_PART_MAIN | LV_STATE_DEFAULT); 
  
  
    _date = lv_label_create(screen);
    lv_obj_set_width(_date, LV_SIZE_CONTENT); 
    lv_obj_set_height(_date, LV_SIZE_CONTENT);
    lv_obj_set_x(_date, 0);
    lv_obj_set_y(_date, -30);
    lv_obj_set_align(_date, LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(_date, &FONT_MEDIUM, LV_PART_MAIN | LV_STATE_DEFAULT); 
  
  
    _time = lv_label_create(screen);
    lv_obj_set_width(_time, LV_SIZE_CONTENT);
    lv_obj_set_height(_time, LV_SIZE_CONTENT);
    lv_obj_set_x(_time, 0);
    lv_obj_set_y(_time, 30);
    lv_obj_set_align(_time, LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(_time, &FONT_LARGE, LV_PART_MAIN | LV_STATE_DEFAULT); 
  
    _message = lv_label_create(screen);
    lv_obj_set_width(_message, 250);
    lv_obj_set_height(_message, LV_SIZE_CONTENT);
    lv_label_set_long_mode(_message, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(_message, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(_message, LV_ALIGN_CENTER);
  
}

void DateTimeScreen::OnScreenPressed(lv_event_t* e)
{
    auto* self = static_cast<DateTimeScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onScreenPressed)
        return;
    self->_onScreenPressed();
}

void DateTimeScreen::SetWeekdayText(const char* text)
{
    lv_label_set_text(_weekday, text);
}

void DateTimeScreen::SetDateText(const char* text)
{
    lv_label_set_text(_date, text);
}

void DateTimeScreen::SetTimeText(const char* text)
{
    lv_label_set_text(_time, text);
}

void DateTimeScreen::SetMessageText(const char* text)
{
    lv_label_set_text(_message, text);
}

void DateTimeScreen::RegisterScreenPressed(std::function<void()> callback)
{
    _onScreenPressed = callback;
}

void DateTimeScreen::Show()
{
    show();
}