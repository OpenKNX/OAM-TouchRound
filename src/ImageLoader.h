#pragma once
#include "lvgl.h"
#include <string>
#include "KnxChannelBase.h"

class ImageLoader
{
    static const char driveLetter;
    static const std::string logPrefix();
    static void* fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode);
    static lv_fs_res_t fs_read(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br);
    static lv_fs_res_t fs_close(lv_fs_drv_t *drv, void *file_p);
    static lv_fs_res_t fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence);
    static lv_fs_res_t fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p);
public:
    static void loadImage(lv_obj_t* imageObject, std::string imageFile, bool useStateColor = false, bool state = false);
    static void unloadImage(lv_obj_t* imageObject);
    static void colorState(lv_obj_t* imageObject, bool useStateColor, bool state);
    static void connectLittleFSwithLVGL();
};