#pragma once

#include "Cell.h"

class JumpCell : public Cell
{
protected:
    virtual const char* cellType() override;
    virtual void setup() override;

};