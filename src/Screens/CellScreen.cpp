#include "CellScreen.h"

#include "ImageLoader.h"

void CellScreen::show() 
{
    Screen::show();
}

CellScreen2* CellScreen2::instance = nullptr;


CellScreen2::CellScreen2() :
cellObject1(*this, LV_HOR_RES, LV_VER_RES / 2, CellLocation::Top),
cellObject2(*this, LV_HOR_RES, LV_VER_RES / 2, CellLocation::Bottom)
{
    cellObject1.SetPlacement(LV_ALIGN_TOP_LEFT, 0, 0);
    cellObject2.SetPlacement(LV_ALIGN_TOP_LEFT, 0, LV_VER_RES / 2);
}

ICellObject& CellScreen2::getCell(uint8_t index)
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
    cellObject1.SetPlacement(LV_ALIGN_TOP_LEFT, 0, 0);
    cellObject2.SetPlacement(LV_ALIGN_TOP_LEFT, 0, LV_VER_RES / 2);
    cellObject3.SetPlacement(LV_ALIGN_TOP_LEFT, LV_HOR_RES / 2, LV_VER_RES / 2);
}

ICellObject& CellScreen3::getCell(uint8_t index)
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
    cellObject1.SetPlacement(LV_ALIGN_TOP_LEFT, 0, 0);
    cellObject2.SetPlacement(LV_ALIGN_TOP_LEFT, LV_HOR_RES / 2, 0);
    cellObject3.SetPlacement(LV_ALIGN_TOP_LEFT, 0, LV_VER_RES / 2);
    cellObject4.SetPlacement(LV_ALIGN_TOP_LEFT, LV_HOR_RES / 2, LV_VER_RES / 2);
}

ICellObject& CellScreen4::getCell(uint8_t index)
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
    
    _cell = lv_obj_create(cellPage.screen);
    lv_obj_set_size(_cell, width, height);
    lv_obj_set_style_bg_opa(_cell, LV_OPA_TRANSP, 0);
    lv_obj_clear_flag(_cell, LV_OBJ_FLAG_SCROLLABLE);

    _label = lv_label_create(_cell);
    _value = lv_label_create(_cell);
    _image = lv_img_create(_cell);
    lv_obj_add_event_cb(_cell, OnPressed, LV_EVENT_PRESSED, this);
    lv_obj_add_event_cb(_cell, OnClicked, LV_EVENT_CLICKED, this);
   
    if (wideCell)
    {
        lv_obj_align(_value, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_text_align(_value, LV_TEXT_ALIGN_CENTER, 0);
        if (isTop)
            lv_obj_align(_label, LV_ALIGN_BOTTOM_MID, 0, 0);
        else
            lv_obj_align(_label, LV_ALIGN_TOP_MID, 0, 0);
        
        lv_obj_set_style_border_side(_cell, isTop ? LV_BORDER_SIDE_BOTTOM : LV_BORDER_SIDE_TOP , LV_PART_MAIN);
    }
    else
    {
        if (isLeft)
        {
            // left side
            lv_obj_align(_value, LV_ALIGN_CENTER, 10, 0);
            lv_obj_set_style_text_align(_value, LV_TEXT_ALIGN_RIGHT, 0);
            if (isTop)
            {
                lv_obj_align(_label, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
                lv_obj_set_style_border_side(_cell, (lv_border_side_t) (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT) , LV_PART_MAIN);
            }
            else
            {
                lv_obj_align(_label, LV_ALIGN_TOP_RIGHT, 0, 0);
                lv_obj_set_style_border_side(_cell, (lv_border_side_t) (LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_RIGHT) , LV_PART_MAIN);
            }
        }
        else
        {
            // right side
            lv_obj_align(_value, LV_ALIGN_CENTER, -10, 0);
            lv_obj_set_style_text_align(_value, LV_TEXT_ALIGN_LEFT, 0);
            if (isTop)
            {
                lv_obj_align(_label, LV_ALIGN_BOTTOM_LEFT, 0, 0);
                lv_obj_set_style_border_side(_cell, (lv_border_side_t) (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT) , LV_PART_MAIN);
            }
            else
            {
                lv_obj_align(_label, LV_ALIGN_TOP_LEFT, 0, 0);
                lv_obj_set_style_border_side(_cell, (lv_border_side_t) (LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT) , LV_PART_MAIN);
            }
        }
    }
 
    lv_obj_align(_image, LV_ALIGN_CENTER,  wideCell ? 0 : isLeft ? 20 : -20, isTop ? -10 : 10);
}

void CellObject::OnPressed(lv_event_t* e)
{
    auto* self = static_cast<CellObject*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onPressed)
        return;
    self->_onPressed();
}

void CellObject::OnClicked(lv_event_t* e)
{
    auto* self = static_cast<CellObject*>(lv_event_get_user_data(e));
    if (self == nullptr || !self->_onClicked)
        return;
    self->_onClicked();
}

void CellObject::SetPlacement(lv_align_t align, lv_coord_t x, lv_coord_t y)
{
    lv_obj_set_align(_cell, align);
    lv_obj_set_x(_cell, x);
    lv_obj_set_y(_cell, y);
}

void CellObject::SetLabelText(const char* text)
{
    lv_label_set_text(_label, text);
}

void CellObject::SetValueText(const char* text)
{
    lv_label_set_text(_value, text);
}

void CellObject::SetImage(const char* imageFile, bool allowRecolor, bool active)
{
    ImageLoader::loadImage(_image, imageFile, allowRecolor, active);
}

void CellObject::ClearImage()
{
    ImageLoader::unloadImage(_image);
}

void CellObject::SetImageState(bool active)
{
    ImageLoader::colorState(_image, true, active);
}

void CellObject::RegisterPressed(std::function<void()> callback)
{
    _onPressed = callback;
}

void CellObject::RegisterClicked(std::function<void()> callback)
{
    _onClicked = callback;
}

