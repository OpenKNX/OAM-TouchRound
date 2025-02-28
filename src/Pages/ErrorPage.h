#pragma once

#include "OpenKNX.h"
#include "Page.h"

class ErrorPage : public Page
{
    const char* _message;
public:
    virtual const char* pageType() override;
    virtual void setup() override;
    virtual void setMessage(const char* message);
};