#include "Page.h"
#include "CellPage.h"
#include "DetailDevicePage.h"
#include "DeactivatedPage.h"
#include "DateTimePage.h"
#include "ErrorPage.h"
#include "../TouchDisplayModule.h"

const std::string Page::logPrefix()
{
    return _name;
}

void Page::errorInSetup(const char* message)
{
    lv_label_set_text(ui_MessageLabel, message);
    lv_disp_load_scr(ui_Message);
}

Page* Page::createErrorPage(const char* message, uint8_t channelIndex)
{
    ErrorPage* result = new ErrorPage();
    result->setMessage(message);
    result->init(channelIndex);
    return result;
}


Page* Page::createPage(uint8_t channelIndex)
{
    uint8_t _channelIndex = channelIndex; // Used in parameter macros
    Page* result = nullptr;
    // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
    // <Enumeration Text="Gerät" Value="1" Id="%ENID%" />
    // <Enumeration Text="Mehrere Felder" Value="2" Id="%ENID%" />
    // <Enumeration Text="Zeit / Datum" Value="3" Id="%ENID%" />
    switch (ParamTCH_ChannelPageType)
    {
    case 0:
        result = new DeactivatedPage();
        break;
    case 1:
        result = new DetailDevicePage();
        break;
    case 2: 
        result = new CellPage();
        break;
    case 3:
        result = new DateTimePage();
        break;
    default:
        auto errorPage = new ErrorPage();
        errorPage->setMessage("Unbekannte Seitentype");
        result = errorPage;
        break;

    }
    result->init(channelIndex);
    return result;
}

void Page::init(uint8_t channelIndex)
{
    _channelIndex = channelIndex;
    auto page = channelIndex + 1;
    _name = pageType();
    _name += "Page";
    _name += std::to_string(page);
    logInfoP("setup");
    setup();
}


Page::~Page()
{
}
