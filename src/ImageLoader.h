#pragma once
#include "lvgl.h"
#include <string>

class ImageLoader
{
    static const char driveLetter;
    static const std::string logPrefix();
public:
    static void loadImage(lv_obj_t* imageObject, std::string fileName);
    static void connectLittleFSwithLVGL();
};