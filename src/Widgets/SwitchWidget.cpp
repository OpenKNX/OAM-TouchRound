#include "SwitchWidget.h"

SwitchWidget::SwitchWidget(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void SwitchWidget::setup(uint8_t _channelIndex)
{
    const char* label = _channel->getNameInUTF8(); 
    lv_label_set_text(ui_Label1, label);
    lv_obj_add_flag(ui_SwitchValue, LV_OBJ_FLAG_CHECKABLE);
    _buttonPressedEvent = lv_obj_add_event_cb(ui_SwitchValue, [](lv_event_t *e) { ((SwitchWidget*) e->user_data)->buttonClicked(); }, LV_EVENT_CLICKED, this);
    lv_scr_load(ui_Switch);
 
}

SwitchWidget::~SwitchWidget()
{
    if (_buttonPressedEvent != nullptr)
        lv_obj_remove_event_dsc(ui_Switch, _buttonPressedEvent);
}

void SwitchWidget::setPower(bool on)
{
    if (on)
        lv_obj_add_state(ui_SwitchValue, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(ui_SwitchValue, LV_STATE_CHECKED);   
}

void SwitchWidget::buttonClicked()
{    
    _channel->commandPower(this,  lv_obj_has_state(ui_SwitchValue, LV_STATE_CHECKED));
}