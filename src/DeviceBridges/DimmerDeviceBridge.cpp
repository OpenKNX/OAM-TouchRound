#include "DimmerDeviceBridge.h"
#include "../ImageLoader.h"

DimmerDeviceBridge::DimmerDeviceBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void DimmerDeviceBridge::setup(uint8_t _channelIndex)
{
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _eventSliderReleased =[](lv_event_t *e) { ((DimmerDeviceBridge*) lv_event_get_user_data(e))->sliderReleased(); };
    lv_obj_add_event_cb(_screen.slider, _eventSliderReleased, LV_EVENT_RELEASED, this);
    _eventSliderPressing = [](lv_event_t *e) { ((DimmerDeviceBridge*) lv_event_get_user_data(e))->sliderPressing(); };
    lv_obj_add_event_cb(_screen.slider, _eventSliderPressing, LV_EVENT_PRESSING, this);
    _eventButtonPressed = [](lv_event_t *e) { ((DimmerDeviceBridge*) lv_event_get_user_data(e))->buttonClicked(); };
    lv_obj_add_event_cb(_screen.image, _eventButtonPressed , LV_EVENT_CLICKED, this);

    mainFunctionValueChanged();
    _screen.show();
}

DimmerDeviceBridge::~DimmerDeviceBridge()
{
    if (_eventSliderReleased != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.slider, _eventSliderReleased, this);
    if (_eventSliderPressing != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.slider, _eventSliderPressing, this);
    if (_eventButtonPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.image, _eventButtonPressed, this);
}

void DimmerDeviceBridge::setBrightness(uint8_t brightness)
{
    if (_isSliderPressed)
        return;
    lv_arc_set_value(_screen.slider, brightness);  
    ImageLoader::loadImage(_screen.image, _channel->mainFunctionImage().imageFile, _channel->mainFunctionImage().allowRecolor, brightness != 0); 
    updateText(); 
}

void DimmerDeviceBridge::updateText()
{
    lv_label_set_text_fmt(_screen.value, "%" LV_PRId32 "%%", lv_arc_get_value(_screen.slider));
}

void DimmerDeviceBridge::sliderReleased()
{    
    _isSliderPressed = false;
    auto value = lv_arc_get_value(_screen.slider);
    _channel->commandBrightness(nullptr,  value);
    updateText();
}

void DimmerDeviceBridge::sliderPressing()
{    
    _isSliderPressed = true;
    auto value = lv_arc_get_value(_screen.slider);
    _channel->commandBrightness(nullptr,  value);
    updateText();
}

void DimmerDeviceBridge::buttonClicked()
{    
    _channel->commandMainFunctionClick();   
}

void DimmerDeviceBridge::mainFunctionValueChanged()
{
    
}