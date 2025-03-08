#include "MainFunctionPage.h"
#include "SmartHomeBridgeModule.h"

MainFunctionPage::~MainFunctionPage()
{
    if (_channel != nullptr)
    {
        _channel->removeChangedHandler(_handler);
    }
    if (_eventPressed != nullptr)
        lv_obj_remove_event_dsc(_screen.screen, _eventPressed);
    if (_eventLongPressed != nullptr)
        lv_obj_remove_event_dsc(_screen.screen, _eventLongPressed);
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
    _eventPressed = lv_obj_add_event_cb(_screen.screen, [](lv_event_t *e) { ((MainFunctionPage*) e->user_data)->pressed(); }, LV_EVENT_PRESSED, this);
    _eventLongPressed = lv_obj_add_event_cb(_screen.screen, [](lv_event_t *e) { ((MainFunctionPage*) e->user_data)->longPressed(); }, LV_EVENT_LONG_PRESSED, this);
  
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _screen.show();
}

void MainFunctionPage::channelValueChanged(KnxChannelBase& channel)
{
    lv_label_set_text(_screen.label, channel.currentValueAsString().c_str());
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

void MainFunctionPage::pressed()
{
    // <Enumeration Text="Hauptfunktion ausführen" Value="0" Id="%ENID%" />
    // <Enumeration Text="Detailseite aufrufen" Value="1" Id="%ENID%" />
    // <Enumeration Text="Absprung zu Seite" Value="2" Id="%ENID%" />
    //  ParamTCH_ChannelShortPress1

    logDebug("MainFunctionPage", "pressed");
    if (_channel->supportMainFunctionClick())
        _channel->commandMainFunctionClick();
}

void MainFunctionPage::longPressed()
{
    logDebug("MainFunctionPage", "longPressed");
  
}