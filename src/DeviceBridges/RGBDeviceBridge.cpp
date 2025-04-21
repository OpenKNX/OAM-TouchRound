#include "RGBDeviceBridge.h"
#include "../ImageLoader.h"

RGBDeviceBridge::RGBDeviceBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

RGBDeviceBridge::~RGBDeviceBridge()
{
    if (_eventColorChanged != nullptr)
    {
        lv_obj_remove_event_cb(_screen.brightnessSlider, _eventColorChanged);
        lv_obj_remove_event_cb(_screen.hsvContainer, _eventColorChanged);
    }
}

void RGBDeviceBridge::setup(uint8_t channelIndex)
{
    logError("RGBDeviceBridge", "Show");
    _eventColorChanged =[](lv_event_t *e) { ((RGBDeviceBridge*) lv_event_get_user_data(e))->colorChanged(); };
    lv_obj_add_event_cb(_screen.brightnessSlider, _eventColorChanged, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(_screen.hsvContainer, _eventColorChanged, LV_EVENT_RELEASED, this);
 
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

void RGBDeviceBridge::colorChanged()
{
    logErrorP("colorChanged from widget");
    auto& device = *(KnxChannelRGB*) _detailDevicePage.getDevice();
    auto rgb = _screen.red << 16 | _screen.green << 8 | _screen.blue;
    device.commandRGB(nullptr, rgb);
    lv_label_set_text(_screen.value, device.currentValueAsString().c_str());
}

void RGBDeviceBridge::setRGB(uint32_t rgb)
{
    logErrorP("color changed from bus");
    // Logic to set the RGB color
    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = rgb & 0xFF;
    _screen.setRGB(r, g, b);
}

void RGBDeviceBridge::setPower(bool on)
{
    // Not used, becuase mainFunctionValueChanged is used
}