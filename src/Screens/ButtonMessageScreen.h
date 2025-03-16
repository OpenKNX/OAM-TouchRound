#include "ScreenWithLabel.h"

class ButtonMessageScreen : public ScreenWithLabel
{
    public:
    static ButtonMessageScreen* instance;
    lv_obj_t* message;
    lv_obj_t* button;
    lv_obj_t* buttonText;
    ButtonMessageScreen();
};