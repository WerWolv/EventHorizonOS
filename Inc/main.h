/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define WATCH_CRYSTAL_IN_Pin GPIO_PIN_14
#define WATCH_CRYSTAL_IN_GPIO_Port GPIOC
#define WATCH_CRYSTAL_OUT_Pin GPIO_PIN_15
#define WATCH_CRYSTAL_OUT_GPIO_Port GPIOC
#define _8MHZ_CRYSTAL_IN_Pin GPIO_PIN_0
#define _8MHZ_CRYSTAL_IN_GPIO_Port GPIOH
#define _8MHZ_CRYSTAL_OUT_Pin GPIO_PIN_1
#define _8MHZ_CRYSTAL_OUT_GPIO_Port GPIOH
#define D0_Pin GPIO_PIN_0
#define D0_GPIO_Port GPIOC
#define D1_Pin GPIO_PIN_1
#define D1_GPIO_Port GPIOC
#define D2_Pin GPIO_PIN_2
#define D2_GPIO_Port GPIOC
#define D3_Pin GPIO_PIN_3
#define D3_GPIO_Port GPIOC
#define SENS_LIGHT_Pin GPIO_PIN_0
#define SENS_LIGHT_GPIO_Port GPIOA
#define RGB_LED_RED_Pin GPIO_PIN_1
#define RGB_LED_RED_GPIO_Port GPIOA
#define RGB_LED_GREEN_Pin GPIO_PIN_2
#define RGB_LED_GREEN_GPIO_Port GPIOA
#define RGB_LED_BLUE_Pin GPIO_PIN_3
#define RGB_LED_BLUE_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOC
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOC
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOC
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOC
#define CS_Pin GPIO_PIN_8
#define CS_GPIO_Port GPIOC
#define RESET_Pin GPIO_PIN_9
#define RESET_GPIO_Port GPIOC
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define A0_Pin GPIO_PIN_10
#define A0_GPIO_Port GPIOC
#define WR_Pin GPIO_PIN_11
#define WR_GPIO_Port GPIOC
#define RD_Pin GPIO_PIN_12
#define RD_GPIO_Port GPIOC
#define ENCODER_B_Pin GPIO_PIN_6
#define ENCODER_B_GPIO_Port GPIOB
#define ENCODER_A_Pin GPIO_PIN_7
#define ENCODER_A_GPIO_Port GPIOB
#define BTN_A_Pin GPIO_PIN_8
#define BTN_A_GPIO_Port GPIOB
#define BTN_B_Pin GPIO_PIN_9
#define BTN_B_GPIO_Port GPIOB
#define BTN_C_Pin GPIO_PIN_5
#define BTN_C_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
