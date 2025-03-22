#pragma once
#include "Cell.h"

class EmptyCell : public Cell
{
    protected:
        virtual const char* cellType() override;
        virtual void setup() override;

};