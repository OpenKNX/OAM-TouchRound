#pragma once
#include "OpenKNX.h"
#include "Cell.h"

class WidgetFactory;
class ChannelBridge;

class DeviceCell : public Cell
{
    static WidgetFactory* _widgetFactory;
protected:
    uint8_t _channelIndex = 0; // device channel index
    ChannelBridge* _device;
public:
    virtual ~DeviceCell() override;
    void init(uint8_t deviceIndex);
    virtual void createWidget();

    void setupCell() override;
};


