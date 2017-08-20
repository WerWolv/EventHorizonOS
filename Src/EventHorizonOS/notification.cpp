#include "notification.h"

Notification::Notification(std::string title, std::string description, std::string shortForm, uint32_t color) : m_title(title), m_description(description), m_shortForm(shortForm), m_color(color) {

}

std::string Notification::getTitle(void) {
	return this->m_title;
}

std::string Notification::getDescription(void) {
	return this->m_description;
}

std::string Notification::getShortForm(void) {
	return this->m_shortForm;
}

uint32_t Notification::getColor(void) {
	return this->m_color;
}
