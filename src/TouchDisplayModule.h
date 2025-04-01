#include "OpenKNX.h"
#include <lvgl.h>

#define EXT1_PIN 28
#define EXT2_PIN 29

#define DISPLAY_SLEEP_DELAY 10000
#define VISU_MAX_PAGE 5
class Page;

class TouchDisplayModule : public OpenKNX::Module
{
	uint8_t _channelIndex = 255; // current active channel, do not rename, because var name is used in macros
	uint8_t _defaultPage = 0;
	uint16_t _displayTimeoutMs = 0;
	uint16_t _pageTimeout = 0;
	unsigned long _lastTimeoutReset = 0;
	bool _displayOn = false;
	lv_obj_t* _displayOffRectangle = nullptr;
	uint8_t _theme = 0;
	bool _detailDevicePageActive = false;
	unsigned long _waitForEnablePageWhichWasRequested = 0;
public:
	void loop(bool configured) override;
	void setup() override;
	void loop1(bool configured) override;
	void setup(bool configured) override;
	
	const std::string name() override;
	const std::string version() override;
	// void writeFlash() override;
	// void readFlash(const uint8_t* data, const uint16_t size) override;
	// uint16_t flashSize() override;

private:
	
	static void interruptTouchLeft();
	static void interruptTouchRight();

	static void lv_log(const char *buf);
	void handleGesture(lv_event_t *event);
	void touched(lv_event_t *event);
	void showFirstPage();

	void resetDisplayTimeout();
	void display_pressed();
	bool pageEnabled(uint8_t page);
	void checkPageEnabledChanged();
	
	inline volatile static bool _touchLeftPressed = false;
	inline volatile static bool _touchRightPressed = false;

public:
	void activatePage(uint8_t channel, bool displayOn = true);
	void display(bool on);
	void nextPage();
	void previousPage();
	void showErrorPage(const char* message);
	void showProgButtonPage();
	void showDetailDevicePage();
	void showMainFunctionDevicePage();

	void processInputKo(GroupObject &ko) override;
	bool processCommand(const std::string cmd, bool diagnoseKo) override;
	void showHelp() override;
	void updateTheme();
	void setTheme(uint8_t theme);

};


extern TouchDisplayModule openknxTouchDisplayModule;