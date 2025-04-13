#pragma once
#include "OpenKNX.h"

class Cell;

class Page
{
    static Page* _currentPage;
    static Page* _pageToSet;

    std::string _name;
protected:
    virtual const std::string logPrefix();
    virtual const char* pageType() = 0;
    uint8_t _channelIndex; // page channel index
    void errorInSetup(const char* label, const char* message);
    virtual void loop(bool configured) {}
  
public:
    static void showPage(Page* page);
    static Page* currentPage();
    static void handleLoop(bool configured);
    virtual ~Page();
    virtual void setup() = 0;
    virtual void resetPressed() {}
    virtual void longPressed() {}
    virtual void shortPressed() {}
    virtual std::string name() = 0;
    virtual std::string image() = 0;
    void init(uint8_t channelIndex);
 
   
    static Page* createPage(uint8_t channelIndex);
    static Page* createDetailDevicePage(uint8_t channelIndex, uint8_t deviceIndex);
    static Page* createErrorPage(const char* message, uint8_t channelIndex);
    static Page* createProgButtonPage();
    static Page* createDeactivatedPage(uint8_t channelIndex);

};


