#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Display/KnxChannelDisplay.h"
#include "../Screens/MainFunctionScreen.h"

class DisplayDisplayBridge : public DisplayBridge
{
    DetailDevicePage& _detailDevicePage;
    MainFunctionScreen& _screen = *MainFunctionScreen::instance;
public:
    DisplayDisplayBridge(DetailDevicePage& detailDevicePage);
    virtual ~DisplayDisplayBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setValue(double value) override;
    virtual void setValue(const char* value) override;
    void updateValue();
};  