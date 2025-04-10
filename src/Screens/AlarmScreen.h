#pragma once

#include "MainFunctionScreen.h"

class AlarmScreen : public MainFunctionScreen
{
public:
    static AlarmScreen* instance;
    AlarmScreen();
};
