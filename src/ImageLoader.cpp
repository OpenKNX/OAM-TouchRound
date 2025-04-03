#include "ImageLoader.h"
#include "OpenKNX.h"
#include "../Images/Type10.c"
#include "../Images/Type11.c"
#include "../Images/Type20.c"
#include "../Images/Type30.c"
#include "../Images/Type31.c"
#include "../Images/Type32.c"
#include "../Images/Type50.c"
#include "../Images/Type60.c"
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
#include "../Images/Clock.c"
#include "../Images/Time.c"
#include "../Images/Date.c"
#include "../Images/DateTime.c"

#include "lvgl.h"
#include "LittleFS.h"

class FileHelper
{
private:
    File file;
public:
    bool open(const char *path, const char *mode) {
        file = LittleFS.open(path, mode);
        return file.available();
    }

    size_t readBytes(char *buf, size_t nbyte) {
        return file.readBytes(buf, nbyte);
    }
    bool seek(uint32_t pos, SeekMode mode) {
        return file.seek(pos, mode);
    }
    size_t position() {
        return file.position();
    }

    ~FileHelper() 
    {
        file.close();
    }
};

void* ImageLoader::fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode) {
    const char *flags = (mode == LV_FS_MODE_WR) ? "w" : "r";
   
    auto result = new FileHelper();
    if (!result->open(path, flags)) {
        logError("fs_open", "Open file '%s' failed", path);
        delete result;
        return nullptr;  // Fehler beim Öffnen der Datei
    }
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
    logDebug("fs_tell", "Position %d", (int) *pos_p);
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

void ImageLoader::loadImage(lv_obj_t* imageObject,  std::string fileName)
{
    if (fileName == "")
    {
        lv_img_set_src(imageObject, nullptr);
        return;
    }
    // else if (LittleFS.exists(("/" + fileName).c_str()))
    // {
    //     std::string filePath;
    //     filePath += driveLetter;
    //     filePath += ":/";
    //     filePath += fileName;
    //     logInfoP("Load file: %s", filePath.c_str());

    //     lv_img_set_src(imageObject, filePath.c_str());
    // }
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
    else if (fileName == "Type60.png")
    {
        lv_img_set_src(imageObject, &Type60);
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
    else if (fileName == "Clock.png")
    {
        lv_img_set_src(imageObject, &Clock);
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
}