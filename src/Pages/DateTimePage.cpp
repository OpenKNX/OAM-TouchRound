#include "DateTimePage.h"

const char* DateTimePage::pageType()
{
    return "DateTime";
}

void DateTimePage::setup()
{
    updateTimeMessage(true);
    lv_disp_load_scr(ui_Message);
}

void DateTimePage::updateTimeMessage(bool force)
{
    bool timeValid = openknx.time.isValid();
    if (timeValid != _lastValid)
    {
        _lastValid = timeValid;
        force = true;
    }
    if (timeValid)
    {
        auto localTime = openknx.time.getLocalTime();
        auto time = localTime.toTime_t();
        if (time != _lastTime || force)
        {
            char buffer[50];
            sprintf(buffer, "%s\n%02d.%02d.%04d\n\n%02d:%02d:%02d", dayOfWeekString(localTime.dayOfWeek), (int)localTime.day, (int)localTime.month, (int)localTime.year, (int) localTime.hour, (int)localTime.minute, (int)localTime.second);
            lv_label_set_text(ui_Label3, buffer);
        }
    }
    else
    {
        if (force)
            lv_label_set_text(ui_Label3, "Zeit nicht vorhande.\nBitte prüfen ob Uhrzeit/Datum\nin der ETS korrekt verbunden ist");
    }
}

const char* DateTimePage::dayOfWeekString(uint8_t dayOfWeek) 
{
    switch (dayOfWeek)
    {
    case 0:
        return "Sonntag";
    case 1:
        return "Montag";
    case 2:
        return "Dienstag";
    case 3:
        return "Mittwoch";
    case 4:
        return "Donnerstag";
    case 5:
        return "Freitag";
    case 6:
        return "Samstag";
    default:
        return "";
    }
}


void DateTimePage::loop()
{
   updateTimeMessage(false);
}