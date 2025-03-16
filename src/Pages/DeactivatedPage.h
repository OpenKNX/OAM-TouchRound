#pragma once
#include "Page.h"
#include "../Screens/MessageScreen.h"


class DeactivatedPage : public Page
{
    MessageScreen& screen = *MessageScreen::instance;
protected:
    virtual const char* pageType() override;
    virtual void setup() override;
};