#include "JalousieScreen.h"
#include "ImageLoader.h"


IJalousieScreen* IJalousieScreen::instance = nullptr;

JalousieScreen::JalousieScreen()
{
    _sliderAux = lv_slider_create(screen);
    lv_obj_set_size(_sliderAux, 25, 110);
    lv_obj_add_flag(_sliderAux, LV_OBJ_FLAG_CLICKABLE);
#if LVGL_VERSION_MAJOR < 9
    lv_slider_set_range(_sliderAux, 0, 100);
#else
    lv_slider_set_range(_sliderAux, 100, 0);
#endif
    lv_obj_align(_sliderAux, LV_ALIGN_RIGHT_MID, -35, -10);
    lv_obj_add_event_cb(_sliderAux, OnAuxPercentageChangeCompleted, LV_EVENT_RELEASED, this);
}

void JalousieScreen::OnAuxPercentageChangeCompleted(lv_event_t* e)
{
    auto* self = static_cast<JalousieScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onAuxPercentageChangeCompleted)
        return;
    self->_onAuxPercentageChangeCompleted(self->GetAuxPercentageValue());
}

void JalousieScreen::SetAuxPercentageValue(uint8_t value)
{
#if LVGL_VERSION_MAJOR < 9
    lv_slider_set_value(_sliderAux, 100 - value, LV_ANIM_ON);
#else
    lv_slider_set_value(_sliderAux, value, LV_ANIM_ON);
#endif
}

uint8_t JalousieScreen::GetAuxPercentageValue() const
{
#if LVGL_VERSION_MAJOR < 9
    return 100 - lv_slider_get_value(_sliderAux);
#else
    return lv_slider_get_value(_sliderAux);
#endif
}

void JalousieScreen::RegisterAuxPercentageChangeCompleted(std::function<void(uint8_t)> callback)
{
    _onAuxPercentageChangeCompleted = callback;
}
