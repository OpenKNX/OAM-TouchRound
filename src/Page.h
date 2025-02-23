#pragma once
#include "OpenKNX.h"

class Cell;

class Page
{
    uint8_t _channelIndex; // page channel index
    uint8_t _numberOfCells;
    Cell** _cells;
public:
    virtual ~Page();
    void init(uint8_t channelIndex);
};


