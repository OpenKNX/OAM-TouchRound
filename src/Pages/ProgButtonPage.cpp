#include "ProgButtonPage.h"
#include "OpenKNX.h"

const char* ProgButtonPage::pageType()
{
    return "ProgButton";
}

void ProgButtonPage::buttonClicked()
{
    knx.progMode(!knx.progMode());
}


ProgButtonPage::~ProgButtonPage()
{
    if (_eventButtonPressed != nullptr)
        lv_obj_remove_event_cb_with_user_data(_screen.button, _eventButtonPressed, this);
}


void ProgButtonPage::loop(bool configured)
{
    if (_progMode != knx.progMode())
    {
        _progMode = knx.progMode();
        updateButtonState();
    }
}

void ProgButtonPage::updateButtonState()
{
    if (_progMode)
    {
        lv_obj_add_state(_screen.button, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(_screen.button, LV_STATE_CHECKED);
    }
}

void ProgButtonPage::setup()
{
    auto label = openknx.info.humanIndividualAddress();
    if (label == "15.15.255")
        label = "Keine Adresse";
    lv_label_set_text(_screen.label, label.c_str());
    
    if (knx.configured())
    {
        lv_label_set_text(_screen.message, "OpenKNX Touch Round");
    }
    else
    {
        lv_label_set_text(_screen.message, "OpenKNX Touch Round\n\nBitte übertragen Sie die\nETS Applikation");
    }

    lv_label_set_text(_screen.buttonText, "Programmier Modus");
  
    _eventButtonPressed = [](lv_event_t *e) { ((ProgButtonPage*) lv_event_get_user_data(e))->buttonClicked(); };
    lv_obj_add_event_cb(_screen.button, _eventButtonPressed, LV_EVENT_CLICKED, this);
 
    _progMode = knx.progMode();
    updateButtonState();
    _screen.show();
}

std::string ProgButtonPage::name()
{
    return "System";
}

std::string ProgButtonPage::image()
{
    return "System.png";
}

