#include "ui.h"
#include "ui_helpers.h"


// ui_Dimm
void ui_Dimm_screen_init(void);
lv_obj_t *ui_Dimm;
void ui_event_DimmValue( lv_event_t * e);
lv_obj_t *ui_DimmValue;
lv_obj_t *ui_DimmLabel;
lv_obj_t *ui_DimmLabelValue;


// ui_Color
void ui_Color_screen_init(void);
lv_obj_t *ui_Color;
lv_obj_t *ui_ColorValue;
lv_obj_t *ui_ColorLabel;


// ui_Switch
void ui_Switch_screen_init(void);
lv_obj_t *ui_Switch;
lv_obj_t *ui_SwitchLabel;
lv_obj_t *ui_SwitchValue;


// ui_Message
void ui_Message_screen_init(void);
lv_obj_t *ui_Message;
lv_obj_t *ui_MessageLabel;


lv_obj_t *ui_screen;


void ui_event_DimmValue( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_arc_set_text_value( ui_DimmLabelValue, target, "", "%");
}
}

