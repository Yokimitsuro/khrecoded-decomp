#include "nitro/types.h"

typedef struct {
    int quot;
    int rem;
} div_t;

extern div_t MSL_Div(int numerator, int denominator);
extern div_t FloorDiv(int numerator, int denominator);
extern int func_02022584(int year);

int LeapDays(int year, int month)
{
    int days;
    div_t q;

    q = MSL_Div(year, 4);
    days = q.quot;

    q = MSL_Div(year, 100);
    days -= q.quot;

    if (year < 100) {
        q = FloorDiv(year + 899, 1000);
        days += q.quot;
    } else {
        q = FloorDiv(year - 100, 1000);
        days += q.quot + 1;
    }

    if (func_02022584(year)) {
        if (year < 0) {
            if (month > 1) {
                ++days;
            }
        } else if (month <= 1) {
            --days;
        }
    }

    return days;
}
