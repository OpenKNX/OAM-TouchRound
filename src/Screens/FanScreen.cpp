#include "FanScreen.h"

#include "ImageLoader.h"

IFanScreen* IFanScreen::instance = nullptr;

FanScreen::FanScreen() 
{
    _buttonAuto = lv_btn_create(screen);
    lv_obj_align(_buttonAuto, LV_ALIGN_CENTER, 0, -80);
    lv_obj_set_size(_buttonAuto, 90, 40);
    lv_obj_add_flag(_buttonAuto, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_event_cb(_buttonAuto, OnAutomaticAction, LV_EVENT_CLICKED, this);

    _buttonAutoLabel = lv_label_create(_buttonAuto);
    lv_label_set_text(_buttonAutoLabel, "Auto");
    lv_obj_center(_buttonAutoLabel);

    _image = lv_img_create(screen);
    lv_obj_align(_image, LV_ALIGN_CENTER, 0, -15);
    lv_obj_add_flag(_image, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_image, OnMainAction, LV_EVENT_CLICKED, this);
  
    _value = lv_label_create(screen);
    lv_obj_set_width(_value, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(_value, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(_value, LV_ALIGN_CENTER);
    lv_obj_align(_value, LV_ALIGN_CENTER, 0, 40);
    lv_obj_set_style_text_font(_value, &FONT_LARGE, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void FanScreen::OnAutomaticAction(lv_event_t* e)
{
    auto* self = static_cast<FanScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onAutomaticAction)
        return;
    self->_onAutomaticAction();
}

void FanScreen::OnMainAction(lv_event_t* e)
{
    auto* self = static_cast<FanScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onMainAction)
        return;
    self->_onMainAction();
}

void FanScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void FanScreen::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void FanScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

void FanScreen::SetAutomaticVisible(bool visible)
{
    if (visible)
        lv_obj_clear_flag(_buttonAuto, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(_buttonAuto, LV_OBJ_FLAG_HIDDEN);
}

void FanScreen::SetAutomaticState(bool automatic)
{
    if (automatic)
        lv_obj_add_state(_buttonAuto, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(_buttonAuto, LV_STATE_CHECKED);
}

void FanScreen::RegisterAutomaticAction(std::function<void()> callback)
{
    _onAutomaticAction = callback;
}

void FanScreen::RegisterMainAction(std::function<void()> callback)
{
    _onMainAction = callback;
}

void FanScreen::Show()
{
    show();
}