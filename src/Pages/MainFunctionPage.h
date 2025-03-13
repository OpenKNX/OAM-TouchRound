#pragma once
#include "Page.h"
#include "../Screens/MainFunctionScreen.h"
#include "SmartHomeBridgeModule.h"

class MainFunctionPage : public Page
{
private:
    MainFunctionScreen& _screen = *MainFunctionScreen::instance;
    MainFunctionChangedHandler _handler;
    virtual const char* pageType() override;
    lv_event_cb_t _eventPressed = nullptr;
    lv_event_cb_t _eventReleased = nullptr;
    KnxChannelBase* _channel;
    unsigned long _clickStarted = 0;

public:
    virtual ~MainFunctionPage() override;

    void setup() override;
    void channelValueChanged(KnxChannelBase& channel);
    void shortClicked();
    void longPressed();
    void buttonReleased();
    void handleClick(int function, int jumpToPage);
};