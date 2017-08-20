#include "layer.h"

#define clamp(n, lower, upper) ((n) < lower ? 0 : (n) > upper ? upper : (n))

Layer::Layer() {
	
}

Layer::~Layer() {
	
}

Bitmap& Layer::getBitmap() {
	return this->m_bitmap;
}

/**
  * @brief  Draw one pixel on the screen.
  * @param  x: The X coordinate on the screen.
  * @param  y: The Y coordinate on the screen.
  * @param  state: Wether the pixel should be set or reset.
  */
void Layer::drawPoint(uint16_t x, uint16_t y, bool set) {
	x = clamp(x, 0, LAYER_WIDTH - 1);
	y = clamp(y, 0, LAYER_HEIGHT - 1);

	this->m_bitmap.pixels[x][y] = set;				
}

/**
  * @brief  Draw a line on the screen using the bresenham algorithm.
  * @param  x1: The X coordinate of the start of the line.
  * @param  y1: The Y coordinate of the start of the line.
  * @param  x2: The X coordinate of the end of the line.
  * @param  y2: The Y coordinate of the end of the line.
  * @param  state: Wether the line should be set or reset.
  */
void Layer::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, bool set) {
  x1 = clamp(x1, 0, LAYER_WIDTH - 1);
  y1 = clamp(y1, 0, LAYER_HEIGHT - 1);
  x2 = clamp(x2, 0, LAYER_WIDTH - 1);
  y2 = clamp(y2, 0, LAYER_HEIGHT - 1);
	
  int16_t deltaX =  fabsf((float)(x2 - x1));					//The difference of the second x and the first x value
  int16_t deltaY = -fabsf((float)(y2 - y1));					//The difference of the second y and the first y value
  int16_t speedX = x1 < x2 ? 1 : -1;							//Determines if the x axis is the faster one
  int16_t speedY = y1 < y2 ? 1 : -1;							//Determines if the y axis is the faster one
    
  int16_t error = deltaX + deltaY;							//Calculate the error

  while(!(x1 == x2 && y1 == y2)){							//While we're not at the end position...
    this->m_bitmap.pixels[x1][y1] = set;							//Set the pixel at the current x and y value to the passed state

    if ((error * 2) > deltaY) {								//If the doubled error is greater than deltaY...
        error += deltaY;									//...add it to the error
        x1 += speedX;										//...and increment or decrement the x axis
    }	
    if ((error * 2) < deltaX) {								//If the doubled error is greater than deltaX...
        error += deltaX;                                    //...add it to the error
        y1 += speedY;                                       //...and increment or decrement the y axis
    }
  }
}    

/**
  * @brief  Draw a rectangle on the screen.
  * @param  x1: The X coordinate of the first corner.
  * @param  y1: The Y coordinate of the first corner.
  * @param  x2: The X coordinate of the second corner.
  * @param  y2: The Y coordinate of the second corner.
  * @param  filled: Wether the rectangle should be filled.
  * @param  state: Wether the line should be set or reset.
  */
void Layer::drawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, bool filled, bool set) {
    x1 = clamp(x1, 0, LAYER_WIDTH - 1);
    y1 = clamp(y1, 0, LAYER_HEIGHT - 1);
    x2 = clamp(x2, 0, LAYER_WIDTH - 1);
    y2 = clamp(y2, 0, LAYER_HEIGHT - 1);
	
    static uint16_t x, y;											//The x and y coordinates in the buffer
    if(filled) {											//If the rectangle should get filled...
        for(x = x1; x <= x2; x++)							//For each pixel between x1 and x2...
            for(y = y1; y <= y2; y++)						//For each pixel between y1 and y2...
                this->m_bitmap.pixels[x][y] = set;				//...Set it to the passed state
    } else {												//If the rectangle shouldn't get filled...
        for(x = x1; x <= x2; x++)							//For each pixel between x1 and x2...
            for(y = y1; y <= y2; y++)                       //For each pixel between y1 and y2...
                if(x == x1 || x == x2 || y == y1 || y == y2)//If the current coordinate is ether the fist or the last one...
                    this->m_bitmap.pixels[x][y] = set;			//...Set the current pixel to the passed state
    }
}


/**
  * @brief  Draw a circle on the screen.
  * @param  centerX: The X coordinate of the center of the circle.
  * @param  centerY: The Y coordinate of the center of the circle.
  * @param  radius: The radius of the circle
  * @param  angleBegin: The drawing start angle.
  * @param  angleEnd: The drawing end angle.
  * @param  state: Wether the line should be set or reset.
  */
void Layer::drawCircle(uint16_t centerX, uint16_t centerY, uint16_t radius, bool filled, bool set) {
    int16_t x = radius;
    int16_t y = 0;
    int16_t radiusError = 0;
	int16_t xChange = 1 - (radius << 1);
	int16_t yChange = 0;
	
	while (x >= y) {
		if(filled) {
			for (int16_t i = centerX - x; i <= centerX + x; i++) {
				int16_t y0 = centerY + y;
				int16_t y1 = centerY - y;
				int16_t x0 = i;

				y0 = clamp(y0, 0, LAYER_HEIGHT - 1);
				y1 = clamp(y1, 0, LAYER_HEIGHT - 1);
				x0 = clamp(x0, 0, LAYER_WIDTH -1 );
				
				this->m_bitmap.pixels[x0][y0] = set;
				this->m_bitmap.pixels[x0][y1] = set;
			}
			
			for (int16_t i = centerX - y; i <= centerX + y; i++) {
				int16_t y0 = centerY + x;
				int16_t y1 = centerY - x;
				int16_t x0 = i;

				y0 = clamp(y0, 0, LAYER_HEIGHT - 1);
				y1 = clamp(y1, 0, LAYER_HEIGHT - 1);
				x0 = clamp(x0, 0, LAYER_WIDTH -1 );

				this->m_bitmap.pixels[x0][y0] = set;
				this->m_bitmap.pixels[x0][y1] = set;
			}

			y++;
			radiusError += yChange;
			yChange += 2;
			if (((radiusError << 1) + xChange) > 0) {
				x--;
				radiusError += xChange;
				xChange += 2;
			}
		} else {
			this->m_bitmap.pixels[clamp(centerX + x, 0, LAYER_WIDTH - 1)][clamp(centerY + y, 0, LAYER_HEIGHT - 1)] = set;
			this->m_bitmap.pixels[clamp(centerX + y, 0, LAYER_WIDTH - 1)][clamp(centerY + x, 0, LAYER_HEIGHT - 1)] = set;
			this->m_bitmap.pixels[clamp(centerX - y, 0, LAYER_WIDTH - 1)][clamp(centerY + x, 0, LAYER_HEIGHT - 1)] = set;
			this->m_bitmap.pixels[clamp(centerX - x, 0, LAYER_WIDTH - 1)][clamp(centerY + y, 0, LAYER_HEIGHT - 1)] = set;
			this->m_bitmap.pixels[clamp(centerX - x, 0, LAYER_WIDTH - 1)][clamp(centerY - y, 0, LAYER_HEIGHT - 1)] = set;
			this->m_bitmap.pixels[clamp(centerX - y, 0, LAYER_WIDTH - 1)][clamp(centerY - x, 0, LAYER_HEIGHT - 1)] = set;
			this->m_bitmap.pixels[clamp(centerX + y, 0, LAYER_WIDTH - 1)][clamp(centerY - x, 0, LAYER_HEIGHT - 1)] = set;
			this->m_bitmap.pixels[clamp(centerX + x, 0, LAYER_WIDTH - 1)][clamp(centerY - y, 0, LAYER_HEIGHT - 1)] = set;
			
			if(radiusError <= 0) {
				y++;
				radiusError += 2 
				* y + 1;
			} else {
				x--;
				radiusError -= 2 * x + 1;
			}
		}
	}
}

void Layer::drawString(const char* string, uint16_t xChar, uint16_t yChar, bool wrap, bool set) {  
	char* str = (char*) string;
	for(; *str != 0x00; str++) {
		bool vowelMutation = false;

		if(*str == 'ä') {
			vowelMutation = true;
			*str = 'a';
		}
		else if(*str == 'ö') {
			vowelMutation = true;
			*str = 'o';
		}
		else if(*str == 'ü') {
			vowelMutation = true;
			*str = 'u';
		}
		
		for(int16_t x = 0; x < 5; x++) {											
			for(int16_t y = 0; y < 8; y++) {	
				if(xChar + x + 2 > 0 && xChar + x + 2 < LAYER_WIDTH && yChar + y + 2 > 0 && yChar + y + 2 < LAYER_HEIGHT) {
					if(set)
						this->m_bitmap.pixels[clamp(xChar + x + 2, 0, LAYER_WIDTH - 1)][clamp(yChar + y + 2, 0, LAYER_HEIGHT - 1)]	= ((font_small[*str - ' '][x] & 0x01 << y) >> y);
					else 
						this->m_bitmap.pixels[clamp(xChar + x + 2, 0, LAYER_WIDTH - 1)][clamp(yChar + y + 2, 0, LAYER_HEIGHT - 1)]	= ((~font_small[*str - ' '][x] & 0x01 << y) >> y);
				}
			}
		}
		
		if(vowelMutation) {
			this->drawPoint(clamp(xChar + 3, 0, LAYER_WIDTH - 1), clamp(yChar + 2, 0, LAYER_HEIGHT - 1), set);
			this->drawPoint(clamp(xChar + 5, 0, LAYER_WIDTH - 1), clamp(yChar + 2, 0, LAYER_HEIGHT - 1), set);
		}
		
		xChar += 6;	
		if(wrap) {		
			if(xChar > LAYER_WIDTH - 2) {												
				xChar = 0;																
				yChar += 7;																
			}	
		}		
	}
}

void Layer::drawIcon8x8(uint8_t icon[8], uint8_t x, uint8_t y) {
	for(uint8_t x1 = x; x1 < x + 8; x1++) 
		for(uint8_t y1 = y; y1 < y + 8; y1++) 
			this->m_bitmap.pixels[x1][y1] = (icon[y1 - y] >> (x1 - x)) & 0x01;

}

void Layer::cleanScreen(void) {
	for(uint8_t x = 0; x < LAYER_WIDTH; x++)
		for(uint8_t y = 0; y < LAYER_HEIGHT; y++)
			this->m_bitmap.pixels[x][y] = false;
}

bool Layer::isOnScreen(void) {
	return this->m_onScreen;
}

void Layer::setOnScreen(bool onScreen) {
	this->m_onScreen = onScreen;
}
