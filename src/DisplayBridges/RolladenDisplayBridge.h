#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Rolladen/KnxChannelRolladen.h"
#include "../Screens/RolladenScreen.h"

class RolladenDisplayBridge : public RolladenBridge
{
    lv_event_cb_t _eventButtonUpPressed = nullptr;
    lv_event_cb_t _eventButtonDownPressed = nullptr;
    lv_event_cb_t _eventButtonStopPressed = nullptr;
    lv_event_cb_t _eventButtonMainFunctionPressed = nullptr;
    lv_event_cb_t _eventSliderReleased = nullptr;
    RolladenScreen& _screen = *RolladenScreen::instance;
protected:
    DetailDevicePage& _detailDevicePage;
    RolladenDisplayBridge(RolladenScreen& screen, DetailDevicePage& detailDevicePage);
 public:
    RolladenDisplayBridge(DetailDevicePage& detailDevicePage);
    virtual ~RolladenDisplayBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setPosition(uint8_t position) override;
    virtual void setMovement(MoveState movement) override;
    virtual void mainFunctionValueChanged() override;

    void buttonUpPressed();
    void buttonDownPressed();
    void buttonStopPressed();
    void buttonMainFunctionPressed();
    void sliderReleased();
};  