#include "WidgetSwitch.h"

WidgetSwitch::WidgetSwitch(DeviceCell& deviceCell)
    : _deviceCell(deviceCell)
{
}

void WidgetSwitch::setup(uint8_t _channelIndex)
{
    const char* label = _channel->getNameInUTF8(); 
}

void WidgetSwitch::setPower(bool on)
{
 // power changed
}