#pragma once
#include "Page.h"
#include "../Screens/MainFunctionScreen.h"
#include "SmartHomeBridgeModule.h"

class MainFunctionPage : public Page
{
private:
    MainFunctionScreen& _screen = *MainFunctionScreen::instance;
    virtual const char* pageType() override;
    MainFunctionChangedHandler _handler;
    lv_event_cb_t _eventPressed = nullptr;
    lv_event_cb_t _eventReleased = nullptr;
    KnxChannelBase* _device;
    unsigned long _clickStarted = 0;
    bool _longPressed = false;
    bool _shortPressed = false;

    void channelValueChanged(KnxChannelBase& channel);
    void shortClicked();
    void longPressed();
    void buttonReleased();
    void handleClick(int function, int jumpToPage);

public:
    virtual ~MainFunctionPage() override;
    void loop() override;
    void setup() override;
};