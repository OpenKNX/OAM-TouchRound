#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Switch/KnxChannelSwitch.h"


class SwitchWidget : public SwitchBridge
{
    _lv_event_dsc_t* _eventButtonPressed = nullptr;
    DetailDevicePage& _detailDevicePage;
public:
    SwitchWidget(DetailDevicePage& detailDevicePage);
    virtual ~SwitchWidget() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setPower(bool on) override;
    void buttonClicked();
};  