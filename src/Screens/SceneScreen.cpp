#include "SceneScreen.h"

#include "ImageLoader.h"

ISceneScreen* ISceneScreen::instance = nullptr;

SceneScreen::SceneScreen()
{
    _image = lv_img_create(screen);
    lv_obj_align(_image, LV_ALIGN_CENTER, 0, -10);
    lv_obj_add_flag(_image, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_image, OnPrimaryActionPressed, LV_EVENT_PRESSED, this);
    lv_obj_add_event_cb(_image, OnPrimaryActionReleased, LV_EVENT_RELEASED, this);

    _value = lv_label_create(screen);
    lv_obj_set_width(_value, LV_SIZE_CONTENT);
    lv_obj_set_height(_value, LV_SIZE_CONTENT);
    lv_obj_set_align(_value, LV_ALIGN_CENTER);
    lv_obj_align(_value, LV_ALIGN_CENTER, 0, -64);
    lv_obj_set_style_text_font(_value, &FONT_MEDIUM, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void SceneScreen::OnPrimaryActionPressed(lv_event_t* e)
{
    auto* self = static_cast<SceneScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPrimaryActionPressed)
        return;
    self->_onPrimaryActionPressed();
}

void SceneScreen::OnPrimaryActionReleased(lv_event_t* e)
{
    auto* self = static_cast<SceneScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPrimaryActionReleased)
        return;
    self->_onPrimaryActionReleased();
}

void SceneScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void SceneScreen::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void SceneScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

void SceneScreen::RegisterPrimaryActionPressed(std::function<void()> callback)
{
    _onPrimaryActionPressed = callback;
}

void SceneScreen::RegisterPrimaryActionReleased(std::function<void()> callback)
{
    _onPrimaryActionReleased = callback;
}

void SceneScreen::Show()
{
    show();
}
  