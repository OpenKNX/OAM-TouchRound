#pragma once

#include "Screens/IAlarmScreen.h"
#include "MainFunctionScreen.h"

class AlarmScreen : public MainFunctionScreen
                 , public IAlarmScreen
{
    bool _alarm;
    bool _useRedBackground = false;
protected:
    virtual bool useCustomBackgroundColor() override;
    virtual lv_color_t customBackgroundColor() override;
public:
    AlarmScreen();
    virtual void SetLabelText(const char* text) override { MainFunctionScreen::SetLabelText(text); }
    virtual void SetValueText(const char* text) override { MainFunctionScreen::SetValueText(text); }
    virtual void SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active) override { MainFunctionScreen::SetMainIndicatorImage(imageFile, allowRecolor, active); }
    virtual void RegisterScreenPressed(std::function<void()> callback) override { MainFunctionScreen::RegisterScreenPressed(callback); }
    virtual void Show() override { MainFunctionScreen::Show(); }
    virtual void setAlarm(bool alarm) override;
    virtual void setUseRedBackgroundForAlarm(bool useRedBackground) override;
};

