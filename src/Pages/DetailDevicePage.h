#pragma once
#include "OpenKNX.h"
#include "Page.h"
#include "../DeviceBinderFactory.h"

class ChannelBridge;

class DetailDevicePage : public Page
{
    static DeviceBinderFactory* _widgetFactory;
    uint8_t _deviceIndex = 255;
protected:
    ChannelBridge* _bridge = nullptr;
    KnxChannelBase* _device = nullptr;
    virtual const char* pageType() override;
    KnxChannelBase* getDevice();


public:
    virtual ~DetailDevicePage() override;
    virtual void createDeviceBinder();

    void setup() override;
    virtual std::string name() override;
    virtual std::string image() override;
    void setDevice(uint8_t deviceIndex);
};