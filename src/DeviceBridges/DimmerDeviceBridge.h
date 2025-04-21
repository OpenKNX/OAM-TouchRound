
#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Dimmer/KnxChannelDimmer.h"
#include "../Screens/DimmerScreen.h"


class DimmerDeviceBridge : public DimmerBridge
{
    lv_event_cb_t _eventSliderReleased = nullptr;
    lv_event_cb_t _eventSliderPressing = nullptr;
    lv_event_cb_t _eventButtonPressed = nullptr;
    DetailDevicePage& _detailDevicePage;
    DimmerScreen& _screen = *DimmerScreen::instance;
    bool _isSliderPressed = false;
public:
    DimmerDeviceBridge(DetailDevicePage& detailDevicePage);
    virtual ~DimmerDeviceBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setBrightness(uint8_t brightness) override;
    void sliderReleased();
    void sliderPressing();
    void buttonClicked();
    void updateText();
    virtual void mainFunctionValueChanged() override;
};  