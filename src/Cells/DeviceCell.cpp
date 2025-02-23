#include "DeviceCell.h"
#include "SmartHomeBridgeModule.h"
#include "../WidgetFactory.h"

WidgetFactory* DeviceCell::_widgetFactory = nullptr;

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