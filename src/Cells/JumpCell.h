#pragma once

#include "Cell.h"

class JumpCell : public Cell
{
    lv_event_cb_t _eventPressed = nullptr;
    bool _clicked = false;
private:
    void clicked();

protected:
    ~JumpCell();
    virtual const char* cellType() override;
    virtual void setup() override;
    virtual void loop() override;

};