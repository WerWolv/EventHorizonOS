#ifndef DISPLAY_H
#define DISPLAY_H

#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define LCD_WIDTH   128										//The screens width in pixel
#define LCD_HEIGHT  64										//The screens height in pixel
#define LCD_PAGES   8										//The number of pages of the screen

#define LCD_CHAR_WIDTH 6									//The width of a character with spacing
#define LCD_CHAR_HEIGHT 7									//The height of a character with spacing


#define LCD_PIN_CS GPIO_PIN_8								//The LCD Chip Select Pin
#define LCD_PIN_RS GPIO_PIN_9								//The LCD Reset Pin
#define LCD_PIN_A0 GPIO_PIN_10								//The LCD address Pin
#define LCD_PIN_WR GPIO_PIN_11								//The LCD Write Pin
#define LCD_PIN_RD GPIO_PIN_12								//The LCD Read Pin

#define LCD_CONFIG_CONTRAST_LOW  0xA2						//Command for low contrast
#define LCD_CONFIG_CONTRAST_HIGH 0xA3						//Command for high contrast

#define LCD_CONFIG_MIRRORED_ON   0xA1						//Command to mirror the display
#define LCD_CONFIG_MIRRORED_OFF  0xA0						//Command to not mirror the display

#define LCD_CONFIG_ZEROPT_TOP    0xC8						//Command to set the zero point to the top left corner
#define LCD_CONFIG_ZEROPT_BOTTOM 0xC0						//Command to set the zero point to the bottom right corner

#define LCD_CONFIG_DISPLAY_ON    0xAF						//Command to turn the display on
#define LCD_CONFIG_DISPLAY_OFF   0xAE						//Command to turn the display off

#define LCD_CONFIG_INVERTED_ON   0xA7						//Command to enable inverted colors
#define LCD_CONFIG_INVERTED_OFF  0xA6						//Command to disable inverted colors

#define LCD_CONFIG_BOOSTER_RATIO(ratio) (0xF8 | ratio)
#define LCD_CONFIG_VOLTAGE_BIAS(bias)	(0xA2 | bias)
#define LCD_CONFIG_VOLTAGE_RES(res) (0x20 | res)

#define LCD_CONFIG_START_LINE(line) (0x40 | line)			//Macro to set the starting line


#define LCD_CMD_COLUMN_ADDR_H(h) (0x10 | h)					//Macro to set the high byte of the collumn address
#define LCD_CMD_COLUMN_ADDR_L(l) (0x00 | l)					//Macro to set the low byte of the collumn address

#define LCD_CMD_PAGE_ADDR(page)  (0xB0 | page)				//Macro to set the page address
#define LCD_CMD_RESET             0xE2						//Command to reset the display

/*- Function Prototypes -*/

/*-Initializes the Display-*/
extern void lcdInit(void);

/*-Sends a data byte to the LCD-*/
extern void lcdSendDat(uint8_t data);

/*-Sends a command byte to the LCD-*/
extern void lcdSendCom(uint8_t data);

/*-Draws the frame buffer to the screen-*/
extern void lcdSendBuffer(bool buffer[128][64]);

#endif
