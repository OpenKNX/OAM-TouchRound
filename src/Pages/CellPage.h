#pragma once
#include "Page.h"
class Cell;
class Screen;

class CellPage : public Page
{
protected:
    uint8_t _numberOfCells;
    Screen* _screen;
    virtual const char* pageType() override; 
    virtual void setup() override;
public:
    virtual ~CellPage();
};

