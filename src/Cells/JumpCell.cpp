#include "JumpCell.h"
#include "CellParameterDefines.h"
#include "../Screens/CellScreen.h"
#include "../TouchDisplayModule.h"
#include "../Pages/Page.h"
#include "../ImageLoader.h"

const char* JumpCell::cellType()
{
    return "Jump";
}

JumpCell::~JumpCell()
{
    if (_eventPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_cellObject->cell, _eventPressed, this);
}

void JumpCell::setup()
{
    CellObject& cellObject = *_cellObject;
    _eventPressed = [](lv_event_t *e) { ((JumpCell*) e->user_data)->_clicked = true; };
    lv_obj_add_event_cb(cellObject.cell, _eventPressed, LV_EVENT_CLICKED, this);
  
    Page* page = Page::createPage(ParamTCH_ChannelJumpToShort1 - 1);
    lv_label_set_text(cellObject.label, page->name().c_str());
    ImageLoader::loadImage(cellObject.image, page->image().c_str());
    delete page;
}

void JumpCell::loop()
{
    Cell::loop();
    if (_clicked)
    {
        _clicked = false;
        clicked();
    }
}

void JumpCell::clicked()
{
    openknxTouchDisplayModule.activatePage(ParamTCH_ChannelJumpToShort1);
}