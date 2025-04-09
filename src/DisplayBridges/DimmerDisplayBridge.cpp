#include "DimmerDisplayBridge.h"

DimmerDisplayBridge::DimmerDisplayBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void DimmerDisplayBridge::setup(uint8_t _channelIndex)
{
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _eventReleased =[](lv_event_t *e) { ((DimmerDisplayBridge*) lv_event_get_user_data(e))->released(); };
    lv_obj_add_event_cb(_screen.value, _eventReleased, LV_EVENT_RELEASED, this);
    _eventButtonPressed = [](lv_event_t *e) { ((DimmerDisplayBridge*) lv_event_get_user_data(e))->buttonClicked(); };
    lv_obj_add_event_cb(_screen.button, _eventButtonPressed , LV_EVENT_CLICKED, this);

    _screen.show();
}

DimmerDisplayBridge::~DimmerDisplayBridge()
{
    if (_eventReleased != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.value, _eventReleased, this);
    if (_eventButtonPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.button, _eventButtonPressed, this);
}

void DimmerDisplayBridge::setBrightness(uint8_t brightness)
{
    lv_arc_set_value(_screen.value, brightness);  
    if (brightness != 0)
        lv_obj_add_state(_screen.button, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(_screen.button, LV_STATE_CHECKED);   
    updateText(); 
}

void DimmerDisplayBridge::updateText()
{
    lv_label_set_text_fmt(_screen.labelValue, "%" LV_PRId32 "%%", lv_arc_get_value(_screen.value));
}

void DimmerDisplayBridge::released()
{    
    auto value = lv_arc_get_value(_screen.value);
    _channel->commandBrightness(this,  value);
    updateText();
}

void DimmerDisplayBridge::buttonClicked()
{    
    _channel->commandMainFunctionClick();   
}