#include "../ui.h"

void ui_Color_screen_init(void)
{
    ui_Color = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Color, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_ColorValue = lv_colorwheel_create(ui_Color, true);
    lv_obj_set_width(ui_ColorValue, 200);
    lv_obj_set_height(ui_ColorValue, 200);
    lv_obj_set_align(ui_ColorValue, LV_ALIGN_CENTER);
    lv_obj_set_style_arc_width(ui_ColorValue, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ColorLabel = lv_label_create(ui_Color);
    lv_obj_set_width(ui_ColorLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ColorLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_ColorLabel, LV_ALIGN_CENTER);
}
