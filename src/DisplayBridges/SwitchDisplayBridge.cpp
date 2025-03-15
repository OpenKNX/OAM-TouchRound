#include "SwitchDisplayBridge.h"

SwitchDisplayBridge::SwitchDisplayBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void SwitchDisplayBridge::setup(uint8_t _channelIndex)
{   
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _eventButtonPressed = [](lv_event_t *e) { ((SwitchDisplayBridge*) e->user_data)->buttonClicked(); };
    lv_obj_add_event_cb(_screen.button, _eventButtonPressed, LV_EVENT_CLICKED, this);
    _screen.show();
 
}

SwitchDisplayBridge::~SwitchDisplayBridge()
{
    if (_eventButtonPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.button, _eventButtonPressed, this);
}

void SwitchDisplayBridge::setPower(bool on)
{
    if (on)
        lv_obj_add_state(_screen.button, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(_screen.button, LV_STATE_CHECKED);   
}

void SwitchDisplayBridge::buttonClicked()
{    
    _channel->commandMainFunctionClick();
}