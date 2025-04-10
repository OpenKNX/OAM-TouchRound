#include "SensorDisplayBridge.h"
#include "../ImageLoader.h"

SensorDisplayBridge::SensorDisplayBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void SensorDisplayBridge::setup(uint8_t _channelIndex)
{   
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _screen.show();
}

SensorDisplayBridge::~SensorDisplayBridge()
{
}

void SensorDisplayBridge::setDetected(bool detected)
{
    auto& device = *_channel;
    lv_label_set_text(_screen.value, device.currentValueAsString().c_str());
    ImageLoader::loadImage(_screen.image, device.mainFunctionImage().imageFile, device.mainFunctionImage().allowRecolor, device.mainFunctionValue());
    
}
