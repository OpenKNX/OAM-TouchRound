#include "MainFunctionPage.h"
#include "SmartHomeBridgeModule.h"
#include "TouchDisplayModule.h"

MainFunctionPage::~MainFunctionPage()
{
    if (_channel != nullptr)
        _channel->removeChangedHandler(_handler);
   
    if (_eventPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.screen, _eventPressed, this);
    if (_eventLongPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.screen, _eventLongPressed, this);  
}

const char* MainFunctionPage::pageType()
{
    return "MainFunction";
}

void MainFunctionPage::setup()
{

    _channel = openknxSmartHomeBridgeModule.getChannel(ParamTCH_ChannelDeviceSelection1 - 1);
    if (_channel == nullptr)
    {
        errorInSetup("Gerät ist deaktiviert");
        return;
    }
    _handler = [this](KnxChannelBase& channel)
    {
       channelValueChanged(channel);
    };
    _channel->addChangedHandler(_handler);
    _eventPressed = [](lv_event_t *e) { ((MainFunctionPage*) e->user_data)->shortClicked(); };
    lv_obj_add_event_cb(_screen.screen, _eventPressed, LV_EVENT_SHORT_CLICKED, this);
    _eventLongPressed = [](lv_event_t *e) { ((MainFunctionPage*) e->user_data)->longPressed(); };
    lv_obj_add_event_cb(_screen.screen, _eventLongPressed, LV_EVENT_LONG_PRESSED, this);
  
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _screen.show();
}

void MainFunctionPage::channelValueChanged(KnxChannelBase& channel)
{
    lv_label_set_text(_screen.value, channel.currentValueAsString().c_str());
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
    logDebugP("MainFunctionPage shortClicked %d", (int) this);
    handleClick(ParamTCH_ChannelShortPress1, ParamTCH_ChannelJumpToShort1);
}

void MainFunctionPage::longPressed()
{
    logDebugP("MainFunctionPage longPressed %d", (int) this);
    handleClick(ParamTCH_ChannelLongPress1, ParamTCH_ChannelJumpToLong1);
}

void MainFunctionPage::handleClick(int function, int jumpToPage)
{
    // <Enumeration Text="Hauptfunktion ausführen" Value="0" Id="%ENID%" />
    // <Enumeration Text="Detailseite aufrufen" Value="1" Id="%ENID%" />
    // <Enumeration Text="Absprung zu Seite" Value="2" Id="%ENID%" />
    switch(function)
    {
    case 0:      
        if (_channel->supportMainFunctionClick())
            _channel->commandMainFunctionClick();
        break;
    case 1:
        openknxTouchDisplayModule.showDetailDevicePage();
        break;
    case 2:
        openknxTouchDisplayModule.activatePage(jumpToPage);
        break;
    }
}