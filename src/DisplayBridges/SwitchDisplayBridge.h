#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Switch/KnxChannelSwitch.h"
#include "../Screens/SwitchScreen.h"

class SwitchDisplayBridge : public SwitchBridge
{
    lv_event_cb_t _eventButtonPressed = nullptr;
    DetailDevicePage& _detailDevicePage;
    SwitchScreen& _screen = *SwitchScreen::instance;
public:
    SwitchDisplayBridge(DetailDevicePage& detailDevicePage);
    virtual ~SwitchDisplayBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setPower(bool on) override;
    void buttonClicked();
};  