#include <TouchDisplayModule.h>
#include <Arduino.h>
#include <ui.h>
#include "lv_xiao_round_screen.h"
#include "knxprod.h"
#include "Page.h"

const std::string TouchDisplayModule::name()
{
    return "TouchRound";
}

const std::string TouchDisplayModule::version()
{
    return MAIN_Version;
}

void TouchDisplayModule::setup()
{
    logDebugP("TouchDisplayModule setup");
    logDebugP("ParamTCH_DefaultPage %d", (int) ParamTCH_DefaultPage);
    logDebugP("ParamTCH_DefaultPageKO %d", (int) ParamTCH_DefaultPageKO);
    logDebugP("ParamTCH_VisibleChannels %d", (int) ParamTCH_VisibleChannels);
    logDebugP("ParamTCH_ChannelNavigation %d", (int) ParamTCH_ChannelNavigation);
    logDebugP("ParamTCH_ChannelDeviceSelection1 %d", (int) ParamTCH_ChannelDeviceSelection1);
    logDebugP("ParamTCH_ChannelNumFields %d", (int) ParamTCH_ChannelNumFields);
    _defaultPage = ParamTCH_DefaultPage;
    if (ParamTCH_DefaultPageKO)
    {
        if (KoTCH_DefaultPage.initialized())
            _defaultPage = KoTCH_DefaultPage.value(DPT_SceneNumber);
        else
            KoTCH_DefaultPage.requestObjectRead();
    }
    activePage(_defaultPage);
}

void TouchDisplayModule::processInputKo(GroupObject &ko)
{
    switch (ko.asap())
    {
        case TCH_KoPage:
        {
            activePage(ko.value(DPT_SceneNumber));
        }
        break;
        case TCH_KoPrevNext:
        {
            if (ko.value(DPT_UpDown))
                nextPage();
            else
                previousPage();
        }
        break;
        case TCH_KoDefaultPage:
        {
            bool isDefaultPageActive = _defaultPage != _channelIndex;
            _defaultPage = ko.value(DPT_SceneNumber);
            if (isDefaultPageActive)
                activePage(_defaultPage);
        }
        break;
    }
}

void TouchDisplayModule::activePage(uint8_t channel)
{
   _channelIndex = channel;
    KoTCH_CurrentPage.value(_channelIndex, DPT_SceneNumber);
    if (_currentPage != nullptr)
        delete _currentPage;
    _currentPage = new Page();
    _currentPage->init(_channelIndex);
   
}

void TouchDisplayModule::nextPage()
{
    uint8_t currentChannel = _channelIndex;
    while(currentChannel != _channelIndex++)
    {
        if (_channelIndex >= ParamTCH_VisibleChannels)
            _channelIndex = 0;

        if (ParamTCH_ChannelNavigation)
            break;
      
    }
    activePage(_channelIndex);
}

void TouchDisplayModule::previousPage()
{
    uint8_t currentChannel = _channelIndex;
    while(currentChannel != _channelIndex--)
    {
        if (_channelIndex >= ParamTCH_VisibleChannels)
            _channelIndex = ParamTCH_VisibleChannels - 1;
        if (ParamTCH_ChannelNavigation)
            break;
    }
    activePage(_channelIndex);
}

void TouchDisplayModule::setup(bool configured)
{
    TouchDisplayModule::displayOn = true;
    TouchDisplayModule::lastPressed = 0;

    lv_log_register_print_cb(lv_log);

    lv_init();

    lv_xiao_disp_init();
    lv_xiao_touch_init();

    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Switch_screen_init();
    ui_Dimm_screen_init();
    ui_Color_screen_init();
    ui_Message_screen_init();

    ui____initial_actions0 = lv_obj_create(NULL);

    lv_obj_add_event_cb(ui_Switch, handleGesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(ui_Dimm, handleGesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(ui_Color, handleGesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(ui_DimmValue, handleValues, LV_EVENT_ALL, NULL);

    _ui_flag_modify(ui_DimmValue, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_Color, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_Dimm, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_Switch, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);

    if (!configured)
    {
        logErrorP("No start Page found");
        lv_disp_load_scr(ui_Message);
    }
    Module::setup(configured);
}

void TouchDisplayModule::lv_log(const char *buf)
{
    //     logDebug("lvgl", buf);
}

void TouchDisplayModule::handleValues(lv_event_t *event)
{
    TouchDisplayModule::resetDisplayTimeout();
}

void TouchDisplayModule::resetDisplayTimeout()
{
    TouchDisplayModule::lastPressed = millis();
    if (!TouchDisplayModule::displayOn)
    {
        logDebug("Display", "Turn display on.");
        TouchDisplayModule::displayOn = true;
        digitalWrite(XIAO_BL, HIGH);
    }
}

void TouchDisplayModule::handleGesture(lv_event_t *event)
{
    TouchDisplayModule::resetDisplayTimeout();

    int oldIndex = TouchDisplayModule::currentScreenIndex;
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        openknxTouchDisplayModule.nextPage();
    }
    else if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        openknxTouchDisplayModule.previousPage();
    }
}


void TouchDisplayModule::loop(bool configured)
{
    lv_timer_handler(); // let the GUI do its work

}
void TouchDisplayModule::loop1(bool configured)
{
//    lv_timer_handler(); // let the GUI do its work

    // if (TouchDisplayModule::currentScreenIndex != 255 && TouchDisplayModule::displayOn && (millis() - TouchDisplayModule::lastPressed > DISPLAY_SLEEP_DELAY)) {
    //     logDebugP("Turn display off.");
    //     TouchDisplayModule::displayOn = false;
    //     digitalWrite(XIAO_BL, LOW);
    // }
}


void TouchDisplayModule::processAfterStartupDelay()
{
}

// void TouchDisplayModule::writeFlash()
// {
//     for (size_t i = 0; i < flashSize(); i++)
//     {
//         //openknx.flash.writeByte(0xd0 + i);
//     }
// }

// void TouchDisplayModule::readFlash(const uint8_t* data, const uint16_t size)
// {
//     // printHEX("RESTORE:", data,  len);
// }

// uint16_t TouchDisplayModule::flashSize()
// {
//     return 10;
// }

TouchDisplayModule openknxTouchDisplayModule;