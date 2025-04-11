#pragma once
#include "Page.h"

class DateTimePage : public Page
{
    bool _lastValid = false;   
    uint8_t _lastYear = 0;
    uint8_t _lastMonth = 0;
    uint8_t _lastHour = 0;
    uint8_t _lastMinute = 0;

protected:
    virtual const char* pageType() override;
    virtual void setup() override;
    virtual void loop(bool configured) override;
    void updateTime(bool forceUpdate);
    const char* dayOfWeekString(uint8_t dayOfWeek);
    virtual std::string name() override;
    virtual std::string image() override;
};