#include "Page.h"
#include "Cells/Cell.h"

void Page::init(uint8_t channelIndex)
{
    _channelIndex = channelIndex;
    if (channelIndex >= ParamTCH_VisibleChannels)
        return;

    _numberOfCells = ParamTCH_ChannelNumFields;
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
