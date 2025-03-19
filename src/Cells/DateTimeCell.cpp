#include "DateTimeCell.h"
#include "CellParameterDefines.h"
#include "../Screens/CellScreen.h"

const char* DateTimeCell::cellType()
{
    return "DateTime";
}

DateTimeCell::DateTimeCell(bool showDate, bool showTime)
{
    _showDate = showDate;
    _showTime = showTime;
}

void DateTimeCell::setup ()
{
    CellObject& cellObject = *_cellObject;
    lv_img_set_src(cellObject.image, nullptr);
    updateTime(true);
}

void DateTimeCell::loop()
{
    updateTime(false);
}

void DateTimeCell::updateTime(bool forceUpdate)
{
    CellObject& cellObject = *_cellObject;

    bool timeValid = openknx.time.isValid();
    if (timeValid != _lastValid)
    {
        _lastValid = timeValid;
        forceUpdate = true;
    }
    if (timeValid)
    {
        auto localTime = openknx.time.getLocalTime();
        auto time = localTime.toTime_t();
        if (time != _lastTime || forceUpdate)
        {
            char buffer[50] = {0};
            if (_showTime && _showDate)
            {
                sprintf(buffer, "%02d.%02d.%04d %02d:%02d:%02d", (int)localTime.day, (int)localTime.month, (int)localTime.year, (int)localTime.hour, (int)localTime.minute, (int)localTime.second);
            }
            else if (_showDate)
            {
                sprintf(buffer, "%02d.%02d.%04d", (int)localTime.day, (int)localTime.month, (int)localTime.year);
            }
            else if (_showTime)
            {
                sprintf(buffer, "%02d:%02d:%02d", (int) localTime.hour, (int)localTime.minute, (int)localTime.second);
            }
            lv_label_set_text(cellObject.label, buffer);
        }
    }
    else
    {
        if (forceUpdate)
        {
          lv_label_set_text(cellObject.label, "--");
        }
    }

}