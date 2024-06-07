//
// Created by heiyt_R9000P on 2024/4/1.
//

#include "pid.h"

double error;
const double kp = 0.01;

void k_control(double predict) {
    error = predict - pid_pace;
    pid_pace = pid_pace + kp * error;
}

//应该是接收到的轮胎速度？
//data16 = received_data[22];
//data16 = (data16 << 8) | received_data[21];
//wheel_angular_velocity[0] = (int16_t)data16;
//
//data16 = received_data[24];
//data16 = (data16 << 8) | received_data[23];
//wheel_angular_velocity[1] = (int16_t)data16;
//
//data16 = received_data[26];
//data16 = (data16 << 8) | received_data[25];
//wheel_angular_velocity[2] = (int16_t)data16;
//
//data16 = received_data[28];
//data16 = (data16 << 8) | received_data[27];
//wheel_angular_velocity[3] = (int16_t)data16;