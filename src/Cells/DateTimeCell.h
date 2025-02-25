#pragma once
#include "Cell.h"

class DateTimeCell : public Cell
{
    protected:
        virtual const char* cellType() override;
};