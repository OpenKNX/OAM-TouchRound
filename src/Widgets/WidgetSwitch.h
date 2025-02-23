#pragma once
#include "../Cells/DeviceCell.h"
#include "Switch/KnxChannelSwitch.h"


class WidgetSwitch : public SwitchBridge
{
    DeviceCell& _deviceCell;
public:
    WidgetSwitch(DeviceCell& deviceCell);
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setPower(bool on) override;
};  