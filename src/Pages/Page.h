#pragma once
#include "OpenKNX.h"
#include "ui.h"

class Cell;

class Page
{
    std::string _name;
 protected:
    virtual const std::string logPrefix();
    virtual const char* pageType() = 0;
    uint8_t _channelIndex; // page channel index
    virtual void setup() = 0;
    void errorInSetup(const char* message);

public:
    virtual ~Page();
    void init(uint8_t channelIndex);
    virtual void loop() {}

   
    static Page* createPage(uint8_t channelIndex);
    static Page* createErrorPage(const char* message, uint8_t channelIndex);
};


