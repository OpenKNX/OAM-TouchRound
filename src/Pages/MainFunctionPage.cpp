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
    if (_eventReleased != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.screen, _eventReleased, this);  
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
    _eventPressed = [](lv_event_t *e) { ((MainFunctionPage*) e->user_data)->_clickStarted = max(1l, millis()); };
    lv_obj_add_event_cb(_screen.screen, _eventPressed, LV_EVENT_PRESSED, this);
    _eventReleased = [](lv_event_t *e) { ((MainFunctionPage*) e->user_data)->buttonReleased(); };
    lv_obj_add_event_cb(_screen.screen, _eventReleased, LV_EVENT_RELEASED, this);
  
    lv_label_set_text(_screen.label, device.getNameInUTF8());
    
    _screen.show();
}

void MainFunctionPage::loop()
{
    Page::loop();
    if (_shortPressed)
    {
        _shortPressed = false;
        shortClicked();
    }
    if (_longPressed)
    {
        _longPressed = false;
        longPressed();
    }
}

void MainFunctionPage::channelValueChanged(KnxChannelBase& channel)
{
    lv_label_set_text(_screen.value, channel.currentValueAsString().c_str());
    ImageLoader::loadImage(_screen.image, channel.mainFunctionImage());
  
    if (channel.mainFunctionValue())
    {
        lv_obj_set_style_img_recolor_opa(_screen.image, 255, 0);
        lv_obj_set_style_img_recolor(_screen.image, lv_color_make(255,255,0), 0);
    }
    else
    {
        lv_obj_set_style_img_recolor_opa(_screen.image, 0, 0);
        lv_obj_set_style_img_recolor(_screen.image, lv_color_make(128,128,128), 0);
    }
}

void MainFunctionPage::shortClicked()
{
    handleClick(ParamTCH_CHShortPress1, ParamTCH_CHJumpToShort1);
}

void MainFunctionPage::buttonReleased()
{
    if (_clickStarted == 0)
    {
        logDebugP("Button released without click started");
        return;
    }
    auto clickTime = millis() - _clickStarted;
    _clickStarted = 0;
    logDebugP("Button released after %d ms", (int) clickTime);
    if (clickTime < 500)
        _shortPressed = true;
    else
        _longPressed = true;
}

void MainFunctionPage::longPressed()
{
    handleClick(ParamTCH_CHLongPress1, ParamTCH_CHJumpToLong1);
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