#pragma once
#include "Cell.h"

class DateTimeCell : public Cell
{
    private:
        bool _showDate = false;
        bool _showTime = false;
        bool _lastValid = false;   
        time_t _lastTime;
    public:
        DateTimeCell(bool showDate, bool showTime);
    protected:
        virtual const char* cellType() override;
        virtual void setup() override;
        virtual void loop(bool configured) override;
        void updateTime(bool forceUpdate);
};