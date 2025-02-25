#include "DeviceCell.h"
#include "SmartHomeBridgeModule.h"
#include "../WidgetFactory.h"

WidgetFactory* DeviceCell::_widgetFactory = nullptr;

const char* DeviceCell::cellType()
{
    return "Device";
}

DeviceCell::~DeviceCell()
{
    if (_device != nullptr)
    {
        KnxChannelBase* channel = openknxSmartHomeBridgeModule.getChannel(_channelIndex);
        channel->deleteBridgeDevice(_device);
    }
}

void DeviceCell::init(uint8_t deviceIndex)
{
    _channelIndex = deviceIndex;
}

void DeviceCell::createWidget()  
{
    if (_widgetFactory == nullptr)
        _widgetFactory = new WidgetFactory();
    KnxChannelBase* channel = openknxSmartHomeBridgeModule.getChannel(_channelIndex);
    _widgetFactory->currentDeviceCell = this;
    _device = channel->createBridgeDevice(*_widgetFactory);
}

void DeviceCell::setupCell()
{
    createWidget();
}