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
    if (_currentPage != nullptr)
    {
        logDebug("Page", "Delete Page");
        delete _currentPage;
    }
    _currentPage = page;
    logDebug("Page", "Show Page");
    _currentPage->setup();
}

void Page::errorInSetup(const char* message)
{
    MessageScreen& screen = *MessageScreen::instance;
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
    uint8_t _channelIndex = channelIndex; // Used in parameter macros
    Page* result = nullptr;
    if (channelIndex >= ParamTCH_VisibleChannels)
    {
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
        switch (ParamTCH_ChannelPageType)
        {
        case 0:
            result = new DeactivatedPage();
            break;
        case 1:
            if (ParamTCH_ChannelDevicePageType == 0)
                result = new MainFunctionPage();
            else
                result = new DetailDevicePage();
            break;
        case 2: 
            result = new CellPage();
            break;
        case 3:
            result = new DateTimePage();
            break;
        case 4:
            result = new ProgButtonPage();
            break;
        default:
            auto errorPage = new ErrorPage();
            errorPage->setMessage("Unbekannte Seitentype");
            result = errorPage;
            break;
        }
    }
    result->init(channelIndex);
    return result;
}

Page* Page::createDetailDevicePage(uint8_t channelIndex)
{
    auto page = new DetailDevicePage();
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
