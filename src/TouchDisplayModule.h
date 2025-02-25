#include "OpenKNX.h"
#include <lvgl.h>

#define EXT1_PIN 28
#define EXT2_PIN 29

#define DISPLAY_SLEEP_DELAY 10000
#define VISU_MAX_PAGE 5
class Page;

class TouchDisplayModule : public OpenKNX::Module
{
	uint8_t _channelIndex = 255; // current active channel, do not ranme, because var name is used in macros
	uint8_t _defaultPage = 0;
public:
	void loop(bool configured) override;
	void setup() override;
	void loop1(bool configured) override;
	void setup(bool configured) override;
	void processAfterStartupDelay() override;
	
	const std::string name() override;
	const std::string version() override;
	// void writeFlash() override;
	// void readFlash(const uint8_t* data, const uint16_t size) override;
	// uint16_t flashSize() override;

private:
	
	static void lv_log(const char *buf);
	static void handleGesture(lv_event_t *event);
	static void handleValues(lv_event_t *event);
	static void resetDisplayTimeout();
	static void display_pressed();
	static void loadPage(int channel);
	
	inline static lv_obj_t *currentScreen;
	inline static int currentScreenIndex = 0;

	inline static bool displayOn;
	inline static unsigned long lastPressed;
	
private:
	Page* _currentPage = nullptr;
public:
	void activePage(uint8_t channel);
	void nextPage();
	void previousPage();

	void processInputKo(GroupObject &ko) override;
};

extern TouchDisplayModule openknxTouchDisplayModule;