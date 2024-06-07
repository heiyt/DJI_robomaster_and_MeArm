//
// Created by heiyt_R9000P on 2024/4/1.
//

#ifndef BYSJ02_FLOOR_ACTIVE_H
#define BYSJ02_FLOOR_ACTIVE_H

#include "main.h"

extern int16_t wheel_speed[4];

void floor_run(int16_t Wx,int16_t Wy);
int16_t floor_rotate(int16_t angle, int16_t speed);
void floor_rotate_M(char fx, int16_t speed);
void floor_stop();

#endif //BYSJ02_FLOOR_ACTIVE_H
