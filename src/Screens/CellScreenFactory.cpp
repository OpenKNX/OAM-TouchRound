#include "CellScreenFactory.h"
#include "CellScreen.h"

ICellScreenFactory* ICellScreenFactory::instance = nullptr;

ICellScreen* CellScreenFactory::getCellScreen(uint8_t numberOfCells)
{
    switch (numberOfCells)
    {
    case 2:
        return CellScreen2::instance;
    case 3:
        return CellScreen3::instance;
    case 4:
        return CellScreen4::instance;
    default:
        return CellScreen2::instance;
    }
}