#include "DetailDevicePage.h"
#include "../TouchDisplayModule.h"
#include "SmartHomeBridgeModule.h"
#include "../DeviceBinderFactory.h"

DeviceBinderFactory* DetailDevicePage::_widgetFactory = nullptr;

const char* DetailDevicePage::pageType()
{
    return "DetailDevice";
}

DetailDevicePage::~DetailDevicePage()
{
    if (_device != nullptr)
    {
        KnxChannelBase* channel = openknxSmartHomeBridgeModule.getChannel(_channelIndex);
        channel->deleteBridgeDevice(_device);
    }
}


void DetailDevicePage::createDeviceBinder()  
{
    if (_widgetFactory == nullptr)
        _widgetFactory = new DeviceBinderFactory();
    auto deviceNumber = ParamTCH_ChannelDeviceSelection1;
    if (deviceNumber >= openknxSmartHomeBridgeModule.getNumberOfUsedChannels())
    {
        // std::ostringstream message;
        // message << "Gerät " << _channelIndex + 1 << " nicht verfügbar\nIn der ETS unter Geräte|Allgemein\ndie Verfügbare Geräte prüfen";
        // openknxTouchDisplayModule.showErrorPage(message.str().c_str());
        openknxTouchDisplayModule.showErrorPage("Gerät nicht verfügbar");
        return;
    }
    logDebugP("Create device widget %d", deviceNumber);
   
    KnxChannelBase* channel = openknxSmartHomeBridgeModule.getChannel(deviceNumber - 1);
    if (channel == nullptr)
    {
        errorInSetup("Gerät ist deaktiviert");
        return;
    }
    _widgetFactory->_currentDevicePage = this;
    _device = channel->createBridgeDevice(*_widgetFactory);
    if (_device == nullptr)
    {
        errorInSetup("Gerät wird zur Anzeige\nnoch nicht unterstützt");
        return;
    }
}

void DetailDevicePage::setup()
{
    createDeviceBinder();
}