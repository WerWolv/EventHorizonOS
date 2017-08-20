#include "screen_error.h"

ScreenError::ScreenError() {

}

ScreenError::ScreenError(const char* title) : Screen(title) {
	
}

void ScreenError::render(void) {
	this->Screen::render();
	drawDefaultBackground();
	
	char errorStr[18];
	
	sprintf(errorStr, "Error code: 0x%04X", error_code);
	
	bgLayer.drawString("An error occured!", 11, 10, true, true);
	bgLayer.drawString(errorStr, 9, 22, true, true);
	
	bgLayer.drawString("Please restart", 18, 40, true, true);
	bgLayer.drawString("your device...", 18, 47, true, true);
}

void ScreenError::onHardwareButtonPressed(bool btnA, bool btnB, bool btnC) {
	
}

void ScreenError::onHardwareEncoderTurned(int8_t steps) {
	
}
