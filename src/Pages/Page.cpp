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
    auto numberOfCells = ParamTCH_ChannelNumFields;
    if (numberOfCells == 0)
    {
        return createErrorPage("Seite hat keine Felder", channelIndex);
    }
    else if (numberOfCells == 1)
    {
        switch (ParamTCH_ChannelDeviceSelection1)
        {
        case 0: // Jump cell
            result = new CellPage();
            break;
        case 255: // Date time cell   
            result = new DateTimePage();
            break;
        case 254:
            result = new DeactivatedPage();
            break;
        default:
            result = new DetailDevicePage();
            break;
        }
    }
    else
    {
        result = new CellPage();
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
    logInfoP("setup %d", ParamTCH_ChannelDevicePageType1 );
    setup();
}


Page::~Page()
{
}
