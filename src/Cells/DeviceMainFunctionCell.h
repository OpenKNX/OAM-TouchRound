#pragma once
#include "OpenKNX.h"
#include "Cell.h"
#include "SmartHomeBridgeModule.h"

class DeviceMainFunctionCell : public Cell
{
    MainFunctionChangedHandler _handler;
    lv_event_cb_t _eventClicked = nullptr;
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
    virtual void loop() override;

protected:
    virtual const char* cellType() override;
public:
    virtual  ~DeviceMainFunctionCell() override;
    virtual void init(KnxChannelBase* device);
    virtual void setup() override;
    
};
