#include "RGBScreen.h"
#include <cmath> // For atan2f and sqrtf

RGBScreen* RGBScreen::instance = nullptr;

// Static function to handle touch events
static void hsv_event_handler(lv_event_t* e) {
    lv_obj_t* canvas = static_cast<lv_obj_t*>(lv_event_get_user_data(e));
    lv_point_t point;
    lv_indev_get_point(lv_indev_get_act(), &point);
    lv_obj_t* obj = lv_event_get_target(e);
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
        lv_color_t color = lv_canvas_get_px(canvas, imgX, imgY);

        // Use the color or update H, S, and V values here
        // For example, you can log or display the color
    }
}

RGBScreen::RGBScreen()
{
    // Create a custom circular area for H and S values
    lv_obj_t* hsvContainer = lv_obj_create(screen);
    lv_obj_set_size(hsvContainer, 200, 200);
    lv_obj_align(hsvContainer, LV_ALIGN_CENTER, 0, -100);
    lv_obj_set_style_radius(hsvContainer, LV_RADIUS_CIRCLE, 0);

    // Generate the HSV gradient programmatically
    lv_obj_set_style_bg_img_src(hsvContainer, nullptr, 0); // Remove any pre-set image
    lv_obj_set_style_bg_opa(hsvContainer, LV_OPA_TRANSP, 0); // Make the background transparent

    // Create a canvas to draw the gradient
    lv_obj_t* canvas = lv_canvas_create(hsvContainer);
    lv_obj_set_size(canvas, 200, 200);
    lv_obj_align(canvas, LV_ALIGN_CENTER, 0, 0);

    // Allocate memory for the canvas buffer
    static lv_color_t cbuf[200 * 200];
    lv_canvas_set_buffer(canvas, cbuf, 200, 200, LV_IMG_CF_TRUE_COLOR);

    // Draw the circular HSV gradient
    int radius = 100; // Half the size of the canvas
    for (int y = 0; y < 200; y++) {
        for (int x = 0; x < 200; x++) {
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
                lv_canvas_set_px(canvas, x, y, color);
            } else {
                lv_canvas_set_px(canvas, x, y, lv_color_hex(0xFFFFFF)); // Set outside the circle to white
            }
        }
    }

    // Update touch event to handle H, S, and V selection based on the HSV gradient
    lv_obj_add_event_cb(hsvContainer, hsv_event_handler, LV_EVENT_PRESSING, canvas);

    // Create a slider for V value
    valueSlider = lv_slider_create(screen);
    lv_obj_set_width(valueSlider, 200);
    lv_obj_align(valueSlider, LV_ALIGN_CENTER, 0, 25);
    lv_slider_set_range(valueSlider, 0, 100);
    lv_slider_set_value(valueSlider, 50, LV_ANIM_OFF);

    labelValue = lv_label_create(screen);
    lv_obj_set_width(labelValue, LV_SIZE_CONTENT);
    lv_obj_set_height(labelValue, LV_SIZE_CONTENT);
    lv_obj_align(labelValue, LV_ALIGN_CENTER, 0, 50);
    lv_label_set_text(labelValue, "V: 50");

    lv_obj_add_event_cb(valueSlider, [](lv_event_t* e) {
        RGBScreen* self = static_cast<RGBScreen*>(lv_event_get_user_data(e));
        int value = lv_slider_get_value(self->valueSlider);
        lv_label_set_text_fmt(self->labelValue, "V: %d", value);
    }, LV_EVENT_VALUE_CHANGED, this);
}