#include "DeactivatedPage.h"

const char* DeactivatedPage::pageType()
{
    return "Deactivated";
}

void DeactivatedPage::setup()
{
    lv_label_set_text(screen.label, "");
    lv_label_set_text(screen.message, "Seite ist deaktiviert");
    screen.show();
}

std::string DeactivatedPage::name()
{
    return "";
}

std::string DeactivatedPage::image()
{
    return "";
}