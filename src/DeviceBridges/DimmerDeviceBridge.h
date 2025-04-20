
#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Dimmer/KnxChannelDimmer.h"
#include "../Screens/DimmerScreen.h"


class DimmerDeviceBridge : public DimmerBridge
{
    lv_event_cb_t _eventReleased = nullptr;
    lv_event_cb_t _eventButtonPressed = nullptr;
    DetailDevicePage& _detailDevicePage;
    DimmerScreen& _screen = *DimmerScreen::instance;
public:
    DimmerDeviceBridge(DetailDevicePage& detailDevicePage);
    virtual ~DimmerDeviceBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setBrightness(uint8_t brightness) override;
    void released();
    void buttonClicked();
    void updateText();
    virtual void mainFunctionValueChanged() override;
};  