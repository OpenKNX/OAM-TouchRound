#include "CellPage.h"
#include "../Cells/Cell.h"

const char* CellPage::pageType()
{
    return "Cell";
}

void CellPage::setup()
{
     _numberOfCells = ParamTCH_ChannelNumFields;
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
   
    // logDebugP("Init page with %d cells", (int) _numberOfCells);
    // _cells = new Cell*[_numberOfCells];    
    // for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    // {
    //     _cells[cellIndex] = Cell::createCell(_channelIndex, cellIndex, 0, 0, 0, 0);
    // }
    // for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    // {
    //     logDebugP("Setup cell");
    //     _cells[cellIndex]->setup();
    // }

    lv_label_set_text(ui_Label3, "Noch nicht implementiert");
    lv_disp_load_scr(ui_Message);
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