//
// Created by heiyt_R9000P on 2024/4/1
//

#include "floor_active.h"
#include "motor_run.h"

int16_t wheel_speed[4];

//以小车正前方为轴 0°
// 轮胎右前方是0
// 轮胎左前方是1
// 轮胎左后方是2
// 轮胎右后方是3
// 0 和 3 正转是向后
// 1 和 2 正转是向前
void floor_run(int16_t Wx,int16_t Wy) {
    int16_t w[4];
    char w_d[4] = {1, 0, 0, 1};
    if (Wx > 200 || Wy > 200 || Wx < -200 || Wy < -200) {
        return;
    }
    w[0] = (int16_t)(Wy + Wx);
    w[1] = (int16_t)(Wy - Wx);
    w[2] = (int16_t)(Wx + Wy);
    w[3] = (int16_t)(Wy - Wx);
    for (int i = 0; i < 4; i++) {
        wheel_speed[i] = w[i];
        if (w[i] < 0) {
            w[i] = (int16_t)(-w[i]);
            if (i == 0 || i == 3) {
                w_d[i] = 0;
            }
            if (i == 1 || i == 2) {
                w_d[i] = 1;
            }
        }
    }
    setSpeed(w_d[0], (int16_t)w[0], w_d[1], (int16_t)w[1], w_d[2], (int16_t)w[2], w_d[3], (int16_t)w[3]);
}

//旋转，角度为0到360度
int16_t floor_rotate(int16_t angle, int16_t speed) {
    int16_t time;
    int16_t w[4];//速度
    char w_d[4] = {0, 0, 0, 0};//方向
    if (speed > 100 || speed < -100) {
        return 0;
    }
    if (speed < 16 && speed > -16) {
        return 0;
    }
    w[0] = speed;
    w[1] = speed;
    w[2] = speed;
    w[3] = speed;
    if (angle > 180) {
        w_d[0] = 1;
        w_d[1] = 1;
        w_d[2] = 1;
        w_d[3] = 1;
        wheel_speed[0] = -speed;
        wheel_speed[1] = speed;
        wheel_speed[2] = speed;
        wheel_speed[3] = -speed;
        angle = 360 - angle;
    } else {
        wheel_speed[0] = speed;
        wheel_speed[1] = -speed;
        wheel_speed[2] = -speed;
        wheel_speed[3] = speed;
    }
    time = (int16_t)(angle * 1000 / speed);
    setSpeed(w_d[0], (int16_t)w[0], w_d[1], (int16_t)w[1], w_d[2], (int16_t)w[2], w_d[3], (int16_t)w[3]);
    return time;
}

void floor_rotate_M(char fx, int16_t speed) {
    int16_t w[4] = {0, 0, 0, 0};//速度
    char w_d[4] = {0, 0, 0, 0};
    w[0] = speed;
    w[1] = speed;
    w[2] = speed;
    w[3] = speed;
    if (speed > 100 || speed < -100) {
        return;
    }
    if (speed < 16 && speed > -16) {
        return;
    }
    if (fx == 1) {
        w_d[0] = 1;
        w_d[1] = 1;
        w_d[2] = 1;
        w_d[3] = 1;
        wheel_speed[0] = -speed;
        wheel_speed[1] = speed;
        wheel_speed[2] = speed;
        wheel_speed[3] = -speed;
    } else {
        wheel_speed[0] = speed;
        wheel_speed[1] = -speed;
        wheel_speed[2] = -speed;
        wheel_speed[3] = speed;
    }
    setSpeed(w_d[0], (int16_t) w[0], w_d[1], (int16_t) w[1], w_d[2], (int16_t) w[2], w_d[3], (int16_t) w[3]);
}

void floor_stop() {
    int16_t w[4] = {0,0,0,0};//速度
    char w_d[4] = {1, 0, 0, 1};
    for (int i = 0; i < 4; i++) {
        wheel_speed[i] = (int16_t) w[i];
    }
    setSpeed(w_d[0], (uint16_t)w[0], w_d[1], (uint16_t)w[1], w_d[2], (uint16_t)w[2], w_d[3], (uint16_t)w[3]);
}