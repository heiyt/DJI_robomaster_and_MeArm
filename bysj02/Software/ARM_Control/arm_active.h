//
// Created by heiyt_R9000P on 2024/4/19.
//

#ifndef BYSJ02_ARM_ACTIVE_H
#define BYSJ02_ARM_ACTIVE_H

#include "main.h"
#include "ik.h"
#include "roboarm.h"
#define MIN_PULSE_WIDTH 28
#define MAX_PULSE_WIDTH 122

extern int16_t arm_x;
extern int16_t arm_y;
extern int16_t arm_z;

typedef struct {
    int n_min, n_max;   // PWM 'soft' limits - should be just within range
    double gain;         // PWM per radian
    double zero;         // Theoretical PWM for zero angle
} ServoInfo;

extern ServoInfo _svoBase, _svoShoulder, _svoElbow, _svoClaw;

void roboArm_Init();
void arm_move_to(double x, double y, double z);

#endif //BYSJ02_ARM_ACTIVE_H
