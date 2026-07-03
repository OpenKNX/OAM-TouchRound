#include "MainFunctionScreen.h"

#include "ImageLoader.h"

IMainFunctionScreen* IMainFunctionScreen::instance = nullptr;

MainFunctionScreen::MainFunctionScreen() 
{
    lv_obj_add_event_cb(screen, OnScreenPressed, LV_EVENT_PRESSED, this);

    _image = lv_img_create(screen);
    lv_obj_align(_image, LV_ALIGN_CENTER, 0, -45);
  
    _value = lv_label_create(screen);
    lv_obj_set_width(_value, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(_value, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(_value, LV_ALIGN_CENTER);
    lv_obj_align(_value, LV_ALIGN_CENTER, 0, 30);
    lv_obj_set_style_text_font(_value, &FONT_LARGE, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void MainFunctionScreen::OnScreenPressed(lv_event_t* e)
{
    auto* self = static_cast<MainFunctionScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onScreenPressed)
        return;
    self->_onScreenPressed();
}

void MainFunctionScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void MainFunctionScreen::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void MainFunctionScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

void MainFunctionScreen::RegisterScreenPressed(std::function<void()> callback)
{
    _onScreenPressed = callback;
}

void MainFunctionScreen::Show()
{
    show();
}