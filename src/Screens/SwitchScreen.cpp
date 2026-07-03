#include "SwitchScreen.h"

#include "ImageLoader.h"

ISwitchScreen* ISwitchScreen::instance = nullptr;

SwitchScreen::SwitchScreen()
{
    _image = lv_img_create(screen);
    lv_obj_align(_image, LV_ALIGN_CENTER, 0, -32);
    lv_obj_add_flag(_image, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_image, OnPrimaryAction, LV_EVENT_CLICKED, this);

    _value = lv_label_create(screen);
    lv_obj_set_width(_value, LV_SIZE_CONTENT);
    lv_obj_set_height(_value, LV_SIZE_CONTENT);
    lv_obj_set_align(_value, LV_ALIGN_CENTER);
    lv_obj_align(_value, LV_ALIGN_CENTER, 0, 34);
    lv_obj_set_style_text_font(_value, &FONT_LARGE, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void SwitchScreen::OnPrimaryAction(lv_event_t* e)
{
    auto* self = static_cast<SwitchScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPrimaryAction)
        return;
    self->_onPrimaryAction();
}

void SwitchScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void SwitchScreen::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void SwitchScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

void SwitchScreen::RegisterPrimaryAction(std::function<void()> callback)
{
    _onPrimaryAction = callback;
}

void SwitchScreen::Show()
{
    show();
}
  