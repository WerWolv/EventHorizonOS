#ifndef __SCREEN_ERROR_H
#define __SCREEN_ERROR_H

#include "screen.h"
#include "event_horizon.h"

class ScreenError : public Screen {
	public:
		ScreenError();
		ScreenError(const char* title);
	
		virtual void render(void);	
		virtual void onHardwareButtonPressed(bool btnA, bool btnB, bool btnC);
		virtual void onHardwareEncoderTurned(int8_t steps);
};

#endif
