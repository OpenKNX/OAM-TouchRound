#pragma once

#include "Screens/IJalousieScreen.h"
#include "RolladenScreen.h"

class JalousieScreen: public RolladenScreen
                   , public IJalousieScreen
{
private:
    lv_obj_t* _sliderAux;
    std::function<void(uint8_t)> _onAuxPercentageChangeCompleted;

    static void OnAuxPercentageChangeCompleted(lv_event_t* e);

public:
    JalousieScreen();

    virtual void SetAuxPercentageValue(uint8_t value) override;
    virtual uint8_t GetAuxPercentageValue() const override;
    virtual void RegisterAuxPercentageChangeCompleted(std::function<void(uint8_t)> callback) override;
};
