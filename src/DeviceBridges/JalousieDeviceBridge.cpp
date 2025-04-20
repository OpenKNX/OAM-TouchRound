#include "JalousieDeviceBridge.h"
#include "../ImageLoader.h"

JalousieDeviceBridge::JalousieDeviceBridge(DetailDevicePage& detailDevicePage)
    : RolladenDeviceBridge(*JalousieScreen::instance, detailDevicePage)
{
}

void JalousieDeviceBridge::setup(uint8_t _channelIndex)
{   
    _eventSliderSlatReleased = [](lv_event_t *e) { ((JalousieDeviceBridge*) lv_event_get_user_data(e))->sliderSlatReleased(); };  
    lv_obj_add_event_cb(_screen.sliderSlat, _eventSliderSlatReleased, LV_EVENT_RELEASED, this);
    RolladenDeviceBridge::setup(_channelIndex);
   
}

JalousieDeviceBridge::~JalousieDeviceBridge()
{
    if (_eventSliderSlatReleased != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.sliderSlat, _eventSliderSlatReleased, this);
}

void JalousieDeviceBridge::sliderSlatReleased() 
{
#if LVGL_VERSION_MAJOR < 9    
    uint8_t value = 100 - lv_slider_get_value(_screen.sliderSlat);
#else
    uint8_t value = lv_slider_get_value(_screen.sliderSlat);
#endif
    _channel->commandPosition(nullptr, value);
}

void JalousieDeviceBridge::setSlatPosition(uint8_t position)
{
#if LVGL_VERSION_MAJOR < 9
    uint8_t value = 100 - position;
#else
    uint8_t value = position;
#endif
    lv_slider_set_value(_screen.sliderSlat, value, LV_ANIM_ON);
}
