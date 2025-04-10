#include "DisplayDisplayBridge.h"
#include "../ImageLoader.h"

DisplayDisplayBridge::DisplayDisplayBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void DisplayDisplayBridge::setup(uint8_t _channelIndex)
{   
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _screen.show();
}

DisplayDisplayBridge::~DisplayDisplayBridge()
{
}

void DisplayDisplayBridge::setValue(double value)
{
    auto& device = *_channel;
    lv_label_set_text(_screen.value, device.currentValueAsString().c_str());
    ImageLoader::loadImage(_screen.image, device.mainFunctionImage().imageFile, device.mainFunctionImage().allowRecolor, device.mainFunctionValue());

}
