#pragma once

#include <functional>

#include "Screens/IRGBScreen.h"
#include "ScreenWithLabel.h"

class RGBScreen : public ScreenWithLabel
                , public IRGBScreen
{
    void colorChanged(lv_event_t* e);
    void updateColor();
    void updateSlider(uint8_t r, uint8_t g, uint8_t b);
    bool isDeviationGreaterThanOne(uint8_t current, uint8_t newValue);
    void updateColorOfHueKnob();
    void notifyColorChangeCompleted();

    static void OnColorChanged(lv_event_t* e);
    static void OnHueValueChanged(lv_event_t* e);
    static void OnMainAction(lv_event_t* e);

private:
    lv_style_t _colorStyle;
    lv_obj_t* _image;
    lv_obj_t* _brightnessInput;
    lv_obj_t* _saturationInput;
    lv_obj_t* _hueInput;
    lv_obj_t* _value;
    lv_obj_t* _currentColor;
    uint8_t _red = 255;
    uint8_t _green = 0;
    uint8_t _blue = 0;
    bool _initialized = false;
    bool _isPressed = false;
    std::function<void(uint32_t)> _onColorChangeCompleted;
    std::function<void()> _onMainAction;

public:
    RGBScreen();

    virtual void SetLabelText(const char* text) override;
    virtual void SetValueText(const char* text) override;
    virtual void SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active) override;
    virtual void SetColorValue(uint8_t r, uint8_t g, uint8_t b) override;
    virtual uint32_t GetColorValue() const override;
    virtual void RegisterColorChangeCompleted(std::function<void(uint32_t)> callback) override;
    virtual void RegisterMainAction(std::function<void()> callback) override;
    virtual void Show() override;

};
