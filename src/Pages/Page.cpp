#include "Page.h"
#include "CellPage.h"
#include "DetailDevicePage.h"
#include "DeactivatedPage.h"
#include "DateTimePage.h"
#include "ErrorPage.h"
#include "MainFunctionPage.h"
#include "ProgButtonPage.h"
#include "../TouchDisplayModule.h"
#include "../Screens/MessageScreen.h"

Page* Page::_currentPage = nullptr;
Page* Page::_pageToSet = nullptr;

const std::string Page::logPrefix()
{
    return _name;
}

Page* Page::currentPage()
{
    return _currentPage;
}

void Page::showPage(Page* page)
{
    if (openknxTouchDisplayModule.touchPressStateForLgvl)
    {
        // Remove click state before change page
        openknxTouchDisplayModule.touchPressStateForLgvl = false;
        openknxTouchDisplayModule.loop(knx.configured());
    }
    if (_pageToSet != nullptr)
    {
        logError("Page", "Page set multiple times");
        delete _pageToSet;
    }
    logError("Page", "New page to show");
    _pageToSet = page; 
}
void Page::handleLoop(bool configured)
{
    if (_pageToSet != nullptr)
    {
        if (_currentPage != nullptr)
        {
            logDebug("Page", "Delete Page");
            delete _currentPage;
        }
        _currentPage = _pageToSet;
        _pageToSet = nullptr;
        logDebug("Page", "Setup Page %s", _currentPage->name().c_str());
        _currentPage->setup();
        logError("Page", "After Setup Page");
    }
    if (_currentPage != nullptr && openknxTouchDisplayModule.isDisplayOn())
    {
        _currentPage->loop(configured);
    }
}

void Page::errorInSetup(const char* label,  const char* message)
{
    MessageScreen& screen = *MessageScreen::instance;
    lv_label_set_text(screen.label, label);
    lv_label_set_text(screen.message, message);
    lv_disp_load_scr(screen.screen);
}

Page* Page::createErrorPage(const char* message, uint8_t channelIndex)
{
    ErrorPage* result = new ErrorPage();
    result->setMessage(message);
    result->init(channelIndex);
    return result;
}

Page* Page::createProgButtonPage()
{
    auto result = new ProgButtonPage();
    result->init(0);
    return result;
}
Page* Page::createDeactivatedPage(uint8_t channelIndex)
{
    DeactivatedPage* result = new DeactivatedPage();
    result->init(channelIndex);
    return result;
}


Page* Page::createPage(uint8_t channelIndex)
{
    logDebug("Page", "Create Page %d", channelIndex + 1);
    uint8_t _channelIndex = channelIndex; // Used in parameter macros
    Page* result = nullptr;
    if (channelIndex >= ParamTCH_VisibleChannels)
    {
        logDebug("Page", "Create ErrorPage");
    
        auto errorPage = new ErrorPage();
        std::string message = "Unbekannte Seite ";
        message += std::to_string(channelIndex + 1);
        errorPage->setMessage(message.c_str());
        result = errorPage;
    }
    else
    {
        // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
        // <Enumeration Text="Gerät" Value="1" Id="%ENID%" />
        // <Enumeration Text="Mehrere Felder" Value="2" Id="%ENID%" />
        // <Enumeration Text="Zeit / Datum" Value="3" Id="%ENID%" />
        // <Enumeration Text="System" Value="4" Id="%ENID%" />
        switch (ParamTCH_CHPageType)
        {
        case 0:
            logDebug("Page", "Create DeactivatedPage");
            result = new DeactivatedPage();
            break;
        case 1:
            if (ParamTCH_CHDevicePageType == 0)
            {
                logDebug("Page", "Create MainFunctionPage");
                result = new MainFunctionPage();
            }
            else
            {
                logDebug("Page", "Create DetailDevicePage");
                result = new DetailDevicePage();
            }
            break;
        case 2: 
            logDebug("Page", "Create CellPage");
            result = new CellPage();
            break;
        case 3:
            logDebug("Page", "Create DateTimePage");
            result = new DateTimePage();
            break;
        case 4:
            logDebug("Page", "Create ProgButtonPage");
            result = new ProgButtonPage();
            break;
        default:
            logDebug("Page", "Create ErrorPage");
            auto errorPage = new ErrorPage();
            errorPage->setMessage("Unbekannte Seitentype");
            result = errorPage;
            break;
        }
    }
    result->init(channelIndex);
    return result;
}

Page* Page::createDetailDevicePage(uint8_t channelIndex, uint8_t deviceIndex)
{
    auto page = new DetailDevicePage();
    page->setDevice(deviceIndex);
    page->init(channelIndex);
    return page;
}

void Page::init(uint8_t channelIndex)
{
    _channelIndex = channelIndex;
    auto page = channelIndex + 1;
    _name = pageType();
    _name += "Page";
    _name += std::to_string(page);
}


Page::~Page()
{
}
