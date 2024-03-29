// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: Visu

#include "../ui.h"

void ui_Dimm_screen_init(void)
{
ui_Dimm = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Dimm, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_DimmValue = lv_arc_create(ui_Dimm);
lv_obj_set_width( ui_DimmValue, 200);
lv_obj_set_height( ui_DimmValue, 200);
lv_obj_set_align( ui_DimmValue, LV_ALIGN_CENTER );

lv_obj_set_style_arc_width(ui_DimmValue, 20, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_LabelName = lv_label_create(ui_Dimm);
lv_obj_set_width( ui_LabelName, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelName, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LabelName, 0 );
lv_obj_set_y( ui_LabelName, 63 );
lv_obj_set_align( ui_LabelName, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelName,"Deckenlicht");

ui_LabelValue = lv_label_create(ui_Dimm);
lv_obj_set_width( ui_LabelValue, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelValue, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LabelValue, 0 );
lv_obj_set_y( ui_LabelValue, 97 );
lv_obj_set_align( ui_LabelValue, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelValue,"0%");

lv_obj_add_event_cb(ui_DimmValue, ui_event_DimmValue, LV_EVENT_ALL, NULL);

}
