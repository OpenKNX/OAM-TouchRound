#pragma once
#include "../Pages/DetailDevicePage.h"
#include "RGB/KnxChannelRGB.h"
#include "../Screens/RGBScreen.h"

class RGBDeviceBridge : public RGBBridge
{
    RGBScreen& _screen = *RGBScreen::instance;
    lv_event_cb_t _eventColorChanged = nullptr;
    DetailDevicePage& _detailDevicePage;
public:
    RGBDeviceBridge(DetailDevicePage& detailDevicePage);
    virtual ~RGBDeviceBridge() override;

    void setup(uint8_t channelIndex) override;
    void updateColor(uint16_t hue, uint8_t saturation, uint8_t value);
    void updateText();
    void setRGB(uint32_t rgb) override;
    void setPower(bool on) override;
};