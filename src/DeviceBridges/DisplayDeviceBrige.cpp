#include "DisplayDeviceBridge.h"
#include "../ImageLoader.h"

DisplayDeviceBridge::DisplayDeviceBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void DisplayDeviceBridge::setup(uint8_t _channelIndex)
{   
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _screen.show();
}

DisplayDeviceBridge::~DisplayDeviceBridge()
{
}

void DisplayDeviceBridge::setValue(double value)
{
    updateValue();
}

void DisplayDeviceBridge::setValue(const char* value)
{
    updateValue();
}

void DisplayDeviceBridge::updateValue()
{  
    auto& device = *_channel;
    lv_label_set_text(_screen.value, device.currentValueAsString().c_str());
    ImageLoader::loadImage(_screen.image, device.mainFunctionImage().imageFile, device.mainFunctionImage().allowRecolor, device.mainFunctionValue());
}
