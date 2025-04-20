#include "SensorDeviceBridge.h"
#include "../ImageLoader.h"

SensorDeviceBridge::SensorDeviceBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void SensorDeviceBridge::setup(uint8_t _channelIndex)
{   
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    mainFunctionValueChanged();
    _screen.show();
}

SensorDeviceBridge::~SensorDeviceBridge()
{
}

void SensorDeviceBridge::setDetected(bool detected)
{
    
}

void SensorDeviceBridge::mainFunctionValueChanged()
{
    auto& device = *_channel;
    ImageLoader::loadImage(_screen.image, device.mainFunctionImage().imageFile, device.mainFunctionImage().allowRecolor, device.mainFunctionValue());
    lv_label_set_text(_screen.value, device.currentValueAsString().c_str());
}
