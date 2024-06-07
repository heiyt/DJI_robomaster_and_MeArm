/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor_run.h"
#include "lvgl.h"
#include "porting/lv_port_disp.h"
#include "ui.h"
#include "heiytTask.h"
#include "arm_active.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define RECEIVE_SIZE 8
uint8_t receive_buff[RECEIVE_SIZE];
int16_t arm_x_buff = 45, arm_y_buff = 45, arm_z_buff = 80;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart3) {
        if (receive_buff[0] == 0x01) {
            Wx = (int16_t)(receive_buff[1]<<8 | receive_buff[2]);
            Wy = (int16_t)(receive_buff[3]<<8 | receive_buff[4]);
            run = 1;
        }
        if (receive_buff[0] == 0x02) {
            angle = (int16_t)(receive_buff[1]<<8 | receive_buff[2]);
            speed_A = (int16_t)(receive_buff[3]<<8 | receive_buff[4]);
            run = 2;
        }
        if (receive_buff[0] == 0x03) {
            fx = receive_buff[2];
            speed_M = (int16_t) (receive_buff[3] << 8 | receive_buff[4]);
            run = 3;
        }
        if (receive_buff[0] == 0x04) {
            run = 4;
        }
        if (receive_buff[0] == 0x05) {
            run = 4;
            if (receive_buff[1] == 0) {
                arm_x_buff = arm_x_buff + (int16_t)receive_buff[2];
            }
            if (receive_buff[1] == 1) {
                arm_x_buff = arm_x_buff - receive_buff[2];
            }
            if (receive_buff[3] == 0) {
                arm_y_buff = arm_y_buff + receive_buff[4];
            }
            if (receive_buff[3] == 1) {
                arm_y_buff = arm_y_buff - receive_buff[4];
            }
            if (receive_buff[5] == 0) {
                arm_z_buff = arm_z_buff + receive_buff[6];
            }
            if (receive_buff[5] == 1) {
                arm_z_buff = arm_z_buff - receive_buff[6];
            }
            if (receive_buff[7] == 0x04) {
                gj4_angle = 68;
            }
            if (receive_buff[7] == 0x05) {
                gj4_angle = 80;
            }
            if (arm_x_buff > 200) {
                arm_x_buff = 200;
            }
            if (arm_x_buff < -200) {
                arm_x_buff = -200;
            }
            if (arm_y_buff > 200) {
                arm_y_buff = 200;
            }
            if (arm_y_buff < -200) {
                arm_y_buff = -200;
            }
        }
        if (receive_buff[0] == 0x06) {
            arm_x_buff = (int16_t) (receive_buff[1] << 8 | receive_buff[2]);
            arm_y_buff = (int16_t) (receive_buff[3] << 8 | receive_buff[4]);
            arm_z_buff = (int16_t) (receive_buff[5] << 8 | receive_buff[6]);
        }
        if (receive_buff[0] == 0x07) {
            gj4_angle = (uint16_t) (receive_buff[1] << 8 | receive_buff[2]);
        }
        if (receive_buff[0] == 0x08) {
            celiang = true;
        }
    }
    HAL_UART_Receive_IT(&huart3,receive_buff,RECEIVE_SIZE);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_FSMC_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_TIM9_Init();
  /* USER CODE BEGIN 2 */
    roboArm_Init();
    // TIM3 robot arm
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    // TIM9 robot cgq
    HAL_TIM_Base_Start_IT(&htim9);
    // floor
    HAL_UART_Receive_IT(&huart3, receive_buff, RECEIVE_SIZE);
    HAL_GPIO_WritePin(RS485RE_GPIO_Port, RS485RE_Pin, GPIO_PIN_SET);
    // UI
    lv_init();
    lv_port_disp_init();
    ui_init();
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM14 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM14) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
//  __disable_irq();
//  while (1)
//  {
//  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
