#include "CellPage.h"
#include "../Cells/Cell.h"
#include "../Screens/CellScreen.h"

const char* CellPage::pageType()
{
    return "Cell";
}

void CellPage::setup()
{
    logDebugP("Init page with %d cells", (int) _numberOfCells);
     _numberOfCells = ParamTCH_ChannelNumbeOfFields;
    if (_numberOfCells == 0)
    {
        errorInSetup("Seite hat keine Felder");
        return;
    }
    if (_channelIndex >= ParamTCH_VisibleChannels)
    {
        errorInSetup("Seiteindex ist nicht verfügbar");
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