#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Switch/KnxChannelSwitch.h"


class SwitchDisplayBridge : public SwitchBridge
{
    lv_event_cb_t _eventButtonPressed = nullptr;
    DetailDevicePage& _detailDevicePage;
public:
    SwitchDisplayBridge(DetailDevicePage& detailDevicePage);
    virtual ~SwitchDisplayBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setPower(bool on) override;
    void buttonClicked();
};  