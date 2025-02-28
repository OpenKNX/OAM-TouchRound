#pragma once
#include "OpenKNX.h"
#include "Cell.h"


class DeviceMainFunctionCell : public Cell
{
    uint8_t _deviceIndex;
protected:
    virtual const char* cellType() override;
public:
    virtual void init(uint8_t deviceIndex);

};
