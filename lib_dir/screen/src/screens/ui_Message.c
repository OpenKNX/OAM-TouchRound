// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: Visu

#include "../ui.h"

void ui_Message_screen_init(void)
{
ui_Message = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Message, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label3 = lv_label_create(ui_Message);
lv_obj_set_width( ui_Label3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label3, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label3,"");

}
