#pragma once
#include "../Pages/DetailDevicePage.h"
#include "RolladenDisplayBridge.h"
#include "Jalousie/KnxChannelJalousie.h"
#include "../Screens/JalousieScreen.h"

class JalousieDisplayBridge : public RolladenDisplayBridge
{
    lv_event_cb_t _eventSliderSlatReleased = nullptr;
    JalousieScreen& _screen = *JalousieScreen::instance;
    void sliderSlatReleased();
    
 public:
    JalousieDisplayBridge(DetailDevicePage& detailDevicePage);
    virtual ~JalousieDisplayBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setSlatPosition(uint8_t position) override;
    
};  