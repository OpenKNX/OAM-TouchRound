#pragma once
#include "../Pages/DetailDevicePage.h"
#include "RolladenDeviceBridge.h"
#include "Jalousie/KnxChannelJalousie.h"
#include "../Screens/JalousieScreen.h"

class JalousieDeviceBridge : public RolladenDeviceBridge
{
    lv_event_cb_t _eventSliderSlatReleased = nullptr;
    JalousieScreen& _screen = *JalousieScreen::instance;
    void sliderSlatReleased();
    
 public:
    JalousieDeviceBridge(DetailDevicePage& detailDevicePage);
    virtual ~JalousieDeviceBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setSlatPosition(uint8_t position) override;
    
};  