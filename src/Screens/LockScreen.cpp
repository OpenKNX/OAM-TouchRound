#include "LockScreen.h"

#include "ImageLoader.h"

ILockScreen* ILockScreen::instance = nullptr;

LockScreen::LockScreen() 
{
   
    _image = lv_img_create(screen);
    lv_obj_align(_image, LV_ALIGN_CENTER, 0, -45);
    lv_obj_add_flag(_image, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_image, OnMainAction, LV_EVENT_CLICKED, this);

    _blocked = lv_img_create(screen);
    lv_obj_align(_blocked, LV_ALIGN_CENTER, 73, -45);
    ImageLoader::loadImage(_blocked, "alert.png");
    ImageLoader::colorImage(_blocked, 255, 0, 0);
    lv_obj_add_flag(_blocked, LV_OBJ_FLAG_HIDDEN);

    _movement = lv_img_create(screen);
    lv_obj_align(_movement, LV_ALIGN_CENTER, -73, -45);
    ImageLoader::unloadImage(_movement);
   
    _value = lv_label_create(screen);
    lv_obj_set_width(_value, LV_SIZE_CONTENT);
    lv_obj_set_height(_value, LV_SIZE_CONTENT);
    lv_obj_set_align(_value, LV_ALIGN_CENTER);
    lv_obj_align(_value, LV_ALIGN_CENTER, 0, 30);
    lv_obj_set_style_text_font(_value, &FONT_LARGE, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void LockScreen::OnMainAction(lv_event_t* e)
{
    auto* self = static_cast<LockScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onMainAction)
        return;
    self->_onMainAction();
}

void LockScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void LockScreen::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void LockScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

void LockScreen::SetBlockedVisible(bool visible)
{
    if (visible)
        lv_obj_clear_flag(_blocked, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(_blocked, LV_OBJ_FLAG_HIDDEN);
}

void LockScreen::SetMovementImage(const char* imageFile)
{
    ImageLoader::loadImage(_movement, imageFile, true, true);
}

void LockScreen::ClearMovementImage()
{
    ImageLoader::unloadImage(_movement);
}

void LockScreen::RegisterMainAction(std::function<void()> callback)
{
    _onMainAction = callback;
}

void LockScreen::Show()
{
    show();

}
