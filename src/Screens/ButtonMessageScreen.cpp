#include "ButtonMessageScreen.h"

#include "DisplayLed.h"

IButtonMessageScreen* IButtonMessageScreen::instance = nullptr;

ButtonMessageScreen::ButtonMessageScreen()
{

    _led1 = lv_led_create(screen);
    lv_obj_align(_led1, LV_ALIGN_TOP_MID, -28, 15);
    lv_obj_set_size(_led1, 15, 15);
   
    _led2 = lv_led_create(screen);
    lv_obj_align(_led2, LV_ALIGN_TOP_MID, 0, 15);
    lv_obj_set_size(_led2, 15, 15);
   
    _led3 = lv_led_create(screen);
    lv_obj_align(_led3, LV_ALIGN_TOP_MID, 28, 15);
    lv_obj_set_size(_led3, 15, 15);
   
    _message = lv_label_create(screen);
    lv_obj_set_width(_message, LV_SIZE_CONTENT);
    lv_obj_set_height(_message, LV_SIZE_CONTENT);
    lv_obj_set_align(_message, LV_ALIGN_CENTER);
    lv_obj_set_style_text_align(_message, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(_message, LV_ALIGN_CENTER, 0, -40);
 
    _button = lv_btn_create(screen);
    lv_obj_align(_button, LV_ALIGN_CENTER, 0, 40);
    lv_obj_set_width(_button, 180);
    lv_obj_set_height(_button, 50);
    lv_obj_set_align(_button, LV_ALIGN_CENTER);
    lv_obj_add_flag(_button, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_style_bg_color(_button, lv_color_hex(0xFF7D00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(_button, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_event_cb(_button, OnPrimaryAction, LV_EVENT_CLICKED, this);

    _buttonText = lv_label_create(_button);
    lv_obj_center(_buttonText);
}

void ButtonMessageScreen::OnPrimaryAction(lv_event_t* e)
{
    auto* self = static_cast<ButtonMessageScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPrimaryAction)
        return;
    self->_onPrimaryAction();
}

lv_obj_t* ButtonMessageScreen::ledObject(uint8_t index)
{
    switch (index)
    {
    case 0:
        return _led1;
    case 1:
        return _led2;
    case 2:
        return _led3;
    default:
        return nullptr;
    }
}

void ButtonMessageScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void ButtonMessageScreen::SetMessageText(const char* text)
{
    lv_label_set_text(_message, text);
}

void ButtonMessageScreen::SetButtonText(const char* text)
{
    lv_label_set_text(_buttonText, text);
}

void ButtonMessageScreen::SetPrimaryActionChecked(bool checked)
{
    if (checked)
        lv_obj_add_state(_button, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(_button, LV_STATE_CHECKED);
}

void ButtonMessageScreen::RegisterPrimaryAction(std::function<void()> callback)
{
    _onPrimaryAction = callback;
}

void ButtonMessageScreen::ConnectLed(uint8_t index, DisplayLed* led)
{
    if (led == nullptr)
        return;
    led->setLedObject(ledObject(index));
}

void ButtonMessageScreen::Show()
{
    show();
}