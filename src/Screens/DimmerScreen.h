#pragma once

#include <functional>
#include "Screens/IDimmerScreen.h"
#include "ScreenWithLabel.h"

class DimmerScreen: public ScreenWithLabel
                  , public IDimmerScreen
{
private:
    lv_obj_t* _percentageInput;
    lv_obj_t* _value;
    lv_obj_t* _primaryActionImage;
    std::function<void(uint8_t)> _onPercentageChanged;
    std::function<void(uint8_t)> _onPercentageChangeCompleted;
    std::function<void()> _onPrimaryAction;

    static void OnPercentageChanged(lv_event_t* e);
    static void OnPercentageChangeCompleted(lv_event_t* e);
    static void OnPrimaryAction(lv_event_t* e);

public:
    DimmerScreen();

    virtual void SetLabelText(const char* text) override;
    virtual void SetValueText(const char* text) override;
    virtual void SetPercentageValue(uint8_t value) override;
    virtual uint8_t GetPercentageValue() const override;
    virtual void SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active) override;
    virtual void RegisterPercentageChanged(std::function<void(uint8_t)> callback) override;
    virtual void RegisterPercentageChangeCompleted(std::function<void(uint8_t)> callback) override;
    virtual void RegisterPrimaryAction(std::function<void()> callback) override;
    virtual void Show() override;
};
