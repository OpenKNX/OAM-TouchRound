#include "DoorWindowScreen.h"

#include "ImageLoader.h"

IDoorWindowScreen* IDoorWindowScreen::instance = nullptr;

DoorWindowScreen::DoorWindowScreen()
{
    _slider = lv_slider_create(screen);
    lv_obj_add_event_cb(_slider, OnPercentageChangeCompleted, LV_EVENT_RELEASED, this);

    _image = lv_img_create(screen);
    lv_obj_align(_image, LV_ALIGN_CENTER, 0, -15);
    lv_obj_add_flag(_image, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_image, OnMainAction, LV_EVENT_CLICKED, this);

    _obstruction = lv_img_create(screen);
    ImageLoader::loadImage(_obstruction, "alert.png");
    ImageLoader::colorImage(_obstruction, 255, 0, 0);
    lv_obj_add_flag(_obstruction, LV_OBJ_FLAG_HIDDEN);

    _movement = lv_img_create(screen);
    ImageLoader::unloadImage(_movement);

    _value = lv_label_create(screen);
    lv_obj_set_width(_value, LV_SIZE_CONTENT);
    lv_obj_set_height(_value, LV_SIZE_CONTENT);
    lv_obj_set_align(_value, LV_ALIGN_CENTER);
    lv_obj_align(_value, LV_ALIGN_CENTER, 0, 40);
    lv_obj_set_style_text_font(_value, &FONT_LARGE, LV_PART_MAIN | LV_STATE_DEFAULT);

    SetSliderDirection(DoorWindowSliderDirection::DOOR_WINDOW_SLIDER_LEFT);
}

void DoorWindowScreen::OnMainAction(lv_event_t* e)
{
    auto* self = static_cast<DoorWindowScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onMainAction)
        return;
    self->_onMainAction();
}

void DoorWindowScreen::OnPercentageChangeCompleted(lv_event_t* e)
{
    auto* self = static_cast<DoorWindowScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPercentageChangeCompleted)
        return;
    self->_onPercentageChangeCompleted(self->GetPercentageValue());
}

void DoorWindowScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void DoorWindowScreen::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void DoorWindowScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

void DoorWindowScreen::SetPercentageValue(uint8_t value)
{
    lv_slider_set_value(_slider, value, LV_ANIM_ON);
}

uint8_t DoorWindowScreen::GetPercentageValue() const
{
    return lv_slider_get_value(_slider);
}

void DoorWindowScreen::setSliderDirection(DoorWindowSliderDirection direction)
{
    SetSliderDirection(direction);
}

void DoorWindowScreen::SetSliderDirection(DoorWindowSliderDirection direction)
{
    switch (direction)
    {
        case DoorWindowSliderDirection::DOOR_WINDOW_SLIDER_LEFT:
            lv_obj_align(_slider, LV_ALIGN_TOP_MID, 0, 40);
            lv_obj_set_size(_slider, 138, 25);
            lv_slider_set_range(_slider, 0, 100);
            lv_obj_align(_obstruction, LV_ALIGN_CENTER, 73, -15);
            lv_obj_align(_movement, LV_ALIGN_CENTER, -73, -15);
            break;
        case DoorWindowSliderDirection::DOOR_WINDOW_SLIDER_RIGHT:
            lv_obj_align(_slider, LV_ALIGN_TOP_MID, 0, 40);
            lv_obj_set_size(_slider, 138, 25);
            lv_slider_set_range(_slider, 100, 0);
            lv_obj_align(_obstruction, LV_ALIGN_CENTER, 73, -15);
            lv_obj_align(_movement, LV_ALIGN_CENTER, -73, -15);
            break;
        case DoorWindowSliderDirection::DOOR_WINDOW_SLIDER_LEFT_RIGHT:
            lv_obj_align(_slider, LV_ALIGN_TOP_MID, 0, 40);
            lv_obj_set_size(_slider, 138, 25);
            lv_slider_set_range(_slider, 0, 100);
            lv_obj_align(_obstruction, LV_ALIGN_CENTER, 73, -15);
            lv_obj_align(_movement, LV_ALIGN_CENTER, -73, -15);
            break;
        case DoorWindowSliderDirection::DOOR_WINDOW_SLIDER_UP:
            lv_obj_align(_slider, LV_ALIGN_RIGHT_MID, -40, -40);
            lv_obj_set_size(_slider, 25, 80);
            lv_slider_set_range(_slider, 0, 100);
            lv_obj_align(_obstruction, LV_ALIGN_TOP_MID, 0, 15);
            lv_obj_align(_movement, LV_ALIGN_CENTER, -73, -15);
            break;
        case DoorWindowSliderDirection::DOOR_WINDOW_SLIDER_DOWN:
            lv_obj_align(_slider, LV_ALIGN_RIGHT_MID, 40, -40);
            lv_obj_set_size(_slider, 25, 80);
            lv_slider_set_range(_slider, 100, 0);
            lv_obj_align(_obstruction, LV_ALIGN_TOP_MID, 0, 15);
            lv_obj_align(_movement, LV_ALIGN_CENTER, -73, -15);
            break;
        case DoorWindowSliderDirection::DOOR_WINDOW_SLIDER_UP_DOWN:
            lv_obj_align(_slider, LV_ALIGN_RIGHT_MID, 40, -40);
            lv_obj_set_size(_slider, 25, 80);
            lv_slider_set_range(_slider, 0, 100);
            lv_obj_align(_obstruction, LV_ALIGN_TOP_MID, 0, 15);
            lv_obj_align(_movement, LV_ALIGN_CENTER, -73, -15);
            break;
    }
}

void DoorWindowScreen::SetPercentageVisible(bool visible)
{
    if (visible)
        lv_obj_clear_flag(_slider, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(_slider, LV_OBJ_FLAG_HIDDEN);
}

void DoorWindowScreen::SetObstructionVisible(bool visible)
{
    if (visible)
        lv_obj_clear_flag(_obstruction, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(_obstruction, LV_OBJ_FLAG_HIDDEN);
}

void DoorWindowScreen::SetMovementImage(const char* imageFile)
{
    ImageLoader::loadImage(_movement, imageFile, true, true);
}

void DoorWindowScreen::ClearMovementImage()
{
    ImageLoader::unloadImage(_movement);
}

void DoorWindowScreen::RegisterMainAction(std::function<void()> callback)
{
    _onMainAction = callback;
}

void DoorWindowScreen::RegisterPercentageChangeCompleted(std::function<void(uint8_t)> callback)
{
    _onPercentageChangeCompleted = callback;
}

void DoorWindowScreen::Show()
{
    show();
}