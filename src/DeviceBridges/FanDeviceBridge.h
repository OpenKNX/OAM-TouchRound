#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Fan/KnxChannelFan.h"
#include "../Screens/FanScreen.h"

class FanDeviceBridge : public FanBridge
{
    lv_event_cb_t _eventButtonPressed = nullptr;
    lv_event_cb_t _eventIconPressed = nullptr;
    DetailDevicePage& _detailDevicePage;
    FanScreen& _screen = *FanScreen::instance;
    bool _automatic = false;
 public:
    FanDeviceBridge(DetailDevicePage& detailDevicePage);
    virtual ~FanDeviceBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setPower(bool on) override;
    virtual void setAutomatic(bool automatic) override;
    virtual void mainFunctionValueChanged() override;
    void buttonClicked();
    void imageClicked();
};