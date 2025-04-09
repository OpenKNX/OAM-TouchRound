#include "DeviceMainFunctionCell.h"
#include "CellParameterDefines.h"
#include "../Screens/CellScreen.h"
#include "SmartHomeBridgeModule.h"
#include "../ImageLoader.h"
#include "../TouchDisplayModule.h"

const char* DeviceMainFunctionCell::cellType()
{
    return "DeviceMainFunction";
}

DeviceMainFunctionCell::~DeviceMainFunctionCell()
{
    if (_device != nullptr)
        _device->removeChangedHandler(_handler);
    if (_eventPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_cellObject->cell, _eventPressed, this);
}

void DeviceMainFunctionCell::init(KnxChannelBase* device, uint8_t deviceIndex)
{
    _device = device;
    _deviceIndex = deviceIndex;
}

void DeviceMainFunctionCell::setup()
{
    KnxChannelBase& device = *_device;
    CellObject& cellObject = *_cellObject;
    lv_label_set_text(cellObject.label, device.getNameInUTF8());
    
    _handler = [this](KnxChannelBase& channel)
    {
       channelValueChanged(channel);
    };
    device.addChangedHandler(_handler);
    _eventPressed = [](lv_event_t *e) {  ((DeviceMainFunctionCell*)lv_event_get_user_data(e))->_clickStarted = true; };
    lv_obj_add_event_cb(cellObject.cell, _eventPressed, LV_EVENT_PRESSED, this);
 
    lv_label_set_text(cellObject.label, device.getNameInUTF8());
}


void DeviceMainFunctionCell::channelValueChanged(KnxChannelBase& channel)
{
    CellObject& cellObject = *_cellObject;
    ImageLoader::loadImage(cellObject.image, channel.mainFunctionImage());

 //   lv_label_set_text(cell.value, channel.currentValueAsString().c_str());
    if (channel.mainFunctionValue())
    {
        lv_obj_set_style_img_recolor_opa(cellObject.image, 255, 0);
        lv_obj_set_style_img_recolor(cellObject.image, lv_color_make(255,255,0), 0);
    }
    else
    {
        lv_obj_set_style_img_recolor_opa(cellObject.image, 0, 0);
        lv_obj_set_style_img_recolor(cellObject.image, lv_color_make(128,128,128), 0);
    }
}

void DeviceMainFunctionCell::shortPressed()
{
    if (_clickStarted)
        handleClick(ParamTCH_CHShortPress1, ParamTCH_CHJumpToShort1);
}

void DeviceMainFunctionCell::resetPressed()
{
    _clickStarted = false;
}

void DeviceMainFunctionCell::longPressed()
{
    if (_clickStarted)
        handleClick(ParamTCH_CHLongPress1, ParamTCH_CHJumpToLong1);
}

void DeviceMainFunctionCell::handleClick(int function, int jumpToPage)
{
    // <Enumeration Text="Nichts" Value="0" Id="%ENID%" />          
    // <Enumeration Text="Hauptfunktion ausführen" Value="0" Id="%ENID%" />
    // <Enumeration Text="Detailseite aufrufen" Value="1" Id="%ENID%" />
    // <Enumeration Text="Absprung zu Seite" Value="2" Id="%ENID%" />
    switch(function)
    {
    case 0:
        logDebugP("Nichts");
        return;
    case 1:    
        logDebugP("Hauptfunktion");
        if (_device->supportMainFunctionClick())
            _device->commandMainFunctionClick();
        return;
    case 2:
        logDebugP("Detailseite");
        openknxTouchDisplayModule.showDetailDevicePage(_channelIndex, _deviceIndex);
        return;
    case 3:
        logDebugP("Absprung zu Seite %d", jumpToPage);
        openknxTouchDisplayModule.activatePage(jumpToPage);
        return;
    }
}
