#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Display/KnxChannelDisplay.h"
#include "../Screens/MainFunctionScreen.h"

class DisplayDeviceBridge : public DeviceBridge
{
    DetailDevicePage& _detailDevicePage;
    MainFunctionScreen& _screen = *MainFunctionScreen::instance;
public:
    DisplayDeviceBridge(DetailDevicePage& detailDevicePage);
    virtual ~DisplayDeviceBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setValue(double value) override;
    virtual void setValue(const char* value) override;
    virtual void mainFunctionValueChanged() override;
};  