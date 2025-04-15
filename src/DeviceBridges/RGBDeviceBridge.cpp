#include "RGBDeviceBridge.h"

RGBDeviceBridge::RGBDeviceBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

RGBDeviceBridge::~RGBDeviceBridge()
{
    if (_eventColorChanged != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.valueSlider, _eventColorChanged, this);
}

void RGBDeviceBridge::setup(uint8_t channelIndex)
{
    _eventColorChanged = [](lv_event_t* e) {
        RGBDeviceBridge* self = static_cast<RGBDeviceBridge*>(lv_event_get_user_data(e));
        int value = lv_slider_get_value(self->_screen.valueSlider);
        // Update the channel with the new value
        self->_channel->commandRGB(self, value);
        self->updateText();
    };
    lv_obj_add_event_cb(_screen.valueSlider, _eventColorChanged, LV_EVENT_VALUE_CHANGED, this);

    _screen.show();
}

void RGBDeviceBridge::updateText()
{
    int value = lv_slider_get_value(_screen.valueSlider);
    lv_label_set_text_fmt(_screen.labelValue, "V: %d", value);
}

void RGBDeviceBridge::updateColor(uint16_t hue, uint8_t saturation, uint8_t value)
{
    // Update the RGB screen with the new color values
    // This can include updating the visual representation on the screen
    lv_slider_set_value(_screen.valueSlider, value, LV_ANIM_OFF);
    updateText();
}

void RGBDeviceBridge::setRGB(uint32_t rgb)
{
    // Logic to set the RGB color
    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = rgb & 0xFF;

    // Convert RGB to HSV
    uint8_t max = (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
    uint8_t min = (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
    uint16_t hue = 0;
    uint8_t saturation = (max == 0) ? 0 : ((max - min) * 255 / max);
    uint8_t value = max;

    if (max != min) {
        if (max == r) {
            hue = 60 * ((g - b) / (max - min)) + (g < b ? 360 : 0);
        } else if (max == g) {
            hue = 60 * ((b - r) / (max - min)) + 120;
        } else {
            hue = 60 * ((r - g) / (max - min)) + 240;
        }
    }

    // Update the screen with the HSV values
    updateColor(hue, saturation, value);
}

void RGBDeviceBridge::setPower(bool on)
{
    // Logic to turn the RGB device on or off
    if (on)
    {
        // Turn on the RGB device
    }
    else
    {
        // Turn off the RGB device
    }
}