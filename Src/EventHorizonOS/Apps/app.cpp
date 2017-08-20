#include "app.h"

#define LNE 0x01
#define RCT 0x02
#define CIR 0x03
#define PXL 0x04
#define STR 0x05
#define CLR 0x06
#define VAR 0x07

#define PARAM(x) ((m_drawData[i + 1 + x] > 127) ?								\
					(uint8_t) *this->m_vars[m_drawData[i + 1 + x] - 128].str :	\
					m_drawData[i + 1 + x])

#define STR_PARAM(x) ((m_drawData[i + 1 + x] > 127) ?								\
						this->m_vars[m_drawData[i + 1 + x] - 128].str :	\
						 (char*) &m_drawData[i + 1 + x])
					
App::App() {
	
}

App::App(std::string name, std::string app_id, uint8_t icon[8], uint8_t* drawData, size_t length) : m_name(name), m_app_id(app_id), m_drawDataLength(length) {
	for(uint16_t i = 0; i < length; i++)
		m_drawData[i] = drawData[i];
}

void App::onOpen(void) {
	static uint8_t c;
	for(uint16_t i = 0; i < m_drawDataLength;) {
		c = 0;
		switch(m_drawData[i]) {
			case LNE:
				i += 6;
				break;
			case RCT:
				i += 7;
				break;
			case CIR:
				i += 6;
				break;
			case PXL:
				i += 4;
				break;
			case STR:
				for(; PARAM(2 + c) > 0x01; c++);			
				i += 6 + c;
				break;
			case CLR:
				i += 2;
				break;
			case VAR:
				char data[40];
				char request = PARAM(1);
				std::strcpy(data, "|Resolve|");
				std::strcat(data, this->getAppID().c_str());
				std::strcat(data, "|");
				data[this->getAppID().size() + 10] = request;
				data[this->getAppID().size() + 11] = '|';
				data[this->getAppID().size() + 12] = 0x00;

				USB::INSTANCE.sendUSBData((uint8_t*)data, this->getAppID().size() + 12);
				i += 3;
				break;
		}
	}
}



void App::render(Layer &layer) {
	for(uint16_t i = 0; i < m_drawDataLength;) {
		switch(m_drawData[i]) { 
			case LNE:
				layer.drawLine(PARAM(0), PARAM(1), PARAM(2), PARAM(3), PARAM(4) == 1);
				i += 6;
				break;
			case RCT:
				layer.drawRect(PARAM(0), PARAM(1), PARAM(2), PARAM(3), PARAM(4) == 1, PARAM(5) == 1);
				i += 7;
				break;
			case CIR:
				layer.drawCircle(PARAM(0), PARAM(1), PARAM(2), PARAM(3) == 1, PARAM(4) == 1);
				i += 6;
				break;
			case PXL:
				layer.drawPoint(PARAM(0), PARAM(1), PARAM(2) == 1);
				i += 4;
				break;
			case STR:													//TODO: Shit V
				layer.drawString(STR_PARAM(2), PARAM(0), PARAM(1), true, PARAM(std::strlen(STR_PARAM(2)) + 2) == 1);
				i += 6 + std::strlen(STR_PARAM(2));
				break;
			case CLR:
				layer.drawRect(0, 0, 127, 63, true, PARAM(0));
				i += 2;
				break;
			case VAR:
				i += 3;
				break;
		}
	}
}

void App::onDataArrived(uint8_t data[3][40]) {
	std::strcpy((this->m_vars[data[1][0] - 'A'].str), (char*) data[2]);
}

std::string App::getAppName() {
	return this->m_name;
}

std::string App::getAppID() {
	return this->m_app_id;
}
	
uint8_t* App::getIcon() {
	return this->m_icon;
}

