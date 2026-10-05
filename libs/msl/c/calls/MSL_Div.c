#include "nitro/types.h"

typedef struct MSLDivResult {
    int quotient;
    int remainder;
} MSLDivResult;

extern int _s32_div_f(int numerator, int denominator);

MSLDivResult MSL_Div(int numerator, int denominator)
{
    int numeratorSign;
    int denominatorSign;
    MSLDivResult result;

    numeratorSign = 1;
    denominatorSign = 1;

    if (numerator < 0) {
        numerator = -numerator;
        numeratorSign = -1;
    }
    if (denominator < 0) {
        denominator = -denominator;
        denominatorSign = -1;
    }

    result.quotient = _s32_div_f(numerator, denominator);
    result.quotient *= numeratorSign * denominatorSign;
    result.remainder =
        numerator * numeratorSign -
        result.quotient * denominator * denominatorSign;
    return result;
}
