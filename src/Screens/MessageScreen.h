#pragma once

#include "ScreenWithLabel.h"

class MessageScreen : public ScreenWithLabel
{
    public:
    static MessageScreen* instance;
    lv_obj_t* message;
    MessageScreen();
};