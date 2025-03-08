#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Dimmer/KnxChannelDimmer.h"


class DimmerDisplayBridge : public DimmerBridge
{
    _lv_event_dsc_t* _eventReleased = nullptr;
    _lv_event_dsc_t* _eventButtonPressed = nullptr;
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