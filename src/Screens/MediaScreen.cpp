#include "MediaScreen.h"
#include "ImageLoader.h"

IMediaScreen* IMediaScreen::instance = nullptr;

MediaScreen::MediaScreen()
{
    _percentageInput = lv_arc_create(screen);
    lv_obj_set_width(_percentageInput, 200);
    lv_obj_set_height(_percentageInput, 200);
    lv_obj_set_align(_percentageInput, LV_ALIGN_CENTER);
    lv_arc_set_value(_percentageInput, 0);
    lv_arc_set_bg_angles(_percentageInput, 160, 20);
    lv_arc_set_range(_percentageInput, 0, 100);
    lv_obj_set_style_arc_width(_percentageInput, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(_percentageInput, OnPercentageChangeCompleted, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(_percentageInput, OnPercentageChanged, LV_EVENT_PRESSING, this);
   
    _image = lv_img_create(screen);
    lv_obj_align(_image, LV_ALIGN_TOP_MID, 0, 56);
    lv_obj_add_flag(_image, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_image, OnMainAction, LV_EVENT_CLICKED, this);

    _title = lv_label_create(screen);
    lv_obj_set_width(_title, LV_SIZE_CONTENT);
    lv_obj_set_height(_title, LV_SIZE_CONTENT);
    lv_obj_set_align(_title, LV_ALIGN_CENTER);
    lv_obj_align(_title, LV_ALIGN_TOP_MID, 0, 119);

    _buttonPrevious = lv_img_create(screen);
    ImageLoader::loadImage(_buttonPrevious, "left.png", true, false);
    lv_obj_add_flag(_buttonPrevious, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_align(_buttonPrevious, LV_ALIGN_TOP_MID, -30, 140);
    lv_obj_add_event_cb(_buttonPrevious, OnPreviousAction, LV_EVENT_CLICKED, this);
   
    _buttonNext = lv_img_create(screen);
    ImageLoader::loadImage(_buttonNext, "right.png", true, false);
    lv_obj_add_flag(_buttonNext, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_align(_buttonNext, LV_ALIGN_TOP_MID, 30, 140);
    lv_obj_add_event_cb(_buttonNext, OnNextAction, LV_EVENT_CLICKED, this);
}

void MediaScreen::OnPercentageChanged(lv_event_t* e)
{
    auto* self = static_cast<MediaScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPercentageChanged)
        return;
    self->_onPercentageChanged(self->GetPercentageValue());
}

void MediaScreen::OnPercentageChangeCompleted(lv_event_t* e)
{
    auto* self = static_cast<MediaScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPercentageChangeCompleted)
        return;
    self->_onPercentageChangeCompleted(self->GetPercentageValue());
}

void MediaScreen::OnMainAction(lv_event_t* e)
{
    auto* self = static_cast<MediaScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onMainAction)
        return;
    self->_onMainAction();
}

void MediaScreen::OnPreviousAction(lv_event_t* e)
{
    auto* self = static_cast<MediaScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPreviousAction)
        return;
    self->_onPreviousAction();
}

void MediaScreen::OnNextAction(lv_event_t* e)
{
    auto* self = static_cast<MediaScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onNextAction)
        return;
    self->_onNextAction();
}

void MediaScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void MediaScreen::SetTitleText(const char* text)
{
    lv_label_set_text(_title, text);
}

void MediaScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

void MediaScreen::SetPercentageValue(uint8_t value)
{
    lv_arc_set_value(_percentageInput, value);
}

uint8_t MediaScreen::GetPercentageValue() const
{
    return lv_arc_get_value(_percentageInput);
}

void MediaScreen::RegisterPercentageChanged(std::function<void(uint8_t)> callback)
{
    _onPercentageChanged = callback;
}

void MediaScreen::RegisterPercentageChangeCompleted(std::function<void(uint8_t)> callback)
{
    _onPercentageChangeCompleted = callback;
}

void MediaScreen::RegisterMainAction(std::function<void()> callback)
{
    _onMainAction = callback;
}

void MediaScreen::RegisterPreviousAction(std::function<void()> callback)
{
    _onPreviousAction = callback;
}

void MediaScreen::RegisterNextAction(std::function<void()> callback)
{
    _onNextAction = callback;
}

void MediaScreen::Show()
{
    show();
}
  