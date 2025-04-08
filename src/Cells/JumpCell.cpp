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
    _eventPressed = [](lv_event_t *e) { ((JumpCell*) lv_event_get_user_data(e))->_clicked = true; };
    lv_obj_add_event_cb(cellObject.cell, _eventPressed, LV_EVENT_CLICKED, this);
  
    logDebug("JumpCell", "Setup JumpCell %d", (int) ParamTCH_CHJumpToShort1 - 1); 
    Page* page = Page::createPage(ParamTCH_CHJumpToShort1 - 1);
    logDebug("JumpCell", "Setup JumpCell %s", page->name().c_str()); 
    lv_label_set_text(cellObject.label, page->name().c_str());
    ImageLoader::loadImage(cellObject.image, page->image().c_str());
    delete page;
}

void JumpCell::loop(bool configured)
{
    Cell::loop(configured);
    if (_clicked)
    {
        _clicked = false;
        clicked();
    }
}

void JumpCell::clicked()
{
    openknxTouchDisplayModule.activatePage(ParamTCH_CHJumpToShort1);
}