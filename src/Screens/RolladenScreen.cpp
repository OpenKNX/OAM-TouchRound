#include "RolladenScreen.h"
#include "ImageLoader.h"


IRolladenScreen* IRolladenScreen::instance = nullptr;

RolladenScreen::RolladenScreen()
{
    _image = lv_img_create(screen);
    lv_obj_add_flag(_image, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_align(_image, LV_ALIGN_CENTER, 0, -10);
    lv_obj_add_event_cb(_image, OnMainAction, LV_EVENT_CLICKED, this);
 
    _buttonPrimary = lv_img_create(screen);
    ImageLoader::loadImage(_buttonPrimary, "up.png", true, false);
    lv_obj_add_flag(_buttonPrimary, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_align(_buttonPrimary, LV_ALIGN_TOP_MID, 0, 34);
    lv_obj_add_event_cb(_buttonPrimary, OnPrimaryAction, LV_EVENT_CLICKED, this);
   
    _buttonSecondary = lv_img_create(screen);
    ImageLoader::loadImage(_buttonSecondary, "down.png", true, false);
    lv_obj_add_flag(_buttonSecondary, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_align(_buttonSecondary, LV_ALIGN_BOTTOM_MID, 0, -56);
    lv_obj_add_event_cb(_buttonSecondary, OnSecondaryAction, LV_EVENT_CLICKED, this);

    _percentageInput = lv_slider_create(screen);
    lv_obj_add_flag(_percentageInput, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(_percentageInput, 25, 110);
#if LVGL_VERSION_MAJOR < 9
    lv_slider_set_range(_percentageInput, 0, 100);
#else
    lv_slider_set_range(_percentageInput, 100, 0);
#endif
    lv_obj_add_event_cb(_percentageInput, OnPercentageChangeCompleted, LV_EVENT_RELEASED, this);

    lv_obj_align(_percentageInput, LV_ALIGN_LEFT_MID, 35, -10);

     
    _value = lv_label_create(screen);
    lv_obj_set_width(_value, LV_SIZE_CONTENT);
    lv_obj_set_height(_value, LV_SIZE_CONTENT);
    lv_obj_set_align(_value, LV_ALIGN_CENTER);
    lv_obj_align(_value, LV_ALIGN_TOP_MID, 0, 13);
    
}

void RolladenScreen::OnPrimaryAction(lv_event_t* e)
{
    auto* self = static_cast<RolladenScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPrimaryAction)
        return;
    self->_onPrimaryAction();
}

void RolladenScreen::OnSecondaryAction(lv_event_t* e)
{
    auto* self = static_cast<RolladenScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onSecondaryAction)
        return;
    self->_onSecondaryAction();
}

void RolladenScreen::OnMainAction(lv_event_t* e)
{
    auto* self = static_cast<RolladenScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onMainAction)
        return;
    self->_onMainAction();
}

void RolladenScreen::OnPercentageChangeCompleted(lv_event_t* e)
{
    auto* self = static_cast<RolladenScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPercentageChangeCompleted)
        return;
    self->_onPercentageChangeCompleted(self->GetPercentageValue());
}

void RolladenScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void RolladenScreen::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void RolladenScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

void RolladenScreen::SetPercentageValue(uint8_t value)
{
#if LVGL_VERSION_MAJOR < 9
    lv_slider_set_value(_percentageInput, 100 - value, LV_ANIM_ON);
#else
    lv_slider_set_value(_percentageInput, value, LV_ANIM_ON);
#endif
}

uint8_t RolladenScreen::GetPercentageValue() const
{
#if LVGL_VERSION_MAJOR < 9
    return 100 - lv_slider_get_value(_percentageInput);
#else
    return lv_slider_get_value(_percentageInput);
#endif
}

void RolladenScreen::SetDirectionalActionState(bool primaryActive, bool secondaryActive)
{
    ImageLoader::colorState(_buttonPrimary, true, primaryActive);
    ImageLoader::colorState(_buttonSecondary, true, secondaryActive);
}

void RolladenScreen::RegisterPrimaryAction(std::function<void()> callback)
{
    _onPrimaryAction = callback;
}

void RolladenScreen::RegisterSecondaryAction(std::function<void()> callback)
{
    _onSecondaryAction = callback;
}

void RolladenScreen::RegisterMainAction(std::function<void()> callback)
{
    _onMainAction = callback;
}

void RolladenScreen::RegisterPercentageChangeCompleted(std::function<void(uint8_t)> callback)
{
    _onPercentageChangeCompleted = callback;
}

void RolladenScreen::Show()
{
    show();
}
