//
// Created by heiyt_R9000P on 2024/4/9.
//

#include "src04.h"
#include "cmsis_os2.h"

double distance1 = 0;
double distance2 = 0;
double distance3 = 0;
double distance4 = 0;

double getDistance1() {
    uint16_t dis;
    HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_SET);
    osDelay(1);
    HAL_GPIO_WritePin(TRIG1_GPIO_Port, TRIG1_Pin, GPIO_PIN_RESET);
    while (HAL_GPIO_ReadPin(ECHO1_GPIO_Port, ECHO1_Pin) == GPIO_PIN_RESET);
    __HAL_TIM_SetCounter(&htim9, 0);
    __HAL_TIM_ENABLE(&htim9);
    while (HAL_GPIO_ReadPin(ECHO1_GPIO_Port, ECHO1_Pin) == GPIO_PIN_SET);
    dis = __HAL_TIM_GetCounter(&htim9);
    __HAL_TIM_DISABLE(&htim9);
    return (double)dis * 0.034 / 2;
}

double getDistance2() {
    uint16_t dis;
    HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_SET);
    osDelay(1);
    HAL_GPIO_WritePin(TRIG2_GPIO_Port, TRIG2_Pin, GPIO_PIN_RESET);
    while (HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin) == GPIO_PIN_RESET);
    __HAL_TIM_SetCounter(&htim9, 0);
    __HAL_TIM_ENABLE(&htim9);
    while (HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin) == GPIO_PIN_SET);
    dis = __HAL_TIM_GetCounter(&htim9);
    __HAL_TIM_DISABLE(&htim9);
    return (double)dis * 0.034 / 2;
}

double getDistance3() {
    uint16_t dis;
    HAL_GPIO_WritePin(TRIG3_GPIO_Port, TRIG3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TRIG3_GPIO_Port, TRIG3_Pin, GPIO_PIN_SET);
    osDelay(1);
    HAL_GPIO_WritePin(TRIG3_GPIO_Port, TRIG3_Pin, GPIO_PIN_RESET);
    while (HAL_GPIO_ReadPin(ECHO3_GPIO_Port, ECHO3_Pin) == GPIO_PIN_RESET);
    __HAL_TIM_SetCounter(&htim9, 0);
    __HAL_TIM_ENABLE(&htim9);
    while (HAL_GPIO_ReadPin(ECHO3_GPIO_Port, ECHO3_Pin) == GPIO_PIN_SET);
    dis = __HAL_TIM_GetCounter(&htim9);
    __HAL_TIM_DISABLE(&htim9);
    return (double)dis * 0.034 / 2;
}

double getDistance4() {
    uint16_t dis;
    HAL_GPIO_WritePin(TRIG4_GPIO_Port, TRIG4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TRIG4_GPIO_Port, TRIG4_Pin, GPIO_PIN_SET);
    osDelay(1);
    HAL_GPIO_WritePin(TRIG4_GPIO_Port, TRIG4_Pin, GPIO_PIN_RESET);
    while (HAL_GPIO_ReadPin(ECHO4_GPIO_Port, ECHO4_Pin) == GPIO_PIN_RESET);
    __HAL_TIM_SetCounter(&htim9, 0);
    __HAL_TIM_ENABLE(&htim9);
    while (HAL_GPIO_ReadPin(ECHO4_GPIO_Port, ECHO4_Pin) == GPIO_PIN_SET);
    dis = __HAL_TIM_GetCounter(&htim9);
    __HAL_TIM_DISABLE(&htim9);
    return (double)dis * 0.034 / 2;
}

