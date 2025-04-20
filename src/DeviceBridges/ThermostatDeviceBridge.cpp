#include "ThermostatDeviceBridge.h"
#include "../TouchDisplayModule.h"
#include "../ImageLoader.h"

ThermostatDeviceBridge::ThermostatDeviceBridge(DetailDevicePage& detailDevicePage)
    : ThermostatDeviceBridge(*ThermostatScreen::instance, detailDevicePage)
{

}

ThermostatDeviceBridge::ThermostatDeviceBridge(ThermostatScreen& screen, DetailDevicePage& detailDevicePage)
    : _screen(screen), _detailDevicePage(detailDevicePage)
{
}

void ThermostatDeviceBridge::setup(uint8_t _channelIndex)
{   
    lv_label_set_text(_screen.label, _channel->getNameInUTF8());
    _eventButtonUpPressed = [](lv_event_t *e) { ((ThermostatDeviceBridge*) lv_event_get_user_data(e))->buttonUpPressed(); };
    lv_obj_add_event_cb(_screen.buttonUp, _eventButtonUpPressed, LV_EVENT_CLICKED, this);
    _eventButtonDownPressed = [](lv_event_t *e) { ((ThermostatDeviceBridge*) lv_event_get_user_data(e))->buttonDownPressed(); };
    lv_obj_add_event_cb(_screen.buttonDown, _eventButtonDownPressed, LV_EVENT_CLICKED, this);  
    _eventButtonMainFunctionPressed = [](lv_event_t *e) { ((ThermostatDeviceBridge*) lv_event_get_user_data(e))->buttonMainFunctionPressed(); };
    lv_obj_add_event_cb(_screen.image, _eventButtonMainFunctionPressed, LV_EVENT_CLICKED, this);  
    
    ImageLoader::colorImage(_screen.buttonUp, openknxTouchDisplayModule.getInactiveColor());
    ImageLoader::colorImage(_screen.buttonDown, openknxTouchDisplayModule.getInactiveColor());


    mainFunctionValueChanged();
    _screen.show();
}

ThermostatDeviceBridge::~ThermostatDeviceBridge()
{
    if (_eventButtonUpPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.buttonUp, _eventButtonUpPressed, this);
    if (_eventButtonDownPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.buttonDown, _eventButtonDownPressed, this);
    if (_eventButtonMainFunctionPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.image, _eventButtonMainFunctionPressed, this);
}

void ThermostatDeviceBridge::mainFunctionValueChanged() 
{
    auto& device = *_detailDevicePage.getDevice();
    lv_label_set_text(_screen.value, device.currentValueAsString().c_str());
}


void ThermostatDeviceBridge::buttonUpPressed()
{
    if (!std::isnan(_targetTemperature))
    {
        _channel->commandTargetTemperature(this, _targetTemperature + 0.5);
    }
    else if (!std::isnan(_currentTemperature))
    {
        _channel->commandTargetTemperature(this, _currentTemperature + 0.5);
    }
}
   

void ThermostatDeviceBridge::buttonDownPressed()
{
    if (!std::isnan(_targetTemperature))
    {
        _channel->commandTargetTemperature(this, _targetTemperature - 0.5);
    }
    else if (!std::isnan(_currentTemperature))
    {
        _channel->commandTargetTemperature(this, _currentTemperature - 0.5);
    }
}


void ThermostatDeviceBridge::buttonMainFunctionPressed()
{    
    _channel->commandMainFunctionClick();
}

void ThermostatDeviceBridge::setTargetTemperature(double temperature)
{
    _targetTemperature = temperature;
}
void ThermostatDeviceBridge::setCurrentTemperature(double temperature)
{
    _currentTemperature = temperature;
    char buffer[30];
    snprintf(buffer, sizeof(buffer), "Raum: %0.1f°", temperature);
    lv_label_set_text(_screen.labelValue, buffer);
}
void ThermostatDeviceBridge::setMode(ThermostatMode mode)
{
    switch (mode)
    {
    case ThermostatMode::ThermostatModeOff:
        lv_label_set_text(_screen.labelMode, "Aus");
        ImageLoader::loadImage(_screen.image, "thermostatOff.png", true, false);
        break;
    case ThermostatMode::ThermostatModeHeating:
        lv_label_set_text(_screen.labelMode, "Heizen");
        ImageLoader::loadImage(_screen.image, "thermostatHeading.png", true, true);
        break;
    case ThermostatMode::ThermostatModeCooling:
        lv_label_set_text(_screen.labelMode, "Kühlen");
        ImageLoader::loadImage(_screen.image, "thermostatCooling.png", true, false);
        break;
    case ThermostatMode::ThermostatModeAutoHeatingCooling:
        lv_label_set_text(_screen.labelMode, "Auto");
        ImageLoader::loadImage(_screen.image, "thermostatAuto.png", true, false);
        break;
    default:
        break;
    }
}
void ThermostatDeviceBridge::setCurrentState(ThermostatCurrentState currentState)
{
    switch (currentState)
    {
    case ThermostatCurrentState::ThermostatCurrentStateOff:
        ImageLoader::colorImage(_screen.buttonUp, openknxTouchDisplayModule.getInactiveColor());
        ImageLoader::colorImage(_screen.buttonDown, openknxTouchDisplayModule.getInactiveColor());
        break;
    case ThermostatCurrentState::ThermostatCurrentStateHeating:
        ImageLoader::colorImage(_screen.buttonUp, openknxTouchDisplayModule.getActiveColor());
        ImageLoader::colorImage(_screen.buttonDown, openknxTouchDisplayModule.getInactiveColor());
        break;
    case ThermostatCurrentState::ThermostatCurrentStateCooling:
        ImageLoader::colorImage(_screen.buttonUp, openknxTouchDisplayModule.getInactiveColor());
        ImageLoader::colorImage(_screen.buttonDown, openknxTouchDisplayModule.getActiveColor());
        break;
    }
}