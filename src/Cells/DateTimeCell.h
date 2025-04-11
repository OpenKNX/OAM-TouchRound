#pragma once
#include "Cell.h"

class DateTimeCell : public Cell
{
    private:
        bool _showDate = false;
        bool _showTime = false;
        bool _lastValid = false;   
        uint16_t _lastYear = 0;
        uint8_t _lastMonth = 0;
        uint8_t _lastHour = 0;
        uint8_t _lastMinute = 0;
    public:
        DateTimeCell(bool showDate, bool showTime);
    protected:
        virtual const char* cellType() override;
        virtual void setup() override;
        virtual void loop(bool configured) override;
        void updateTime(bool forceUpdate);
};