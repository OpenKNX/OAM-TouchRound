#include "RolladenDeviceBridge.h"
#include "../ImageLoader.h"

RolladenDeviceBridge::RolladenDeviceBridge(DetailDevicePage& detailDevicePage)
    : RolladenDeviceBridge(*RolladenScreen::instance, detailDevicePage)
{

}

RolladenDeviceBridge::RolladenDeviceBridge(RolladenScreen& screen, DetailDevicePage& detailDevicePage)
    : _screen(screen), _detailDevicePage(detailDevicePage)
{
}

void RolladenDeviceBridge::setup(uint8_t _channelIndex)
{   
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _eventButtonUpPressed = [](lv_event_t *e) { ((RolladenDeviceBridge*) lv_event_get_user_data(e))->buttonUpPressed(); };
    lv_obj_add_event_cb(_screen.buttonUp, _eventButtonUpPressed, LV_EVENT_CLICKED, this);
    _eventButtonDownPressed = [](lv_event_t *e) { ((RolladenDeviceBridge*) lv_event_get_user_data(e))->buttonDownPressed(); };
    lv_obj_add_event_cb(_screen.buttonDown, _eventButtonDownPressed, LV_EVENT_CLICKED, this);  
    _eventButtonMainFunctionPressed = [](lv_event_t *e) { ((RolladenDeviceBridge*) lv_event_get_user_data(e))->buttonMainFunctionPressed(); };
    lv_obj_add_event_cb(_screen.image, _eventButtonMainFunctionPressed, LV_EVENT_CLICKED, this);  
    _eventSliderReleased = [](lv_event_t *e) { ((RolladenDeviceBridge*) lv_event_get_user_data(e))->sliderReleased(); };  
    lv_obj_add_event_cb(_screen.sliderPosition, _eventSliderReleased, LV_EVENT_RELEASED, this);
    _evnetSliderClicked = [](lv_event_t *e) { logError("Slider","clicked");  };
    lv_obj_add_event_cb(_screen.sliderPosition, _evnetSliderClicked, LV_EVENT_CLICKED, this);
    
    mainFunctionValueChanged();
    _screen.show();
}

RolladenDeviceBridge::~RolladenDeviceBridge()
{
    if (_eventButtonUpPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.buttonUp, _eventButtonUpPressed, this);
    if (_eventButtonDownPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.buttonDown, _eventButtonDownPressed, this);
    if (_eventButtonMainFunctionPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.image, _eventButtonMainFunctionPressed, this);
    if (_eventSliderReleased != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.sliderPosition, _eventSliderReleased, this);
    if (_evnetSliderClicked != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.sliderPosition, _evnetSliderClicked, this);
}

void RolladenDeviceBridge::mainFunctionValueChanged() 
{
    auto& device = *_detailDevicePage.getDevice();
    auto image = device.mainFunctionImage();
    ImageLoader::loadImage(_screen.image, image.imageFile, image.allowRecolor, device.mainFunctionValue());
}

void RolladenDeviceBridge::setPosition(uint8_t position)
{
#if LVGL_VERSION_MAJOR < 10    
    lv_slider_set_value(_screen.sliderPosition,100 - position, LV_ANIM_ON);
#else
    lv_slider_set_value(_screen.sliderPosition, position, LV_ANIM_ON);
#endif
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d%%", (int) position);
    lv_label_set_text(_screen.value, buffer);
}

void RolladenDeviceBridge::setMovement(MoveState movement)
{
    switch (movement)
    {
        case MoveState::MoveStateHold:
            ImageLoader::colorState(_screen.buttonUp, true, false);
            ImageLoader::colorState(_screen.buttonDown, true, false);
            break;
        case MoveState::MoveStateDown:
            ImageLoader::colorState(_screen.buttonUp, true, false);
            ImageLoader::colorState(_screen.buttonDown, true, true);
            break;
        case MoveState::MoveStateUp:
            ImageLoader::colorState(_screen.buttonUp, true, true);
            ImageLoader::colorState(_screen.buttonDown, true, false);
            break;
    }
}

void RolladenDeviceBridge::sliderReleased()
{
#if LVGL_VERSION_MAJOR < 10    
    uint8_t value = 100 - lv_slider_get_value(_screen.sliderPosition);
#else
    uint8_t value = lv_slider_get_value(_screen.sliderPosition);
#endif
logErrorP("RolladenDeviceBridge::sliderReleased %d", (int) value);
_channel->commandPosition(nullptr, value);
}

void RolladenDeviceBridge::buttonUpPressed()
{
    _channel->commandPosition(nullptr, 0);
}
   

void RolladenDeviceBridge::buttonDownPressed()
{
    _channel->commandPosition(nullptr, 100);
}


void RolladenDeviceBridge::buttonMainFunctionPressed()
{    
    logErrorP("RolladenDeviceBridge::buttonMainFunctionPressed");
    _channel->commandMainFunctionClick();
}