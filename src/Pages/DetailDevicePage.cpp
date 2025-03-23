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
    if (_bridge != nullptr)
    {
        KnxChannelBase* device = getDevice();
        device->deleteBridgeDevice(_bridge);
    }
}

KnxChannelBase* DetailDevicePage::getDevice()
{
    if (_device == nullptr)
       _device = openknxSmartHomeBridgeModule.getChannel(ParamTCH_CHDeviceSelection1 - 1);
    return _device;
}

void DetailDevicePage::createDeviceBinder()  
{
    if (_widgetFactory == nullptr)
        _widgetFactory = new DeviceBinderFactory();
    auto deviceNumber = ParamTCH_CHDeviceSelection1 - 1;
    if (deviceNumber >= openknxSmartHomeBridgeModule.getNumberOfUsedChannels())
    {
        // std::ostringstream message;
        // message << "Gerät " << _channelIndex + 1 << " nicht verfügbar\nIn der ETS unter Geräte|Allgemein\ndie Verfügbare Geräte prüfen";
        // openknxTouchDisplayModule.showErrorPage(message.str().c_str());
        openknxTouchDisplayModule.showErrorPage("Gerät nicht verfügbar");
        return;
    }
    logDebugP("Create device widget %d", deviceNumber);
   
    KnxChannelBase* device = getDevice();
    if (device == nullptr)
    {
        errorInSetup("Gerät ist deaktiviert");
        return;
    }
    _widgetFactory->_currentDevicePage = this;
    _bridge = device->createBridgeDevice(*_widgetFactory);
    if (_bridge == nullptr)
    {
        errorInSetup("Gerät wird zur Anzeige\nnoch nicht unterstützt");
        return;
    }
}

void DetailDevicePage::setup()
{
    createDeviceBinder();
}

std::string DetailDevicePage::name()
{
    KnxChannelBase* device = getDevice();
    if (device != nullptr)
        return device->getNameInUTF8();
    return "Nicht definiert";
}

std::string DetailDevicePage::image()
{
    KnxChannelBase* device = getDevice();
    if (device != nullptr)
        return device->mainFunctionImage();
    return "";
}