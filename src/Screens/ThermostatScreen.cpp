#include "ThermostatScreen.h"

#include "ImageLoader.h"
#include "TouchDisplayModule.h"

IThermostatScreen* IThermostatScreen::instance = nullptr;

ThermostatScreen::ThermostatScreen()
{
    _labelMode = lv_label_create(screen);
    lv_obj_set_width(_labelMode, LV_SIZE_CONTENT);
    lv_obj_set_height(_labelMode, LV_SIZE_CONTENT);
    lv_obj_set_align(_labelMode, LV_ALIGN_CENTER);
    lv_obj_align(_labelMode, LV_ALIGN_TOP_MID, 0, 11);

    _labelValue = lv_label_create(screen);
    lv_obj_set_width(_labelValue, LV_SIZE_CONTENT);
    lv_obj_set_height(_labelValue, LV_SIZE_CONTENT);
    lv_obj_set_align(_labelValue, LV_ALIGN_CENTER);
    lv_obj_align(_labelValue, LV_ALIGN_TOP_MID, 0, 31);

    _image = lv_img_create(screen);
    lv_obj_align(_image, LV_ALIGN_CENTER, 32, -25);
    lv_obj_add_flag(_image, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_image, OnMainAction, LV_EVENT_CLICKED, this);

    _buttonIncrease = lv_img_create(screen);
    lv_obj_align(_buttonIncrease, LV_ALIGN_TOP_LEFT, 42, 73);
    lv_obj_add_flag(_buttonIncrease, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_buttonIncrease, OnIncreaseAction, LV_EVENT_CLICKED, this);
    ImageLoader::loadImage(_buttonIncrease, "up.png", false, false);

    _buttonDecrease = lv_img_create(screen);
    lv_obj_align(_buttonDecrease, LV_ALIGN_TOP_LEFT, 42, 132);
    lv_obj_add_flag(_buttonDecrease, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_buttonDecrease, OnDecreaseAction, LV_EVENT_CLICKED, this);
    ImageLoader::loadImage(_buttonDecrease, "down.png", false, false);

    _value = lv_label_create(screen);
    lv_obj_set_width(_value, LV_SIZE_CONTENT);
    lv_obj_set_height(_value, LV_SIZE_CONTENT);
    lv_obj_set_align(_value, LV_ALIGN_CENTER);
    lv_obj_align(_value, LV_ALIGN_CENTER, 32, 40);
    lv_obj_set_style_text_font(_value, &FONT_LARGE, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ThermostatScreen::OnIncreaseAction(lv_event_t* e)
{
    auto* self = static_cast<ThermostatScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onIncreaseAction)
        return;
    self->_onIncreaseAction();
}

void ThermostatScreen::OnDecreaseAction(lv_event_t* e)
{
    auto* self = static_cast<ThermostatScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onDecreaseAction)
        return;
    self->_onDecreaseAction();
}

void ThermostatScreen::OnMainAction(lv_event_t* e)
{
    auto* self = static_cast<ThermostatScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onMainAction)
        return;
    self->_onMainAction();
}

void ThermostatScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void ThermostatScreen::SetModeText(const char* text)
{
    lv_label_set_text(_labelMode, text);
}

void ThermostatScreen::SetRoomTemperatureText(const char* text)
{
    lv_label_set_text(_labelValue, text);
}

void ThermostatScreen::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void ThermostatScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

void ThermostatScreen::SetCurrentState(ThermostatCurrentState currentState)
{
    switch (currentState)
    {
    case ThermostatCurrentState::ThermostatCurrentStateOff:
        ImageLoader::colorImage(_buttonIncrease, openknxTouchDisplayModule.getInactiveColor());
        ImageLoader::colorImage(_buttonDecrease, openknxTouchDisplayModule.getInactiveColor());
        ImageLoader::colorImage(_image, openknxTouchDisplayModule.getInactiveColor());
        break;
    case ThermostatCurrentState::ThermostatCurrentStateHeating:
        ImageLoader::colorImage(_buttonIncrease, openknxTouchDisplayModule.getActiveColor());
        ImageLoader::colorImage(_buttonDecrease, openknxTouchDisplayModule.getInactiveColor());
        ImageLoader::colorImage(_image, openknxTouchDisplayModule.getActiveColor());
        break;
    case ThermostatCurrentState::ThermostatCurrentStateCooling:
        ImageLoader::colorImage(_buttonIncrease, openknxTouchDisplayModule.getInactiveColor());
        ImageLoader::colorImage(_buttonDecrease, openknxTouchDisplayModule.getActiveColor());
        ImageLoader::colorImage(_image, openknxTouchDisplayModule.getActiveColor());
        break;
    }
}

void ThermostatScreen::RegisterIncreaseAction(std::function<void()> callback)
{
    _onIncreaseAction = callback;
}

void ThermostatScreen::RegisterDecreaseAction(std::function<void()> callback)
{
    _onDecreaseAction = callback;
}

void ThermostatScreen::RegisterMainAction(std::function<void()> callback)
{
    _onMainAction = callback;
}

void ThermostatScreen::Show()
{
    show();
}