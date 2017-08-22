#include "usb.h"

#include <string>
#include <vector>
#include <cstdlib>

#include "screen.h"
#include "notification.h"
#include "app.h"
#include "event_horizon.h"

//Notification|Title|Description|ShortForm|Color

USB USB::INSTANCE = USB();

std::vector<std::string> split(std::string str, std::string sep) {
    char *cstr = const_cast<char*>(str.c_str());
    char *current;

    std::vector<std::string> arr;
    current = std::strtok(cstr, sep.c_str());

    while (current != NULL){
        arr.push_back(current);
        current = std::strtok(NULL, sep.c_str());
    }

    return arr;
}

uint8_t getNumberFromString(std::string s) {
    uint8_t number;
    number = (s.at(0) - '0') * 10;
    number += s.at(1) - '0';

    return number;
}

void USB::sendUSBData(uint8_t data[], uint16_t length) {
	CDC_Transmit_FS(data, length);
}

void USB::onUSBDataReceived(uint8_t *data, uint32_t *length) {
	std::string usbData((const char*)data);
	std::vector<std::string> tokens = split(usbData, "|");

	if(tokens[0].find("Notification") != std::string::npos) {

		Screen::notificationCenter << Notification(tokens[1].c_str(), tokens[2].c_str(), tokens[3].c_str(), std::strtoul(tokens[4].c_str(), NULL, 16));
	}
	else if(tokens[0].find("News") != std::string::npos) {
		News n(tokens[1]);
		Screen::notificationCenter << n;
	}
	else if(tokens[0].find("Time") != std::string::npos) {
		setRTCTime(std::strtoul(tokens[1].c_str(), NULL, 10), std::strtoul(tokens[2].c_str(), NULL, 10), std::strtoul(tokens[3].c_str(), NULL, 10));
		setRTCDate(std::strtoul(tokens[4].c_str(), NULL, 10), std::strtoul(tokens[5].c_str(), NULL, 10), std::strtoul(tokens[6].c_str(), NULL, 10), std::strtoul(tokens[7].c_str(), NULL, 10));
	}
	else if(tokens[0].find("Temp") != std::string::npos)
		Screen::notificationCenter.temparature = std::strtoul(tokens[1].c_str(), NULL, 10);
	else if(tokens[0].find("Init") != std::string::npos)
		initialized = true;
	else if(tokens[0].find("App") != std::string::npos) {

		uint8_t index = 0;
		uint16_t characterIndex = 0;

		uint8_t infos[4][40];
		uint8_t icon_data[8];
		uint8_t draw_data[512];

		/*
			Data format, offset = 4
			covfefe?|len, icon_data|name|app_id|draw_data
			^ [0] Unknown
			^ [1] uint16_t    len
			      uint8_t     icon_data[8]
			^ [2] std::string name
			^ [3] std::string app_id
			^ [4] uint8_t     draw_data[0...512]
			      Any following '|' separator will be ignored and added to draw_data instead

		*/
		for (uint16_t c = 4; c < *length; c++) {
			if (index < 4) {
				if (data[c] == '|') {
					characterIndex = 0;
					index++;
					continue;
				}
				if (characterIndex < 40)
					infos[index][characterIndex] = data[c];
			} else if(characterIndex < 512) {
				// index 4: read draw data
				draw_data[characterIndex] = data[c];
			}

			characterIndex++;
		}

		std::memcpy(&icon_data[0], &infos[1][2], 8);

		App *app = new App(
			std::string((const char*)&infos[2][0]),
			std::string((const char*)&infos[3][0]),
			icon_data,
			draw_data,
			(size_t)(infos[1][0] << 8) | infos[1][1]
		);
		installApp(*app);
	}
	else if(tokens[0].find("Var") != std::string::npos) {
		uint8_t data[3][40];
		std::memcpy(&data[0][0], tokens[1].c_str(), 40);
		std::memcpy(&data[1][0], tokens[2].c_str(), 40);
		std::memcpy(&data[2][0], tokens[3].c_str(), 40);

		getCurrentApp().onDataArrived(data);
	}
	else if(tokens[0].find("Clear") != std::string::npos) {
		if(tokens[1].find("News") != std::string::npos)
			Screen::notificationCenter.removeAllNews();
		else if(tokens[1].find("Notifications") != std::string::npos)
			Screen::notificationCenter.removeAllNotifications();
	}
}
