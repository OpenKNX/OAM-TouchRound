#include "RGBDeviceBridge.h"
#include "../ImageLoader.h"

RGBDeviceBridge::RGBDeviceBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

RGBDeviceBridge::~RGBDeviceBridge()
{
}

void RGBDeviceBridge::setup(uint8_t channelIndex)
{
    logError("RGBDeviceBridge", "Show");
    mainFunctionValueChanged();
    _screen.show();
}

void RGBDeviceBridge::mainFunctionValueChanged()
{
    auto& device = *_detailDevicePage.getDevice();
    auto image = device.mainFunctionImage();
    ImageLoader::loadImage(_screen.image, image.imageFile, image.allowRecolor, device.mainFunctionValue());
    lv_label_set_text(_screen.value, device.currentValueAsString().c_str());
}

void RGBDeviceBridge::setRGB(uint32_t rgb)
{
    logError("RGBDeviceBridge", "setRGB");
    // Logic to set the RGB color
    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = rgb & 0xFF;

}

void RGBDeviceBridge::setPower(bool on)
{
   
}