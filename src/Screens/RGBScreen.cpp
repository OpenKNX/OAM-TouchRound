#include "RGBScreen.h"
#include "OpenKNX.h"

#include <cmath> // For atan2f and sqrtf

RGBScreen* RGBScreen::instance = nullptr;

// Static function to handle touch events
void RGBScreen::hsv_event_handler(lv_event_t* e) {
    lv_point_t point;
    lv_indev_get_point(lv_indev_get_act(), &point);
    lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
    isPressed = lv_event_get_code(e) != LV_EVENT_RELEASED;
    lv_area_t area;
    lv_obj_get_coords(obj, &area);

    int centerX = (area.x1 + area.x2) / 2;
    int centerY = (area.y1 + area.y2) / 2;
    int dx = point.x - centerX;
    int dy = point.y - centerY;
    int radius = lv_obj_get_width(obj) / 2;

    if (dx * dx + dy * dy <= radius * radius) {
        float angle = lv_atan2(-dy, dx) * 180.0f / M_PI;
        if (angle < 0) 
            angle += 360;
        
        hue = (int)angle;
        saturation = (int)(sqrt(dx * dx + dy * dy) / radius * 100);
        brightness = (int)lv_slider_get_value(brightnessSlider);
        logError("ColorPicker", "H: %d, S: %d, V: %d", (int) hue, (int) saturation, (int) brightness);
        lv_color_t color = lv_color_hsv_to_rgb(hue, saturation, brightness);
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
        
        // Use the color or update H, S, and V values here
        // For example, you can log or display the color
    }
    logError("ColorPicker", "pressed: %d", (int) isPressed);
    updateColor();
}
void RGBScreen::setRGB(uint8_t r, uint8_t g, uint8_t b) 
{
    if (!isPressed) {
        logError("RGBScreen", "Ignore setRGB because pressed");
        return;
    }
    red = r;
    green = g;
    blue = b;
    auto lv_color_hsv_t = lv_color_rgb_to_hsv(r, g, b);
    hue = lv_color_hsv_t.h;
    saturation = lv_color_hsv_t.s;
    brightness = lv_color_hsv_t.v;
    lv_slider_set_value(brightnessSlider, brightness, LV_ANIM_OFF);
    updateColor();
}

void RGBScreen::updateColor()
{
    lv_style_set_arc_color(&colorStyle, lv_color_make(red, green, blue));
}

RGBScreen::RGBScreen()
{
    logError("RGBScreen", "Constructor");
    // Create a custom circular area for H and S values
    hsvContainer = lv_obj_create(screen);
    int circleDiameter = 100; // Diameter of the HVL circle
  
    lv_color_t bg = lv_obj_get_style_bg_color(screen, LV_PART_MAIN);

    int hsvX = -40;
    int hsvY = 10;
    lv_obj_set_size(hsvContainer, circleDiameter, circleDiameter);
    lv_obj_align(hsvContainer, LV_ALIGN_CENTER, hsvX, hsvY);
    lv_obj_set_style_radius(hsvContainer, LV_RADIUS_CIRCLE, 0);
    lv_obj_clear_flag(hsvContainer, LV_OBJ_FLAG_SCROLLABLE);


    int arcWitdh = 10;
    lv_obj_t * color = lv_arc_create(screen);
    lv_obj_set_size(hsvContainer, circleDiameter + arcWitdh, circleDiameter + arcWitdh);
    lv_arc_set_rotation(color, 270);
    lv_arc_set_bg_angles(color, 0, 360);
    lv_obj_remove_style(color, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_remove_flag(color, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align(color, LV_ALIGN_CENTER, hsvX, hsvY);
    
    lv_style_init(&colorStyle);
    lv_style_set_arc_color(&colorStyle, lv_color_hex(0xCCCCCC)); // Hellgrau
    lv_style_set_arc_width(&colorStyle, arcWitdh);
    lv_obj_add_style(color, &colorStyle, LV_PART_MAIN);


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
    lv_obj_add_event_cb(hsvContainer, eventPressing, LV_EVENT_RELEASED, this);

    // Create a slider for V value
    brightnessSlider = lv_slider_create(screen);
    lv_obj_set_width(brightnessSlider, 138);
    lv_obj_align(brightnessSlider, LV_ALIGN_TOP_MID, 0, 45);
    lv_slider_set_range(brightnessSlider, 0, 100);

    image = lv_img_create(screen);  
    //lv_img_set_src(image, &lamp_outline);       
    lv_obj_align(image, LV_ALIGN_CENTER, 65, -10);  

    value = lv_label_create(screen);
    lv_obj_set_width(value, LV_SIZE_CONTENT);
    lv_obj_set_height(value, LV_SIZE_CONTENT);
    lv_obj_align(value, LV_ALIGN_CENTER, 65, 50);

   

}