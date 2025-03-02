#include "DeviceBinderFactory.h"
#include "DeviceBinders/SwitchDeviceBinder.h"
#include "DeviceBinders/DimmerDeviceBinder.h"

const std::string DeviceBinderFactory::name()
{
    return "DeviceBinderFactory";
}

SwitchBridge* DeviceBinderFactory::createSwitch(KnxChannelSwitch& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new SwitchDeviceBinder(*_currentDevicePage);
    channel.add(result);
    return result;
}

DimmerBridge* DeviceBinderFactory::createDimmer(KnxChannelDimmer& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new DimmerDeviceBinder(*_currentDevicePage);
    channel.add(result);
    return result;
}