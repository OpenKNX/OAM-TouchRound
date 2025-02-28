#include "DimmerWidget.h"

DimmerWidget::DimmerWidget(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void DimmerWidget::setup(uint8_t _channelIndex)
{
    const char* label = _channel->getNameInUTF8(); 
    lv_label_set_text(ui_LabelName, label);
    // lv_obj_add_flag(ui_SwitchValue, LV_OBJ_FLAG_CHECKABLE);
    // _buttonPressedEvent = lv_obj_add_event_cb(ui_SwitchValue, [](lv_event_t *e) { ((DimmerWidget*) e->user_data)->buttonClicked(); }, LV_EVENT_CLICKED, this);
    lv_scr_load(ui_Dimm);
 
}

DimmerWidget::~DimmerWidget()
{
    if (_buttonPressedEvent != nullptr)
        lv_obj_remove_event_dsc(ui_Switch, _buttonPressedEvent);
}

void DimmerWidget::setBrightness(uint8_t brightness)
{
    char buffer[5];
    sprintf(buffer, "%d%%", (int) brightness);
    lv_label_set_text(ui_LabelValue, buffer);
    lv_obj_set_style_arc_width(ui_DimmValue, (int) brightness, LV_PART_INDICATOR| LV_STATE_DEFAULT);

    if (brightness != 0)
        lv_obj_add_state(ui_SwitchValue, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(ui_SwitchValue, LV_STATE_CHECKED);   
}

void DimmerWidget::buttonClicked()
{    
    _channel->commandPower(this,  lv_obj_has_state(ui_SwitchValue, LV_STATE_CHECKED));
}