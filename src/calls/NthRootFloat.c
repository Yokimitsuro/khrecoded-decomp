#include "nitro/types.h"

extern double MSL_Fabs(double x);
extern float func_0202354c(double value);
extern void PowThenAddFloat();
extern void PowDerivativeTimesN();
extern float NewtonSolveFloat(float guess, int n, float value, void (*func)(), void (*deriv)(), float tolerance);

float NthRootFloat(float value, int n)
{
    float magnitude;
    float guess;

    if (0.0f == value) {
        return 0.0f;
    }
    magnitude = func_0202354c(MSL_Fabs(value));
    if (magnitude < 1e-6f) {
        guess = 5000.0f * value;
    } else if (magnitude < 1e-4f) {
        guess = 300.0f * value;
    } else if (magnitude < 0.01f) {
        guess = 20.0f * value;
    } else if (magnitude < 1.0f) {
        guess = 2.0f * value;
    } else if (magnitude < 10.0f) {
        guess = 0.5f * value;
    } else if (magnitude < 1000.0f) {
        guess = 0.01f * value;
    } else {
        guess = 1e-4f * value;
    }
    return NewtonSolveFloat(guess, n, value, PowThenAddFloat, PowDerivativeTimesN, 1.0f / 256.0f);
}
