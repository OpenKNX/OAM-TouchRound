#include "EmptyCell.h"
#include "CellParameterDefines.h"
#include "../Screens/CellScreen.h"
#include "../ImageLoader.h"

const char* EmptyCell::cellType()
{
    return "Empty";
}

void EmptyCell::setup()
{
    CellObject& cellObject = *_cellObject;
    lv_label_set_text(cellObject.label, "");
    ImageLoader::unloadImage(cellObject.image);
    lv_label_set_text(cellObject.value, "");
}