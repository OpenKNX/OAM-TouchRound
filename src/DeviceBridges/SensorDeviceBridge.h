#pragma once
#include "../Pages/DetailDevicePage.h"
#include "Sensor/KnxChannelSensor.h"
#include "../Screens/AlarmScreen.h"

class SensorDeviceBridge : public SensorBridge
{
    DetailDevicePage& _detailDevicePage;
    AlarmScreen& _screen = *AlarmScreen::instance;
public:
    SensorDeviceBridge(DetailDevicePage& detailDevicePage);
    virtual ~SensorDeviceBridge() override;
    virtual void setup(uint8_t _channelIndex) override;
    virtual void setDetected(bool detected) override;
};  