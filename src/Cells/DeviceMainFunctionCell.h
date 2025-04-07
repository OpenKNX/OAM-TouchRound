#pragma once
#include "OpenKNX.h"
#include "Cell.h"
#include "SmartHomeBridgeModule.h"

class DeviceMainFunctionCell : public Cell
{
    MainFunctionChangedHandler _handler;
    lv_event_cb_t _eventPressed = nullptr;
    KnxChannelBase* _device;
    uint8_t _deviceIndex = 255;
    bool _clickStarted = false;
   
    void channelValueChanged(KnxChannelBase& channel);
    virtual void shortPressed() override;
    virtual void longPressed() override;
    virtual void resetPressed() override;
    void handleClick(int function, int jumpToPage);
   
protected:
    virtual const char* cellType() override;
public:
    virtual  ~DeviceMainFunctionCell() override;
    virtual void init(KnxChannelBase* device, uint8_t deviceIndex);
    virtual void setup() override;
    
};
