#include "FanDisplayBridge.h"
#include "../ImageLoader.h"

FanDisplayBridge::FanDisplayBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void FanDisplayBridge::setup(uint8_t _channelIndex)
{   
    if (ParamBRI_CHFanAutomatic)
        lv_obj_clear_flag(_screen.buttonAuto, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(_screen.buttonAuto, LV_OBJ_FLAG_HIDDEN);
 
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
   
    _eventButtonPressed = [](lv_event_t *e) { ((FanDisplayBridge*) lv_event_get_user_data(e))->buttonClicked(); };
    lv_obj_add_event_cb(_screen.buttonAuto, _eventButtonPressed, LV_EVENT_CLICKED, this);
   
    _eventIconPressed = [](lv_event_t *e) { ((FanDisplayBridge*) lv_event_get_user_data(e))->imageClicked(); };
    lv_obj_add_event_cb(_screen.image, _eventIconPressed, LV_EVENT_CLICKED, this);
    
    _screen.show();
    mainFunctionValueChanged();
}

FanDisplayBridge::~FanDisplayBridge()
{
    if (_eventButtonPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.buttonAuto, _eventButtonPressed, this);
    if (_eventIconPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.image, _eventIconPressed, this);
}

void FanDisplayBridge::setAutomatic(bool automatic)
{
    _automatic = automatic;
    if (automatic)
        lv_obj_add_state(_screen.buttonAuto, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(_screen.buttonAuto, LV_STATE_CHECKED);   
}

void FanDisplayBridge::setPower(bool power)
{
    _channel->commandPower(this, power);
}

void FanDisplayBridge::buttonClicked()
{
    auto& device = *_channel;
    device.commandAutomatic(this, !_automatic);
}

void FanDisplayBridge::mainFunctionValueChanged()
{
    auto& device = *_channel;
    auto image = device.mainFunctionImage();
    bool power = device.mainFunctionValue();
    ImageLoader::loadImage(_screen.image, image.imageFile, image.allowRecolor, power);
    lv_label_set_text(_screen.value, device.currentValueAsString().c_str());
}

void FanDisplayBridge::imageClicked()
{    
    _channel->commandMainFunctionClick();
}