#include "Page.h"
#include "Cells/Cell.h"

const std::string Page::logPrefix()
{
    return _name;
}

void Page::init(uint8_t channelIndex)
{
    _channelIndex = channelIndex;
    auto page = channelIndex + 1;
    _name = "Page";
    _name += page;
    if (channelIndex >= ParamTCH_VisibleChannels)
    {
        logInfoP("Page not visible: %d", (int) ParamTCH_VisibleChannels);
        return;
    }
    _numberOfCells = ParamTCH_ChannelNumFields;
    if (_numberOfCells == 0)
    {
        logInfoP("Page has no cells");
        return;
    }
    logDebugP("Init page with %d cells", (int) _numberOfCells);
    _cells = new Cell*[_numberOfCells];    
    for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    {
        _cells[cellIndex] = Cell::createCell(_channelIndex, cellIndex, 0, 0, 0, 0);
    }
    for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    {
        logDebugP("Setup cell");
        _cells[cellIndex]->setupCell();
    }
}


Page::~Page()
{
    if (_cells == nullptr)
        return;
    for (uint8_t i = 0; i < _numberOfCells; i++)
    {
        delete _cells[i];
    }
    delete[] _cells;
}
