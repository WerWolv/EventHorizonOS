/**
  ******************************************************************************
  * @file           : PERIPHERALS  
  * @version        : V10 EventHorizonOS
  * @brief          : This file implements the interaction with all peripherals
  ******************************************************************************
  */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rtc.h"

#include "usbd_cdc_if.h"

#include "display.h"
#include "peripherals.h"

void (*buttonCallbacks[16])(bool btnA, bool btnB, bool btnC) = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
void (*encoderCallbacks[16])(int8_t steps) = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
void (*usbReceivedCallbacks[16])(uint8_t* Buf, uint32_t *Len) = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

/** @addtogroup EventHorizonOS
  * @{
  */

/**
  * @brief  Set the color of the notification LED using 
  *         three PWM modules of the Timer2.
  * @param  color: The color of the led in RRGGBB layout
  * @retval None
  */
void setNotificationLedColor(uint32_t color) {
	sConfigOC.Pulse = (color & 0xFF0000) >> 4;						//Extract the red part of the passed color
	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);	//Start the PWM module for the red LED
	sConfigOC.Pulse = (color & 0xFF00) >> 2;						//Extract the green part of the passed color
	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);	//Start the PWM module for the green LED
	sConfigOC.Pulse = (color & 0xFF);								//Extract the blue part of the passed color
	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4);	//Start the PWM module for the blue LED
	
	HAL_TIM_Base_Start(&htim2);										//Start the timer 2
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);						//Start the PWM of timer 2 on channel 2
	HAL_TIMEx_PWMN_Start(&htim2, TIM_CHANNEL_2);					
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);                       //Start the PWM of timer 2 on channel 3
	HAL_TIMEx_PWMN_Start(&htim2, TIM_CHANNEL_3);					
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);                       //Start the PWM of timer 2 on channel 4
	HAL_TIMEx_PWMN_Start(&htim2, TIM_CHANNEL_4);
}

void onButtonPressed(bool btnA, bool btnB, bool btnC) {
	for(uint8_t callback = 0; callback < 16; callback++)
		if(buttonCallbacks[callback] != NULL)
			buttonCallbacks[callback](btnA, btnB, btnC);
}

void onEncoderTurned(void) {
	if (TIM4->CNT > 101) {			
		for(uint8_t callback = 0; callback < 16; callback++)
			if(encoderCallbacks[callback] != NULL)
				encoderCallbacks[callback](TIM4->CNT - 101);	
		TIM4->CNT = 100;						
	}			
	else if (TIM4->CNT < 99) {			
		for(uint8_t callback = 0; callback < 16; callback++)
			if(encoderCallbacks[callback] != NULL)
				encoderCallbacks[callback](TIM4->CNT - 99);	
		TIM4->CNT = 100;						
	}
}

void onUSBReceived(uint8_t* Buf, uint32_t *Len) {
	for(uint8_t callback = 0; callback < 16; callback++)
		if(usbReceivedCallbacks[callback] != NULL)
			usbReceivedCallbacks[callback](Buf, Len);
}

void addOnButtonPressedCallback(void (*function)(bool btnA, bool btnB, bool btnC)) {
	for(uint8_t callback = 0; callback < 16; callback++) {
		if(buttonCallbacks[callback] == NULL) {
			buttonCallbacks[callback] = function;
			break;
		}
	}
}

void addOnEncoderTurnedCallback(void (*function)(int8_t steps)) {
	for(uint8_t callback = 0; callback < 16; callback++) {
		if(encoderCallbacks[callback] == NULL) {
			encoderCallbacks[callback] = function;
			break;
		}
	}
}

void addOnUSBReceivedCallback(void (*function)(uint8_t* Buf, uint32_t *Len)) {
	for(uint8_t callback = 0; callback < 16; callback++) {
		if(usbReceivedCallbacks[callback] == NULL) {
			usbReceivedCallbacks[callback] = function;
			break;
		}
	}
}

/**
  * @brief  Get the current light level based on the environment
  * @param  None
  * @retval The amount of light devided into three levels
  */
EH_LightLevelTypeDef getLightLevel(void) {
    uint16_t lightValue;
    
	HAL_ADC_Start(&hadc1);						//Start the ADC convertion
	
	HAL_ADC_PollForConversion(&hadc1, 100);		//Start polling for the ADC value
	
    lightValue = HAL_ADC_GetValue(&hadc1);		//Save the current ADC value
    
    if (lightValue > LIGHT_MEDIUM_THREASHOLD) 	//If the lightlevel is greater than the medium light threashold...
        return LIGHT_HIGH;						//...there is a great amount of light in the room
    else if (lightValue > LIGHT_LOW_THREASHOLD) //Otherwise if the lightlevel is greater than the low light threashold...
        return LIGHT_MEDIUM;					//...there is a medium amount of light in the room
    else return LIGHT_LOW;						//Otherwise there isn't much light in the room
}

/**
  * @brief  Gets the current Time stored in the internal RTC.
  * @param  None
  * @retval RTC_TimeTypeDef including hours, minutes and seconds.
  */
RTC_TimeTypeDef getRTCTime() {
    RTC_TimeTypeDef time;
	uint8_t t;
    if(HAL_RTC_GetTime(&hrtc, &time, FORMAT_BIN) != HAL_OK)
		setNotificationLedColor(0xFF0000);
	t = RTC->DR;
	
    return time;
}

/**
  * @brief  Gets the current Date stored in the internal RTC.
  * @param  None
  * @retval RTC_TimeTypeDef including the date, month, year and weekday.
  */
RTC_DateTypeDef getRTCDate() {
    RTC_DateTypeDef date;
	uint8_t d;
    if(HAL_RTC_GetDate(&hrtc, &date, FORMAT_BIN) != HAL_OK)
		setNotificationLedColor(0xFF0000);
	d = RTC->DR;
    
    return date;
}
/**
  * @brief  Sets the current Time stored in the internal RTC.
  * @param  hours: The hour that should get stored.
  * @param  minutes: The minutes that should get stored.
  * @param  seconds: The seconds that should get stored.
  * @retval None.
  */
void setRTCTime(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    RTC_TimeTypeDef time;
       
    time.TimeFormat = RTC_HOURFORMAT_24;		//Set the timeformat to 24 hours
    time.Hours = hours;							//Set the hours
    time.Minutes = minutes;						//Set the minutes
    time.Seconds = seconds;						//Set the seconds
    
    
    HAL_RTC_SetTime(&hrtc, &time, FORMAT_BIN);	//Pass the time to the RTC
}

/**
  * @brief  Sets the current Date stored in the internal RTC.
  * @param  year: The year that should get stored.
  * @param  month: The month that should get stored.
  * @param  day: The day that should get stored.
  * @param  weekday: The weekday that should get stored.
  * @retval None.
  */
void setRTCDate(uint8_t year, uint8_t month, uint8_t day, uint8_t weekday) {
    RTC_DateTypeDef date;
    
    date.Year = year;							//Set the year
    date.Month = month;							//Set the month
    date.Date = day;							//Set the day
    date.WeekDay = weekday;						//Set the weekday. This isn't used at the moment
    
    HAL_RTC_SetDate(&hrtc, &date, FORMAT_BIN);	//Pass the date to the RTC
}
