#include "ImageLoader.h"
#include "OpenKNX.h"
#include "TouchDisplayModule.h"
#include "lvgl.h"

#include "../Images/up.c"
#include "../Images/down.c"
#include "../Images/stop.c"
#include "../Images/Type10.c"
#include "../Images/Type11.c"
#include "../Images/Type20.c"
#include "../Images/Type30.c"
#include "../Images/Type31.c"
#include "../Images/Type32.c"
#include "../Images/Type50.c"
#include "../Images/Type60_0.c"
#include "../Images/Type60_1.c"
#include "../Images/Type60_2.c"
#include "../Images/Type60_3.c"
#include "../Images/Type60_4.c"
#include "../Images/Type60_5.c"
#include "../Images/Type60_9.c"
#include "../Images/Type70.c"
#include "../Images/Type71.c"
#include "../Images/Type72.c"
#include "../Images/Type73.c"
#include "../Images/Type74.c"
#include "../Images/Type75.c"
#include "../Images/Type76.c"
#include "../Images/Type80.c"
#include "../Images/Type90.c"
#include "../Images/Type91.c"
#include "../Images/Type92.c"
#include "../Images/missing_file.c"
#include "../Images/System.c"
#include "../Images/Error.c"
#include "../Images/Time.c"
#include "../Images/Date.c"
#include "../Images/DateTime.c"
#include "../Images/Bild1.c"
#include "../Images/Bild2.c"
#include "../Images/Bild3.c"



#include "LittleFS.h"

class FileHelper
{
private:
        File file;
public:
    bool open(const char *path, const char *mode) {
//        logInfo("fs_open", "Open file '%s' with mode '%s'", path, mode);
        file = LittleFS.open(path, mode);
        return file.available();
    }

    size_t readBytes(char *buf, size_t nbyte) {
//        logInfo("fs_read", "Read %zu bytes from file", nbyte);
        return file.readBytes(buf, nbyte);
    }
    bool seek(uint32_t pos, SeekMode mode) {
//       logInfo("fs_seek", "Seek to position %zu with mode %d", pos, mode);
        bool result = file.seek(pos, mode);
        if (!result) {
            logError("fs_seek", "Seek failed");
        }
        return result;
    }
    size_t position() {
        return file.position();
    }

    ~FileHelper() 
    {
//        logInfo("fs_close", "Close file");
        file.close();
    }
};

void* ImageLoader::fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode) {
    const char *flags = (mode == LV_FS_MODE_WR) ? "w" : "r";
   
    auto result = new FileHelper();
    if (!result->open(path, flags)) {
        logError("fs_open", "Open file '%s' failed", path);
        delete result;
        return nullptr; 
    }
//  logInfo("fs_open", "File '%s' opened successfully", path);
    return result;
}

lv_fs_res_t ImageLoader::fs_read(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br) {
    FileHelper *fileHelper = (FileHelper*)file_p;
    auto read = fileHelper->readBytes((char*)buf, btr);
    *br = read;
    return (*br > 0) ? LV_FS_RES_OK : LV_FS_RES_UNKNOWN;
}

lv_fs_res_t ImageLoader::fs_close(lv_fs_drv_t *drv, void *file_p) {
    FileHelper *fileHelper = (FileHelper*)file_p;
    delete fileHelper;
    return LV_FS_RES_OK;
}

lv_fs_res_t ImageLoader::fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence) {
    FileHelper *fileHelper = (FileHelper*)file_p;
    fileHelper->seek(pos, whence == LV_FS_SEEK_SET ? SeekSet : (whence == LV_FS_SEEK_CUR ? SeekCur : SeekEnd));
    return LV_FS_RES_OK;
}

lv_fs_res_t ImageLoader::fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p) {
   
    FileHelper *fileHelper = (FileHelper*)file_p;
    *pos_p = fileHelper->position();
    return LV_FS_RES_OK;
}

const char ImageLoader::driveLetter = 'L';


void ImageLoader::connectLittleFSwithLVGL() 
{
    static lv_fs_drv_t drv;
    lv_fs_drv_init(&drv);
    drv.letter = driveLetter;  // LittleFS as 'L:'
    drv.open_cb = fs_open;
    drv.read_cb = fs_read;
    drv.seek_cb = fs_seek;
    drv.close_cb = fs_close;
    drv.tell_cb = fs_tell;
    
    lv_fs_drv_register(&drv);

}


const std::string ImageLoader::logPrefix()
{
    return "ImageLoader";
}

void ImageLoader::unloadImage(lv_obj_t* imageObject)
{
    lv_img_set_src(imageObject, nullptr);
    lv_obj_add_flag(imageObject, LV_OBJ_FLAG_HIDDEN);
}

void ImageLoader::loadImage(lv_obj_t* imageObject, std::string fileName, bool useStateColor, bool state)
{
    if (fileName == "")
    {
        unloadImage(imageObject);
        return;
    }
    else if (LittleFS.exists(("/" + fileName).c_str()))
    {
        std::string filePath;
        filePath += driveLetter;
        filePath += ":/";
        filePath += fileName;
        logInfoP("Load file: %s", filePath.c_str());

        lv_img_set_src(imageObject, filePath.c_str());
    }
    else if (fileName == "missing_file.png")
    {
        lv_img_set_src(imageObject, &missing_file);
    }
    else if (fileName == "up.png")
    {
        lv_img_set_src(imageObject, &up);
    }
    else if (fileName == "down.png")
    {
        lv_img_set_src(imageObject, &down);
    }
    else if (fileName == "stop.png")
    {
        lv_img_set_src(imageObject, &stop);
    }
    else if (fileName == "Bild1.png")
    {
        lv_img_set_src(imageObject, &Bild1);
    }
    else if (fileName == "Bild2.png")
    {
        lv_img_set_src(imageObject, &Bild2);
    }
    else if (fileName == "Bild3.png")
    {
        lv_img_set_src(imageObject, &Bild3);
    }
    else if (fileName == "Type10.png")
    {
        lv_img_set_src(imageObject, &Type10);
    }
    else if (fileName == "Type11.png")
    {
        lv_img_set_src(imageObject, &Type11);
    }
    else if (fileName == "Type20.png")
    {
        lv_img_set_src(imageObject, &Type20);
    }
    else if (fileName == "Type30.png")
    {
        lv_img_set_src(imageObject, &Type30);
    }
    else if (fileName == "Type31.png")
    {
        lv_img_set_src(imageObject, &Type31);
    }
    else if (fileName == "Type32.png")
    {
        lv_img_set_src(imageObject, &Type32);
    }
    else if (fileName == "Type50.png")
    {
        lv_img_set_src(imageObject, &Type50);
    }
    else if (fileName == "Type60_0.png")
    {
        lv_img_set_src(imageObject, &Type60_0);
    }
    else if (fileName == "Type60_1.png")
    {
        lv_img_set_src(imageObject, &Type60_1);
    }
    else if (fileName == "Type60_2.png")
    {
        lv_img_set_src(imageObject, &Type60_2);
    }
    else if (fileName == "Type60_3.png")
    {
        lv_img_set_src(imageObject, &Type60_3);
    }
    else if (fileName == "Type60_4.png")
    {
        lv_img_set_src(imageObject, &Type60_4);
    }
    else if (fileName == "Type60_5.png")
    {
        lv_img_set_src(imageObject, &Type60_5);
    }
    else if (fileName == "Type60_9.png")
    {
        lv_img_set_src(imageObject, &Type60_9);
    }
    else if (fileName == "Type70.png")
    {
        lv_img_set_src(imageObject, &Type70);
    }
    else if (fileName == "Type71.png")
    {
        lv_img_set_src(imageObject, &Type71);
    }
    else if (fileName == "Type72.png")
    {
        lv_img_set_src(imageObject, &Type72);
    }
    else if (fileName == "Type73.png")
    {
        lv_img_set_src(imageObject, &Type73);
    }
    else if (fileName == "Type74.png")
    {
        lv_img_set_src(imageObject, &Type74);
    }
    else if (fileName == "Type75.png")
    {
        lv_img_set_src(imageObject, &Type75);
    }
    else if (fileName == "Type76.png")
    {
        lv_img_set_src(imageObject, &Type76);
    }
    else if (fileName == "Type80.png")
    {
        lv_img_set_src(imageObject, &Type80);
    }
    else if (fileName == "Type90.png")
    {
        lv_img_set_src(imageObject, &Type90);
    }
    else if (fileName == "Type91.png")
    {
        lv_img_set_src(imageObject, &Type91);
    }
    else if (fileName == "Type92.png")
    {
        lv_img_set_src(imageObject, &Type92);
    }
    else if (fileName == "System.png")
    {
        lv_img_set_src(imageObject, &System);
    }
    else if (fileName == "Error.png")
    {
        lv_img_set_src(imageObject, &ErrorImg);
    }
    else if (fileName == "Time.png")
    {
        lv_img_set_src(imageObject, &Time);
    }
    else if (fileName == "Date.png")
    {
        lv_img_set_src(imageObject, &Date);
    }
    else if (fileName == "DateTime.png")
    {
        lv_img_set_src(imageObject, &DateTime);
    }
    else
    {
        logError("loadImage", "File not found: %s", fileName.c_str());
        lv_img_set_src(imageObject, &missing_file);
    }
    colorState(imageObject, useStateColor, state);
    lv_obj_clear_flag(imageObject, LV_OBJ_FLAG_HIDDEN);
} 

void ImageLoader::colorState(lv_obj_t* imageObject, bool useStateColor, bool state)
{
    if (useStateColor)
    {
        if (state)
        {
            lv_obj_set_style_img_recolor_opa(imageObject, 255, 0);
            lv_obj_set_style_img_recolor(imageObject, openknxTouchDisplayModule.getActiveColor(), 0);
        }
        else
        {
            lv_obj_set_style_img_recolor_opa(imageObject, 255, 0);
            lv_obj_set_style_img_recolor(imageObject, openknxTouchDisplayModule.getInactiveColor(), 0);
        }
    }
    else
    {
        lv_obj_set_style_img_recolor_opa(imageObject, 0, 0);
    }
}