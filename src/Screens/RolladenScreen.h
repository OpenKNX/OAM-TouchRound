#pragma once

#include <functional>

#include "Screens/IRolladenScreen.h"
#include "ScreenWithLabel.h"

class RolladenScreen: public ScreenWithLabel
                    , public IRolladenScreen
{
private:
    lv_obj_t* _image;
    lv_obj_t* _value;
    lv_obj_t* _buttonPrimary;
    lv_obj_t* _buttonSecondary;
    lv_obj_t* _percentageInput;
    std::function<void()> _onPrimaryAction;
    std::function<void()> _onSecondaryAction;
    std::function<void()> _onMainAction;
    std::function<void(uint8_t)> _onPercentageChangeCompleted;

    static void OnPrimaryAction(lv_event_t* e);
    static void OnSecondaryAction(lv_event_t* e);
    static void OnMainAction(lv_event_t* e);
    static void OnPercentageChangeCompleted(lv_event_t* e);

public:
    RolladenScreen();

    virtual void SetLabelText(const char* text) override;
    virtual void SetValueText(const char* text) override;
    virtual void SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active) override;
    virtual void SetPercentageValue(uint8_t value) override;
    virtual uint8_t GetPercentageValue() const override;
    virtual void SetDirectionalActionState(bool primaryActive, bool secondaryActive) override;
    virtual void RegisterPrimaryAction(std::function<void()> callback) override;
    virtual void RegisterSecondaryAction(std::function<void()> callback) override;
    virtual void RegisterMainAction(std::function<void()> callback) override;
    virtual void RegisterPercentageChangeCompleted(std::function<void(uint8_t)> callback) override;
    virtual void Show() override;
};
