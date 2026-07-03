#include "AlarmScreen.h"

IAlarmScreen* IAlarmScreen::instance = nullptr;

AlarmScreen::AlarmScreen()
 : MainFunctionScreen()
{
}

bool AlarmScreen::useCustomBackgroundColor()
{
    if (_alarm)
        return true;
    return MainFunctionScreen::useCustomBackgroundColor();
}   

lv_color_t AlarmScreen::customBackgroundColor()
{
    if (_alarm && _useRedBackground)
        return lv_color_make(255, 0, 0);
    return MainFunctionScreen::customBackgroundColor();
}

void AlarmScreen::setAlarm(bool alarm)
{
    if (_alarm != alarm)
    {
        _alarm = alarm;
        updateBackgroundColor();
    }
}

void AlarmScreen::setUseRedBackgroundForAlarm(bool useRedBackground)
{
    if (_useRedBackground != useRedBackground)
    {
        _useRedBackground = useRedBackground;
        updateBackgroundColor();
    }
}