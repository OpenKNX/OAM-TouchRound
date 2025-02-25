#pragma once
#include "OpenKNX.h"
#include "DeviceCell.h"


class DeviceMainFunctionCell : public DeviceCell
{
protected:
    virtual const char* cellType() override;

};
