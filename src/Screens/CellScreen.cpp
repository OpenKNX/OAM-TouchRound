#include "CellScreen.h"

CellScreen2* CellScreen2::instance = nullptr;


CellScreen2::CellScreen2() :
cellObject1(*this, LV_HOR_RES, LV_VER_RES / 2, CellLocation::Top),
cellObject2(*this, LV_HOR_RES, LV_VER_RES / 2, CellLocation::Bottom)
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

CellScreen3::CellScreen3() :
cellObject1(*this, LV_HOR_RES, LV_VER_RES / 2, CellLocation::Top),
cellObject2(*this, LV_HOR_RES / 2, LV_VER_RES / 2, CellLocation::BottomLeft),
cellObject3(*this, LV_HOR_RES / 2, LV_VER_RES / 2, CellLocation::BottomRight)
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


CellScreen4::CellScreen4() :
cellObject1(*this, LV_HOR_RES / 2, LV_VER_RES / 2, CellLocation::TopLeft),
cellObject2(*this, LV_HOR_RES / 2, LV_VER_RES / 2, CellLocation::TopRight),
cellObject3(*this, LV_HOR_RES / 2, LV_VER_RES / 2, CellLocation::BottomLeft), 
cellObject4(*this, LV_HOR_RES / 2, LV_VER_RES / 2, CellLocation::BottomRight)
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


CellObject::CellObject(CellScreen& cellPage, lv_coord_t width, lv_coord_t height, CellLocation cellLocation) :
_cellPage(cellPage),
_width(width),
_height(height)
{  
    bool wideCell = cellLocation == CellLocation::Top || cellLocation == CellLocation::Bottom;
    bool isTop = cellLocation == CellLocation::Top || cellLocation == CellLocation::TopLeft || cellLocation == CellLocation::TopRight;
    bool isLeft = cellLocation == CellLocation::TopLeft || cellLocation == CellLocation::BottomLeft;
    
    cell = lv_obj_create(cellPage.screen);
    lv_obj_set_size(cell, width, height);
    lv_obj_clear_flag(cell, LV_OBJ_FLAG_SCROLLABLE); 

    label = lv_label_create(cell);
    value = lv_label_create(cell);
    image = lv_img_create(cell);  
   
    if (wideCell)
    {
        lv_obj_align(value, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_text_align(value, LV_TEXT_ALIGN_CENTER, 0);
        if (isTop)
            lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);
        else
            lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
    }
    else
    {
        if (isLeft)
        {
            lv_obj_align(value, LV_ALIGN_CENTER, -10, 0);
            lv_obj_set_style_text_align(value, LV_TEXT_ALIGN_RIGHT, 0);
            if (isTop)
                lv_obj_align(label, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
            else
                lv_obj_align(label, LV_ALIGN_TOP_RIGHT, 0, 0);
        }
        else
        {
            lv_obj_align(value, LV_ALIGN_CENTER, -10, 0);
            lv_obj_set_style_text_align(value, LV_TEXT_ALIGN_LEFT, 0);
            if (isTop)
                lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, 0);
            else
                lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
        }
    }
 
    lv_obj_align(image, LV_ALIGN_CENTER,  wideCell ? 0 : isLeft ? 20 : -20, isTop ? -10 : 10);  
}

