#include "RGBScreen.h"
#include "OpenKNX.h"

#include "ImageLoader.h"

IRGBScreen* IRGBScreen::instance = nullptr;

RGBScreen::RGBScreen()
{
    _value = lv_label_create(screen);
    lv_obj_set_width(_value, LV_SIZE_CONTENT);
    lv_obj_set_height(_value, LV_SIZE_CONTENT);
    lv_obj_set_align(_value, LV_ALIGN_RIGHT_MID);
    lv_obj_align(_value, LV_ALIGN_RIGHT_MID, -115, -20);
    lv_obj_set_style_text_font(_value, &FONT_LARGE, LV_PART_MAIN | LV_STATE_DEFAULT);
  
    _image = lv_img_create(screen);
    lv_obj_align(_image, LV_ALIGN_CENTER, 40, -20);
    lv_obj_add_flag(_image, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(_image, OnMainAction, LV_EVENT_CLICKED, this);

    _currentColor = lv_arc_create(screen);
    lv_obj_set_size(_currentColor, 240, 240);
    lv_arc_set_range(_currentColor,0, 100);
    lv_arc_set_value(_currentColor, 0);
    lv_arc_set_bg_angles(_currentColor, 0, 360);
    lv_obj_remove_style(_currentColor, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(_currentColor, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_align(_currentColor, LV_ALIGN_CENTER, 0, 0);
    
    lv_style_init(&_colorStyle);
    lv_style_set_arc_color(&_colorStyle, lv_color_make(128,128,128));
    lv_style_set_arc_width(&_colorStyle, 10);
    lv_obj_add_style(_currentColor, &_colorStyle, LV_PART_MAIN);
  
    const int32_t hueSliderWidth = 170;
    const int32_t heuSliderPosY = 40;

    static const int canvasWidth = hueSliderWidth;
    static lv_color_t canvas_buf[canvasWidth];

    int canvasHight = 17;
    for (size_t i = 0; i < canvasHight; i++)
    {
        lv_obj_t* canvas = lv_canvas_create(screen);
    #if LVGL_VERSION_MAJOR < 9
        lv_canvas_set_buffer(canvas, canvas_buf, canvasWidth, 1, LV_IMG_CF_TRUE_COLOR);
    #else
        lv_canvas_set_buffer(canvas, canvas_buf, canvasWidth, 1, LV_COLOR_FORMAT_NATIVE);
    #endif
        lv_obj_align(canvas, LV_ALIGN_CENTER, 0, heuSliderPosY + i - canvasHight / 2);

        // Fill canvas with hue gradient
        for (int x = 0; x < canvasWidth; x++) {
            lv_color_hsv_t hsv;
            hsv.h = (x * 359) / canvasWidth;;    // Hue (0-359)
            hsv.s = 100; 
            hsv.v = 100;
            lv_color_t color = lv_color_hsv_to_rgb(hsv.h, hsv.s, hsv.v);
    #if LVGL_VERSION_MAJOR < 9
            lv_canvas_set_px(canvas, x, 0, color);
    #else
            lv_canvas_set_px(canvas, x, 0, color, LV_OPA_COVER);
    #endif
        }
    }

    _hueInput = lv_slider_create(screen);
    lv_obj_set_size(_hueInput, hueSliderWidth, 25);
    lv_slider_set_range(_hueInput, 0, 359);
    lv_obj_align(_hueInput, LV_ALIGN_CENTER, 0, heuSliderPosY);
    lv_obj_add_event_cb(_hueInput, OnColorChanged, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(_hueInput, OnColorChanged, LV_EVENT_PRESSING, this);
    lv_obj_add_event_cb(_hueInput, OnHueValueChanged, LV_EVENT_VALUE_CHANGED, this);
    lv_obj_set_style_bg_opa(_hueInput, LV_OPA_TRANSP, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(_hueInput, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(_hueInput, 6, LV_PART_KNOB);
    lv_obj_set_style_border_color(_hueInput, lv_obj_get_style_bg_color(_hueInput, LV_PART_KNOB), LV_PART_KNOB);

    const int32_t diameterBrigtnessAndSaturation = 220;
    _brightnessInput = lv_arc_create(screen);
    lv_obj_set_width(_brightnessInput, diameterBrigtnessAndSaturation);
    lv_obj_set_height(_brightnessInput, diameterBrigtnessAndSaturation);
    lv_obj_set_align(_brightnessInput, LV_ALIGN_CENTER);
    lv_arc_set_value(_brightnessInput, 0);
    lv_arc_set_bg_angles(_brightnessInput, 180, 260);
    lv_arc_set_range(_brightnessInput, 0, 100);
    lv_obj_set_style_arc_width(_brightnessInput, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_flag(_brightnessInput, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(_brightnessInput, OnColorChanged, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(_brightnessInput, OnColorChanged, LV_EVENT_PRESSING, this);
    lv_arc_set_mode(_brightnessInput, LV_ARC_MODE_REVERSE);
  
    lv_obj_set_style_border_width(_brightnessInput, 6, LV_PART_KNOB);
    lv_obj_set_style_border_color(_brightnessInput, lv_obj_get_style_bg_color(_brightnessInput, LV_PART_KNOB), LV_PART_KNOB);
    lv_obj_set_style_bg_color(_brightnessInput, lv_color_make(0,0,0), LV_PART_KNOB);
  
    _saturationInput = lv_arc_create(screen);
    lv_obj_set_width(_saturationInput, diameterBrigtnessAndSaturation);
    lv_obj_set_height(_saturationInput, diameterBrigtnessAndSaturation);
    lv_obj_set_align(_saturationInput, LV_ALIGN_CENTER);
    lv_arc_set_value(_saturationInput, 0);
    lv_arc_set_bg_angles(_saturationInput, 290, 0);
    lv_arc_set_range(_saturationInput, 0, 100);
    lv_obj_set_style_arc_width(_saturationInput, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_flag(_saturationInput, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(_saturationInput, OnColorChanged, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(_saturationInput, OnColorChanged, LV_EVENT_PRESSING, this);

    lv_obj_set_style_border_width(_saturationInput, 6, LV_PART_KNOB);
    lv_obj_set_style_border_color(_saturationInput, lv_obj_get_style_bg_color(_saturationInput, LV_PART_KNOB), LV_PART_KNOB);
    lv_obj_set_style_bg_color(_saturationInput, lv_color_make(255,255,255), LV_PART_KNOB);
    updateColorOfHueKnob();
}

void RGBScreen::SetColorValue(uint8_t r, uint8_t g, uint8_t b)
{
    if (_isPressed)
        return;
    _red = r;
    _green = g;
    _blue = b;
    auto lv_color_hsv_t = lv_color_rgb_to_hsv(r, g, b);
   
    updateSlider(r, g, b);
    updateColor();
}

void RGBScreen::SetLabelText(const char* text)
{
    lv_label_set_text(label, text);
}

void RGBScreen::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void RGBScreen::SetMainIndicatorImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

uint32_t RGBScreen::GetColorValue() const
{
    return (_red << 16) | (_green << 8) | _blue;
}

void RGBScreen::RegisterColorChangeCompleted(std::function<void(uint32_t)> callback)
{
    _onColorChangeCompleted = callback;
}

void RGBScreen::RegisterMainAction(std::function<void()> callback)
{
    _onMainAction = callback;
}

void RGBScreen::Show()
{
    show();
}

void RGBScreen::updateColorOfHueKnob()
{
    auto hue = lv_slider_get_value(_hueInput);
    lv_color_hsv_t hsv;
    hsv.h = hue;
    hsv.s = 100; 
    hsv.v = 100;
    lv_color_t color = lv_color_hsv_to_rgb(hsv.h, hsv.s, hsv.v);
    lv_obj_set_style_bg_color(_hueInput, color, LV_PART_KNOB);
}

bool RGBScreen::isDeviationGreaterThanOne(uint8_t current, uint8_t newValue) {
    int diff = static_cast<int>(current) - static_cast<int>(newValue);
    return std::abs(diff) > 1;
}
void RGBScreen::colorChanged(lv_event_t* e)
{
    _isPressed = lv_event_get_code(e) == LV_EVENT_PRESSING;
    auto hue = lv_slider_get_value(_hueInput);
    auto saturation = 100 - lv_arc_get_value(_saturationInput);
    auto brightness = 100 - lv_arc_get_value(_brightnessInput);
    auto color = lv_color_hsv_to_rgb(hue, saturation, brightness);
#if LVGL_VERSION_MAJOR >= 9
    uint8_t r = color.red;
    uint8_t g = color.green;
    uint8_t b = color.blue;
#else
    uint8_t r = color.ch.red;
    uint8_t g = color.ch.green;
    uint8_t b = color.ch.blue;
#endif
    if (isDeviationGreaterThanOne(_red, r) || isDeviationGreaterThanOne(_green, g) || isDeviationGreaterThanOne(_blue, b)) {
        _red = r;
        _green = g;
        _blue = b;
        updateColor();
    }
    if (lv_event_get_code(e) == LV_EVENT_RELEASED)
        notifyColorChangeCompleted();
}

void RGBScreen::updateSlider(uint8_t r, uint8_t g, uint8_t b)
{
    auto hsv = lv_color_rgb_to_hsv(r, g, b);
    lv_arc_set_value(_brightnessInput, 100 - hsv.v);
    lv_arc_set_value(_saturationInput, 100 - hsv.s);
    if (_initialized)
    {
        if (r == 0 && g == 0 && b == 0 || (r == 255 && g == 255 && b == 255)) {
            return;
        }
    }
    _initialized = true;
    lv_slider_set_value(_hueInput, hsv.h, LV_ANIM_OFF);
}

void RGBScreen::updateColor()
{
    lv_style_set_arc_color(&_colorStyle, lv_color_make(_red, _green, _blue));
    lv_obj_add_style(_currentColor, &_colorStyle, LV_PART_MAIN);
    updateColorOfHueKnob();
}

void RGBScreen::notifyColorChangeCompleted()
{
    if (_onColorChangeCompleted)
        _onColorChangeCompleted(GetColorValue());
}

void RGBScreen::OnColorChanged(lv_event_t* e)
{
    auto* self = static_cast<RGBScreen*>(lv_event_get_user_data(e));
    if (self == nullptr)
        return;
    self->colorChanged(e);
}

void RGBScreen::OnHueValueChanged(lv_event_t* e)
{
    auto* self = static_cast<RGBScreen*>(lv_event_get_user_data(e));
    if (self == nullptr)
        return;
    self->updateColorOfHueKnob();
}

void RGBScreen::OnMainAction(lv_event_t* e)
{
    auto* self = static_cast<RGBScreen*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onMainAction)
        return;
    self->_onMainAction();
}
