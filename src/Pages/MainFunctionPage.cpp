#include "MainFunctionPage.h"
#include "SmartHomeBridgeModule.h"
#include "../TouchDisplayModule.h"
#include "../ImageLoader.h"


MainFunctionPage::~MainFunctionPage()
{
    if (_device != nullptr)
        _device->removeChangedHandler(_handler);
   
    if (_eventPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.screen, _eventPressed, this);  
}

const char* MainFunctionPage::pageType()
{
    return "MainFunction";
}

KnxChannelBase* MainFunctionPage::getDevice()
{
    if (_device == nullptr)
        _device = openknxSmartHomeBridgeModule.getChannel(ParamTCH_CHDeviceSelection1 - 1);
    return _device;
}

void MainFunctionPage::setup()
{
    _device = getDevice();
    if (_device == nullptr)
    {
        errorInSetup("Gerät ist deaktiviert");
        return;
    }
    auto& device = *_device;
    _handler = [this](KnxChannelBase& channel)
    {
       channelValueChanged(channel);
    };
    device.addChangedHandler(_handler);
    _eventPressed = [](lv_event_t *e) { ((MainFunctionPage*) e->user_data)->_clickStarted = true; };
    lv_obj_add_event_cb(_screen.screen, _eventPressed, LV_EVENT_PRESSED, this);
  
    lv_label_set_text(_screen.label, device.getNameInUTF8());
    
    logErrorP("show");
    _screen.show();
    logErrorP("showFinished");
}


void MainFunctionPage::channelValueChanged(KnxChannelBase& channel)
{
    lv_label_set_text(_screen.value, channel.currentValueAsString().c_str());
    logErrorP("loadImage");
    ImageLoader::loadImage(_screen.image, channel.mainFunctionImage());
  
    logErrorP("mainFunctionValue");
    if (channel.mainFunctionValue())
    {
        logErrorP("on");
        lv_obj_set_style_img_recolor_opa(_screen.image, 255, 0);
        lv_obj_set_style_img_recolor(_screen.image, lv_color_make(255,255,0), 0);
    }
    else
    {
        logErrorP("off");
        lv_obj_set_style_img_recolor_opa(_screen.image, 0, 0);
        lv_obj_set_style_img_recolor(_screen.image, lv_color_make(128,128,128), 0);
    }
}

void MainFunctionPage::shortPressed()
{
    if (_clickStarted)
    {
        logErrorP("handle shortPressed");
        handleClick(ParamTCH_CHShortPress1, ParamTCH_CHJumpToShort1);
    }
}

void MainFunctionPage::longPressed()
{
    if (_clickStarted)
    {
        logErrorP("handle longPressed");   
        handleClick(ParamTCH_CHLongPress1, ParamTCH_CHJumpToLong1);
    }      
}

void MainFunctionPage::resetPressed()
{
    logErrorP("handle resetPressed");
    _clickStarted = false;
}
   

void MainFunctionPage::handleClick(int function, int jumpToPage)
{
    // <Enumeration Text="Nichts" Value="0" Id="%ENID%" />          
    // <Enumeration Text="Hauptfunktion ausführen" Value="0" Id="%ENID%" />
    // <Enumeration Text="Detailseite aufrufen" Value="1" Id="%ENID%" />
    // <Enumeration Text="Absprung zu Seite" Value="2" Id="%ENID%" />
    switch(function)
    {
    case 0:
        logDebugP("Nichts");
        return;
    case 1:    
        logDebugP("Hauptfunktion");
        if (_device->supportMainFunctionClick())
            _device->commandMainFunctionClick();
        return;
    case 2:
        logDebugP("Detailseite");
        openknxTouchDisplayModule.showDetailDevicePage();
        return;
    case 3:
        logDebugP("Absprung zu Seite %d", jumpToPage);
        openknxTouchDisplayModule.activatePage(jumpToPage);
        return;
    }
}

std::string MainFunctionPage::name()
{
    KnxChannelBase* device = getDevice();
    if (device != nullptr)
        return device->getNameInUTF8();
    return "Nicht definiert";
}

std::string MainFunctionPage::image()
{
    KnxChannelBase* device = getDevice();
    if (device != nullptr)
        return device->mainFunctionImage(); 
    return "";  
}