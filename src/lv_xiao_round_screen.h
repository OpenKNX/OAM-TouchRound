/* display and touch driver for XIAO round screen */

#include <Arduino.h>
#include <lvgl.h>
#include <SPI.h>
#include <Wire.h>

// uncomment a library for display driver
#define USE_TFT_ESPI_LIBRARY
// #define USE_ARDUINO_GFX_LIBRARY

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240
#define LVGL_BUFF_SIZE 10 // Number of rows

#define CHSC6X_I2C_ID 0x2e
#define CHSC6X_MAX_POINTS_NUM 1
#define CHSC6X_READ_POINT_LEN 5

#ifdef BUILD_SEEED_RP2040
#define TOUCH_INT D7

#ifndef XIAO_BL
#define XIAO_BL D6
#endif
#define XIAO_CS D1
#define XIAO_DC D3

// Use Wire:
// SDA: 6
// SCL: 7

uint8_t screen_rotation = 3;
#else
#define TOUCH_INT 15 //1 //D7

#ifndef XIAO_BL
#define XIAO_BL 1 //0 //D6
#endif
#define XIAO_CS 5 //28 //27 //D1
#define XIAO_DC 6 //29 //D3

// Use Wire1:
// SDA: 26
// SCL: 27

uint8_t screen_rotation = 2;
#endif

/* display driver : use TFT_eSPI or Arduino_GFX */
#if defined(USE_TFT_ESPI_LIBRARY) && defined(USE_ARDUINO_GFX_LIBRARY)
#error "More than one graphics library is defined."
#elif defined(USE_TFT_ESPI_LIBRARY)
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT);
#elif defined(USE_ARDUINO_GFX_LIBRARY)
#include <Arduino_GFX_Library.h>
#define SPI_FREQ 20000000 // SPI bus frequency: 20Mhz
#if defined(CONFIG_IDF_TARGET_ESP32S3) || defined(CONFIG_IDF_TARGET_ESP32C3)
Arduino_DataBus *bus = new Arduino_ESP32SPI(XIAO_DC, XIAO_CS, SCK, MOSI, MISO, FSPI);
#elif defined(ARDUINO_Seeed_XIAO_nRF52840_Sense) || defined(ARDUINO_Seeed_XIAO_nRF52840)
Arduino_DataBus *bus = new Arduino_NRFXSPI(XIAO_DC, XIAO_CS, SCK, MOSI, MISO);
#elif defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE) || defined(ARDUINO_SEEED_XIAO_NRF52840)
Arduino_DataBus *bus = new Arduino_mbedSPI(XIAO_DC, XIAO_CS);
#elif defined(ARDUINO_SEEED_XIAO_RP2040)
Arduino_DataBus *bus = new Arduino_RPiPicoSPI(XIAO_DC, XIAO_CS, SCK, MOSI, MISO, spi0);
#else
Arduino_DataBus *bus = new Arduino_HWSPI(XIAO_DC, XIAO_CS);
#endif
Arduino_GFX *gfx = new Arduino_GC9A01(bus, -1, screen_rotation, true);
#else
#error "Please define a graphics library for display."
#endif

void xiao_disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * color_p)
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );
#if defined(USE_TFT_ESPI_LIBRARY)
    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )color_p, w * h, true );
    tft.endWrite();
#elif defined(USE_ARDUINO_GFX_LIBRARY)
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif
    lv_disp_flush_ready( disp );
}

void xiao_disp_init(void)
{
#if defined(XIAO_BL)
    pinMode(XIAO_BL, OUTPUT); //Turn on screen backlight
    digitalWrite(XIAO_BL, HIGH);
#endif

#if defined(USE_TFT_ESPI_LIBRARY)
    tft.begin();
    tft.setRotation( screen_rotation );
    tft.fillScreen(TFT_BLACK);
#elif defined(USE_ARDUINO_GFX_LIBRARY)
    gfx->begin(SPI_FREQ);
    gfx->fillScreen(BLACK);
#endif
}



void lv_xiao_disp_init(void) 
{
    logError("lv_xiao_disp_init", "lv_xiao_disp_init");
    xiao_disp_init();


    logError("lv_xiao_disp_init", "lv_display_create");
   
    lv_display_t * disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    logError("lv_xiao_disp_init", "lv_display_set_flush_cb");
    lv_display_set_flush_cb(disp, xiao_disp_flush);
    logError("lv_xiao_disp_init", "lv_display_set_buffers");

    int colorSize = lv_color_format_get_size(lv_display_get_color_format(disp));
    int drawBufSize = SCREEN_HEIGHT * SCREEN_WIDTH * colorSize;
    static void* buf0 = new byte[drawBufSize];
    static void* buf1 = new byte[drawBufSize];
    lv_display_set_buffers(disp, buf0, buf1, drawBufSize, LV_DISPLAY_RENDER_MODE_PARTIAL);
    logError("lv_xiao_disp_init", "finished");
}



/* touch driver : chsc6x */

bool chsc6x_is_pressed(void)
{
    if(digitalRead(TOUCH_INT) != LOW) {
        delay(3);
        if(digitalRead(TOUCH_INT) != LOW)
        return false;
    }
    return true;
}

void chsc6x_convert_xy(uint8_t *x, uint8_t *y)
{
    uint8_t x_tmp = *x, y_tmp = *y, _end = 0;
    for(int i=1; i<=screen_rotation; i++){
        x_tmp = *x;
        y_tmp = *y;
        _end = (i % 2) ? SCREEN_WIDTH : SCREEN_HEIGHT;
        *x = y_tmp;
        *y = _end - x_tmp;
    }
}

void chsc6x_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    uint8_t temp[CHSC6X_READ_POINT_LEN] = {0};
#ifdef BUILD_SEEED_RP2040
    uint8_t read_len = Wire.requestFrom(CHSC6X_I2C_ID, CHSC6X_READ_POINT_LEN);
#else
    uint8_t read_len = Wire1.requestFrom(CHSC6X_I2C_ID, CHSC6X_READ_POINT_LEN);
#endif
    if(read_len == CHSC6X_READ_POINT_LEN){
#ifdef BUILD_SEEED_RP2040
        Wire.readBytes(temp, read_len);
#else
        Wire1.readBytes(temp, read_len);
#endif
        if (temp[0] == 0x01) {
        chsc6x_convert_xy(&temp[2], &temp[4]);
        *x = temp[2];
        *y = temp[4];
        }
        else
        {
            *x = 0;
            *y = 0;
        }
    }
}

void chsc6x_read(lv_indev_t * indev, lv_indev_data_t * data)
{
    lv_coord_t touchX, touchY;
    if( !chsc6x_is_pressed() )
    {
        data->state = LV_INDEV_STATE_RELEASED;
    } else {
        data->state = LV_INDEV_STATE_PRESSED;
        chsc6x_get_xy(&touchX, &touchY);
        /*Set the coordinates*/
        if (touchX >= SCREEN_WIDTH) touchX = SCREEN_WIDTH - 1;
        if (touchY >= SCREEN_HEIGHT) touchY = SCREEN_HEIGHT - 1;
        data->point.x = touchX;
        data->point.y = touchY;
    }
}

void lv_xiao_touch_init(void)
{
    pinMode(TOUCH_INT, INPUT_PULLUP);
#ifdef BUILD_SEEED_RP2040
    Wire.begin(); // Turn on the IIC bus for touch driver
#else
    Wire1.begin(); // Turn on the IIC bus for touch driver
#endif
    /*Initialize the touch driver for lvgl*/
    // static lv_indev_drv_t indev_drv;
    // lv_indev_drv_init(&indev_drv);
    // indev_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_drv.read_cb = chsc6x_read;
    // lv_indev_drv_register(&indev_drv);
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, chsc6x_read);
}