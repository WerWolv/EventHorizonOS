#include "event_horizon.h"

#include "screen.h"
#include "screen_boot.h"
#include "screen_error.h"
#include "screen_home.h"
#include "screen_apps.h"

#include "renderer.h"
#include "layer.h"

#include <string>

ScreenBoot screenBoot("Boot");
ScreenError screenError("Error");
ScreenHome screenHome("Home");
ScreenApps screenApps("Apps");

Screen *currScreen;


uint16_t error_code;
bool running = false;
bool initialized = false;


void setScreen(EScreen screen) {
	switch(screen) {
		case BOOT: currScreen = &screenBoot; break;
		case HOME: currScreen = &screenHome; break;
		case ERR: currScreen = &screenError; break;
		case APPS: currScreen = &screenApps; break;
	}
}

void installApp(App &app) {
	screenApps.installApp(app);
}

App& getCurrentApp(void) {
	return screenApps.getCurrentApp();
}

void onHardwareButtonPressed(bool btnA, bool btnB, bool btnC) {	
	if(currScreen != NULL)
		currScreen->onHardwareButtonPressed(btnA, btnB, btnC);
}

void onHardwareEncoderTurned(int8_t steps) {
	if(currScreen != NULL)
		currScreen->onHardwareEncoderTurned(steps);
}

void onUSBDataReceived(uint8_t *data, uint32_t *length) {
	USB::INSTANCE.onUSBDataReceived(data, length);
}

void EventHorizon::init_os(void) {
	running = true;
	error_code = 0x0000;
	setScreen(BOOT);
			
	addOnButtonPressedCallback(&onHardwareButtonPressed);
	addOnEncoderTurnedCallback(&onHardwareEncoderTurned);
	addOnUSBReceivedCallback(&onUSBDataReceived);
	
	lcdInit();
}

void EventHorizon::start_os(void) {		
	
	currScreen->render();
	Screen::renderer.flush();
	Screen::renderer.clr_layers();
	//Screen::notificationCenter.handleNotificationLED();

	if(error_code != 0x0000)
		setScreen(ERR);
}

void EventHorizon::error_handler(uint16_t errorCode) {
	error_code = errorCode;
	setScreen(ERR);
	
	start_os();
}
