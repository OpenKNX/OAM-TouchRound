#include "DeactivatedCell.h"
#include "CellParameterDefines.h"
#include "../Screens/CellScreen.h"

const char* DeactivatedCell::cellType()
{
    return "Deactivated";
}

void DeactivatedCell::setup()
{
    CellObject& cellObject = *_cellObject;
    lv_label_set_text(cellObject.label, "Deaktiviert");
    lv_img_set_src(cellObject.image, nullptr);
    lv_label_set_text(cellObject.value, "");
}