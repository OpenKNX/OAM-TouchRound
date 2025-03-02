#pragma once
#include "OpenKNX.h"
#include "Page.h"
#include "../DeviceBinderFactory.h"

class ChannelBridge;

class DetailDevicePage : public Page
{
    static DeviceBinderFactory* _widgetFactory;
protected:
    ChannelBridge* _device;
    virtual const char* pageType() override;

public:
    virtual ~DetailDevicePage() override;
    virtual void createDeviceBinder();

    void setup() override;
};