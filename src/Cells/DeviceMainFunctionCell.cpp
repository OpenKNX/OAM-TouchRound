#include "DeviceMainFunctionCell.h"

const char* DeviceMainFunctionCell::cellType()
{
    return "DeviceMainFunction";
}

void DeviceMainFunctionCell::init(uint8_t deviceIndex)
{
    _deviceIndex = deviceIndex;
}