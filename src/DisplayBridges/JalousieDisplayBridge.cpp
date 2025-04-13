#include "JalousieDisplayBridge.h"
#include "../ImageLoader.h"

JalousieDisplayBridge::JalousieDisplayBridge(DetailDevicePage& detailDevicePage)
    : RolladenDisplayBridge(*JalousieScreen::instance, detailDevicePage)
{
}

void JalousieDisplayBridge::setup(uint8_t _channelIndex)
{   
    _eventSliderSlatReleased = [](lv_event_t *e) { ((JalousieDisplayBridge*) lv_event_get_user_data(e))->sliderSlatReleased(); };  
    lv_obj_add_event_cb(_screen.sliderSlat, _eventSliderSlatReleased, LV_EVENT_RELEASED, this);
    RolladenDisplayBridge::setup(_channelIndex);
   
}

JalousieDisplayBridge::~JalousieDisplayBridge()
{
    if (_eventSliderSlatReleased != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.sliderSlat, _eventSliderSlatReleased, this);
}

void JalousieDisplayBridge::sliderSlatReleased() 
{
    uint8_t value = lv_slider_get_value(_screen.sliderSlat);
    logErrorP("Slider Slat released %d", value); 
    _channel->commandPosition(this, value);
}

void JalousieDisplayBridge::setSlatPosition(uint8_t position)
{
    lv_slider_set_value(_screen.sliderSlat, position, LV_ANIM_ON);
}
