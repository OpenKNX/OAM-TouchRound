#include "DeactivatedCell.h"
#include "CellParameterDefines.h"
#include "../Screens/CellScreen.h"
#include "../ImageLoader.h"

const char* DeactivatedCell::cellType()
{
    return "Deactivated";
}

void DeactivatedCell::setup()
{
    CellObject& cellObject = *_cellObject;
    lv_label_set_text(cellObject.label, "Deaktiviert");
    ImageLoader::unloadImage(cellObject.image);
    lv_label_set_text(cellObject.value, "");
}