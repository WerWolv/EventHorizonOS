#ifndef __APP_H
#define __APP_H

#include <string>
#include <map>

#include "usb.h"
#include "layer.h"

typedef struct USBData{
	char str[40];
} USBData;

class App {
	public:
		App();
		App(std::string name, std::string app_id, uint8_t icon[8], uint8_t* drawData, size_t length);
			
		void onOpen(void);
		void render(Layer &layer);
		
		std::string getAppName();
		std::string getAppID();
	
		uint8_t* getIcon();
	
		void onDataArrived(uint8_t data[3][40]);
	
	private:
		std::string m_name, m_app_id;
		uint8_t m_drawData[512];
		size_t m_drawDataLength;
		uint8_t m_icon[8];
	
		std::map<char, USBData> m_vars;
	
		char* getParamOrVar(uint8_t par);
};

#endif
