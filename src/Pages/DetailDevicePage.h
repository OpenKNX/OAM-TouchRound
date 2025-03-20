#pragma once
#include "OpenKNX.h"
#include "Page.h"
#include "../DeviceBinderFactory.h"

class ChannelBridge;

class DetailDevicePage : public Page
{
    static DeviceBinderFactory* _widgetFactory;
protected:
    ChannelBridge* _bridge;
    KnxChannelBase* _device;
    virtual const char* pageType() override;
    KnxChannelBase* getDevice();

public:
    virtual ~DetailDevicePage() override;
    virtual void createDeviceBinder();

    void setup() override;
    virtual std::string name() override;
    virtual std::string image() override;
};