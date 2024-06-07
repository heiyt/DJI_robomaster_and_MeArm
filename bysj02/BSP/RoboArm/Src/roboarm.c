//
// Created by heiyt_R9000P on 2024/4/12.
//

#include "roboarm.h"

uint16_t gj1_angle = 0;
uint16_t gj2_angle = 0;
uint16_t gj3_angle = 0;
uint16_t gj4_angle = 0;
// 0x32是转45度,0x64是转90度，0x84(132)转到最大的负角度，0x12(18)转到最小角度，0x4b(75)转到最中间位置,114
// 似乎对于舵机活动范围是180度多
// 对于夹爪，最大值时张开
// 对于主臂，最大值时到最后面
// 对于伸直臂，最大值时
void guanjie1(uint16_t angle) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, angle);
}

void guanjie2(uint16_t angle) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, angle);
}

void guanjie3(uint16_t angle) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, angle);
}

void guanjie4(uint16_t angle) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, angle);
}


