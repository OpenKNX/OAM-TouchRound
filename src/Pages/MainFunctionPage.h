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
    KnxChannelBase* _device = nullptr;
    bool _clickStarted = false;
  
    KnxChannelBase* getDevice();
    void channelValueChanged(KnxChannelBase& channel);
    void shortPressed() override;
    void longPressed() override;
    void resetPressed() override;
   
    void handleClick(int function, int jumpToPage);

public:
    virtual ~MainFunctionPage() override;
    void setup() override;
    virtual std::string name() override;
    virtual std::string image() override;
};