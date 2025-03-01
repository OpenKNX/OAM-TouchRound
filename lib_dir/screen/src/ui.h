#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"
// ui_Dimm
void ui_Dimm_screen_init(void);
void ui_event_DimmValue( lv_event_t * e);
extern lv_obj_t *ui_Dimm;
extern lv_obj_t *ui_DimmValue;
extern lv_obj_t *ui_DimmLabel;
extern lv_obj_t *ui_DimmLabelValue;
extern lv_obj_t *ui_DimmSwitch;
// ui_Color
void ui_Color_screen_init(void);
extern lv_obj_t *ui_Color;
extern lv_obj_t *ui_ColorValue;
extern lv_obj_t *ui_ColorLabel;
// ui_Switch
void ui_Switch_screen_init(void);
extern lv_obj_t *ui_Switch;
extern lv_obj_t *ui_SwitchLabel;
extern lv_obj_t *ui_SwitchValue;
// ui_Message
void ui_Message_screen_init(void);
extern lv_obj_t *ui_Message;
extern lv_obj_t *ui_MessageLabel;


extern lv_obj_t *ui_screen;



#ifdef __cplusplus
} /*extern "C"*/
#endif

