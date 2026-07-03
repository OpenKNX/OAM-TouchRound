#pragma once

#include <functional>

#include "Screens/ILockScreen.h"
#include "ScreenWithLabel.h"

class LockScreen: public ScreenWithLabel
               , public ILockScreen
{
private:
    lv_obj_t* _image;
    lv_obj_t* _value;
    lv_obj_t* _blocked;
    lv_obj_t* _movement;
    std::function<void()> _onMainAction;

    static void OnMainAction(lv_event_t* e);

public:
    LockScreen();

    virtual void SetLabelText(const char* text) override;
    virtual void SetValueText(const char* text) override;
    virtual void SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active) override;
    virtual void SetBlockedVisible(bool visible) override;
    virtual void SetMovementImage(const char* imageFile) override;
    virtual void ClearMovementImage() override;
    virtual void RegisterMainAction(std::function<void()> callback) override;
    virtual void Show() override;
 
};
