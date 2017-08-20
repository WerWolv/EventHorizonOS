#include "screen_apps.h"

#include "event_horizon.h"

App noApp(NULL, NULL, NULL, NULL, 0);

ScreenApps::ScreenApps() {
	m_selectedAppIndex = 0;
	m_runningApp = -1;
}

ScreenApps::ScreenApps(const char* title) : Screen(title) {
	m_selectedAppIndex = 0;
	m_runningApp = -1;
}

void ScreenApps::installApp(App &app) {
	if(std::find(this->m_installedAppIDs.begin(), this->m_installedAppIDs.end(), app.getAppID()) == this->m_installedAppIDs.end())
		this->m_installedAppIDs.push_back(app.getAppID());
	
	this->m_installedApps[app.getAppID()] = app;
	
	if(m_runningApp >= 0)
		if(m_installedApps[m_installedAppIDs[m_runningApp]].getAppID() == app.getAppID())
			this->m_runningApp = -1;
}

App& ScreenApps::getCurrentApp() {
	return m_runningApp >= 0 ? m_installedApps[m_installedAppIDs[m_runningApp]] : noApp;
}

void ScreenApps::render(void) {
	char nameStr[32], alignedNameStr[40];
	
	this->Screen::render();
	Screen::renderer << this->m_appLayer;
	
	this->drawDefaultBackground();
		
	if(m_runningApp >= 0) {
		if(m_runningApp < m_installedApps.size())
			m_installedApps[m_installedAppIDs[m_runningApp]].render(this->bgLayer);
	}
	else {
		for(uint8_t i = 0; i < 5; i++)
			for(uint8_t j = 0; j < 2; j++)
				if(i + j * 5 >= m_installedApps.size()) break;
				else
					this->bgLayer.drawRect(11 + (22 * i), 5 + (22 * j), 27 + (22 * i), 21 + (22 * j), false, true);
					
		if(m_installedApps.size() != 0)
			this->bgLayer.drawRect(9 + (22 * (m_selectedAppIndex % 5)), 3 + (22 * (m_selectedAppIndex / 5)), 29 + (22 * (m_selectedAppIndex % 5)), 23 + (22 * (m_selectedAppIndex / 5)), false, true);
		
		this->bgLayer.drawLine(0, 48, 127, 48, true);
	
		if(m_installedApps.size() > 0) {
			sprintf(nameStr, "%s", m_installedApps[m_installedAppIDs[m_selectedAppIndex]].getAppName().c_str());
			sprintf(alignedNameStr, "%*s", 11 + std::strlen(nameStr) / 2, nameStr);
			this->bgLayer.drawString(alignedNameStr, 0, 50, false, true);
		}
	}	
}

void ScreenApps::onHardwareButtonPressed(bool btnA, bool btnB, bool btnC) {
	if(btnA) {
		if(m_runningApp == -1)
			setScreen(HOME);
		else
			m_runningApp = -1;
	}
	
	if(btnB) {
	}
	
	if(btnC) {
		if(this->m_selectedAppIndex >= 0 && this->m_selectedAppIndex < this->m_installedApps.size()) {
			this->m_runningApp = this->m_selectedAppIndex;
			m_installedApps[m_installedAppIDs[m_runningApp]].onOpen();
		}
	}
}

void ScreenApps::onHardwareEncoderTurned(int8_t steps) {
	m_selectedAppIndex += steps;
	
	if(m_selectedAppIndex < 0) m_selectedAppIndex = 0;
	if(m_selectedAppIndex > m_installedApps.size() - 1) m_selectedAppIndex = m_installedApps.size() - 1;
}
