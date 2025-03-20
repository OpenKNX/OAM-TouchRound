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
    errorInSetup(_message);
}

std::string ErrorPage::name()
{
    return "Fehler";
}

std::string ErrorPage::image()
{
    return "Error";
}
