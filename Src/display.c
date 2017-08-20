/**
  ******************************************************************************
  * @file           : DISPLAY  
  * @version        : V10 EventHorizonOS
  * @brief          : This file implements the draw functions for the display
  ******************************************************************************
  */
#include "display.h"

#include "stm32f4xx_hal_gpio.h"

/** @addtogroup EventHorizonOS
  * @{
  */

/**
  * @brief  Send one byte of data to the LCD-Screen.
  * @param  data: The data byte to send.
  */
void lcdSendDat(uint8_t data) {
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_CS, GPIO_PIN_RESET);	//Select the display
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_A0, GPIO_PIN_SET);		//Set the address to 1 to write the data to the data register
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_WR, GPIO_PIN_RESET);	//Set the lcd to write mode
    
    HAL_GPIO_WritePin(GPIOC, 0x00FF, GPIO_PIN_RESET);		//Reset all data pins
    HAL_GPIO_WritePin(GPIOC, data, GPIO_PIN_SET);			//Put the data onto the data bus
    
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_WR, GPIO_PIN_SET);		//Disable the lcd write mode
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_CS, GPIO_PIN_SET);		//Unselect the display

}

/**
  * @brief  Send a command byte to the LCD-Screen.
  * @param  data: The command byte to send.
  */
void lcdSendCom(uint8_t data) {
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_CS, GPIO_PIN_RESET);	//Select the display
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_A0, GPIO_PIN_RESET);	//Set the address to 0 to write the data to the command register
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_WR, GPIO_PIN_RESET);	//Set the lcd to write mode
															
    HAL_GPIO_WritePin(GPIOC, 0x00FF, GPIO_PIN_RESET);    	//Reset all data pins
    HAL_GPIO_WritePin(GPIOC, data, GPIO_PIN_SET);        	//Put the data onto the data bus
															
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_WR, GPIO_PIN_SET);  	//Disable the lcd write mode
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_CS, GPIO_PIN_SET);  	//Unselect the display
}

/**
  * @brief  Initialize and startup the LCD-Screen.
  */
void lcdInit(void) {
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_WR, GPIO_PIN_SET);		//Disable the lcd write mode
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_RD, GPIO_PIN_SET);		//Disable the lcd read mode
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_CS, GPIO_PIN_RESET);	//Select the display
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_RS, GPIO_PIN_RESET);	//Reset the display
    HAL_Delay(150);											//Wait for the display to reset
    HAL_GPIO_WritePin(GPIOC, LCD_PIN_RS, GPIO_PIN_SET);		//Stop resetting of the display
    HAL_Delay(150);											//Wait for the display to startup
    
    lcdSendCom(LCD_CONFIG_CONTRAST_LOW);					//Set the display to Low-Contrast Mode
    lcdSendCom(LCD_CONFIG_MIRRORED_OFF);					//Disable mirrored mode
    lcdSendCom(LCD_CONFIG_ZEROPT_TOP);						//Set the zero point to the top right corner
    lcdSendCom(0x25);                                		//Set the Internal power control
    lcdSendCom(0x81);                                		//Set the chargepump output voltage
    lcdSendCom(0x15);                                		//Set the Internal power control
    lcdSendCom(0x2F);                                		//Set the Internal power control
    lcdSendCom(LCD_CONFIG_START_LINE(0));					//Set the start line to 0
	lcdSendCom(LCD_CONFIG_BOOSTER_RATIO(3));
	lcdSendCom(LCD_CONFIG_VOLTAGE_BIAS(1));
	lcdSendCom(LCD_CONFIG_VOLTAGE_RES(5));
    lcdSendCom(LCD_CONFIG_DISPLAY_ON);						//Turn the display on
    
    HAL_Delay(10);											//Wait for startup
}


/**
  * @brief  Draw the big center clock.
  * @param  hours: The hours to display.
  * @param  minutes: The minutes to display.
  * @param  seconds: The seconds to display.
  */
/*void lcdDrawClock(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    uint8_t x, y;
    
	//Draw the tens of the hour
    for(x = 0; x < 10; x++) {
        for(y = 0; y < 16; y++) {
            displayBuffer[lcdTextPointerX + x + 2][lcdTextPointerY + y + 2] = ((font_clock[hours / 10][x] & 0x01 << y) >> y);
        }
    }
    
	//Draw the ones of the hour
    for(x = 0; x < 10; x++) {
        for(y = 0; y < 16; y++) {
            displayBuffer[lcdTextPointerX + x + 12][lcdTextPointerY + y + 2] = ((font_clock[hours % 10][x] & 0x01 << y) >> y);
        }
    }
            
	//Draw the tens of the minutes
    for(x = 0; x < 10; x++) {
        for(y = 0; y < 16; y++) {
            displayBuffer[lcdTextPointerX + x + 32][lcdTextPointerY + y + 2] = ((font_clock[minutes / 10][x] & 0x01 << y) >> y);
        }
    }
        
	//Draw the ones of the minutes
    for(x = 0; x < 10; x++) {
        for(y = 0; y < 16; y++) {
            displayBuffer[lcdTextPointerX + x + 42][lcdTextPointerY + y + 2] = ((font_clock[minutes % 10][x] & 0x01 << y) >> y);
        }
    }
    
	//Draw the colon in the middle of the clock
    for(x = 0; x < 10; x++) {
        for(y = 0; y < 16; y++) {
            displayBuffer[lcdTextPointerX + x + 22][lcdTextPointerY + y + 2] = ((font_clock[(seconds % 2 == 0 ? 10 : 11)][x] & 0x01 << y) >> y);
        }
    }
    
	//Draw the seconds
    lcdTextPointerX = lcdTextPointerX + 51;
    lcdTextPointerY = lcdTextPointerY + 6;
    printf("%02d", seconds);
    
}*/

/**
  * @brief  Send the draw buffer to the LCD-Screen.
  */
void lcdSendBuffer(bool buffer[128][64]) {
    uint8_t x, y, byte, page = 0;								//The x and y coordinates, the byte to write and the current page
    
    for(page = 0; page < LCD_PAGES; page++) {					//For each page...
        lcdSendCom(LCD_CMD_COLUMN_ADDR_H(0x00));				//Reset the collumn address High byte
        lcdSendCom(LCD_CMD_COLUMN_ADDR_L(0x00));				//Reset the collumn address Low byte
        lcdSendCom(LCD_CMD_PAGE_ADDR(page));					//Set the page to the current page
        for(x = 0; x < LCD_WIDTH; x++) {						//For each row in the buffer...
            byte = 0;											//...Reset the byte
            for(y = 0; y < 8; y++) {							//For each collumn in the buffer...
                byte |= buffer[x][y+(8 * page)] << y;	//Set the byte to the correct value for the display to recognize it
            }
            lcdSendDat(byte);									//Send the byte to the display
        }
    }
}
