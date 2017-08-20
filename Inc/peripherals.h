/**
  ******************************************************************************
  * @file           : PERIPHERALS  
  * @version        : V10 EventHorizonOS
  * @brief          : This file implements the interaction with all peripherals
  ******************************************************************************
  */
#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <stdbool.h>
#include <stdio.h>

#include "stm32f4xx_hal.h"

#define LIGHT_MEDIUM_THREASHOLD  350						//Threashold for the program to recognize the light level as medium	
#define LIGHT_LOW_THREASHOLD     250						//Threashold for the program to recognize the light level as low


/*- Peripheral Configuration Structs -*/
extern TIM_OC_InitTypeDef sConfigOC;						//PWM Timer configuration struct

extern ADC_HandleTypeDef hadc1;								//ADC1 Handler struct
extern RTC_HandleTypeDef hrtc;								//RTC Handler struct
extern TIM_HandleTypeDef htim2;								//Timer 2 Handler struct
extern TIM_HandleTypeDef htim4;								//Timer 4 Handler struct

/*- Encoder Function Pointer typedefs -*/
typedef void(*EncoderCallFncPointer_TypeDef)(uint8_t);
typedef void(*ButtonCallFncPointer_TypeDef)(void);

/*- Lightlevel typedef -*/
typedef enum {
    LIGHT_HIGH,
    LIGHT_MEDIUM,
    LIGHT_LOW
} EH_LightLevelTypeDef;

/*- Function prototypes -*/

/*-Sets the color of the Notification LED-*/
extern void setNotificationLedColor(uint32_t color);

extern void onButtonPressed(bool btnA, bool btnB, bool btnC);
extern void onEncoderTurned(void);
extern void onUSBReceived(uint8_t* Buf, uint32_t *Len);
extern void addOnButtonPressedCallback(void (*function)(bool btnA, bool btnB, bool btnC));
extern void addOnEncoderTurnedCallback(void (*function)(int8_t steps));
extern void addOnUSBReceivedCallback(void (*function)(uint8_t* Buf, uint32_t *Len));

/*-Callback handler for the button press event-*/
extern bool hasButtonBeenPressed(ButtonCallFncPointer_TypeDef func_pressA, ButtonCallFncPointer_TypeDef func_pressB, ButtonCallFncPointer_TypeDef func_pressC);

/*-Callback handler for the encoder turned event-*/
extern bool hasEncoderBeenTurned(EncoderCallFncPointer_TypeDef func_turnCW, EncoderCallFncPointer_TypeDef func_turnCCW);

/*-Get the current light level-*/
extern EH_LightLevelTypeDef getLightLevel(void);

/*-Get the current time from the RTC-*/
extern RTC_TimeTypeDef getRTCTime(void);

/*-Get the current date from the RTC-*/
extern RTC_DateTypeDef getRTCDate(void);

/*-Set the current time in the RTC-*/
extern void setRTCTime(uint8_t hours, uint8_t minutes, uint8_t seconds);

/*-Set the current date in the RTC-*/
extern void setRTCDate(uint8_t year, uint8_t month, uint8_t day, uint8_t weekday);

#endif
