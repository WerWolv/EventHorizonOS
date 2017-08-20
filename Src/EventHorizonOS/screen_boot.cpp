#include "screen_boot.h"

#include "event_horizon.h"

ScreenBoot::ScreenBoot() {
	
}

ScreenBoot::ScreenBoot(const char* title) : Screen(title) {
	
}

void ScreenBoot::render(void) {
	static double outerPlanetCnt = 0;
	static double innerPlanetCnt = 0;
	static double initCnt = -M_PI / 2;
	
	this->Screen::render();	
	
	outerPlanetCnt += 0.015;
	innerPlanetCnt += 0.03;
	
	bgLayer.drawRect(0, 0, 127, 63, false, true);
	bgLayer.drawString("EventHorizonOS", 20, 5, true, true);

	bgLayer.drawRect(59, 29, 69, 39, true, true);
	bgLayer.drawCircle(59, 29, 4, true, false);
	bgLayer.drawCircle(59, 39, 4, true, false);
	bgLayer.drawCircle(69, 29, 4, true, false);
	bgLayer.drawCircle(69, 39, 4, true, false);
	bgLayer.drawPoint(64, 34, false);


	bgLayer.drawCircle(64, 34, 12, false, true);
	bgLayer.drawCircle(64, 34, 8, false, true);
	
	bgLayer.drawCircle((sin(outerPlanetCnt)) * 11.3 + 64, (cos(outerPlanetCnt)) * 11.3 + 34, 2, true, true);
	bgLayer.drawCircle((sin(innerPlanetCnt)) * 7.2 + 64, (cos(innerPlanetCnt)) * 7.2 + 34, 2, true, true);
		
	bgLayer.drawString("Waiting for USB...", 11, 50, true, true);
	
	if(initialized) {
		initCnt += 0.05;
		if(initCnt >= M_PI/2)
			bgLayer.drawRect(0, 0, 127, 63, true, true);
		else
			bgLayer.drawCircle(64, 34, (sin(initCnt) + 1) * 40, true, true);
	}	

	if(initCnt >= M_PI*1.5)
		setScreen(HOME);
}

void ScreenBoot::onHardwareButtonPressed(bool btnA, bool btnB, bool btnC) {
	
}

void ScreenBoot::onHardwareEncoderTurned(int8_t steps) {
	
}
