#include "DimmerScreen.h"

#include "ImageLoader.h"

IDimmerScreen* IDimmerScreen::instance = nullptr;

DimmerScreen::DimmerScreen()
{
    _percentageInput = lv_arc_create(screen);
    lv_obj_set_width(_percentageInput, 200);
    lv_obj_set_height(_percentageInput, 200);
    lv_obj_set_align(_percentageInput, LV_ALIGN_CENTER);
    lv_arc_set_value(_percentageInput, 0);
    lv_arc_set_bg_angles(_percentageInput, 160, 20);
    lv_arc_set_range(_percentageInput, 0, 100);
    lv_obj_set_style_arc_width(_percentageInput, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(_percentageInput, OnPercentageChanged, LV_EVENT_PRESSING, this);
    lv_obj_add_event_cb(_percentageInput, OnPercentageChangeCompleted, LV_EVENT_RELEASED, this);
   
    _primaryActionImage = lv_img_create(screen);
    lv_obj_align(_primaryActionImage, LV_ALIGN_CENTER, 0, -32);
    lv_obj_add_flag(_primaryActionImage, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_primaryActionImage, OnPrimaryAction, LV_EVENT_CLICKED, this);

    _value = lv_label_create(screen);
    lv_obj_set_width(_value, LV_SIZE_CONTENT);
    lv_obj_set_height(_value, LV_SIZE_CONTENT);
    lv_obj_set_align(_value, LV_ALIGN_CENTER);
    lv_obj_align(_value, LV_ALIGN_CENTER, 0, 34);
    lv_obj_set_style_text_font(_value, &FONT_LARGE, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void DimmerScreen::OnPercentageChanged(lv_event_t* e)
{
    auto* self = static_cast<DimmerScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPercentageChanged)
        return;
    self->_onPercentageChanged(self->GetPercentageValue());
}

void DimmerScreen::OnPercentageChangeCompleted(lv_event_t* e)
{
    auto* self = static_cast<DimmerScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPercentageChangeCompleted)
        return;
    self->_onPercentageChangeCompleted(self->GetPercentageValue());
}

void DimmerScreen::OnPrimaryAction(lv_event_t* e)
{
    auto* self = static_cast<DimmerScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPrimaryAction)
        return;
    self->_onPrimaryAction();
}

void DimmerScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void DimmerScreen::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void DimmerScreen::SetPercentageValue(uint8_t value)
{
    lv_arc_set_value(_percentageInput, value);
}

uint8_t DimmerScreen::GetPercentageValue() const
{
    return lv_arc_get_value(_percentageInput);
}

void DimmerScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_primaryActionImage, imageFile, allowRecolor, active);
}

void DimmerScreen::RegisterPercentageChanged(std::function<void(uint8_t)> callback)
{
    _onPercentageChanged = callback;
}

void DimmerScreen::RegisterPercentageChangeCompleted(std::function<void(uint8_t)> callback)
{
    _onPercentageChangeCompleted = callback;
}

void DimmerScreen::RegisterPrimaryAction(std::function<void()> callback)
{
    _onPrimaryAction = callback;
}

void DimmerScreen::Show()
{
    show();
}
  