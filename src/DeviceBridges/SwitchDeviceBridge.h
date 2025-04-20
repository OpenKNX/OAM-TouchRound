
#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Switch/KnxChannelSwitch.h"
#include "../Screens/SwitchScreen.h"


class SwitchDeviceBridge : public SwitchBridge
{
    lv_event_cb_t _eventButtonPressed = nullptr;
    DetailDevicePage& _detailDevicePage;
    SwitchScreen& _screen = *SwitchScreen::instance;
public:
    SwitchDeviceBridge(DetailDevicePage& detailDevicePage);
    virtual ~SwitchDeviceBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setPower(bool on) override;
    virtual void mainFunctionValueChanged() override;
  
    void released();
    void buttonClicked();
    void updateText();
};  