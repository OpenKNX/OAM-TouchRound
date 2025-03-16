#pragma once

#include "OpenKNX.h"
#include "Page.h"
#include "../Screens/MessageScreen.h"

class ErrorPage : public Page
{
    MessageScreen& message = *MessageScreen::instance;
    const char* _message;
public:
    virtual const char* pageType() override;
    virtual void setup() override;
    virtual void setMessage(const char* message);
};