#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// ui_Color
void ui_Color_screen_init(void);
extern lv_obj_t *ui_Color;
extern lv_obj_t *ui_ColorValue;
extern lv_obj_t *ui_ColorLabel;


extern lv_obj_t *ui_screen;



#ifdef __cplusplus
} /*extern "C"*/
#endif

