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
    uint8_t value = 100 - lv_slider_get_value(_screen.sliderSlat);
    _channel->commandPosition(this, value);
}

void JalousieDeviceBridge::setSlatPosition(uint8_t position)
{
    lv_slider_set_value(_screen.sliderSlat, 100 - position, LV_ANIM_ON);
}
