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
       _device = openknxSmartHomeBridgeModule.getChannel(_deviceIndex);
    return _device;
}

void DetailDevicePage::setDevice(uint8_t deviceIndex)  
{
    _deviceIndex = deviceIndex;
}

void DetailDevicePage::createDeviceBinder()
{
    if (_widgetFactory == nullptr)
        _widgetFactory = new DeviceBinderFactory();
    if (_deviceIndex >= openknxSmartHomeBridgeModule.getNumberOfUsedChannels())
    {
        openknxTouchDisplayModule.showErrorPage("Gerät nicht verfügbar");
        return;
    }
    logDebugP("Create device widget %d", _deviceIndex);
   
    KnxChannelBase* device = getDevice();
    if (device == nullptr)
    {
        char label[30];
        snprintf(label, sizeof(label), "Seite %d", _channelIndex + 1);
        char message[30];
        snprintf(message, sizeof(message), "Gerät %d ist deaktiviert", _deviceIndex + 1);
        errorInSetup(label, message);
        return;
    }
    _widgetFactory->_currentDevicePage = this;
    _bridge = device->createBridgeDevice(*_widgetFactory);
    if (_bridge == nullptr)
    {
        errorInSetup(name().c_str(), "Detailseite des Gerätetype\nwird zur Anzeige\nnoch nicht unterstützt.\nBitte die\nHauptfunktionseite\nkonfigurieren.");
        return;
    }
}

void DetailDevicePage::setup()
{
    if (_deviceIndex == 255)
        _deviceIndex = ParamTCH_CHDeviceSelection1 - 1;
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
        return device->mainFunctionImage().imageFile;
    return "";
}