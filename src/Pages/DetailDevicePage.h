#pragma once
#include "OpenKNX.h"
#include "Page.h"
#include "../WidgetFactory.h"

class ChannelBridge;

class DetailDevicePage : public Page
{
    static WidgetFactory* _widgetFactory;
protected:
    ChannelBridge* _device;
    virtual const char* pageType() override;

public:
    virtual ~DetailDevicePage() override;
    virtual void createWidget();

    void setup() override;
};