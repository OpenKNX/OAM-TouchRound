#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Dimmer/KnxChannelDimmer.h"


class DimmerWidget : public DimmerBridge
{
    _lv_event_dsc_t* _eventReleased = nullptr;
    _lv_event_dsc_t* _eventButtonPressed = nullptr;
    DetailDevicePage& _detailDevicePage;
public:
    DimmerWidget(DetailDevicePage& detailDevicePage);
    virtual ~DimmerWidget() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setBrightness(uint8_t brightness) override;
    void released();
    void buttonClicked();
    void updateText();
};  