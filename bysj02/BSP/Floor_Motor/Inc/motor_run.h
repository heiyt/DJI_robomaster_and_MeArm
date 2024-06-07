//
// Created by heiyt_R9000P on 2024/3/29.
//

#ifndef BYSJ02_MOTOR_RUN_H
#define BYSJ02_MOTOR_RUN_H

#include "main.h"

extern uint8_t Speed0_TABLE[22];
extern uint8_t Speed1_TABLE[22];
extern uint8_t Speed2_TABLE[22];
extern uint8_t Speed3_TABLE[22];

void getCRC16CheckSum(uint8_t *pchMessage, uint32_t dwLength, uint16_t wCRC);

void setSpeed(uint8_t wheel0_d, uint16_t speed0, uint8_t wheel1_d, uint16_t speed1, uint8_t wheel2_d, uint16_t speed2,
              uint8_t wheel3_d, uint16_t speed3);

#endif //BYSJ02_MOTOR_RUN_H
