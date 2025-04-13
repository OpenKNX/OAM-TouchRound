#include "RolladenDisplayBridge.h"
#include "../ImageLoader.h"

RolladenDisplayBridge::RolladenDisplayBridge(DetailDevicePage& detailDevicePage)
    : RolladenDisplayBridge(*RolladenScreen::instance, detailDevicePage)
{

}

RolladenDisplayBridge::RolladenDisplayBridge(RolladenScreen& screen, DetailDevicePage& detailDevicePage)
    : _screen(screen), _detailDevicePage(detailDevicePage)
{
}

void RolladenDisplayBridge::setup(uint8_t _channelIndex)
{   
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _eventButtonUpPressed = [](lv_event_t *e) { ((RolladenDisplayBridge*) lv_event_get_user_data(e))->buttonUpPressed(); };
    lv_obj_add_event_cb(_screen.buttonUp, _eventButtonUpPressed, LV_EVENT_CLICKED, this);
    _eventButtonDownPressed = [](lv_event_t *e) { ((RolladenDisplayBridge*) lv_event_get_user_data(e))->buttonDownPressed(); };
    lv_obj_add_event_cb(_screen.buttonDown, _eventButtonDownPressed, LV_EVENT_CLICKED, this);  
    _eventButtonStopPressed = [](lv_event_t *e) { ((RolladenDisplayBridge*) lv_event_get_user_data(e))->buttonStopPressed(); };
    lv_obj_add_event_cb(_screen.buttonStop, _eventButtonStopPressed, LV_EVENT_CLICKED, this);  
    _eventButtonMainFunctionPressed = [](lv_event_t *e) { ((RolladenDisplayBridge*) lv_event_get_user_data(e))->buttonMainFunctionPressed(); };
    lv_obj_add_event_cb(_screen.icon, _eventButtonMainFunctionPressed, LV_EVENT_CLICKED, this);  
    _eventSliderReleased = [](lv_event_t *e) { ((RolladenDisplayBridge*) lv_event_get_user_data(e))->sliderReleased(); };  
    lv_obj_add_event_cb(_screen.sliderPosition, _eventSliderReleased, LV_EVENT_RELEASED, this);
    
    mainFunctionValueChanged();
    _screen.show();
}

RolladenDisplayBridge::~RolladenDisplayBridge()
{
    if (_eventButtonUpPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.buttonUp, _eventButtonUpPressed, this);
    if (_eventButtonDownPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.buttonDown, _eventButtonDownPressed, this);
    if (_eventButtonStopPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.buttonStop, _eventButtonStopPressed, this);
    if (_eventButtonMainFunctionPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.icon, _eventButtonMainFunctionPressed, this);
    if (_eventSliderReleased != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.sliderPosition, _eventSliderReleased, this);
}

void RolladenDisplayBridge::mainFunctionValueChanged() 
{
    auto& device = *_detailDevicePage.getDevice();
    auto image = device.mainFunctionImage();
    ImageLoader::loadImage(_screen.icon, image.imageFile, image.allowRecolor, device.mainFunctionValue());
}

void RolladenDisplayBridge::setPosition(uint8_t position)
{
    lv_slider_set_value(_screen.sliderPosition, position, LV_ANIM_ON);
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d%%", (int) position);
    lv_label_set_text(_screen.value, buffer);
}

void RolladenDisplayBridge::setMovement(MoveState movement)
{

}

void RolladenDisplayBridge::sliderReleased()
{
    uint8_t value = lv_slider_get_value(_screen.sliderPosition);
    logErrorP("Slider released %d", value); 
    _channel->commandPosition(this, value);
}

void RolladenDisplayBridge::buttonUpPressed()
{
    logErrorP("Up pressed");
    _channel->commandPosition(this, 0);
}
   

void RolladenDisplayBridge::buttonDownPressed()
{
    logErrorP("Down pressed");
    _channel->commandPosition(this, 100);
}

void RolladenDisplayBridge::buttonStopPressed()
{
    logErrorP("Stop pressed");
}

void RolladenDisplayBridge::buttonMainFunctionPressed()
{    
    logErrorP("Main function pressed");
    _channel->commandMainFunctionClick();
}