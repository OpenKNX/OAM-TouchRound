#pragma once
#include "Cell.h"

class DeactivatedCell : public Cell
{
    protected:
        virtual const char* cellType() override;

};