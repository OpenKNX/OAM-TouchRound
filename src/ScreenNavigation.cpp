#include "ScreenNavigation.h"

#include "TouchDisplayModule.h"

IScreenNavigation *IScreenNavigation::instance = nullptr;

void ScreenNavigation::init(TouchDisplayModule *module)
{
    if (!ParamTCH_Slide)
        return;
    _module = module;
    if (_module == nullptr)
        return;

    if (_gestureLayer != nullptr)
        return;

    _gestureLayer = lv_obj_create(lv_layer_top());
    const int gestureLayerHeight = 50;
    lv_obj_clear_flag(_gestureLayer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_y(_gestureLayer, LV_VER_RES - gestureLayerHeight);
    lv_obj_set_size(_gestureLayer, LV_HOR_RES, gestureLayerHeight);
    lv_obj_set_style_border_width(_gestureLayer, 0, 0);
    lv_obj_set_style_opa(_gestureLayer, LV_OPA_0, 0);
    lv_obj_clear_flag(_gestureLayer, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_add_event_cb(_gestureLayer, ScreenNavigation::onGestureEvent, LV_EVENT_GESTURE, this);
}

void ScreenNavigation::onGestureEvent(lv_event_t *event)
{
    auto *navigation = static_cast<ScreenNavigation *>(lv_event_get_user_data(event));
    if (navigation != nullptr)
        navigation->handleGesture(event);
}

void ScreenNavigation::handleGesture(lv_event_t *event)
{
    if (_module == nullptr)
        return;

    logDebugP("Gesture event");
    if (!_module->_displayOn)
    {
        lv_event_stop_bubbling(event);
        lv_indev_wait_release(lv_indev_get_act());
        _module->display(true);
        return;
    }

    _module->resetDisplayTimeout();

    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        logDebug("Gesture", "Left");
        lv_event_stop_bubbling(event);
        lv_indev_wait_release(lv_indev_get_act());
        _module->nextPage();
    }
    else if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        logDebug("Gesture", "Right");
        lv_event_stop_bubbling(event);
        lv_indev_wait_release(lv_indev_get_act());
        _module->previousPage();
    }
}
