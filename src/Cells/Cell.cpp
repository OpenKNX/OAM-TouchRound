#include "OpenKNX.h"
#include "Cell.h"
#include "CellParameterDefines.h"
#include "JumpCell.h"
#include "DateTimeCell.h"
#include "DeactivatedCell.h"
#include "DeviceCell.h"
#include "DeviceMainFunctionCell.h"
   
void Cell::init(uint8_t channelIndex, uint8_t cellIndex, uint8_t top, uint8_t left, uint8_t width, uint8_t height)
{
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
            uint8_t deviceIndex = ParamTCH_ChannelDeviceSelection1;
            if (ParamTCH_ChannelNumFields == 1)
            {
                auto deviceCell = new DeviceCell();
                deviceCell->init(deviceIndex);
                result = deviceCell;
            }
            else
            {
                auto deviceCell = new DeviceMainFunctionCell();
                deviceCell->init(deviceIndex);
                result = deviceCell;   
            }
            break;

    }
    result->init(channelIndex, cellIndex, top, left, width, height);
    return result;
}