#include "CellPage.h"
#include "../Cells/Cell.h"
#include "../Screens/CellScreen.h"
#include "CP1252ToUTF8.h"

const char* CellPage::pageType()
{
    return "Cell";
}

void CellPage::setup()
{
    _numberOfCells = ParamTCH_CHNumbeOfFields;
    logDebugP("setup %d cells", (int) _numberOfCells);
    if (_numberOfCells == 0)
    {
        errorInSetup("Seite hat keine Felder");
        return;
    }
    switch (_numberOfCells)
    {
    case 2:
        _screen = CellScreen2::instance;
        break;
    case 3:
        _screen = CellScreen3::instance;
        break;
    case 4:
        _screen = CellScreen4::instance;
        break;
    default:
        errorInSetup("Zellenanzahl nicht unterstützt");
        break;
    }
  
    _cells = new Cell*[_numberOfCells];    
    for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    {
        logDebugP("Get cell object %d", cellIndex);
        CellObject& cellObject =  _screen->getCell(cellIndex);
        _cells[cellIndex] = Cell::createCell(_channelIndex, cellIndex, cellObject);
    }
    for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    {
        logDebugP("Setup cell");
        _cells[cellIndex]->setup();
    }
    _screen->show();

}

void CellPage::loop()
{
    Page::loop();
    if (_cells == nullptr)
        return;
    for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    {
        _cells[cellIndex]->loop();
    }
}

void CellPage::shortPressed()
{
    if (_cells == nullptr)
        return;
    for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    {
        _cells[cellIndex]->shortPressed();
    }
}

void CellPage::longPressed()
{
    if (_cells == nullptr)
        return;
    for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    {
        _cells[cellIndex]->longPressed();
    }
}


void CellPage::resetPressed()
{
    if (_cells == nullptr)
        return;
    for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    {
        _cells[cellIndex]->resetPressed();
    }
}

CellPage::~CellPage()
{
    if (_cells == nullptr)
        return;
    for (uint8_t i = 0; i < _numberOfCells; i++)
    {
        delete _cells[i];
    }
    delete[] _cells;
}

std::string CellPage::name()
{
    char* pageName1252 = (char *) ParamTCH_CHPageName;
    const char* utf8 = convert1252ToUTF8(pageName1252);
    auto result = std::string(utf8);
    if (pageName1252 != utf8)
        free((void*) utf8);
    return result;
}

std::string CellPage::image()
{
    uint8_t icon = ParamTCH_CHIconSelection;
    if (icon == 0)
    {
        // custom icon
        auto name = (const char*)ParamTCH_CHIconName;
        return std::string(name, 8) + ".png";
    }
    return std::string("Type") + std::to_string(icon) + ".png";
}