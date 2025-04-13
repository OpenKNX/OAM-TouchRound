#include "DeviceBinderFactory.h"
#include "DisplayBridges/SwitchDisplayBridge.h"
#include "DisplayBridges/DimmerDisplayBridge.h"
#include "DisplayBridges/DisplayDisplayBridge.h"
#include "DisplayBridges/SensorDisplayBridge.h"
#include "DisplayBridges/RolladenDisplayBridge.h"
#include "DisplayBridges/JalousieDisplayBridge.h"

const std::string DeviceBinderFactory::name()
{
    return "DeviceBinderFactory";
}

SwitchBridge* DeviceBinderFactory::createSwitch(KnxChannelSwitch& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new SwitchDisplayBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}

DimmerBridge* DeviceBinderFactory::createDimmer(KnxChannelDimmer& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new DimmerDisplayBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}

RolladenBridge* DeviceBinderFactory::createRolladen(KnxChannelRolladen& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new RolladenDisplayBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}

RolladenBridge* DeviceBinderFactory::createJalousien(KnxChannelJalousie& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    logError("DeviceBinderFactory", "Jolousie");
    auto result = new JalousieDisplayBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}


DisplayBridge* DeviceBinderFactory::createDisplay(KnxChannelDisplay& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new DisplayDisplayBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}

SensorBridge* DeviceBinderFactory::createSensor(KnxChannelSensor& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new SensorDisplayBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}