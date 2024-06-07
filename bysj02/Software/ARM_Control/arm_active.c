//
// Created by heiyt_R9000P on 2024/4/19.
//

#include "arm_active.h"

const double pi = 3.14159265359;
int16_t arm_x = 50;
int16_t arm_y = 50;
int16_t arm_z = 90;

ServoInfo _svoBase, _svoShoulder, _svoElbow, _svoClaw;

int sweepMinBase=180; int sweepMaxBase=0; double angleMinBase=pi; double angleMaxBase=0;
int sweepMinShoulder=135; int sweepMaxShoulder=45; double angleMinShoulder=3*pi/4; double angleMaxShoulder=pi/4;
int sweepMinElbow=90; int sweepMaxElbow=36; double angleMinElbow=0; double angleMaxElbow=-pi/4;
int sweepMinClaw=75; int sweepMaxClaw=180; double angleMinClaw=pi/2; double angleMaxClaw=0;

bool setup_servo(ServoInfo *svo, const int n_min, const int n_max, const double a_min, const double a_max) {
    double n_range = n_max - n_min;
    double a_range = a_max - a_min;
    // Must have a non-zero angle range
    if (a_range == 0) return false;
    // Calculate gain and zero
    svo->gain = n_range / a_range;
    svo->zero = n_min - svo->gain * a_min;
    // Set limits
    svo->n_min = n_min;
    svo->n_max = n_max;
    return true;
}
//ServoInfo *_svoBase,ServoInfo*_svoShoulder,ServoInfo*_svoElbow,ServoInfo*_svoClaw
void roboArm_Init() {
    setup_servo(&_svoBase, sweepMinBase, sweepMaxBase, angleMinBase, angleMaxBase);
    setup_servo(&_svoShoulder, sweepMinShoulder, sweepMaxShoulder, angleMinShoulder, angleMaxShoulder);
    setup_servo(&_svoElbow, sweepMinElbow, sweepMaxElbow, angleMinElbow, angleMaxElbow);
    setup_servo(&_svoClaw, sweepMinClaw, sweepMaxClaw, angleMinClaw, angleMaxClaw);
}

uint16_t angle2pwm(const ServoInfo svo, const double angle) {
    double pwm = 0.5f + svo.zero + svo.gain * angle;
    return (uint16_t) (pwm * (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) / 180.0) + MIN_PULSE_WIDTH; // convert 0-180 to microseconds
}

void arm_move_to(double x, double y, double z) {
    double radBase,radShoulder,radArm;
    if (solve(x, y, z, &radBase, &radShoulder, &radArm)) {
        gj1_angle = angle2pwm(_svoBase, radBase);
        gj2_angle = angle2pwm(_svoShoulder, radShoulder);
        gj3_angle = angle2pwm(_svoElbow, radArm);
    }
}