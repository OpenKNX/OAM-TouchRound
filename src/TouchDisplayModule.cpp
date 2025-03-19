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
            _defaultPage = KoTCH_DefaultPage.value(DPT_SceneNumber);
        else
            KoTCH_DefaultPage.requestObjectRead();
    }
    if (ParamTCH_DayNightObject > 0 && !KoTCH_DayNight.initialized())
        KoTCH_DayNight.requestObjectRead();
    if (ParamTCH_ChannelAvailable > 0 && !KoTCH_CHPageEnabled.initialized())
        KoTCH_CHPageEnabled.requestObjectRead();
    logDebugP("Default Page: %d", _defaultPage);
    activatePage(_defaultPage);
}

void TouchDisplayModule::processInputKo(GroupObject &ko)
{
    switch (ko.asap())
    {
    case TCH_KoPage:
    {
        activatePage(ko.value(DPT_SceneNumber));
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
    }
    switch (TCH_KoCalcIndex(ko.asap()))
    {
        case TCH_KoCHPageEnabled:
        {
            if (pageActivated())
            {
                activatePage(_channelIndex + 1);
            }
            else
            {
                nextPage();
            }
        }
        break;
    }
}

void TouchDisplayModule::activatePage(uint8_t page, bool displayOn)
{
    if (displayOn)
        display(true);

    _lastTimeoutReset = millis();
    auto current = _channelIndex;
    _channelIndex = page - 1;
    bool activated = pageActivated();
    if (current == _channelIndex && _currentPageActivated == activated && _currentPage != nullptr && !_detailDevicePageActive)
    {
        logDebugP("Page: %d already activ", page);
        return;
    }
    logDebugP("Active Page: %d", page);
    _currentPageActivated = activated;
    _detailDevicePageActive = false;
    logDebugP("Set KO: %d", _channelIndex);
    KoTCH_CurrentPage.value(_channelIndex, DPT_SceneNumber);
    if (_currentPage != nullptr)
    {
        logDebugP("Delete Page: %d", page);
        delete _currentPage;
    }
    if (activated)
    {
        logDebugP("Create Page: %d", page);
        _currentPage = Page::createPage(_channelIndex);
    }
    else
    {  
         logDebugP("Deativated Page: %d", page);
        _currentPage = Page::createDeactivatedPage(_channelIndex);
    }
}

void TouchDisplayModule::showDetailDevicePage()
{
    logDebugP("Show Detail Device Page %d", _channelIndex + 1);
    _detailDevicePageActive = true;
    if (_currentPage != nullptr)
        delete _currentPage;
    _currentPage = Page::createDetailDevicePage(_channelIndex);
}

void TouchDisplayModule::showProgButtonPage()
{
    display(true);
    _lastTimeoutReset = 0;
    if (_currentPage != nullptr)
        delete _currentPage;
    _currentPage = Page::createProgButtonPage();
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
    _detailDevicePageActive = false;
    uint8_t currentChannel = _channelIndex;
    uint8_t newPage = _channelIndex + 1;
    while (currentChannel != ++_channelIndex)
    {
        if (_channelIndex >= ParamTCH_VisibleChannels)
            _channelIndex = 0;

        if (ParamTCH_ChannelNavigation && pageActivated())
        {
            newPage = _channelIndex + 1;
            break;
        }
    }
    _channelIndex = currentChannel; // restore current channel
    activatePage(newPage);
}

bool TouchDisplayModule::pageActivated()
{
    if (ParamTCH_ChannelPageType == 0)
        return false;
    //     <Enumeration Text="Immer" Value="0" Id="%ENID%" />
    //     <Enumeration Text="Über Objekt aktivierbar" Value="1" Id="%ENID%" />
    //     <Enumeration Text="Über Objekt deaktivierbar" Value="2" Id="%ENID%" />
    if (KoTCH_CHPageEnabled.initialized())
    {
        switch (ParamTCH_ChannelAvailable)
        {
        case 1:
            if (!KoTCH_CHPageEnabled.value(DPT_Switch))
                return false;
            break;
        case 2:
            if (KoTCH_CHPageEnabled.value(DPT_Switch))
                return false;
            break;
        }
    }
    return true;
}

void TouchDisplayModule::previousPage()
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
        if (ParamTCH_ChannelNavigation && pageActivated())
        {
            newPage = _channelIndex + 1;
            break;
        }
    }
    _channelIndex = currentChannel;
    activatePage(newPage);
}

void TouchDisplayModule::addGlobalEvents(lv_obj_t *sreen)
{
    lv_obj_add_event_cb(sreen, [](lv_event_t *e)
                        { ((TouchDisplayModule *)e->user_data)->touched(e); }, LV_EVENT_PRESSED, this);
    lv_obj_add_event_cb(sreen, [](lv_event_t *e)
                        { ((TouchDisplayModule *)e->user_data)->touched(e); }, LV_EVENT_LONG_PRESSED_REPEAT, this);
}

void TouchDisplayModule::setup(bool configured)
{
    if (configured)
        _lastTimeoutReset = millis();

    lv_init();
    lv_log_register_print_cb(lv_log);
    ImageLoader::connectLittleFSwithLVGL();
  
    lv_xiao_disp_init();
    lv_xiao_touch_init();

   
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

    addGlobalEvents(MainFunctionScreen::instance->screen);
    addGlobalEvents(CellScreen2::instance->screen);
    addGlobalEvents(CellScreen3::instance->screen);
    addGlobalEvents(CellScreen4::instance->screen);
    addGlobalEvents(DateTimeScreen::instance->screen);
    addGlobalEvents(SwitchScreen::instance->screen);
    addGlobalEvents(DimmerScreen::instance->screen);
    addGlobalEvents(MessageScreen::instance->screen);
    addGlobalEvents(ButtonMessageScreen::instance->screen);

    if (configured)
    {
        auto gestureLayer = lv_obj_create(lv_layer_top());
        const int gestureLayerHeight = 50;
        lv_obj_clear_flag(gestureLayer, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_y(gestureLayer, LV_VER_RES - gestureLayerHeight);
        lv_obj_set_size(gestureLayer, LV_HOR_RES, gestureLayerHeight);
        lv_obj_set_style_border_width(gestureLayer, 0, 0);
        lv_obj_set_style_opa(gestureLayer, LV_OPA_0, 0);
        lv_obj_set_style_bg_color(gestureLayer, lv_color_make(0, 255, 0), 0);
        lv_obj_clear_flag(gestureLayer, LV_OBJ_FLAG_GESTURE_BUBBLE);
        lv_obj_add_event_cb(gestureLayer, [](lv_event_t *e)
                            { ((TouchDisplayModule *)e->user_data)->handleGesture(e); }, LV_EVENT_GESTURE, this);
    }
    _displayOffRectangle = lv_obj_create(lv_layer_top());
    lv_obj_set_size(_displayOffRectangle, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_bg_color(_displayOffRectangle, lv_color_black(), 0);
    lv_obj_set_style_border_width(_displayOffRectangle, 0, 0);
    lv_obj_add_flag(_displayOffRectangle, LV_OBJ_FLAG_HIDDEN);
    addGlobalEvents(_displayOffRectangle);
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
            activatePage(_defaultPage, false);
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