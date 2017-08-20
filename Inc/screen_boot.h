#ifndef __SCREEN_BOOT
#define __SCREEN_BOOT

#include "screen.h"

class ScreenBoot : public Screen {
	public:
		ScreenBoot();
		ScreenBoot(const char* title);
	
		virtual void render(void);	
		virtual void onHardwareButtonPressed(bool btnA, bool btnB, bool btnC);
		virtual void onHardwareEncoderTurned(int8_t steps);
	
};

#endif
