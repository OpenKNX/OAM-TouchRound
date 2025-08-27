#pragma once
#define LV_CONF_H

#ifndef FONT_SMALL
#define FONT_SMALL "NotoSans_Regular_16_CP_1252_ISO_8859_1_15"
#endif

#ifndef FONT_MEDIUM
#define FONT_MEDIUM "NotoSans_Regular_24_CP_1252_ISO_8859_1_15"
#endif

#ifndef FONT_LARGE
#define FONT_LARGE "NotoSans_Regular_40_CP_1252_ISO_8859_1_15"
#endif

#if LVGL_VERSION_MAJOR >= 9
#include "../lib/OFM-TouchDisplay/src/lv_conf_v9.h"
#else
#include "../lib/OFM-TouchDisplay/src/lv_conf_v8.h"
#endif