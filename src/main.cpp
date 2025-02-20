#include <Arduino.h>
#include "OpenKNX.h"
#include "TouchDisplayModule.h"
#include "FileTransferModule.h"
//#include "UsbExchangeModule.h"
#include "FunctionBlocksModule.h"
#include "SmartHomeBridgeModule.h"
#include "Logic.h"


void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(9, openknxFileTransferModule);
  //  openknx.addModule(8, openknxUsbExchangeModule);
    openknx.addModule(7, openknxSmartHomeBridgeModule);
    openknx.addModule(1, openknxTouchDisplayModule);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxFunctionBlocksModule);
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