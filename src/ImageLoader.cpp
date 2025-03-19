#include "ImageLoader.h"
#include "OpenKNX.h"
#include "./Images/lamp-outline.c"
#include "./Images/light-switch-off.c"
#include "./Images/power-socket-eu.c"


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

static void* fs_open(_lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode) {
    const char *flags = (mode == LV_FS_MODE_WR) ? "w" : "r";
   
    auto result = new FileHelper();
    if (!result->open(path, flags)) {
        logError("fs_open", "Open file '%s' failed", path);
        delete result;
        return nullptr;  // Fehler beim Öffnen der Datei
    }
    return result;
}

static lv_fs_res_t fs_read(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br) {
    FileHelper *fileHelper = (FileHelper*)file_p;
    auto read = fileHelper->readBytes((char*)buf, btr);
    *br = read;
    return (*br > 0) ? LV_FS_RES_OK : LV_FS_RES_UNKNOWN;
}

static lv_fs_res_t fs_close(lv_fs_drv_t *drv, void *file_p) {
    FileHelper *fileHelper = (FileHelper*)file_p;
    delete fileHelper;
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence) {
    FileHelper *fileHelper = (FileHelper*)file_p;
    fileHelper->seek(pos, whence == LV_FS_SEEK_SET ? SeekSet : (whence == LV_FS_SEEK_CUR ? SeekCur : SeekEnd));
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p) {
   
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
    // <Enumeration Value="0"  Id="%ENID%" Text="Deaktiviert"  />
    // <Enumeration Value="10" Id="%ENID%" Text="Ein-/Ausschaltbares Gerät" Icon="light-switch-off" />
    // <Enumeration Value="11" Id="%ENID%" Text="Steckdose" Icon="power-socket-eu" />
    // <Enumeration Value="20" Id="%ENID%" Text="Lampe" Icon="lamp-outline"   />
    // <Enumeration Value="30" Id="%ENID%" Text="Jalousie" Icon="window-shutter" />
    // <Enumeration Value="31" Id="%ENID%" Text="Rolladen" Icon="roller-shade-closed" />
    // <Enumeration Value="32" Id="%ENID%" Text="Markise" Icon="storefront-outline" />
    // <Enumeration Value="50" Id="%ENID%" Text="Thermostat" Icon="thermostat" />
    // <Enumeration Value="60" Id="%ENID%" Text="Anzeige" Icon="card-text-outline" />
    // <Enumeration Value="70" Id="%ENID%" Text="Kontakt" Icon="electric-switch"/>
    // <Enumeration Value="71" Id="%ENID%" Text="Bewegungsmelder" Icon="walk" />
    // <Enumeration Value="72" Id="%ENID%" Text="Präsensmelder" Icon="human-male-female"/>
    // <Enumeration Value="73" Id="%ENID%" Text="Leckmelder" Icon="water-alert-outline" />
    // <Enumeration Value="74" Id="%ENID%" Text="Rauchmelder" Icon="smoke" />
    // <Enumeration Value="75" Id="%ENID%" Text="Kohlendioxidmelder (CO2)" Icon="molecule-co2"  />
    // <Enumeration Value="76" Id="%ENID%" Text="Kohlenmonoxidmelder (CO)" Icon="molecule-co" />
    // <Enumeration Value="80" Id="%ENID%" Text="Lüfter" Icon="fan" />
    // <Enumeration Value="90" Id="%ENID%" Text="Fenster" Icon="window-closed-variant" />
    // <Enumeration Value="91" Id="%ENID%" Text="Tür" Icon="door" />
    // <Enumeration Value="92" Id="%ENID%" Text="Garagentor" Icon="garage-open-variant" />
    // if (fileName == "Type10.png")
    // {
    //     lv_img_set_src(imageObject, &light_switch_off);
    // }
    // else if (fileName == "Type11.png")
    // {
    //     lv_img_set_src(imageObject, &power_socket_eu);
    // }
    // else if (fileName == "Type20.png")
    // {
    //     lv_img_set_src(imageObject, &lamp_outline);
    // }
    // else
    {
        std::string filePath;
        filePath += driveLetter;
        filePath += ":/";
        filePath += fileName;
        logInfoP("Load file: %s", filePath.c_str());
        lv_img_set_src(imageObject, filePath.c_str());
    }
}