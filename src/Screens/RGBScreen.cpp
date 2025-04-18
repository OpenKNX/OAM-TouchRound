#include "RGBScreen.h"
#include "OpenKNX.h"

#include <cmath> // For atan2f and sqrtf

RGBScreen* RGBScreen::instance = nullptr;

// Static function to handle touch events
void RGBScreen::hsv_event_handler(lv_event_t* e) {
    lv_point_t point;
    lv_indev_get_point(lv_indev_get_act(), &point);
    lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
    lv_area_t area;
    lv_obj_get_coords(obj, &area);

    int centerX = (area.x1 + area.x2) / 2;
    int centerY = (area.y1 + area.y2) / 2;
    int dx = point.x - centerX;
    int dy = point.y - centerY;
    int radius = lv_obj_get_width(obj) / 2;

    if (dx * dx + dy * dy <= radius * radius) {
        float angle = lv_atan2(-dy, dx) * 180.0f / M_PI;
        if (angle < 0) angle += 360;
        int h = (int)angle;
        int s = (int)(sqrt(dx * dx + dy * dy) / radius * 100);

        // Retrieve the actual color from the HSV gradient canvas
        int imgX = dx + radius;
        int imgY = dy + radius;
        auto color = lv_canvas_get_px(canvas, imgX, imgY);
    

        logError("ColorPicker", "H: %d, S: %d, V: %d", h, s);
        #if LVGL_VERSION_MAJOR >= 9   
        red = color.red;
        green = color.green;
        blue = color.blue;
        #else
        red = color & 0xFF;
        green = (color >> 8) & 0xFF;
        blue = (color >> 16) & 0xFF;
        #endif
        logError("ColorPicker", "R: %d, G: %d, B: %d", (int) red, (int) green, (int) blue);
      
        hasNewColor = true;
        // Use the color or update H, S, and V values here
        // For example, you can log or display the color
    }
}

RGBScreen::RGBScreen()
{
    logError("RGBScreen", "Constructor");
    // Create a custom circular area for H and S values
    lv_obj_t* hsvContainer = lv_obj_create(screen);
    int circleDiameter = 100; // Diameter of the HVL circle
  
    lv_color_t bg = lv_obj_get_style_bg_color(screen, LV_PART_MAIN);

    lv_obj_set_size(hsvContainer, circleDiameter, circleDiameter);
    lv_obj_align(hsvContainer, LV_ALIGN_CENTER, -40, 10);
    lv_obj_set_style_radius(hsvContainer, LV_RADIUS_CIRCLE, 0);
    lv_obj_clear_flag(hsvContainer, LV_OBJ_FLAG_SCROLLABLE);


    // Generate the HSV gradient programmatically
    // Create a canvas to draw the gradient
    canvas = lv_canvas_create(hsvContainer);
    lv_obj_set_size(canvas, circleDiameter, circleDiameter);
    lv_obj_align(canvas, LV_ALIGN_CENTER, 0, 0);


    // Allocate memory for the canvas buffer
#if LVGL_VERSION_MAJOR >= 9   
    static lv_color32_t* cbuf = new lv_color32_t[circleDiameter * circleDiameter];
    lv_canvas_set_buffer(canvas, cbuf, circleDiameter, circleDiameter, LV_COLOR_FORMAT_NATIVE);
#else
    static lv_color_t* cbuf = new lv_color_t[circleDiameter * circleDiameter];
    lv_canvas_set_buffer(canvas, cbuf, circleDiameter, circleDiameter, LV_IMG_CF_TRUE_COLOR);
#endif
logError("RGBScreen", "create canvas");
    int radius = circleDiameter / 2;
    // Draw the circular HSV gradient
    for (int y = 0; y < circleDiameter ; y++) {
        for (int x = 0; x < circleDiameter; x++) {
            int dx = x - radius;
            int dy = y - radius;
            float distance = sqrtf(dx * dx + dy * dy);

            if (distance <= radius) {
                float angle = atan2f(-dy, dx) * 180.0f / M_PI;
                if (angle < 0) angle += 360;
                int h = (int)angle;
                int s = (int)((distance / radius) * 100);

                // Convert HSV to RGB
                lv_color_t color = lv_color_hsv_to_rgb(h, s, 100);
#if LVGL_VERSION_MAJOR >= 9  
                lv_canvas_set_px(canvas, x, y, color, LV_OPA_100);
#else
                lv_canvas_set_px(canvas, x, y, color);
#endif
            } else {
#if LVGL_VERSION_MAJOR >= 9  
                lv_canvas_set_px(canvas, x, y, bg, LV_OPA_TRANSP); // Set outside the circle to transparent
#else
                lv_canvas_set_px(canvas, x, y, lv_color_hex(0xFFFFFF)); // Set outside the circle to white
#endif
            }
        }
    }
    logError("RGBScreen", "Add event");
    // Update touch event to handle H, S, and V selection based on the HSV gradient
    auto eventPressing = [](lv_event_t *e) { ((RGBScreen*) lv_event_get_user_data(e))->hsv_event_handler(e); };
    lv_obj_add_event_cb(hsvContainer, eventPressing, LV_EVENT_PRESSING, this);

    // Create a slider for V value
    valueSlider = lv_slider_create(screen);
    lv_obj_set_width(valueSlider, 138);
    lv_obj_align(valueSlider, LV_ALIGN_TOP_MID, 0, 45);
    lv_slider_set_range(valueSlider, 0, 100);

    image = lv_img_create(screen);  
    //lv_img_set_src(image, &lamp_outline);       
    lv_obj_align(image, LV_ALIGN_CENTER, 65, -10);  

    value = lv_label_create(screen);
    lv_obj_set_width(value, LV_SIZE_CONTENT);
    lv_obj_set_height(value, LV_SIZE_CONTENT);
    lv_obj_align(value, LV_ALIGN_CENTER, 65, 50);

}