//
// Created by heiyt_R9000P on 2024/5/6.
//
#include "weight.h"


void swap(uint32_t *a,uint32_t *b) {
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(uint32_t list[])//冒泡排序
{
    static int i, j;
    static int temp;
    bool flag;
    flag = true;
    for(i = 1;flag && i<15-1;i++){
        flag = false;
        for (j = 0; j < 15 - i; j++) {
            if (list[j] > list[j + 1]) {
                flag = true;
                swap(&list[j], &list[j + 1]);
            }
        }
    }
}

uint32_t ReadCount(void)
{
    uint32_t Count = 0;
    uint8_t i = 0;
    HAL_GPIO_WritePin(WEIGHT_CLK_GPIO_Port, WEIGHT_CLK_Pin, GPIO_PIN_RESET);
    while(HAL_GPIO_ReadPin(WEIGHT_DATA_GPIO_Port, WEIGHT_DATA_Pin));
    for(i = 0; i <24; i++)
    {
        HAL_GPIO_WritePin(WEIGHT_CLK_GPIO_Port, WEIGHT_CLK_Pin, GPIO_PIN_SET);
        Count = Count << 1;
        HAL_GPIO_WritePin(WEIGHT_CLK_GPIO_Port, WEIGHT_CLK_Pin, GPIO_PIN_RESET);
        if(HAL_GPIO_ReadPin(WEIGHT_DATA_GPIO_Port, WEIGHT_DATA_Pin))
        {
            Count++;
        }
    }
    HAL_GPIO_WritePin(WEIGHT_CLK_GPIO_Port, WEIGHT_CLK_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(WEIGHT_CLK_GPIO_Port, WEIGHT_CLK_Pin, GPIO_PIN_RESET);
    return Count;
}

