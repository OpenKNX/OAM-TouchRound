#include "RGBScreen.h"
#include <cmath> // For atan2f and sqrtf

RGBScreen* RGBScreen::instance = nullptr;

RGBScreen::RGBScreen()
{
    // Create a custom circular area for H and S values
    lv_obj_t* hsvContainer = lv_obj_create(screen);
    lv_obj_set_size(hsvContainer, 200, 200);
    lv_obj_align(hsvContainer, LV_ALIGN_CENTER, 0, -100);
    lv_obj_set_style_radius(hsvContainer, LV_RADIUS_CIRCLE, 0);

    // Render a color gradient to represent the HSV color range
    lv_obj_set_style_bg_opa(hsvContainer, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(hsvContainer, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_grad_color(hsvContainer, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_grad_dir(hsvContainer, LV_GRAD_DIR_NONE, 0);

    // Create an image to overlay the HSV gradient
    lv_obj_t* hsvImage = lv_img_create(hsvContainer);
    // lv_img_set_src(hsvImage, &hsv_gradient_image); // Assuming hsv_gradient_image is a pre-generated image of the HSV color wheel
    lv_obj_align(hsvImage, LV_ALIGN_CENTER, 0, 0);

    // Update touch event to handle H, S, and V selection based on the HSV gradient
    lv_obj_add_event_cb(hsvContainer, [](lv_event_t* e) {
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

            // Retrieve the actual color from the HSV gradient image
            // int imgX = (dx + radius) * hsv_gradient_image.header.w / (2 * radius);
            // int imgY = (dy + radius) * hsv_gradient_image.header.h / (2 * radius);
            // lv_color_t color = lv_img_buf_get_px_color(&hsv_gradient_image, imgX, imgY);

            // Use the color or update H, S, and V values here
        }
    }, LV_EVENT_PRESSING, this);

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