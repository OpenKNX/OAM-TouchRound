#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Rolladen/KnxChannelRolladen.h"
#include "../Screens/RolladenScreen.h"

class RolladenDeviceBridge : public RolladenBridge
{
    lv_event_cb_t _eventButtonUpPressed = nullptr;
    lv_event_cb_t _eventButtonDownPressed = nullptr;
    lv_event_cb_t _eventButtonMainFunctionPressed = nullptr;
    lv_event_cb_t _eventSliderReleased = nullptr;
    lv_event_cb_t _evnetSliderClicked = nullptr;
    RolladenScreen& _screen;
protected:
    DetailDevicePage& _detailDevicePage;
    RolladenDeviceBridge(RolladenScreen& screen, DetailDevicePage& detailDevicePage);
 public:
    RolladenDeviceBridge(DetailDevicePage& detailDevicePage);
    virtual ~RolladenDeviceBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setPosition(uint8_t position) override;
    virtual void setMovement(MoveState movement) override;
    virtual void mainFunctionValueChanged() override;

    void buttonUpPressed();
    void buttonDownPressed();
    void buttonMainFunctionPressed();
    void sliderReleased();
};  