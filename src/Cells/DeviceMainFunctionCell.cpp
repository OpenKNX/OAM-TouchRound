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

void DeviceMainFunctionCell::init(KnxChannelBase* device)
{
    _device = device;
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
    _eventPressed = [](lv_event_t *e) { ((DeviceMainFunctionCell*) e->user_data)->_clickStarted = max(1l, millis()); };
    lv_obj_add_event_cb(cellObject.cell, _eventPressed, LV_EVENT_PRESSED, this);
    _eventReleased = [](lv_event_t *e) { ((DeviceMainFunctionCell*) e->user_data)->buttonReleased(); };
    lv_obj_add_event_cb(cellObject.cell, _eventReleased, LV_EVENT_RELEASED, this);

    lv_label_set_text(cellObject.label, device.getNameInUTF8());
    ImageLoader::loadImage(cellObject.image, device.mainFunctionImage());
}

void DeviceMainFunctionCell::loop()
{
    Cell::loop();
    if (_shortPressed)
    {
        _shortPressed = false;
        shortClicked();
    }
    if (_longPressed)
    {
        _longPressed = false;
        longPressed();
    }
}

void DeviceMainFunctionCell::channelValueChanged(KnxChannelBase& channel)
{
    CellObject& cellObject = *_cellObject;
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

void DeviceMainFunctionCell::shortClicked()
{
    handleClick(ParamTCH_CHShortPress1, ParamTCH_CHJumpToShort1);
}

void DeviceMainFunctionCell::buttonReleased()
{
    if (_clickStarted == 0)
        return;
    auto clickTime = millis() - _clickStarted;
    _clickStarted = 0;
    if (clickTime < 500)
        _shortPressed = true;
    else
        _longPressed = true;
}

void DeviceMainFunctionCell::longPressed()
{
    logErrorP("Long Press");
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
        openknxTouchDisplayModule.showDetailDevicePage();
        return;
    case 3:
        logDebugP("Absprung zu Seite %d", jumpToPage);
        openknxTouchDisplayModule.activatePage(jumpToPage);
        return;
    }
}
