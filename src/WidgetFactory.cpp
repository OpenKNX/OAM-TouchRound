#include "WidgetFactory.h"
#include "Widgets/SwitchWidget.h"
#include "Widgets/DimmerWidget.h"

const std::string WidgetFactory::name()
{
    return "WidgetFactory";
}

SwitchBridge* WidgetFactory::createSwitch(KnxChannelSwitch& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new SwitchWidget(*_currentDevicePage);
    channel.add(result);
    return result;
}

DimmerBridge* WidgetFactory::createDimmer(KnxChannelDimmer& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new DimmerWidget(*_currentDevicePage);
    channel.add(result);
    return result;
}