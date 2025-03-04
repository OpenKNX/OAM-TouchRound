#include <TouchDisplayModule.h>
#include <Arduino.h>
#include <ui.h>
#include "lv_xiao_round_screen.h"
#include "knxprod.h"
#include "./Pages/Page.h"
#include "./Screens/CellScreen.h"


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
    _displayTimeoutMs = ParamTCH_SwitchOffDelayTimeMS;
    _pageTimeout = ParamTCH_DefaultPageDelayTimeMS;
    _defaultPage = ParamTCH_DefaultPage;
    if (ParamTCH_DefaultPageKO)
    {
        if (KoTCH_DefaultPage.initialized())
            _defaultPage = KoTCH_DefaultPage.value(DPT_SceneNumber);
        else
            KoTCH_DefaultPage.requestObjectRead();
    }
    logDebugP("Default Page: %d", _defaultPage);
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
        case TCH_KoDisplayOnOff:
        {
            display(ko.value(DPT_Switch));
        }
        break;
    }
}

void TouchDisplayModule::activePage(uint8_t page, bool displayOn)
{
    if (displayOn)
        display(true);  

    _lastTimeoutReset = millis();
    if (_channelIndex == page - 1)
    {
        logDebugP("Page: %d already activ", page);
        return;
    }
    logDebugP("Active Page: %d", page);
    _channelIndex = page - 1;
    KoTCH_CurrentPage.value(_channelIndex, DPT_SceneNumber);
    if (_currentPage != nullptr)
        delete _currentPage;
    _currentPage = Page::createPage(_channelIndex);  
}


void TouchDisplayModule::showErrorPage(const char *message)
{
    display(true);
    _lastTimeoutReset = 0;
    logErrorP("Error Screen: %s", message);
    if (_currentPage != nullptr)
        delete _currentPage;
    _currentPage = Page::createErrorPage(message, _channelIndex);
}

void TouchDisplayModule::nextPage()
{
    uint8_t currentChannel = _channelIndex;
    uint8_t newPage = _channelIndex + 1;
    while(currentChannel != ++_channelIndex)
    {
        if (_channelIndex >= ParamTCH_VisibleChannels)
            _channelIndex = 0;
        if (ParamTCH_ChannelNavigation && ParamTCH_ChannelNumbeOfFields > 0)
        {
            newPage = _channelIndex + 1;
            break;
        }
    }
    _channelIndex = currentChannel; // restore current channel
    activePage(newPage);
}

void TouchDisplayModule::previousPage()
{
    uint8_t currentChannel = _channelIndex;
    uint8_t newPage = _channelIndex + 1;
    while(currentChannel != --_channelIndex)
    {
        if (_channelIndex >= ParamTCH_VisibleChannels)
            _channelIndex = ParamTCH_VisibleChannels - 1;
        if (ParamTCH_ChannelNavigation && ParamTCH_ChannelNumbeOfFields > 0)
        {
            newPage = _channelIndex + 1;
            break;
        }
    }
    _channelIndex = currentChannel;
    activePage(newPage);
}

void TouchDisplayModule::addGlobalEvents(lv_obj_t *sreen)
{
    lv_obj_add_event_cb(sreen, [](lv_event_t *e) { ((TouchDisplayModule *)e->user_data)->touched(e); }, LV_EVENT_PRESSED, this);
    lv_obj_add_event_cb(sreen, [](lv_event_t *e) { ((TouchDisplayModule *)e->user_data)->touched(e); }, LV_EVENT_LONG_PRESSED_REPEAT, this);
}  

void TouchDisplayModule::setup(bool configured)
{
    if (configured)
        _lastTimeoutReset = millis();

    lv_log_register_print_cb(lv_log);

    lv_init();

    lv_xiao_disp_init();
    lv_xiao_touch_init();

    lv_disp_t *display = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(display, lv_palette_main(LV_PALETTE_GREY), lv_palette_main(LV_PALETTE_YELLOW), 1, LV_FONT_DEFAULT);
    lv_disp_set_theme(display, theme);
    ui_Switch_screen_init();
    ui_Dimm_screen_init();
    ui_Color_screen_init();
    ui_Message_screen_init();
    CellScreen2::init();
    CellScreen3::init();
    CellScreen4::init();

    addGlobalEvents(ui_Switch);
    addGlobalEvents(ui_Dimm);
    addGlobalEvents(ui_Color);
    addGlobalEvents(ui_Message);
    addGlobalEvents(CellScreen2::instance->screen);
    addGlobalEvents(CellScreen3::instance->screen);
    addGlobalEvents(CellScreen4::instance->screen);

    ui_screen = lv_obj_create(nullptr); // create screen
   
    if (configured)
    {
        auto gestureLayer = lv_obj_create(lv_layer_top());
        const int gestureLayerHeight = 50;
        lv_obj_clear_flag(gestureLayer, LV_OBJ_FLAG_SCROLLABLE );  
        lv_obj_set_y(gestureLayer, LV_VER_RES - gestureLayerHeight);
        lv_obj_set_size(gestureLayer, LV_HOR_RES, gestureLayerHeight) ;
        lv_obj_set_style_border_width(gestureLayer, 0, 0);
        lv_obj_set_style_opa(gestureLayer, LV_OPA_0, 0);
        lv_obj_set_style_bg_color(gestureLayer, lv_color_make(0, 255, 0), 0);
        lv_obj_clear_flag(gestureLayer, LV_OBJ_FLAG_GESTURE_BUBBLE);
        lv_obj_add_event_cb(gestureLayer, [](lv_event_t *e) { ((TouchDisplayModule *)e->user_data)->handleGesture(e); }, LV_EVENT_GESTURE, this);
    }
    _displayOffRectangle = lv_obj_create(lv_layer_top());
    lv_obj_set_size(_displayOffRectangle, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_bg_color(_displayOffRectangle, lv_color_black(), 0);
    lv_obj_set_style_border_width(_displayOffRectangle, 0, 0);
    lv_obj_add_flag(_displayOffRectangle, LV_OBJ_FLAG_HIDDEN);
    addGlobalEvents(_displayOffRectangle);
    if (!configured)
    {
        showErrorPage("OpenKNX Touch Round\nBitte übertragen Sie die\nETS Applikation");
    }
    Module::setup(configured);
}

void TouchDisplayModule::touched(lv_event_t *event)
{
    if (!_displayOn)
    {
        lv_event_stop_bubbling(event);
    }
    display(true);
}


void TouchDisplayModule::lv_log(const char *buf)
{
    //     logDebug("lvgl", buf);
}


void TouchDisplayModule::resetDisplayTimeout()
{
    if (_lastTimeoutReset != 0)
        _lastTimeoutReset = millis();
}

void TouchDisplayModule::display(bool on)
{
    if (on)
        resetDisplayTimeout();
    if (_displayOn == on)
    {
        return;
    }
    _displayOn = false;
    if (on)
    {
        logDebug("Display", "Turn display on.");
        _displayOn = true;
        digitalWrite(XIAO_BL, HIGH);
        lv_obj_add_flag(_displayOffRectangle, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        logDebug("Display", "Turn display off.");
        _displayOn = false;
        lv_obj_clear_flag(_displayOffRectangle, LV_OBJ_FLAG_HIDDEN);
        digitalWrite(XIAO_BL, LOW);
    }
    if (knx.configured())
        KoTCH_DisplayOnOffState.value(_displayOn, DPT_State);
}

void TouchDisplayModule::handleGesture(lv_event_t *event)
{
    logDebugP("Gesture event");
    if (!_displayOn)
    {
        lv_event_stop_bubbling(event);
        lv_indev_wait_release(lv_indev_get_act());
        display(true);
        return;
    }
    TouchDisplayModule::resetDisplayTimeout();

    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        logDebug("Gesture", "Left");
        lv_event_stop_bubbling(event);
        lv_indev_wait_release(lv_indev_get_act());
        openknxTouchDisplayModule.nextPage();
    }
    else if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        logDebug("Gesture", "Right");
        lv_event_stop_bubbling(event);
        lv_indev_wait_release(lv_indev_get_act());
        openknxTouchDisplayModule.previousPage();
    }
}

void TouchDisplayModule::loop(bool configured)
{
    lv_timer_handler(); // let the GUI do its work
    if (_currentPage != nullptr)
        _currentPage->loop();

    if (_lastTimeoutReset != 0)
    {
        unsigned int now = millis();
        unsigned int pastMs = now - _lastTimeoutReset;
        
        if (_displayTimeoutMs && _displayOn && pastMs > _displayTimeoutMs)
        {
            logDebugP("Display timeout %d", _displayTimeoutMs);
            display(false);
        }
        if (_pageTimeout && _defaultPage != _channelIndex && pastMs > _pageTimeout)
        {
            logDebugP("Default page timeout %d", _pageTimeout);
            activePage(_defaultPage, false);
        }
        if (pastMs > _pageTimeout && pastMs > _displayTimeoutMs)
        {
            _lastTimeoutReset = 0;
        }

    }
}
void TouchDisplayModule::loop1(bool configured)
{
}


bool TouchDisplayModule::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd == "pn")
    {
        openknxTouchDisplayModule.nextPage();
        return true;
    }
    if (cmd == "pp")
    {
        openknxTouchDisplayModule.previousPage();
        return true;
    }
    if (cmd.rfind("p", 0) == 0 && cmd.length() > 1 && cmd[1] >= '0' && cmd[1] <= '9')
    {
        int page = atoi(cmd.substr(1).c_str());
        if (page > 0 && page <= ParamTCH_VisibleChannels)
            openknxTouchDisplayModule.activePage(page);
        else
            logErrorP("Page %d not available", page);
        return true;
    }
    if (cmd == "d1")
    {
        openknxTouchDisplayModule.display(true);
        return true;
    }
    if (cmd == "d0")
    {
        openknxTouchDisplayModule.display(false);
        return true;
    }
    return false;
}

void TouchDisplayModule::showHelp()
{
    if (!knx.configured())
        return;
    openknx.console.printHelpLine("pn", "Next page");
    openknx.console.printHelpLine("pp", "Previous page");
    openknx.console.printHelpLine("p<nn>", "Show page <nn>");
    openknx.console.printHelpLine("d1", "Turn display on");
    openknx.console.printHelpLine("d0", "Turn display off");
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