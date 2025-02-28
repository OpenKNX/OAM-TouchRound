#pragma once
#include "Page.h"


class DeactivatedPage : public Page
{
protected:
    virtual const char* pageType() override;
    virtual void setup() override;
};