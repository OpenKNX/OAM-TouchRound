#include "ErrorPage.h"

const char* ErrorPage::pageType()
{
    return "Error";
}

void ErrorPage::setMessage(const char* message)
{
    _message = message;
}

void ErrorPage::setup()
{
    errorInSetup("Fehler", _message.c_str());
}

std::string ErrorPage::name()
{
    return "Fehler";
}

std::string ErrorPage::image()
{
    return "Error";
}
