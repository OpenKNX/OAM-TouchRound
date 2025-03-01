#include "DeactivatedPage.h"

const char* DeactivatedPage::pageType()
{
    return "Deactivated";
}

void DeactivatedPage::setup()
{
    lv_label_set_text(ui_MessageLabel, "Seite ist deaktiviert");
    lv_disp_load_scr(ui_Message);
}