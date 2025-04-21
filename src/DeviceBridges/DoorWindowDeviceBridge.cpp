#include "DoorWindowDeviceBridge.h"
#include "../ImageLoader.h"

DoorWindowDeviceBridge::DoorWindowDeviceBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void DoorWindowDeviceBridge::setup(uint8_t _channelIndex)
{   
    if (ParamBRI_CHDoorWindowMotor)
        lv_obj_clear_flag(_screen.slider, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(_screen.slider, LV_OBJ_FLAG_HIDDEN);
    
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    
    _eventIconPressed = [](lv_event_t *e) { ((DoorWindowDeviceBridge*) lv_event_get_user_data(e))->imageClicked(); };
    lv_obj_add_event_cb(_screen.image, _eventIconPressed, LV_EVENT_CLICKED, this);
    _eventSliderReleased = [](lv_event_t *e) { ((DoorWindowDeviceBridge*) lv_event_get_user_data(e))->sliderReleased(); };
    lv_obj_add_event_cb(_screen.slider, _eventSliderReleased, LV_EVENT_RELEASED, this);
    
    ImageLoader::loadImage(_screen.obstruction, "alert.png");
    ImageLoader::colorImage(_screen.obstruction, 255, 0, 0);
    lv_obj_add_flag(_screen.obstruction, LV_OBJ_FLAG_HIDDEN);
    ImageLoader::unloadImage(_screen.movement);
    mainFunctionValueChanged();
    _screen.show();

}

DoorWindowDeviceBridge::~DoorWindowDeviceBridge()
{
    if (_eventIconPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.image, _eventIconPressed, this);
}

void DoorWindowDeviceBridge::setPosition(uint8_t position)
{
    lv_slider_set_value(_screen.slider, position, LV_ANIM_ON);
}

void DoorWindowDeviceBridge::setMovement(DoorWindowMoveState movement)
{
    switch (movement)
    {
        case DoorWindowMoveState::DoorWindowMoveStateOpening:
            ImageLoader::loadImage(_screen.movement, "opening.png", true, true);
            break;
        case DoorWindowMoveState::DoorWindowMoveStateClosing:
            ImageLoader::loadImage(_screen.movement, "closing.png", true, true);
            break;
        case DoorWindowMoveState::DoorWindowMoveStateHold:
            ImageLoader::unloadImage(_screen.movement);
            break;
    }
}

void DoorWindowDeviceBridge::sliderReleased()
{
    auto& device = *_channel;
    int32_t value = lv_slider_get_value(_screen.slider);
    device.commandPosition(nullptr, value);
}

void DoorWindowDeviceBridge::setObstructionDetected(bool obstructionDetected)
{
    if (obstructionDetected)
    {
        lv_obj_clear_flag(_screen.obstruction, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(_screen.obstruction, LV_OBJ_FLAG_HIDDEN);
    }
}

void DoorWindowDeviceBridge::mainFunctionValueChanged()
{
    auto& device = *_channel;
    auto image = device.mainFunctionImage();
    bool power = device.mainFunctionValue();
    ImageLoader::loadImage(_screen.image, image.imageFile, image.allowRecolor, power);
    lv_label_set_text(_screen.value, device.currentValueAsString().c_str());
}

void DoorWindowDeviceBridge::imageClicked()
{    
    _channel->commandMainFunctionClick();
}