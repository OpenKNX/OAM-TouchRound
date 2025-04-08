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
        if (timeValid)
        {
            lv_obj_set_style_img_recolor_opa(cellObject.image, 255, 0);
            lv_obj_set_style_img_recolor(cellObject.image, lv_color_make(255,255,0), 0);
        }
        else
        {
            lv_obj_set_style_img_recolor_opa(cellObject.image, 0, 0);
            lv_obj_set_style_img_recolor(cellObject.image, lv_color_make(128,128,128), 0);
        }
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