#include "TouchDisplayScreenFactory.h"

#include "Screens/AlarmScreen.h"
#include "Screens/ButtonMessageScreen.h"
#include "Screens/CellScreen.h"
#include "Screens/DateTimeScreen.h"
#include "Screens/DimmerScreen.h"
#include "Screens/DoorWindowScreen.h"
#include "Screens/FanScreen.h"
#include "Screens/IMessageScreen.h"
#include "Screens/IMainFunctionScreen.h"
#include "Screens/IDateTimeScreen.h"
#include "Screens/IDimmerScreen.h"
#include "Screens/IDoorWindowScreen.h"
#include "Screens/IFanScreen.h"
#include "Screens/IJalousieScreen.h"
#include "Screens/ILockScreen.h"
#include "Screens/IMediaScreen.h"
#include "Screens/IRGBScreen.h"
#include "Screens/IRolladenScreen.h"
#include "Screens/ISceneScreen.h"
#include "Screens/ISwitchScreen.h"
#include "Screens/IThermostatScreen.h"
#include "Screens/JalousieScreen.h"
#include "Screens/LockScreen.h"
#include "Screens/MainFunctionScreen.h"
#include "Screens/MediaScreen.h"
#include "Screens/MessageScreen.h"
#include "Screens/RGBScreen.h"
#include "Screens/RolladenScreen.h"
#include "Screens/SceneScreen.h"
#include "Screens/SwitchScreen.h"
#include "Screens/ThermostatScreen.h"
#include "Screens/CellScreen.h"
#include "Screens/CellScreenFactory.h"
#include "IScreenNavigation.h"
#include "ScreenNavigation.h"

namespace
{
class DefaultTouchDisplayScreenFactory final : public TouchDisplayScreenFactory
{
public:
    void createScreens() override
    {
        IScreenNavigation::instance = new ScreenNavigation();
        IMessageScreen::instance = new MessageScreen();
        IMainFunctionScreen::instance = new MainFunctionScreen();
        IDateTimeScreen::instance = new DateTimeScreen();
        CellScreen2::instance = new CellScreen2();
        CellScreen3::instance = new CellScreen3();
        CellScreen4::instance = new CellScreen4();
        ICellScreenFactory::instance = new CellScreenFactory();
        ISwitchScreen::instance = new SwitchScreen();
        IDimmerScreen::instance = new DimmerScreen();
        IButtonMessageScreen::instance = new ButtonMessageScreen();
        IAlarmScreen::instance = new AlarmScreen();
        IRolladenScreen::instance = new RolladenScreen();
        IJalousieScreen::instance = new JalousieScreen();
        IFanScreen::instance = new FanScreen();
        IRGBScreen::instance = new RGBScreen();
        IDoorWindowScreen::instance = new DoorWindowScreen();
        ILockScreen::instance = new LockScreen();
        ISceneScreen::instance = new SceneScreen();
        IThermostatScreen::instance = new ThermostatScreen();
        IMediaScreen::instance = new MediaScreen();
    }

    void setBackgroundColor(uint8_t red, uint8_t green, uint8_t blue) override
    {
        Screen::setBackgroundColor(lv_color_make(red, green, blue));
    }

    void removeBackgroundColor() override
    {
        Screen::removeBackgroundColor();
    }
};

DefaultTouchDisplayScreenFactory factory;
}

TouchDisplayScreenFactory& touchDisplayScreenFactory()
{
    return factory;
}
