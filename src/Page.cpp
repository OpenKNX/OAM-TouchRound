#include "Page.h"
#include "Cells/Cell.h"

const std::string Page::logPrefix()
{
    return _name;
}

void Page::init(uint8_t channelIndex)
{
    _channelIndex = channelIndex;
    _name = "Page";
    _name += _channelIndex;
    if (channelIndex >= ParamTCH_VisibleChannels)
    {
        logDebugP("Page not visible: %d", (int) ParamTCH_VisibleChannels);
        return;
    }
    _numberOfCells = ParamTCH_ChannelNumFields;
    if (_numberOfCells == 0)
    {
        logDebugP("Page has no cells");
        return;
    }
    logDebugP("Init page with %d cells", (int) _numberOfCells);
    _cells = new Cell*[_numberOfCells];    
    for (size_t cellIndex = 0; cellIndex < _numberOfCells; cellIndex++)
    {
        _cells[cellIndex] = Cell::createCell(_channelIndex, cellIndex, 0, 0, 0, 0);
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
