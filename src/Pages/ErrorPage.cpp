#include "ErrorPage.h"
#include "ui.h"

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