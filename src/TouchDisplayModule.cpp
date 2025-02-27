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

void TouchDisplayModule::activePage(uint8_t page)
{
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
    _currentPage = new Page();
    _currentPage->init(_channelIndex);
   
}

void TouchDisplayModule::nextPage()
{
    uint8_t currentChannel = _channelIndex;
    uint8_t newPage = _channelIndex + 1;
    while(currentChannel != ++_channelIndex)
    {
        if (_channelIndex >= ParamTCH_VisibleChannels)
            _channelIndex = 0;
        if (ParamTCH_ChannelNavigation && ParamTCH_ChannelNumFields > 0)
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
        if (ParamTCH_ChannelNavigation && ParamTCH_ChannelNumFields > 0)
        {
            newPage = _channelIndex + 1;
            break;
        }
    }
    _channelIndex = currentChannel;
    activePage(newPage);
}

void TouchDisplayModule::setup(bool configured)
{
    if (configured)
        _lastTimeoutReset = millis();

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

    if (configured)
    {
        // lv_obj_t *touch_area = lv_obj_create(lv_scr_act()); // Neues Objekt auf dem aktiven Bildschirm
        // lv_obj_set_size(touch_area, LV_HOR_RES, LV_VER_RES); // Volle Bildschirmgröße
        // lv_obj_add_flag(touch_area, LV_OBJ_FLAG_CLICKABLE);  // Mach das Objekt berührbar
        // lv_obj_add_event_cb(touch_area, [](lv_event_t *e) { ((TouchDisplayModule*) e->user_data)->touched();  }, LV_EVENT_PRESSED, this); // Event setzen
    
        // lv_obj_add_event_cb(touch_area, [](lv_event_t *e) { ((TouchDisplayModule*) e->user_data)->handleGesture(e);  }, LV_EVENT_GESTURE, this); // Event setzen
    
        lv_obj_add_event_cb(ui_Switch, [](lv_event_t *e) { ((TouchDisplayModule*) e->user_data)->handleGesture(e); }, LV_EVENT_GESTURE, this);
        lv_obj_add_event_cb(ui_Dimm, [](lv_event_t *e) { ((TouchDisplayModule*) e->user_data)->handleGesture(e); }, LV_EVENT_GESTURE, this);
        lv_obj_add_event_cb(ui_Color, [](lv_event_t *e) { ((TouchDisplayModule*) e->user_data)->handleGesture(e); }, LV_EVENT_GESTURE, this);
        lv_obj_add_event_cb(ui_Message, [](lv_event_t *e) { ((TouchDisplayModule*) e->user_data)->handleGesture(e); }, LV_EVENT_GESTURE, this);
    }
    _ui_flag_modify(ui_DimmValue, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_Color, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_Dimm, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_Switch, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);

    if (!configured)
    {
        showErrorPage("OpenKNX Touch Round\nBitte uebertragen Sie die\nETS Applikation");
    }
    Module::setup(configured);
}

void TouchDisplayModule::touched()
{
    logDebugP("Touched");
    resetDisplayTimeout();
}

void TouchDisplayModule::showErrorPage(const char *message)
{
    display(true);
    _lastTimeoutReset = 0;
    logErrorP("Error Screen: %s", message);
    lv_label_set_text(ui_Label3, message);
    lv_disp_load_scr(ui_Message);
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
    if (_displayOn == on)
    {
        if (on)
            resetDisplayTimeout();
        return;
    }
    _displayOn = false;
    if (on)
    {
        logDebug("Display", "Turn display on.");
        _displayOn = true;
        digitalWrite(XIAO_BL, HIGH);
    }
    else
    {
        logDebug("Display", "Turn display off.");
        _displayOn = false;
        digitalWrite(XIAO_BL, LOW);
    }
    KoTCH_DisplayOnOffState.value(_displayOn, DPT_State);
}

void TouchDisplayModule::handleGesture(lv_event_t *event)
{
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

bool TouchDisplayModule::isTouched() 
{
    lv_indev_t *indev = lv_indev_get_next(NULL); // Erstes Eingabegerät abrufen
    while (indev) {
        if (lv_indev_get_type(indev) == LV_INDEV_TYPE_POINTER) { // Ist es ein Touchscreen?
            lv_point_t point;
            lv_indev_get_point(indev, &point); // Touch-Koordinaten abrufen
            return true; // Falls eine Berührung erkannt wurde
        }
        indev = lv_indev_get_next(indev); // Nächstes Eingabegerät prüfen
    }
    return false; // Keine Berührung erkannt
}

void TouchDisplayModule::loop(bool configured)
{
    lv_timer_handler(); // let the GUI do its work
    if (isTouched())
    {
        display(true);
    }

    if (_lastTimeoutReset != 0)
    {
        auto now = millis();
        if (_displayTimeoutMs && _displayOn && now - _lastTimeoutReset > _displayTimeoutMs)
        {
            display(false);
        }
        if (_pageTimeout && _defaultPage != _channelIndex && now - _lastTimeoutReset > _pageTimeout)
        {
            activePage(_defaultPage);
        }
        if (!_displayOn && _defaultPage == _channelIndex)
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
    return false;
}

void TouchDisplayModule::showHelp()
{
    if (!knx.configured())
        return;
    openknx.console.printHelpLine("pn", "Next page");
    openknx.console.printHelpLine("pp", "Previous page");
    openknx.console.printHelpLine("p<nn>", "Show page <nn>");
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