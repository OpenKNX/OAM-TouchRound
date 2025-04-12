#include "DateTimeCell.h"
#include "CellParameterDefines.h"
#include "../Screens/CellScreen.h"
#include "../ImageLoader.h"

const char* DateTimeCell::cellType()
{
    return "DateTime";
}

DateTimeCell::DateTimeCell(bool showDate, bool showTime)
{
    _showDate = showDate;
    _showTime = showTime;
}

void DateTimeCell::setup()
{
    CellObject& cellObject = *_cellObject;
    if (_showDate && _showTime)
    {
        ImageLoader::loadImage(cellObject.image, "DateTime.png");
    }
    else if (_showDate)
    {
        ImageLoader::loadImage(cellObject.image, "Date.png");
    }
    else if (_showTime)
    {
        ImageLoader::loadImage(cellObject.image, "Time.png");
    }
    lv_label_set_text(cellObject.value, "");
    updateTime(true);
}

void DateTimeCell::loop(bool configured)
{
    if (configured)
        updateTime(false);
}

void DateTimeCell::updateTime(bool forceUpdate)
{
    CellObject& cellObject = *_cellObject;

    bool timeValid = openknx.time.isValid();
    if (timeValid != _lastValid || forceUpdate)
    {
        _lastValid = timeValid;
        forceUpdate = true;
        ImageLoader::colorState(cellObject.image, true, timeValid);
    }
    if (timeValid)
    {
        auto localTime = openknx.time.getLocalTime();
        if (forceUpdate || (
            _lastYear != localTime.year ||
            _lastMonth != localTime.month ||
            _lastHour != localTime.hour ||
            _lastMinute != localTime.minute
        ))
        {
            _lastYear = localTime.year;
            _lastMonth = localTime.month;
            _lastHour = localTime.hour;
            _lastMinute = localTime.minute;    
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
                sprintf(buffer, "%02d:%02d", (int) localTime.hour, (int)localTime.minute/*, (int)localTime.second*/);
            }
            lv_label_set_text(cellObject.label, buffer);
        }
    }
    else
    {
        if (forceUpdate)
        {
            if (_showTime && _showDate)
            {
                lv_label_set_text(cellObject.label, "??.??.???? ??:??:??");
            }
            else if (_showDate)
            {
                lv_label_set_text(cellObject.label, "??.??.????");
            }
            else if (_showTime)
            {
                lv_label_set_text(cellObject.label, "??:??:??");
            }
        }
    }

}