#ifndef __SCREEN_APPS_H
#define __SCREEN_APPS_H

#include <map>
#include <algorithm>

#include "screen.h"
#include "app.h"

class ScreenApps : public Screen {
	public:
		ScreenApps();
		ScreenApps(const char* title);
	
		void installApp(App &app);
		App& getCurrentApp(void);
	
		virtual void render(void);	
		virtual void onHardwareButtonPressed(bool btnA, bool btnB, bool btnC);
		virtual void onHardwareEncoderTurned(int8_t steps);
	
	private:
		int16_t m_selectedAppIndex, m_runningApp;
	
		std::vector<std::string> m_installedAppIDs;
		std::map<std::string, App> m_installedApps;
		Layer m_appLayer;
};

#endif
