#include <Arduino.h>
#include "OpenKNX.h"
#include "TouchDisplayModule.h"

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(1, openknxTouchDisplayModule);
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