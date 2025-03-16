#include "DeactivatedPage.h"

const char* DeactivatedPage::pageType()
{
    return "Deactivated";
}

void DeactivatedPage::setup()
{
    lv_label_set_text(screen.label, "");
    lv_label_set_text(screen.message, "Seite ist deaktiviert");
    lv_disp_load_scr(screen.screen);
}