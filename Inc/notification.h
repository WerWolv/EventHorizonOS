#ifndef __NOTIFICATION_H
#define __NOTIFICATION_H

#include <string>

extern "C" {
	#include "stm32f4xx_hal.h"
}

class Notification {
	public:	
		Notification(std::string title, std::string description, std::string shortForm, uint32_t color);
	
		std::string getTitle(void);
		std::string getDescription(void);
		std::string getShortForm(void);
		uint32_t getColor(void);

		std::string m_title, m_description, m_shortForm;
		uint32_t m_color;
	
};

#endif
