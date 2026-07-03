#pragma once

#include <functional>

#include "Screens/IDateTimeScreen.h"
#include "ScreenWithLabel.h"

class DateTimeScreen: public Screen
                   , public IDateTimeScreen
{
private:
    lv_obj_t* _weekday;
    lv_obj_t* _date;
    lv_obj_t* _time;
    lv_obj_t* _message;
    std::function<void()> _onScreenPressed;

    static void OnScreenPressed(lv_event_t* e);

public:
    DateTimeScreen();

    virtual void SetWeekdayText(const char* text) override;
    virtual void SetDateText(const char* text) override;
    virtual void SetTimeText(const char* text) override;
    virtual void SetMessageText(const char* text) override;
    virtual void RegisterScreenPressed(std::function<void()> callback) override;
    virtual void Show() override;
};
