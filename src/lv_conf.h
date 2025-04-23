#pragma once
#define LV_CONF_H

#if LVGL_VERSION_MAJOR >= 9
#include "../lib/OFM-TouchDisplay/src/lv_conf_v9.h"
#else
#include "../lib/OFM-TouchDisplay/src/lv_conf_v8.h"
#endif