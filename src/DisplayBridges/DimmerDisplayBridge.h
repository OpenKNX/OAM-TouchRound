#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Dimmer/KnxChannelDimmer.h"


class DimmerDisplayBridge : public DimmerBridge
{
    lv_event_cb_t _eventReleased = nullptr;
    lv_event_cb_t _eventButtonPressed = nullptr;
    DetailDevicePage& _detailDevicePage;
public:
    DimmerDisplayBridge(DetailDevicePage& detailDevicePage);
    virtual ~DimmerDisplayBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setBrightness(uint8_t brightness) override;
    void released();
    void buttonClicked();
    void updateText();
};  