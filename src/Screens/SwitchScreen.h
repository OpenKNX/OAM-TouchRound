#pragma once

#include <functional>
#include "Screens/ISwitchScreen.h"
#include "ScreenWithLabel.h"

class SwitchScreen: public ScreenWithLabel
                  , public ISwitchScreen
{
private:
    lv_obj_t* _value;
    lv_obj_t* _image;
    std::function<void()> _onPrimaryAction;

    static void OnPrimaryAction(lv_event_t* e);

public:
    SwitchScreen();

    virtual void SetLabelText(const char* text) override;
    virtual void SetValueText(const char* text) override;
    virtual void SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active) override;
    virtual void RegisterPrimaryAction(std::function<void()> callback) override;
    virtual void Show() override;
};
