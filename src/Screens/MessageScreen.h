#pragma once

#include "Screens/IMessageScreen.h"
#include "ScreenWithLabel.h"

class MessageScreen : public ScreenWithLabel
                    , public IMessageScreen
{
private:
    lv_obj_t* _message;

public:

    MessageScreen();
    virtual void SetLabelText(const char* text) override;
    virtual void SetMessageText(const char* text) override;
    virtual void Show() override;
};
