#pragma once
#include "OpenKNX.h"
#include <ui.h>

class Cell
{
    std::string _name;
protected:
    uint8_t _top = 0;
    uint8_t _left = 0;
    uint8_t _width = 0;
    uint8_t _height = 0;
    uint8_t _cellIndex = 0;
    uint8_t _channelIndex = 0;
 
    virtual const std::string logPrefix();
    virtual const char* cellType() = 0;

public:
    void init(uint8_t channelIndex, uint8_t cellIndex, uint8_t top, uint8_t left, uint8_t width, uint8_t height);
    virtual ~Cell() {};
    virtual void setupCell() {};

    static Cell* createCell(uint8_t channelIndex, uint8_t cellIndex, uint8_t top, uint8_t left, uint8_t width, uint8_t height);
};

