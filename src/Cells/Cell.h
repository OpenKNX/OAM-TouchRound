#pragma once
#include "OpenKNX.h"
#include "lvgl.h"

class CellObject;

class Cell
{
    std::string _name;
protected:
    uint8_t _cellIndex = 0;
    uint8_t _channelIndex = 0;
    CellObject* _cellObject = nullptr;
 
    virtual const std::string logPrefix();
    virtual const char* cellType() = 0;
 
public:
    void init(uint8_t channelIndex, uint8_t cellIndex, CellObject& cellObject);
    virtual ~Cell() {};
    virtual void setup() {};
    virtual void loop() {};

    static Cell* createCell(uint8_t channelIndex, uint8_t cellIndex, CellObject& cellObject);
    virtual void resetPressed() {};
    virtual void shortPressed() {};
    virtual void longPressed() {};
};

