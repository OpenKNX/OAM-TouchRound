#pragma once
#include "../Cells/DeviceCell.h"
#include "Switch/KnxChannelSwitch.h"


class WidgetSwitch : public SwitchBridge
{
    _lv_event_dsc_t* _buttonPressedEvent = nullptr;
    DeviceCell& _deviceCell;
public:
    WidgetSwitch(DeviceCell& deviceCell);
    virtual ~WidgetSwitch() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setPower(bool on) override;
    void buttonClicked();
};  