/* MeArmIK - York Hackspace May 2014
 * Inverse Kinematics solver for three degrees of freedom
 * created for MeArm Robotics Class MeArm Robot Arm
 */
#ifndef IK_H_INCLUDED
#define IK_H_INCLUDED


#include <stdbool.h>
#include "math.h"

extern double L1, L2, L3;

// Get polar coords from cartesian ones
void cart2polar(double a, double b, double* r, double* theta);

// Get angle from a triangle using cosine rule
bool cosangle(double opp, double adj1, double adj2, double* theta);

// Solve angles!
bool solve(double x, double y, double z, double*a0, double* a1, double* a2);

#endif // IK_H_INCLUDED
