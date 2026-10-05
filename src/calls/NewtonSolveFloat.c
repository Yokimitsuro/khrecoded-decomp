#include "nitro/types.h"

typedef float (*NewtonFunc)(float x, float target, float arg);
typedef float (*NewtonDeriv)(float x, float target);

extern double MSL_Fabs(double x);
extern float func_0202354c(double x);

float NewtonSolveFloat(float x, float target, float arg, NewtonFunc func, NewtonDeriv deriv, float epsilon)
{
    u16 iter;
    float next;

    for (iter = 0; iter < 1000; iter++) {
        next = x - func(x, arg, target) / deriv(x, target);
        if (func_0202354c(MSL_Fabs(next - x)) < epsilon) {
            return next;
        }
        x = next;
    }
    return next;
}
