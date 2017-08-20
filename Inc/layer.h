#ifndef __LAYER_H
#define __LAYER_H

extern "C" {
	#include "stm32f4xx_hal.h"
}

#include <math.h> 
#include <string>
#include "fonts.h"

#define LAYER_WIDTH 128
#define LAYER_HEIGHT 64

#define M_PI 3.14159265358979323846

typedef struct Bitmap {
	bool pixels[128][64];
} Bitmap;

class Layer {
	public:	
		Layer();
		~Layer();
		
		Bitmap& getBitmap();
		void drawPoint(uint16_t x, uint16_t y, bool set);
		void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, bool set);
		void drawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, bool filled, bool set);
		void drawCircle(uint16_t centerX, uint16_t centerY, uint16_t radius, bool filled, bool set);
		void drawString(const char* str, uint16_t xChar, uint16_t yChar, bool wrap, bool set);
		void drawIcon8x8(uint8_t icon[8], uint8_t x, uint8_t y);
	
		void cleanScreen(void);
	
		bool isOnScreen(void);
		void setOnScreen(bool onScreen);
	
	private:
		Bitmap m_bitmap;
		bool m_onScreen;
	
};

#endif
