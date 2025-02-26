#include "DeviceCell.h"
#include "../TouchDisplayModule.h"
#include "SmartHomeBridgeModule.h"
#include "../WidgetFactory.h"
//#include <sstream>


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
    if (_channelIndex >= openknxSmartHomeBridgeModule.getNumberOfUsedChannels())
    {
        // std::ostringstream message;
        // message << "Gerät " << _channelIndex + 1 << " nicht verfügbar\nIn der ETS unter Geräte|Allgemein\ndie Verfügbare Geräte prüfen";
        // openknxTouchDisplayModule.showErrorPage(message.str().c_str());
        openknxTouchDisplayModule.showErrorPage("Gerät nicht verfügbar");
        return;
    }
    KnxChannelBase* channel = openknxSmartHomeBridgeModule.getChannel(_channelIndex);
    if (channel == nullptr)
    {
        // std::ostringstream message;
        // message << "Gerät " << _channelIndex + 1 << " ist deaktiviert";
        // openknxTouchDisplayModule.showErrorPage(message.str().c_str());
        openknxTouchDisplayModule.showErrorPage("Gerät ist deaktivier");
        return;
    }
    _widgetFactory->currentDeviceCell = this;
    _device = channel->createBridgeDevice(*_widgetFactory);
    if (_device == nullptr)
    {
        // std::ostringstream message;
        // message << "Gerät " << _channelIndex + 1 << "\nwird zur Anzeige nicht unterstützt";
        // openknxTouchDisplayModule.showErrorPage(message.str().c_str());
        openknxTouchDisplayModule.showErrorPage("Gerät wird zur Anzeige nicht unterstützt");
        return;
    }
}

void DeviceCell::setupCell()
{
    createWidget();
}