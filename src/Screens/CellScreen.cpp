#include "CellScreen.h"

CellScreen2* CellScreen2::instance = nullptr;

void CellScreen2::init()
{
    instance = new CellScreen2();
}

CellScreen2::CellScreen2() :
cellObject1(*this, LV_HOR_RES, LV_VER_RES / 2),
cellObject2(*this, LV_HOR_RES, LV_VER_RES / 2)
{
    lv_obj_set_align(cellObject1.cell, LV_ALIGN_TOP_LEFT);
    lv_obj_set_x(cellObject1.cell, 0);
    lv_obj_set_y(cellObject1.cell, 0);
  
    lv_obj_set_align(cellObject2.cell, LV_ALIGN_TOP_LEFT);
    lv_obj_set_x(cellObject2.cell, 0);
    lv_obj_set_y(cellObject2.cell, LV_VER_RES / 2);
}

CellObject& CellScreen2::getCell(uint8_t index)
{
    switch (index)
    {
    case 0:
        return cellObject1;
    case 1:
        return cellObject2;
    default:
        return cellObject1;
    }
}

CellScreen3* CellScreen3::instance = nullptr;

void CellScreen3::init()
{
    instance = new CellScreen3();
}

CellScreen3::CellScreen3() :
cellObject1(*this, LV_HOR_RES, LV_VER_RES / 2),
cellObject2(*this, LV_HOR_RES / 2, LV_VER_RES / 2),
cellObject3(*this, LV_HOR_RES / 2, LV_VER_RES / 2)
{
    lv_obj_set_align(cellObject1.cell, LV_ALIGN_TOP_LEFT);
    lv_obj_set_x(cellObject1.cell, 0);
    lv_obj_set_y(cellObject1.cell, 0);
  
    lv_obj_set_align(cellObject2.cell, LV_ALIGN_TOP_LEFT);
    lv_obj_set_x(cellObject2.cell, 0);
    lv_obj_set_y(cellObject2.cell, LV_VER_RES / 2);
  
    lv_obj_set_align(cellObject3.cell, LV_ALIGN_TOP_LEFT);
    lv_obj_set_x(cellObject3.cell, LV_HOR_RES / 2);
    lv_obj_set_y(cellObject3.cell, LV_VER_RES / 2);
}

CellObject& CellScreen3::getCell(uint8_t index)
{
    switch (index)
    {
    case 0:
        return cellObject1;
    case 1:
        return cellObject2;
    case 2:
        return cellObject3;
    default:
        return cellObject1;
    }
}

CellScreen4* CellScreen4::instance = nullptr;

void CellScreen4::init()
{
    instance = new CellScreen4();
}

CellScreen4::CellScreen4() :
cellObject1(*this, LV_HOR_RES / 2, LV_VER_RES / 2),
cellObject2(*this, LV_HOR_RES / 2, LV_VER_RES / 2),
cellObject3(*this, LV_HOR_RES / 2, LV_VER_RES / 2), 
cellObject4(*this, LV_HOR_RES / 2, LV_VER_RES / 2)
{
    lv_obj_set_align(cellObject1.cell, LV_ALIGN_TOP_LEFT);
    lv_obj_set_x(cellObject1.cell, 0);
    lv_obj_set_y(cellObject1.cell, 0);
  
    lv_obj_set_align(cellObject2.cell, LV_ALIGN_TOP_LEFT);
    lv_obj_set_x(cellObject2.cell, LV_HOR_RES / 2);
    lv_obj_set_y(cellObject2.cell, 0);
  
    lv_obj_set_align(cellObject3.cell, LV_ALIGN_TOP_LEFT);
    lv_obj_set_x(cellObject3.cell, 0);
    lv_obj_set_y(cellObject3.cell, LV_VER_RES / 2);
  
    lv_obj_set_align(cellObject4.cell, LV_ALIGN_TOP_LEFT);
    lv_obj_set_x(cellObject4.cell, LV_HOR_RES / 2);
    lv_obj_set_y(cellObject4.cell, LV_VER_RES / 2);
}

CellObject& CellScreen4::getCell(uint8_t index)
{
    switch (index)
    {
    case 0:
        return cellObject1;
    case 1:
        return cellObject2;
    case 2:
        return cellObject3;
    case 3:
        return cellObject4;
    default:
        return cellObject1;
    }
}

CellObject::CellObject(CellScreen& cellPage, lv_coord_t width, lv_coord_t height) :
_cellPage(cellPage),
_width(width),
_height(height)
{
    cell = lv_obj_create(cellPage.screen);
    lv_obj_set_size(cell, width, height);
    lv_obj_clear_flag(cell, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(cell, lv_color_make(0, 255, 0), LV_PART_MAIN);
}

