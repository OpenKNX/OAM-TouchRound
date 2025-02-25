#pragma once
#include "OpenKNX.h"

class Cell;

class Page
{
    std::string _name;
    uint8_t _channelIndex; // page channel index
    uint8_t _numberOfCells;
    Cell** _cells;
    virtual const std::string logPrefix();
public:
    virtual ~Page();
    void init(uint8_t channelIndex);
};


