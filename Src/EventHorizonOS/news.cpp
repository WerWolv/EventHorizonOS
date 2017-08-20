#include "news.h"

News::News(std::string description) : m_description(description) {
	
}

std::string News::getDescription(void) {
	return this->m_description;
}	