//
// Created by heiyt_R9000P on 2024/4/9.
//

#ifndef BYSJ02_HEIYTTASK_H
#define BYSJ02_HEIYTTASK_H

#include "cmsis_os2.h"
#include "src/misc/lv_timer.h"
#include "floor_active.h"
#include "src/widgets/lv_label.h"
#include "ui.h"
#include <stdio.h>
#include "usart.h"
#include "src04.h"
#include "FreeRTOS.h"
#include "roboarm.h"
#include "arm_active.h"

extern int16_t angle, speed_A, speed_M;
extern int16_t Wx, Wy;
extern char run, fx;
extern bool celiang;
extern uint8_t send_buffer[5];

#endif //BYSJ02_HEIYTTASK_H
