#include "notification_center.h"

std::vector<Notification> NotificationCenter::m_notifications;
std::vector<News> NotificationCenter::m_news;

NotificationCenter::NotificationCenter() {
}

std::vector<Notification>& NotificationCenter::getNotifications(void) {
	return this->m_notifications;
}

void NotificationCenter::removeFirstNotification(void) {
	this->m_notifications.pop_back();
}

void NotificationCenter::removeNotificationAtIndex(uint8_t index) {
	if(index < this->m_notifications.size()) {
		std::vector<Notification>::iterator begin = this->m_notifications.begin();
		this->m_notifications.erase(begin + index);
	}
}

void NotificationCenter::removeAllNotifications(void) {
	this->m_notifications.clear();
}

void NotificationCenter::removeAllNews(void) {
	this->m_news.clear();
}

uint16_t NotificationCenter::getNotificationCount(void) {
	return this->m_notifications.size();
}

std::vector<News>& NotificationCenter::getNews(void) {	
	return this->m_news;
}

//TODO: Strange
void NotificationCenter::handleNotificationLED(void) {
	static uint16_t timeElapsed = 0;
	static uint16_t colorIndex;
	static uint32_t color;
	
	if(getNotificationCount() > 0) {
		if(timeElapsed % 400 < 100)
			color = getNotifications().at(colorIndex).getColor();
		else if(timeElapsed % 400 >= 100 && timeElapsed % 400 < 399)
			color = 0x000000;
		else colorIndex++;
		
		if(getLightLevel() != LIGHT_LOW)
			setNotificationLedColor(color);
		else
			setNotificationLedColor(0x000000);
		
		if(colorIndex >= getNotificationCount())
			colorIndex = 0;
	}
	else
		setNotificationLedColor(0x000000);
	
	timeElapsed++;
}


NotificationCenter& NotificationCenter::operator<<(Notification notification) {
	/*if(getNotificationCount() >= 128)
		this->m_notifications.erase(this->m_notifications.begin());*/
	
	this->m_notifications.push_back(notification);
	
	return *this;
}

NotificationCenter& NotificationCenter::operator<<(News news) {
	m_news.push_back(news);
	
	return *this;
}
