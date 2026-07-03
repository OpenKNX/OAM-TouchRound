#pragma once

#include <functional>

#include "Screens/IButtonMessageScreen.h"
#include "ScreenWithLabel.h"

class ButtonMessageScreen : public ScreenWithLabel
                         , public IButtonMessageScreen
{
private:
    lv_obj_t* _message;
    lv_obj_t* _button;
    lv_obj_t* _buttonText;
    lv_obj_t* _led1;
    lv_obj_t* _led2;
    lv_obj_t* _led3;
    std::function<void()> _onPrimaryAction;

    static void OnPrimaryAction(lv_event_t* e);
    lv_obj_t* ledObject(uint8_t index);

public:
    ButtonMessageScreen();

    virtual void SetLabelText(const char* text) override;
    virtual void SetMessageText(const char* text) override;
    virtual void SetButtonText(const char* text) override;
    virtual void SetPrimaryActionChecked(bool checked) override;
    virtual void RegisterPrimaryAction(std::function<void()> callback) override;
    virtual void ConnectLed(uint8_t index, DisplayLed* led) override;
    virtual void Show() override;
};
