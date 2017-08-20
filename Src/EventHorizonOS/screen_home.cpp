#include "screen_home.h"

#include "notification.h"
#include "event_horizon.h"
#include "peripherals.h"

Layer notificationLayer;

bool notificationsShown = false;
bool deleteNotification = false;
int16_t selectedNotification = 0;

std::string newsString("");
uint16_t newsPos = 0;


ScreenHome::ScreenHome() : Screen("Home") {
	
}

ScreenHome::ScreenHome(const char* title) : Screen(title) {
}

const char* getMonthNameFromIndex(uint8_t index) {
	switch(index) {
		case 1: return "January";
		case 2: return "February";
		case 3: return "March";
		case 4: return "April";
		case 5: return "May";
		case 6: return "June";
		case 7: return "July";
		case 8: return "August";
		case 9: return "September";
		case 10: return "October";
		case 11: return "November";
		case 12: return "December";
		default: return "WAT? No month!";
	}
}

const char* getNumberEnding(uint8_t number) {
	if(number == 11 || number == 12)
		return "th";
	
	switch(number % 10) {
		case 0: return "th";
		case 1: return "st";
		case 2: return "nd";
		case 3: return "rd";
		default: return "th";
	}
}

void drawClock(Layer &layer, uint8_t xPos, uint8_t yPos, uint8_t hours, uint8_t minutes, uint8_t seconds) {
    for(uint8_t x = 0; x < 10; x++)
        for(uint8_t y = 0; y < 16; y++)
            layer.drawPoint(xPos + x + 2, yPos + y + 2, (font_clock[hours / 10][x] & 0x01 << y) >> y);

    for(uint8_t x = 0; x < 10; x++)
        for(uint8_t y = 0; y < 16; y++)
            layer.drawPoint(xPos + x + 12, yPos + y + 2, (font_clock[hours % 10][x] & 0x01 << y) >> y);
	
    for(uint8_t x = 0; x < 10; x++)
        for(uint8_t y = 0; y < 16; y++)
            layer.drawPoint(xPos + x + 32, yPos + y + 2, (font_clock[minutes / 10][x] & 0x01 << y) >> y);

    for(uint8_t x = 0; x < 10; x++)
        for(uint8_t y = 0; y < 16; y++)
            layer.drawPoint(xPos + x + 42, yPos + y + 2, (font_clock[minutes % 10][x] & 0x01 << y) >> y);

    for(uint8_t x = 0; x < 10; x++)
        for(uint8_t y = 0; y < 16; y++)
            layer.drawPoint(xPos + x + 22, yPos + y + 2, (font_clock[10 + (seconds & 0x01)][x] & 0x01 << y) >> y);
}

void drawNotification(Layer &layer, uint16_t yPos, Notification &notification) {
	layer.drawRect(3, yPos, 124, yPos + 20, false, false); 
	layer.drawLine(6, yPos, 6, yPos + 20, false);
	
	layer.drawString(notification.getTitle().c_str(), 8, yPos + 1, true, false);
	layer.drawString(notification.getDescription().c_str(), 13, yPos + 9, true, false);
}	

void drawNotificationPanel(Layer &layer, NotificationCenter &notificationCenter) {
	static double deleteAnimCnt = -M_PI/2;
		
	if(Screen::notificationCenter.getNotificationCount() == 0)
		layer.drawString("No notifications", 15, 25, true, false);	
	else {
		char notificationCnt[16];
		if(notificationCenter.getNotificationCount() > 1)
			sprintf(notificationCnt, "%0d notifications", notificationCenter.getNotificationCount());
		else
			sprintf(notificationCnt, "%0d notification", notificationCenter.getNotificationCount());
		
		layer.drawString(notificationCnt, 18, 5, true, false);
		layer.drawRect(4, 18, 6, 38, true, false);
		
		uint8_t n = 0;
		for(auto iter = notificationCenter.getNotifications().rbegin(); iter != notificationCenter.getNotifications().rend(); ++iter) {
			if(n > notificationCenter.getNotificationCount() - 1) break;
			drawNotification(layer, 18 + (22 * (n - selectedNotification)), *iter);
			n++;
		}
		
		if(deleteNotification && deleteAnimCnt < 1.6)
			deleteAnimCnt += 0.4;
		
		if(!deleteNotification && deleteAnimCnt > -1.6)
			deleteAnimCnt -= 0.4;
		
		if(deleteNotification)
			layer.drawRect(124 - ((sin(deleteAnimCnt) + 1) * 10), 18, 124, 38, true, false);
		else deleteAnimCnt = -M_PI/2;
	}

}

void drawHomeScreen(Layer &layer) {
	RTC_TimeTypeDef time = getRTCTime();
	RTC_DateTypeDef date = getRTCDate();
	char dateStr[32];
	char alignedDateStr[40];
	char secStr[2];
	static uint32_t newsAnimCnt = 0;
	char temparatureStr[6];
		
	drawClock(layer, 37, 6, time.Hours, time.Minutes, time.Seconds);
	sprintf(secStr, "%02d", time.Seconds);
	layer.drawString(secStr, 88, 13, true, true);
	
	sprintf(dateStr, "%d%s of %s", date.Date, getNumberEnding(date.Date), getMonthNameFromIndex(date.Month));
	sprintf(alignedDateStr, "%*s", 11 + std::strlen(dateStr) / 2, dateStr);
	layer.drawString(alignedDateStr, 0, 22, false, true);
	
	layer.drawLine(3, 50, 125, 50, true);
	layer.drawString(newsString.c_str() + newsPos, 2, 50, false, true); 
	
	if(newsAnimCnt++ % 16 == 0)
		newsPos++;
	
	if(newsString.begin() + newsPos - 1 == newsString.end())
		newsPos = 0;
	
	sprintf(temparatureStr, "%*d C", 5, Screen::notificationCenter.temparature);
	layer.drawString(temparatureStr, 34, 38, false, true);
	layer.drawRect(68, 40, 70, 42, false, true);

}

void ScreenHome::render() {
	static double notificationMenuAnimCnt = -M_PI/2;
	static double notificationAnimCnt = -M_PI/2;
	static bool notificationArrived = false;
	static uint16_t lastNotificationCnt = 0;
	static uint16_t notificationShownCnt = 0;
	uint16_t currNotificationCnt = notificationCenter.getNotificationCount();
	
	newsString = "                    ";
	
	for(auto iter = Screen::notificationCenter.getNews().begin(); iter != Screen::notificationCenter.getNews().end(); iter++) {
		newsString += iter->getDescription();
		newsString += "|";
	}

	this->Screen::render();
	this->renderer << notificationLayer;
	
	if(!notificationArrived) {
		notificationArrived = lastNotificationCnt < currNotificationCnt;
		notificationShownCnt = 100;
	}
	
	if(notificationsShown && notificationMenuAnimCnt < 1.6)
		notificationMenuAnimCnt += 0.2;
	
	if(!notificationsShown && notificationMenuAnimCnt > -1.6)
		notificationMenuAnimCnt -= 0.2;
	
	if(notificationShownCnt-- == 0)
		notificationArrived = false;
	
	if(notificationArrived && notificationAnimCnt < 1.6)
		notificationAnimCnt += 0.5;
	
	if(!notificationArrived && notificationAnimCnt > -1.6)
		notificationAnimCnt -= 0.5;
	
	notificationLayer.drawCircle(0, 55, (sin(notificationMenuAnimCnt) + 1) * 75, true, true);
	notificationLayer.drawRect(1, 1, 126, 62, false, false);

	bgLayer.drawCircle(127, 0, (sin(notificationAnimCnt) + 1) * 10, true, true);
	
	if(notificationArrived && notificationAnimCnt >= 1.6 && this->notificationCenter.getNotificationCount() > 0)
		bgLayer.drawString(this->notificationCenter.getNotifications().at(this->notificationCenter.getNotificationCount() - 1).getShortForm().c_str(), 115, 3, true, false);
	
	if(notificationsShown && notificationMenuAnimCnt >= 1.6) {
		drawNotificationPanel(notificationLayer, Screen::notificationCenter);
		bgLayer.drawString("X", 110, 23, true, true);
	}
	else 
		drawHomeScreen(bgLayer);
	
	bgLayer.drawRect(1, 1, 126, 62, false, false);
	bgLayer.drawRect(0, 0, 127, 63, false, true);
	bgLayer.drawRect(2, 2, 125, 61, false, true);
	
	lastNotificationCnt = currNotificationCnt;
}

void ScreenHome::onHardwareButtonPressed(bool btnA, bool btnB, bool btnC) {
	if(btnA)
		setScreen(APPS);
	if(btnB) {
		if(notificationsShown && this->notificationCenter.getNotificationCount() > 0) {
			if(!deleteNotification)
				deleteNotification = true;
			else {
				this->notificationCenter.removeNotificationAtIndex(this->notificationCenter.getNotificationCount() - 1 - selectedNotification);
				deleteNotification = false;
				if(selectedNotification > 0)
					selectedNotification--;
			}
		}
	}
	if(btnC) {
		notificationsShown = !notificationsShown;
		selectedNotification = 0;
		deleteNotification = false;
	}
}

void ScreenHome::onHardwareEncoderTurned(int8_t steps) {
	selectedNotification += steps;
	
	deleteNotification = false;
	
	if(selectedNotification < 0) selectedNotification = 0;
	if(selectedNotification > this->notificationCenter.getNotificationCount() - 1)
		selectedNotification = this->notificationCenter.getNotificationCount() - 1;
}
