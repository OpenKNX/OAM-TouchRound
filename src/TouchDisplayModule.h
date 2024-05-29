#include "OpenKNX.h"
#include <lvgl.h>

#define EXT1_PIN 28
#define EXT2_PIN 29

#define DISPLAY_SLEEP_DELAY 10000
#define VISU_MAX_PAGE 5

class TouchDisplayModule : public OpenKNX::Module
{
public:
	void loop(bool configured) override;
	void setup(bool configured) override;
	void loop1(bool configured) override;
	void setup1(bool configured) override;
	void processAfterStartupDelay() override;
	void processInputKo(GroupObject &ko) override;

	const std::string name() override;
	const std::string version() override;
	// void writeFlash() override;
	// void readFlash(const uint8_t* data, const uint16_t size) override;
	// uint16_t flashSize() override;

private:
	enum DoorState
	{
		UNDEFINED,
		OPEN,
		CLOSED,
		AUTO
	};

	static void lv_log(const char *buf);
	static void handleGesture(lv_event_t *event);
	static void handleValues(lv_event_t *event);
	static void resetDisplayTimeout();
	static void display_pressed();
	static void setTextForChannel(int channel);
	static bool checkPageActive(int channel);
	static uint8_t getPageType(int channel);
	static void loadPage(int channel);

	inline static lv_obj_t *screenTypes[VISU_MAX_PAGE];
	inline static lv_obj_t *screenLabels[VISU_MAX_PAGE];
	inline static void (*screenInits[VISU_MAX_PAGE])(void);

	inline static lv_obj_t *currentScreen;
	inline static int currentScreenIndex = 0;

	inline static DoorState doorState;
	inline static bool displayOn;
	inline static unsigned long lastPressed;
	inline static bool isChangingValue = false;
	inline static int16_t lastValue = 0;
	inline static int16_t last2Value = 0;
};

extern TouchDisplayModule openknxTouchDisplayModule;