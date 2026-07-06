#pragma once

#include "IScreenNavigation.h"
#include "lvgl.h"
#include <string>

class TouchDisplayModule;

class ScreenNavigation : public IScreenNavigation
{
public:
    void init(TouchDisplayModule *module) override;

private:
    static void onGestureEvent(lv_event_t *event);
    std::string logPrefix() { return "ScreenNavigation"; }
    void handleGesture(lv_event_t *event);

    TouchDisplayModule *_module = nullptr;
    lv_obj_t *_gestureLayer = nullptr;
};
