#pragma once
#include "OpenKNX.h"

class Cell;

class Page
{
    static Page* _currentPage;

    std::string _name;
protected:
    virtual const std::string logPrefix();
    virtual const char* pageType() = 0;
    uint8_t _channelIndex; // page channel index
    void errorInSetup(const char* message);
 
public:
    static void showPage(Page* page);
    static Page* currentPage();
    virtual ~Page();
    virtual void setup() = 0;
    virtual void loop() {}
    virtual std::string name() = 0;
    virtual std::string image() = 0;
    void init(uint8_t channelIndex);
 
   
    static Page* createPage(uint8_t channelIndex);
    static Page* createDetailDevicePage(uint8_t channelIndex);
    static Page* createErrorPage(const char* message, uint8_t channelIndex);
    static Page* createProgButtonPage();
    static Page* createDeactivatedPage(uint8_t channelIndex);
};


