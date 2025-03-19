#include "JumpCell.h"
#include "CellParameterDefines.h"
#include "../Screens/CellScreen.h"

const char* JumpCell::cellType()
{
    return "Jump";
}


void JumpCell::setup()
{
    CellObject& cellObject = *_cellObject;
   
    std::string pageName = "Seite ";
    pageName += std::to_string(ParamTCH_ChannelJumpToShort1);
    lv_label_set_text(cellObject.label, pageName.c_str());
    lv_img_set_src(cellObject.image, nullptr);
}