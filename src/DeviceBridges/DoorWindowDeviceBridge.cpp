#include "DoorWindowDeviceBridge.h"
#include "../ImageLoader.h"

DoorWindowDeviceBridge::DoorWindowDeviceBridge(DetailDevicePage& detailDevicePage)
    : _detailDevicePage(detailDevicePage)
{
}

void DoorWindowDeviceBridge::setup(uint8_t _channelIndex)
{   
    // if (ParamBRI_CHDoorWindowAutomatic)
    //     lv_obj_clear_flag(_screen.buttonAuto, LV_OBJ_FLAG_HIDDEN);
    // else
    //     lv_obj_add_flag(_screen.buttonAuto, LV_OBJ_FLAG_HIDDEN);
 
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
   
    
    _eventIconPressed = [](lv_event_t *e) { ((DoorWindowDeviceBridge*) lv_event_get_user_data(e))->imageClicked(); };
    lv_obj_add_event_cb(_screen.image, _eventIconPressed, LV_EVENT_CLICKED, this);
    
    _screen.show();
    mainFunctionValueChanged();
}

DoorWindowDeviceBridge::~DoorWindowDeviceBridge()
{
    if (_eventIconPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.image, _eventIconPressed, this);
}

void DoorWindowDeviceBridge::setPosition(uint8_t position)
{
}

void DoorWindowDeviceBridge::setMovement(DoorWindowMoveState movement)
{
}

void DoorWindowDeviceBridge::setObstructionDetected(bool obstructionDetected)
{
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