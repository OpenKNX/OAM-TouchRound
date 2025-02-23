#include "WidgetFactory.h"
#include "Cells/DeviceCell.h"
#include "Widgets/WidgetSwitch.h"


const std::string WidgetFactory::name()
{
    return "WidgetFactory";
}

SwitchBridge* WidgetFactory::createSwitch(KnxChannelSwitch& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    return new WidgetSwitch(*currentDeviceCell);
}