/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define N_SAMPLES 20	//SAMPLES de entrada + salida tomadas con el ADC

#define MAX_FREQ_POINTS 600

#define FREQ_TIM1 84000000
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define ROUND_TO_INT(x) ((uint32_t)((x)+0.5))
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define DB0_Pin GPIO_PIN_0
#define DB0_GPIO_Port GPIOC
#define DB1_Pin GPIO_PIN_1
#define DB1_GPIO_Port GPIOC
#define DB2_Pin GPIO_PIN_2
#define DB2_GPIO_Port GPIOC
#define DB3_Pin GPIO_PIN_3
#define DB3_GPIO_Port GPIOC
#define LCD_RESET_Pin GPIO_PIN_1
#define LCD_RESET_GPIO_Port GPIOA
#define ADC_VIN_Pin GPIO_PIN_2
#define ADC_VIN_GPIO_Port GPIOA
#define ADC_VOUT_Pin GPIO_PIN_3
#define ADC_VOUT_GPIO_Port GPIOA
#define LCD_WR_Pin GPIO_PIN_4
#define LCD_WR_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define LCD_RD_Pin GPIO_PIN_6
#define LCD_RD_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_7
#define LCD_RS_GPIO_Port GPIOA
#define DB4_Pin GPIO_PIN_4
#define DB4_GPIO_Port GPIOC
#define DB5_Pin GPIO_PIN_5
#define DB5_GPIO_Port GPIOC
#define DB13_Pin GPIO_PIN_0
#define DB13_GPIO_Port GPIOB
#define DB14_Pin GPIO_PIN_1
#define DB14_GPIO_Port GPIOB
#define DB15_Pin GPIO_PIN_2
#define DB15_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_10
#define LCD_CS_GPIO_Port GPIOB
#define TOUCH_CS_Pin GPIO_PIN_12
#define TOUCH_CS_GPIO_Port GPIOB
#define DB6_Pin GPIO_PIN_6
#define DB6_GPIO_Port GPIOC
#define DB7_Pin GPIO_PIN_7
#define DB7_GPIO_Port GPIOC
#define DB8_Pin GPIO_PIN_8
#define DB8_GPIO_Port GPIOC
#define DB9_Pin GPIO_PIN_9
#define DB9_GPIO_Port GPIOC
#define DDS_CS_Pin GPIO_PIN_8
#define DDS_CS_GPIO_Port GPIOA
#define IC_VIN_Pin GPIO_PIN_9
#define IC_VIN_GPIO_Port GPIOA
#define IC_VOUT_Pin GPIO_PIN_10
#define IC_VOUT_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define DB10_Pin GPIO_PIN_10
#define DB10_GPIO_Port GPIOC
#define DB11_Pin GPIO_PIN_11
#define DB11_GPIO_Port GPIOC
#define DB12_Pin GPIO_PIN_12
#define DB12_GPIO_Port GPIOC
#define RST_VIN_Pin GPIO_PIN_6
#define RST_VIN_GPIO_Port GPIOB
#define TOUCH_IRQ_Pin GPIO_PIN_8
#define TOUCH_IRQ_GPIO_Port GPIOB
#define RST_VOUT_Pin GPIO_PIN_9
#define RST_VOUT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
