#include <TouchDisplayModule.h>
#include <Arduino.h>
#include "lvgl.h"
#include "lv_xiao_round_screen.h"
#include "knxprod.h"
#include "./Pages/Page.h"
#include "./Screens/CellScreen.h"
#include "./Screens/MainFunctionScreen.h"
#include "./Screens/DateTimeScreen.h"
#include "./Screens/SwitchScreen.h"
#include "./Screens/DimmerScreen.h"
#include "./Screens/MessageScreen.h"
#include "./Pages/ProgButtonPage.h"
#include "./ImageLoader.h"

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
            _defaultPage = 1 + (uint8_t) KoTCH_DefaultPage.value(DPT_SceneNumber);
        else
            KoTCH_DefaultPage.requestObjectRead();
    }
    if (ParamTCH_DayNightObject > 0 && !KoTCH_DayNight.initialized())
        KoTCH_DayNight.requestObjectRead();

    if (!KoTCH_PageEnabledA.initialized())
        KoTCH_PageEnabledA.requestObjectRead();
    if (!KoTCH_PageEnabledB.initialized())
        KoTCH_PageEnabledB.requestObjectRead();
    if (!KoTCH_PageEnabledC.initialized())
        KoTCH_PageEnabledC.requestObjectRead();
    if (!KoTCH_PageEnabledD.initialized())
        KoTCH_PageEnabledD.requestObjectRead();
    if (!KoTCH_PageEnabledE.initialized())
        KoTCH_PageEnabledE.requestObjectRead();
    if (!KoTCH_PageEnabledF.initialized())
        KoTCH_PageEnabledF.requestObjectRead();
    if (!KoTCH_PageEnabledG.initialized())
        KoTCH_PageEnabledG.requestObjectRead();
    if (!KoTCH_PageEnabledH.initialized())
        KoTCH_PageEnabledH.requestObjectRead();

    logDebugP("Default Page: %d", _defaultPage);
    showFirstPage();
    Module::setup();
}

void TouchDisplayModule::processInputKo(GroupObject &ko)
{
    switch (ko.asap())
    {
    case TCH_KoPage:
    {
        uint8_t page = 1 + (uint8_t) ko.value(DPT_SceneNumber);
        logDebugP("Requested Page: %d", page);
        if (pageEnabled(page))
            activatePage(page);
        else
        {
            logDebugP("Requested Page: %d not enabled", page);
            _waitForEnablePageWhichWasRequested = max(millis(), 1L);
        }
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
        _defaultPage = 1 + (uint8_t) ko.value(DPT_SceneNumber);
        if (isDefaultPageActive)
            activatePage(_defaultPage);
    }
    case TCH_KoDisplayOnOff:
    {
        display(ko.value(DPT_Switch));
        break;
    }
    case TCH_KoDayNight:
    {
        updateTheme();
        break;
    }
    case TCH_KoPageEnabledA:
    case TCH_KoPageEnabledB:
    case TCH_KoPageEnabledC:
    case TCH_KoPageEnabledD:
    case TCH_KoPageEnabledE:
    case TCH_KoPageEnabledF:
    case TCH_KoPageEnabledG:    
    case TCH_KoPageEnabledH:
    {
        if (_waitForEnablePageWhichWasRequested > 0)
        {
            uint8_t page = 1 + (uint8_t) KoTCH_Page.value(DPT_SceneNumber);
            if (pageEnabled(page))
                activatePage(page);
        }

        if (_channelIndex != 255)
        {
            uint8_t page = _channelIndex + 1;
            if (!pageEnabled(page))
            {
                _channelIndex = 255;
                showFirstPage();
            }   
        }
        else
        {
            showFirstPage();
        }
        break;
    }
    }
}

void TouchDisplayModule::showFirstPage()
{
    if (pageEnabled(_defaultPage))
        activatePage(_defaultPage);
    else
        nextPage();
    if (_channelIndex == 255)
    {
        showErrorPage("Keine Seite freigegeben");
    } 
}


void TouchDisplayModule::activatePage(uint8_t page, bool displayOn)
{
    bool enabled = pageEnabled(page);
    if (!enabled)
    {
        logDebugP("Page: %d not enabled", page);
        return;
    }
    if (_waitForEnablePageWhichWasRequested > 0)
    {
        _waitForEnablePageWhichWasRequested = 0;
        logDebugP("Stop waiting for requested page because a page is activated");
    }
    if (displayOn)
        display(true);

    _lastTimeoutReset = millis();
    auto current = _channelIndex;
    _channelIndex = page - 1;
    if (current == _channelIndex && Page::currentPage() != nullptr && !_detailDevicePageActive)
    {
        logDebugP("Page: %d already activ", page);
        return;
    }
    logDebugP("Active Page: %d", page);
    _detailDevicePageActive = false;
    logDebugP("Set KO: %d", _channelIndex);
    KoTCH_CurrentPage.value(_channelIndex, DPT_SceneNumber);
    logDebugP("Create Page: %d", page);
    Page::showPage(Page::createPage(_channelIndex));
}

void TouchDisplayModule::showDetailDevicePage(uint8_t deviceIndex)
{
    logDebugP("Show Detail Device %d", deviceIndex + 1);
    _detailDevicePageActive = true;
    Page::showPage(Page::createDetailDevicePage(deviceIndex));
}

void TouchDisplayModule::showProgButtonPage()
{
    display(true);
    _lastTimeoutReset = 0;
    Page::showPage(Page::createProgButtonPage());
}

void TouchDisplayModule::showErrorPage(const char *message)
{
    display(true);
    _lastTimeoutReset = 0;
    logErrorP("Error Screen: %s", message);
    Page::showPage(Page::createErrorPage(message, _channelIndex));
}

void TouchDisplayModule::nextPage()
{
    if (knx.configured() && ParamTCH_VisibleChannels > 0)
    {
        _detailDevicePageActive = false;
        uint8_t currentChannel = _channelIndex;
        uint8_t newPage = _channelIndex + 1;
        while (currentChannel != ++_channelIndex)
        {
            if (_channelIndex >= ParamTCH_VisibleChannels)
                _channelIndex = 0;

            uint8_t page = _channelIndex + 1;
            if (ParamTCH_CHNavigation && pageEnabled(page))
            {
                newPage = page;
                break;
            }
        }
        _channelIndex = currentChannel; // restore current channel
        activatePage(newPage);
    }
}

bool TouchDisplayModule::pageEnabled(uint8_t page)
{
    uint8_t _channelIndex = page - 1;
    if (ParamTCH_CHPageType == 0)
        return false;
  
    switch (ParamTCH_CHPageEnabled)
    {
    case 1:
        if (!KoTCH_PageEnabledA.value(DPT_Switch))
            return false;
        break;
    case 2:
        if (KoTCH_PageEnabledB.value(DPT_Switch))
            return false;
        break;
    }
    // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
    // <Enumeration Text="Seitenfreigabe A" Value="1" Id="%ENID%" />
    // <Enumeration Text="Seitenfreigabe B" Value="2" Id="%ENID%" />
    // <Enumeration Text="Seitenfreigabe C" Value="3" Id="%ENID%" /> 
    // <Enumeration Text="Seitenfreigabe D" Value="4" Id="%ENID%" />
    // <Enumeration Text="Seitenfreigabe E" Value="5" Id="%ENID%" />
    // <Enumeration Text="Seitenfreigabe F" Value="6" Id="%ENID%" />
    // <Enumeration Text="Seitenfreigabe G" Value="7" Id="%ENID%" />
    // <Enumeration Text="Seitenfreigabe H" Value="8" Id="%ENID%" />
    switch (ParamTCH_CHPageEnabled)
    {
    case 1:
        if (!KoTCH_PageEnabledA.value(DPT_Switch))
            return false;
        break;
    case 2:
        if (!KoTCH_PageEnabledB.value(DPT_Switch))
            return false;
        break;
    case 3:
        if (!KoTCH_PageEnabledC.value(DPT_Switch))
            return false;
        break;
    case 4:
        if (!KoTCH_PageEnabledD.value(DPT_Switch))
            return false;
        break;
    case 5:
        if (!KoTCH_PageEnabledE.value(DPT_Switch))
            return false;
        break;
    case 6:
        if (!KoTCH_PageEnabledF.value(DPT_Switch))
            return false;
        break;
    case 7:
        if (!KoTCH_PageEnabledG.value(DPT_Switch))
            return false;
        break;
    case 8: 
        if (!KoTCH_PageEnabledH.value(DPT_Switch))
            return false;
        break;
    }
    
    return true;
}

void TouchDisplayModule::previousPage()
{
    if (knx.configured() && ParamTCH_VisibleChannels > 0)
    {
        if (_detailDevicePageActive)
        {
            activatePage(_channelIndex + 1);
            return;
        }
        uint8_t currentChannel = _channelIndex;
        uint8_t newPage = _channelIndex + 1;
        while (currentChannel != --_channelIndex)
        {
            if (_channelIndex >= ParamTCH_VisibleChannels)
                _channelIndex = ParamTCH_VisibleChannels - 1;
            uint8_t page = _channelIndex + 1;
            if (ParamTCH_CHNavigation && pageEnabled(page))
            {
                newPage = page;
                break;
            }
        }
        _channelIndex = currentChannel;
        activatePage(newPage);
    }
}


void TouchDisplayModule::setup(bool configured)
{
    if (configured)
        _lastTimeoutReset = millis();

    if (configured)
    {
        screen_rotation = ParamTCH_DisplayRotation;
    }
    lv_init();
#if LV_USE_LOG
    lv_log_register_print_cb(lv_log);
#endif
#if LVGL_VERSION_MAJOR >= 9
    lv_tick_set_cb(millis);
#endif
    //lv_lodepng_init();
    ImageLoader::connectLittleFSwithLVGL();
  
    logErrorP("Setup lv_xiao_disp_init");
    lv_xiao_disp_init();
    logErrorP("Setup lv_xiao_touch_init");
    lv_xiao_touch_init();
    logErrorP("init display finished");
   
    updateTheme();
    MessageScreen::instance = new MessageScreen();
    MainFunctionScreen::instance = new MainFunctionScreen();
    DateTimeScreen::instance = new DateTimeScreen();
    CellScreen2::instance = new CellScreen2();
    CellScreen3::instance = new CellScreen3();
    CellScreen4::instance = new CellScreen4();
    SwitchScreen::instance = new SwitchScreen();
    DimmerScreen::instance = new DimmerScreen();
    ButtonMessageScreen::instance = new ButtonMessageScreen();

    if (configured)
    {
        if (ParamTCH_SensorKeys)
        {
            pinMode(TOUCH_LEFT_PIN, INPUT);
            pinMode(TOUCH_RIGHT_PIN, INPUT);
            if (ParamTCH_LeftRightChanged)
            {
                attachInterrupt(digitalPinToInterrupt(TOUCH_LEFT_PIN), TouchDisplayModule::interruptTouchRight, CHANGE);
                attachInterrupt(digitalPinToInterrupt(TOUCH_RIGHT_PIN), TouchDisplayModule::interruptTouchLeft, CHANGE);  
            }
            else
            {
                attachInterrupt(digitalPinToInterrupt(TOUCH_LEFT_PIN), TouchDisplayModule::interruptTouchLeft, CHANGE);
                attachInterrupt(digitalPinToInterrupt(TOUCH_RIGHT_PIN), TouchDisplayModule::interruptTouchRight, CHANGE);
            }
        }
    }

    if (configured)
    {
        if (ParamTCH_Slide)
        {
            auto gestureLayer = lv_obj_create(lv_layer_top());
            const int gestureLayerHeight = 50;
            lv_obj_clear_flag(gestureLayer, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_y(gestureLayer, LV_VER_RES - gestureLayerHeight);
            lv_obj_set_size(gestureLayer, LV_HOR_RES, gestureLayerHeight);
            lv_obj_set_style_border_width(gestureLayer, 0, 0);
            lv_obj_set_style_opa(gestureLayer, LV_OPA_0, 128);
            lv_obj_set_style_bg_color(gestureLayer, lv_color_make(128, 128, 128), 0);
            lv_obj_clear_flag(gestureLayer, LV_OBJ_FLAG_GESTURE_BUBBLE);
            lv_obj_add_event_cb(gestureLayer, [](lv_event_t *e)
            { ((TouchDisplayModule *)lv_event_get_user_data(e))->handleGesture(e); }, LV_EVENT_GESTURE, this);
        }
    }
    // _displayOffRectangle = lv_obj_create(lv_layer_top());
    // lv_obj_set_size(_displayOffRectangle, LV_HOR_RES, LV_VER_RES);
    // lv_obj_set_style_bg_color(_displayOffRectangle, lv_color_black(), 0);
    // lv_obj_set_style_border_width(_displayOffRectangle, 0, 0);
    // lv_obj_add_flag(_displayOffRectangle, LV_OBJ_FLAG_HIDDEN);
    if (!configured)
    {
        showProgButtonPage();
    }
    Module::setup(configured);
}

void TouchDisplayModule::updateTheme()
{
    if (!knx.configured())
        setTheme(0);
    else
    {
        // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
        // <Enumeration Text="Umschaltobjekt Nacht EIN" Value="1" Id="%ENID%" />
        // <Enumeration Text="Umschaltobjekt Tag EIN" Value="2" Id="%ENID%" />
        if (ParamTCH_DayNightObject > 0 && KoTCH_DayNight.initialized())
        {
            if (KoTCH_DayNight.value(DPT_Switch))
            {
                if (ParamTCH_DayNightObject == 1)
                    setTheme(ParamTCH_ThemeNight);
                else
                    setTheme(ParamTCH_ThemeDay);
            }
            else
            {
                if (ParamTCH_DayNightObject == 1)
                    setTheme(ParamTCH_ThemeDay);
                else
                    setTheme(ParamTCH_ThemeNight);
            }
        }
        else
        {
            setTheme(ParamTCH_ThemeDay);
        }
    }
}

void TouchDisplayModule::setTheme(uint8_t theme)
{
    lv_disp_t *display = lv_disp_get_default();
    // <Enumeration Text="Light" Value="0" Id="%ENID%" />
    // <Enumeration Text="Dark" Value="1" Id="%ENID%" />
    switch (theme)
    {
    case 0:
        _theme = theme;
        lv_theme_default_init(display, lv_palette_main(LV_PALETTE_GREY), lv_palette_main(LV_PALETTE_YELLOW), 0, LV_FONT_DEFAULT);
        break;
    case 1:
        _theme = theme;
        lv_theme_default_init(display, lv_palette_main(LV_PALETTE_GREY), lv_palette_main(LV_PALETTE_YELLOW), 1, LV_FONT_DEFAULT);
        break;
    }
}

void TouchDisplayModule::lv_log(
#if LVGL_VERSION_MAJOR >= 9
    lv_log_level_t level, 
#endif
    const char *buf)
{
    logInfo("lvgl", "%s", buf);
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
        if (_displayOffRectangle != nullptr)
            lv_obj_add_flag(_displayOffRectangle, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        logDebug("Display", "Turn display off.");
        _displayOn = false;
        if (_displayOffRectangle != nullptr)
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

void TouchDisplayModule::interruptTouchLeft()
{
    _touchLeftPressed = digitalRead(TOUCH_LEFT_PIN) == HIGH;
}

void TouchDisplayModule::interruptTouchRight()
{
    _touchRightPressed = digitalRead(TOUCH_RIGHT_PIN) == HIGH;
}

bool isTouchPressed()
{
    return openknxTouchDisplayModule.touchPressStateForLgvl;
}

unsigned long lowReads = 0;
void TouchDisplayModule::loop(bool configured)
{
    bool touchPressed = chsc6x_is_pressed();
   
    if (touchPressed != _touchPressState)
    {

        _touchPressState = touchPressed;
        if (touchPressed)
        {
            logErrorP("Touch pressed");
            if (!_displayOn)
                display(true);
            else
            {
                _pageAtPressStart = Page::currentPage();
                _touchPressedTimer = max(1L, millis());
                touchPressStateForLgvl = true;
            }
        }
        else
        {
            logErrorP("Touch released");
            touchPressStateForLgvl = false;
      
            if (_touchPressedTimer != 0)
            {
                auto page = Page::currentPage();   
                unsigned long pressedTime = millis() - _touchPressedTimer; 
                logErrorP("Short pressed %d", pressedTime);
                if (page != nullptr)
                {
                    if (page == _pageAtPressStart)
                        page->shortPressed();
                    page->resetPressed();
                }             
                _pageAtPressStart = nullptr;
                _touchPressedTimer = 0;
            }
        }
    }
    if (_touchPressedTimer != 0)
    {
        unsigned long pressedTime = millis() - _touchPressedTimer;
        if (pressedTime > 800)
        {
            _touchPressedTimer = 0;
            logErrorP("Long pressed %d", pressedTime);
            auto page = Page::currentPage();  
            if (page != nullptr)
            {
                if (page == _pageAtPressStart)
                    page->longPressed();
                page->resetPressed();
            }
            _pageAtPressStart = nullptr;
        }
    }

    lv_timer_handler(); // let the GUI do its work
    
    Page* currentPage = Page::currentPage();
    if (currentPage != nullptr && _displayOn)
        currentPage->loop();

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
            activatePage(_defaultPage, false);
        }
        if (pastMs > _pageTimeout && pastMs > _displayTimeoutMs)
        {
            _lastTimeoutReset = 0;
        }
    }

    if (_touchLeftPressed)
    {
        if (_displayOn)
            previousPage();
        else
            display(true);
      
        _touchLeftPressed = false;
    }

    if (_touchRightPressed)
    {
        if (_displayOn)
            nextPage();
        else
            display(true);
            
        _touchRightPressed = false;
    }

    if (_waitForEnablePageWhichWasRequested > 0 && millis() - _waitForEnablePageWhichWasRequested > 1000)
    {
        _waitForEnablePageWhichWasRequested = 0;
        logDebugP("Stop waiting for requested page because of timeout");
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
            openknxTouchDisplayModule.activatePage(page);
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
    if (cmd == "t0")
    {
        openknxTouchDisplayModule.setTheme(0);
        return true;
    }
    if (cmd == "t1")
    {
        openknxTouchDisplayModule.setTheme(1);
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
    openknx.console.printHelpLine("t0", "Set theme to light");
    openknx.console.printHelpLine("t1", "Set theme to dark");
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