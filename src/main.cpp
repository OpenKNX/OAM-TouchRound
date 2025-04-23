#include <Arduino.h>
#include "OpenKNX.h"
#include "FileTransferModule.h"
#include "UsbExchangeModule.h"
#include "FunctionBlocksModule.h"
#include "SmartHomeBridgeModule.h"
#include "TouchDisplayModule.h"
#include "Logic.h"
#include "SensorModule.h"
#include "SensorDevices.h"
#include "lv_xiao_round_screen.h"


bool touchIsPressed()
{
    return chsc6x_is_pressed();
}

void displayInit()
{
    lv_xiao_disp_init();
}

void touchInit()
{
    lv_xiao_touch_init();
}

void backgroundLight(bool on)
{
    digitalWrite(XIAO_BL, on ? HIGH : LOW);
}

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(9, openknxFileTransferModule);
    openknx.addModule(8, openknxUsbExchangeModule);
    openknx.addModule(7, openknxSmartHomeBridgeModule);
    openknx.addModule(1, openknxTouchDisplayModule);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxFunctionBlocksModule);
    openknx.addModule(3, openknxSensorModule);
    openknx.addModule(4, openknxSensorDevicesModule);
    openknx.setup();
}

void loop()
{
    openknx.loop();
}

#ifdef OPENKNX_DUALCORE
void setup1()
{
    openknx.setup1();
}

void loop1()
{
    openknx.loop1();
}
#endif