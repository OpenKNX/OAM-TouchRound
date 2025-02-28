#pragma once
#include "Page.h"
class Cell;

class CellPage : public Page
{
    uint8_t _numberOfCells;
    Cell** _cells;
 
protected:
    virtual const char* pageType() override; 
    virtual void setup() override;
public:
    virtual ~CellPage();
};