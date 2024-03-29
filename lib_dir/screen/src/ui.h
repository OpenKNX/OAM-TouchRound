// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: Visu

#ifndef _VISU_UI_H
#define _VISU_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
  #if __has_include("lvgl.h")
    #include "lvgl.h"
  #elif __has_include("lvgl/lvgl.h")
    #include "lvgl/lvgl.h"
  #else
    #include "lvgl.h"
  #endif
#else
  #include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_Dimm
void ui_Dimm_screen_init(void);
extern lv_obj_t *ui_Dimm;
void ui_event_DimmValue( lv_event_t * e);
extern lv_obj_t *ui_DimmValue;
extern lv_obj_t *ui_LabelName;
extern lv_obj_t *ui_LabelValue;
// SCREEN: ui_Color
void ui_Color_screen_init(void);
extern lv_obj_t *ui_Color;
extern lv_obj_t *ui_ColorValue;
extern lv_obj_t *ui_Label2;
// SCREEN: ui_Switch
void ui_Switch_screen_init(void);
extern lv_obj_t *ui_Switch;
extern lv_obj_t *ui_Label1;
extern lv_obj_t *ui_SwitchValue;
// SCREEN: ui_Message
void ui_Message_screen_init(void);
extern lv_obj_t *ui_Message;
extern lv_obj_t *ui_Label3;
extern lv_obj_t *ui____initial_actions0;




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
