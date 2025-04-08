#pragma once

#include "OpenKNX.h"
#include "Page.h"
#include "../Screens/ButtonMessageScreen.h"

class ProgButtonPage : public Page
{

    lv_event_cb_t _eventButtonPressed = nullptr;
    ButtonMessageScreen& _screen = *ButtonMessageScreen::instance;
    bool _progMode = false;
    void buttonClicked();
    void updateButtonState();
public:
    ~ProgButtonPage();
    virtual const char* pageType() override;
    virtual void loop(bool configured) override;
    virtual void setup() override;
    virtual std::string name() override;
    virtual std::string image() override;
};