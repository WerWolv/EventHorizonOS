#include "screen.h"

Renderer Screen::renderer;
NotificationCenter Screen::notificationCenter;

Screen::Screen() {
	this->renderer = Renderer();
	this->notificationCenter = NotificationCenter();
}

Screen::Screen(const char* title) : m_title(title) {
	this->renderer = Renderer();
}

void Screen::render(void) {
	renderer << this->bgLayer;
}

void Screen::drawDefaultBackground() {	
	bgLayer.drawRect(0, 0, 127, 63, false, true);
}
