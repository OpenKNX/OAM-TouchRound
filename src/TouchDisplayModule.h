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
	
	static void lv_log(const char *buf);
	//bool isTouched();
	void handleGesture(lv_event_t *event);
	void touched(lv_event_t *event);
	void addGlobalEvents(lv_obj_t* sreen);

	void resetDisplayTimeout();
	void display_pressed();
	static void loadPage(int channel);
	
	
private:
	Page* _currentPage = nullptr;
public:
	void activePage(uint8_t channel, bool displayOn = true);
	void display(bool on);
	void nextPage();
	void previousPage();
	void showErrorPage(const char* message);

	void processInputKo(GroupObject &ko) override;
	bool processCommand(const std::string cmd, bool diagnoseKo) override;
	void showHelp() override;
#
};

extern TouchDisplayModule openknxTouchDisplayModule;