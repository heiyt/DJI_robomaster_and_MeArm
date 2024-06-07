#include "ik.h"
double L1=80; //Shoulder to elbow length
double L2=80; //Elbow to wrist length
double L3=22;  // Correct to MeArm Version 3.0

const double PI=3.14159265359;

// Get polar coords from cartesian ones
void cart2polar(double a, double b, double *r, double* theta)
{
    // Determine magnitude of cartesian coords
    *r = sqrt(a * a + b * b);

    // Don't try to calculate zero-magnitude vectors' angles
    if (*r == 0) return;

    double c = a / (*r);
    double s = b / (*r);

    // Safety!
    if (s > 1) s = 1;
    if (c > 1) c = 1;
    if (s < -1) s = -1;
    if (c < -1) c = -1;

    // Calculate angle in 0..PI
    *theta = acos(c);

    // Convert to full range
    if (s < 0) *theta *= -1;
}


bool cosangle(double opp, double adj1, double adj2, double* theta)
{
    double den = 2 * adj1 * adj2;
    if (den == 0) return false;
    double c = (adj1 * adj1 + adj2 * adj2 - opp * opp) / den;
    if (c > 1 || c < -1) return false;
    *theta = acos(c);
    return true;
}

bool solve(double x, double y, double z, double* a0, double* a1, double* a2)
{
    // Solve top-down view
    double r, th0;
    cart2polar(y, x, &r, &th0);
    // Account for the wrist length!
    r -= L3;
    // In arm plane, convert to polar
    double ang_P, R;
    cart2polar(r, z, &R, &ang_P);
    // Solve arm inner angles as required
    double B, C;
    if (!cosangle(L2, L1, R, &B)) return false;
    if (!cosangle(R, L1, L2, &C)) return false;
    // Solve for servo angles from horizontal
    *a0 = th0;
    *a1 = ang_P + B;
    *a2 = C + (*a1) - PI;
    return true;
}
