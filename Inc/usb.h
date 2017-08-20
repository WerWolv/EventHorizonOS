#ifndef __USB_H
#define __USB_H

extern "C" {
	#include "usbd_cdc_if.h"
}

//[][]
class USB {
	public:
		static USB INSTANCE;
	
		void sendUSBData(uint8_t data[], uint16_t length);
		void onUSBDataReceived(uint8_t *data, uint32_t *length);
};

#endif
