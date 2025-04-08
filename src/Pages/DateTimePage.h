#pragma once
#include "Page.h"

class DateTimePage : public Page
{
    bool _lastValid = false;   
    time_t _lastTime;

protected:
    virtual const char* pageType() override;
    virtual void setup() override;
    virtual void loop(bool configured) override;
    void updateTime(bool forceUpdate);
    const char* dayOfWeekString(uint8_t dayOfWeek);
    virtual std::string name() override;
    virtual std::string image() override;
};