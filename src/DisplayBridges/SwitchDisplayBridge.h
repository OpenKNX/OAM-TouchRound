#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Switch/KnxChannelSwitch.h"


class SwitchDisplayBridge : public SwitchBridge
{
    _lv_event_dsc_t* _eventButtonPressed = nullptr;
    DetailDevicePage& _detailDevicePage;
public:
    SwitchDisplayBridge(DetailDevicePage& detailDevicePage);
    virtual ~SwitchDisplayBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setPower(bool on) override;
    void buttonClicked();
};  