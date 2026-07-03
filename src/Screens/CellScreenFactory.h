#pragma once
#include "Screens/ICellScreenFactory.h"

class CellScreenFactory : public ICellScreenFactory
{
public:
    virtual ICellScreen* getCellScreen(uint8_t numberOfCells) override;
};