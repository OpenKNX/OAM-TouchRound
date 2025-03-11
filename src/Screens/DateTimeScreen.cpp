#include "DateTimeScreen.h"

DateTimeScreen* DateTimeScreen::instance = nullptr;

DateTimeScreen::DateTimeScreen()
{
    weekday = lv_label_create(screen);
    lv_obj_set_width(weekday, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(weekday, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(weekday, 0);
    lv_obj_set_y(weekday, -60);
    lv_obj_set_align(weekday, LV_ALIGN_CENTER);

    date = lv_label_create(screen);
    lv_obj_set_width(date, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(date, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(date, 0);
    lv_obj_set_y(date, -20);
    lv_obj_set_align(date, LV_ALIGN_CENTER);

    time = lv_label_create(screen);
    lv_obj_set_width(time, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(time, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(time, 0);
    lv_obj_set_y(time, 30);
    lv_obj_set_align(time, LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(time, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT); 

    message = lv_obj_create(NULL);
    lv_obj_clear_flag( ui_Message, LV_OBJ_FLAG_SCROLLABLE );  

}