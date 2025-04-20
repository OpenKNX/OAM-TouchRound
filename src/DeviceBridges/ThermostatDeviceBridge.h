#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Thermostat/KnxChannelThermostat.h"
#include "../Screens/ThermostatScreen.h"

class ThermostatDeviceBridge : public ThermostatBridge
{
    lv_event_cb_t _eventButtonUpPressed = nullptr;
    lv_event_cb_t _eventButtonDownPressed = nullptr;
    lv_event_cb_t _eventButtonMainFunctionPressed = nullptr;
    MainFunctionChangedHandler _handler;
  
    ThermostatScreen& _screen;
    double _targetTemperature = NAN;
    double _currentTemperature = NAN;
protected:
    DetailDevicePage& _detailDevicePage;
    ThermostatDeviceBridge(ThermostatScreen& screen, DetailDevicePage& detailDevicePage);
 public:
    ThermostatDeviceBridge(DetailDevicePage& detailDevicePage);
    virtual ~ThermostatDeviceBridge() override;
    virtual void mainFunctionValueChanged() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setTargetTemperature(double temperature) override;
    virtual void setCurrentTemperature(double temperature) override;
    virtual void setMode(ThermostatMode mode) override;
    virtual void setCurrentState(ThermostatCurrentState currentState) override;

    void buttonUpPressed();
    void buttonDownPressed();
    void buttonMainFunctionPressed();
};  