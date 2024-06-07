/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "src/hal/lv_hal_tick.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for lvglT */
osThreadId_t lvglTHandle;
uint32_t lvglBuffer[ 6144 ];
osStaticThreadDef_t lvglControlBlock;
const osThreadAttr_t lvglT_attributes = {
  .name = "lvglT",
  .cb_mem = &lvglControlBlock,
  .cb_size = sizeof(lvglControlBlock),
  .stack_mem = &lvglBuffer[0],
  .stack_size = sizeof(lvglBuffer),
  .priority = (osPriority_t) osPriorityLow3,
};
/* Definitions for floorRunT */
osThreadId_t floorRunTHandle;
const osThreadAttr_t floorRunT_attributes = {
  .name = "floorRunT",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh5,
};
/* Definitions for distanceT */
osThreadId_t distanceTHandle;
const osThreadAttr_t distanceT_attributes = {
  .name = "distanceT",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for updatelvglT */
osThreadId_t updatelvglTHandle;
const osThreadAttr_t updatelvglT_attributes = {
  .name = "updatelvglT",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for armRunT */
osThreadId_t armRunTHandle;
const osThreadAttr_t armRunT_attributes = {
  .name = "armRunT",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow5,
};
/* Definitions for weight */
osThreadId_t weightHandle;
const osThreadAttr_t weight_attributes = {
  .name = "weight",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow4,
};
/* Definitions for floorRunTimer */
osTimerId_t floorRunTimerHandle;
const osTimerAttr_t floorRunTimer_attributes = {
  .name = "floorRunTimer"
};
/* Definitions for floorTimer */
osTimerId_t floorTimerHandle;
const osTimerAttr_t floorTimer_attributes = {
  .name = "floorTimer"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartlvglTask(void *argument);
void StartFloorRunTask(void *argument);
void StartDistanceTask(void *argument);
void StartUpdatelvglTask(void *argument);
void StartArmRunTask(void *argument);
void GetWeightTask(void *argument);
void floorRunTimerCallback(void *argument);
void floorTimerCallback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationTickHook(void);

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
    lv_tick_inc(1);
}
/* USER CODE END 3 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of floorRunTimer */
  floorRunTimerHandle = osTimerNew(floorRunTimerCallback, osTimerOnce, NULL, &floorRunTimer_attributes);

  /* creation of floorTimer */
  floorTimerHandle = osTimerNew(floorTimerCallback, osTimerPeriodic, NULL, &floorTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of lvglT */
  lvglTHandle = osThreadNew(StartlvglTask, NULL, &lvglT_attributes);

  /* creation of floorRunT */
  floorRunTHandle = osThreadNew(StartFloorRunTask, NULL, &floorRunT_attributes);

  /* creation of distanceT */
  distanceTHandle = osThreadNew(StartDistanceTask, NULL, &distanceT_attributes);

  /* creation of updatelvglT */
  updatelvglTHandle = osThreadNew(StartUpdatelvglTask, NULL, &updatelvglT_attributes);

  /* creation of armRunT */
  armRunTHandle = osThreadNew(StartArmRunTask, NULL, &armRunT_attributes);

  /* creation of weight */
  weightHandle = osThreadNew(GetWeightTask, NULL, &weight_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
    osTimerStart(floorTimerHandle, pdMS_TO_TICKS(20));
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
      osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartlvglTask */
/**
* @brief Function implementing the lvglTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartlvglTask */
__weak void StartlvglTask(void *argument)
{
  /* USER CODE BEGIN StartlvglTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartlvglTask */
}

/* USER CODE BEGIN Header_StartFloorRunTask */
/**
* @brief Function implementing the floorRunTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFloorRunTask */
__weak void StartFloorRunTask(void *argument)
{
  /* USER CODE BEGIN StartFloorRunTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartFloorRunTask */
}

/* USER CODE BEGIN Header_StartDistanceTask */
/**
* @brief Function implementing the distanceT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDistanceTask */
__weak void StartDistanceTask(void *argument)
{
  /* USER CODE BEGIN StartDistanceTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDistanceTask */
}

/* USER CODE BEGIN Header_StartUpdatelvglTask */
/**
* @brief Function implementing the updatelvglTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUpdatelvglTask */
__weak void StartUpdatelvglTask(void *argument)
{
  /* USER CODE BEGIN StartUpdatelvglTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartUpdatelvglTask */
}

/* USER CODE BEGIN Header_StartArmRunTask */
/**
* @brief Function implementing the armRunT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartArmRunTask */
__weak void StartArmRunTask(void *argument)
{
  /* USER CODE BEGIN StartArmRunTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartArmRunTask */
}

/* USER CODE BEGIN Header_GetWeightTask */
/**
* @brief Function implementing the weight thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GetWeightTask */
__weak void GetWeightTask(void *argument)
{
  /* USER CODE BEGIN GetWeightTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END GetWeightTask */
}

/* floorRunTimerCallback function */
__weak void floorRunTimerCallback(void *argument)
{
  /* USER CODE BEGIN floorRunTimerCallback */

  /* USER CODE END floorRunTimerCallback */
}

/* floorTimerCallback function */
__weak void floorTimerCallback(void *argument)
{
  /* USER CODE BEGIN floorTimerCallback */

  /* USER CODE END floorTimerCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

