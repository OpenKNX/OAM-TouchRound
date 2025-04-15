#include "DeviceBridgeFactory.h"
#include "DeviceBridges/SwitchDeviceBridge.h"
#include "DeviceBridges/DimmerDeviceBridge.h"
#include "DeviceBridges/DisplayDeviceBridge.h"
#include "DeviceBridges/SensorDeviceBridge.h"
#include "DeviceBridges/RolladenDeviceBridge.h"
#include "DeviceBridges/JalousieDeviceBridge.h"
#include "DeviceBridges/FanDeviceBridge.h"
#include "DeviceBridges/RGBDeviceBridge.h"

const std::string DeviceBridgeFactory::name()
{
    return "DeviceBridgeFactory";
}

SwitchBridge* DeviceBridgeFactory::createSwitch(KnxChannelSwitch& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new SwitchDeviceBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}

DimmerBridge* DeviceBridgeFactory::createDimmer(KnxChannelDimmer& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new DimmerDeviceBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}

RolladenBridge* DeviceBridgeFactory::createRolladen(KnxChannelRolladen& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new RolladenDeviceBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}

RolladenBridge* DeviceBridgeFactory::createJalousien(KnxChannelJalousie& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    logError("DeviceBridgeFactory", "Jolousie");
    auto result = new JalousieDeviceBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}


DeviceBridge* DeviceBridgeFactory::createDisplay(KnxChannelDisplay& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new DisplayDeviceBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}

SensorBridge* DeviceBridgeFactory::createSensor(KnxChannelSensor& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new SensorDeviceBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}

FanBridge* DeviceBridgeFactory::createFan(KnxChannelFan& channel, uint8_t _channelIndex /* this parameter is used in macros, do not rename */, uint8_t deviceType)
{
    auto result = new FanDeviceBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}

RGBBridge* DeviceBridgeFactory::createRGB(KnxChannelRGB& channel, uint8_t channelIndex, uint8_t deviceType)
{
    auto result = new RGBDeviceBridge(*_currentDevicePage);
    channel.add(result);
    return result;
}