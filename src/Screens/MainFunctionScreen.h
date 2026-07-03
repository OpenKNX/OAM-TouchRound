#pragma once

#include "Screens/IMainFunctionScreen.h"
#include "ScreenWithLabel.h"
#include <functional>

class MainFunctionScreen: public ScreenWithLabel
                         , public IMainFunctionScreen
{
private:
    lv_obj_t* _image;
    lv_obj_t* _value;
    std::function<void()> _onScreenPressed;

    static void OnScreenPressed(lv_event_t* e);

public:
    MainFunctionScreen();

    virtual void SetLabelText(const char* text) override;
    virtual void SetValueText(const char* text) override;
    virtual void SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active) override;
    virtual void RegisterScreenPressed(std::function<void()> callback) override;
    virtual void Show() override;
};
