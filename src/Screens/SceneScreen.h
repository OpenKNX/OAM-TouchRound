#pragma once

#include <functional>
#include "Screens/ISceneScreen.h"
#include "ScreenWithLabel.h"

class SceneScreen: public ScreenWithLabel
                 , public ISceneScreen
{
private:
    lv_obj_t* _value;
    lv_obj_t* _image;
    std::function<void()> _onPrimaryActionPressed;
    std::function<void()> _onPrimaryActionReleased;

    static void OnPrimaryActionPressed(lv_event_t* e);
    static void OnPrimaryActionReleased(lv_event_t* e);

public:
    SceneScreen();

    virtual void SetLabelText(const char* text) override;
    virtual void SetValueText(const char* text) override;
    virtual void SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active) override;
    virtual void RegisterPrimaryActionPressed(std::function<void()> callback) override;
    virtual void RegisterPrimaryActionReleased(std::function<void()> callback) override;
    virtual void Show() override;
};
