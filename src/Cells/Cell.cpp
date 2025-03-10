#include "OpenKNX.h"
#include "Cell.h"
#include "CellParameterDefines.h"
#include "JumpCell.h"
#include "DateTimeCell.h"
#include "DeactivatedCell.h"
#include "DeviceMainFunctionCell.h"
   
const std::string Cell::logPrefix()
{
    return _name;
}

void Cell::init(uint8_t channelIndex, uint8_t cellIndex, uint8_t top, uint8_t left, uint8_t width, uint8_t height)
{
    _name = cellType();
    _name += "Cell";
    _name += std::to_string(channelIndex + 1);
    _name += "/";
    _name += std::to_string(cellIndex + 1);
    _channelIndex = channelIndex;
    _cellIndex = cellIndex;
    _top = top;
    _left = left;
    _width = width;
    _height = height;
}
   


Cell* Cell::createCell(uint8_t channelIndex, uint8_t cellIndex, uint8_t top, uint8_t left, uint8_t width, uint8_t height)
{
    uint8_t _channelIndex = channelIndex; // Used in parameter macros
    uint8_t _cellIndex = cellIndex; // Used in parameter macros
    Cell* result = nullptr;

    switch(ParamTCH_ChannelDeviceSelection1)   
    {

        case 0: // Jump cell
            result = new JumpCell();
            break;
        case 255:
            result = new DateTimeCell();
            break;
        case 254:
            result = new DeactivatedCell();
            break;
        default:
            uint8_t deviceIndex = ParamTCH_ChannelDeviceSelection1 - 1;
            auto deviceCell = new DeviceMainFunctionCell();
            deviceCell->init(deviceIndex);
            result = deviceCell;   
            break;

    }
    result->init(channelIndex, cellIndex, top, left, width, height);
    return result;
}