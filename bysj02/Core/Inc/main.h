/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
extern int16_t arm_x_buff, arm_y_buff, arm_z_buff;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_BLK_Pin GPIO_PIN_15
#define LCD_BLK_GPIO_Port GPIOB
#define RS485RE_Pin GPIO_PIN_8
#define RS485RE_GPIO_Port GPIOG
#define WEIGHT_CLK_Pin GPIO_PIN_9
#define WEIGHT_CLK_GPIO_Port GPIOG
#define WEIGHT_DATA_Pin GPIO_PIN_10
#define WEIGHT_DATA_GPIO_Port GPIOG
#define ECHO4_Pin GPIO_PIN_15
#define ECHO4_GPIO_Port GPIOG
#define TRIG4_Pin GPIO_PIN_3
#define TRIG4_GPIO_Port GPIOB
#define ECHO2_Pin GPIO_PIN_4
#define ECHO2_GPIO_Port GPIOB
#define TRIG2_Pin GPIO_PIN_5
#define TRIG2_GPIO_Port GPIOB
#define ECHO1_Pin GPIO_PIN_6
#define ECHO1_GPIO_Port GPIOB
#define TRIG1_Pin GPIO_PIN_7
#define TRIG1_GPIO_Port GPIOB
#define ECHO3_Pin GPIO_PIN_8
#define ECHO3_GPIO_Port GPIOB
#define TRIG3_Pin GPIO_PIN_9
#define TRIG3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern double pid_pace;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
