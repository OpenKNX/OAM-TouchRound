#include "DimmerWidget.h"

DimmerWidget::DimmerWidget(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void DimmerWidget::setup(uint8_t _channelIndex)
{
    const char* label = _channel->getNameInUTF8(); 
    lv_label_set_text(ui_DimmLabel, label);
    _eventReleased = lv_obj_add_event_cb(ui_DimmValue, [](lv_event_t *e) { ((DimmerWidget*) e->user_data)->released(); }, LV_EVENT_RELEASED, this);
    _eventButtonPressed = lv_obj_add_event_cb(ui_DimmSwitch, [](lv_event_t *e) { ((DimmerWidget*) e->user_data)->buttonClicked(); }, LV_EVENT_CLICKED, this);
  
    lv_scr_load(ui_Dimm);
}

DimmerWidget::~DimmerWidget()
{
    if (_eventReleased != nullptr)
        lv_obj_remove_event_dsc(ui_DimmValue, _eventReleased);
    if (_eventButtonPressed != nullptr)
        lv_obj_remove_event_dsc(ui_DimmSwitch, _eventButtonPressed);
}

void DimmerWidget::setBrightness(uint8_t brightness)
{
    lv_arc_set_value(ui_DimmValue, brightness);  
    if (brightness != 0)
        lv_obj_add_state(ui_DimmSwitch, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(ui_DimmSwitch, LV_STATE_CHECKED);   
    updateText(); 
}

void DimmerWidget::updateText()
{
    lv_label_set_text_fmt(ui_DimmLabelValue, "%" LV_PRId32 "%%", lv_arc_get_value(ui_DimmValue));
}

void DimmerWidget::released()
{    
    auto value = lv_arc_get_value(ui_DimmValue);
    _channel->commandBrightness(this,  value);
    updateText();
}

void DimmerWidget::buttonClicked()
{    
    _channel->commandPower(this, lv_obj_has_state(ui_DimmSwitch, LV_STATE_CHECKED));
}