#ifndef __NEWS_H
#define __NEWS_H

#include <string>

class News {
	public:
		News(std::string description);
	
		std::string getDescription(void);
	
	private:
		std::string m_description;
	
};

#endif
