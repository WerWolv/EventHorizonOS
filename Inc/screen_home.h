#ifndef __SCREEN_HOME
#define __SCREEN_HOME

#include "screen.h"

#include <string>

class ScreenHome : public Screen {
	public:
		ScreenHome();
		ScreenHome(const char* title);
	
		virtual void render(void);
		virtual void onHardwareButtonPressed(bool btnA, bool btnB, bool btnC);
		virtual void onHardwareEncoderTurned(int8_t steps);	
};

#endif
