#pragma once

#include <functional>

#include "Screens/IFanScreen.h"
#include "ScreenWithLabel.h"

class FanScreen: public ScreenWithLabel
               , public IFanScreen
{
private:
    lv_obj_t* _buttonAuto;
    lv_obj_t* _buttonAutoLabel;
    lv_obj_t* _image;
    lv_obj_t* _value;
    std::function<void()> _onAutomaticAction;
    std::function<void()> _onMainAction;

    static void OnAutomaticAction(lv_event_t* e);
    static void OnMainAction(lv_event_t* e);

public:
    FanScreen();

    virtual void SetLabelText(const char* text) override;
    virtual void SetValueText(const char* text) override;
    virtual void SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active) override;
    virtual void SetAutomaticVisible(bool visible) override;
    virtual void SetAutomaticState(bool automatic) override;
    virtual void RegisterAutomaticAction(std::function<void()> callback) override;
    virtual void RegisterMainAction(std::function<void()> callback) override;
    virtual void Show() override;
};
