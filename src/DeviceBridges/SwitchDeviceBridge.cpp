#include "SwitchDeviceBridge.h"
#include "../ImageLoader.h"

SwitchDeviceBridge::SwitchDeviceBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void SwitchDeviceBridge::setup(uint8_t _channelIndex)
{
    _eventButtonPressed = [](lv_event_t *e) { ((SwitchDeviceBridge*) lv_event_get_user_data(e))->buttonClicked(); };
    lv_obj_add_event_cb(_screen.image, _eventButtonPressed , LV_EVENT_CLICKED, this);

    mainFunctionValueChanged();
    _screen.show();
}

SwitchDeviceBridge::~SwitchDeviceBridge()
{
    if (_eventButtonPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.image, _eventButtonPressed, this);
}

void SwitchDeviceBridge::setPower(bool on)
{

}

void SwitchDeviceBridge::mainFunctionValueChanged()
{
    auto& device = *_channel;
    auto image = device.mainFunctionImage();
    bool power = device.mainFunctionValue();
    ImageLoader::loadImage(_screen.image, image.imageFile, image.allowRecolor, power);
    lv_label_set_text(_screen.value, device.currentValueAsString().c_str());
}


void SwitchDeviceBridge::buttonClicked()
{    
    _channel->commandMainFunctionClick();   
}