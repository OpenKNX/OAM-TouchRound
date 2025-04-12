#include "EmptyCell.h"
#include "CellParameterDefines.h"
#include "../Screens/CellScreen.h"

const char* EmptyCell::cellType()
{
    return "Empty";
}

void EmptyCell::setup()
{
    CellObject& cellObject = *_cellObject;
    lv_label_set_text(cellObject.label, "");
    lv_img_set_src(cellObject.image, nullptr);
    lv_label_set_text(cellObject.value, "");
}