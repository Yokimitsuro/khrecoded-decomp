#include "nitro/types.h"

extern int _s32_div_f(int numerator, int denominator);

int FloorMod(int numerator, int denominator)
{
    int numeratorSign;
    int denominatorSign;
    int resultSign;
    int quotient;
    int remainder;

    numeratorSign = 1;
    denominatorSign = 1;
    if (numerator < 0) {
        numerator = -numerator;
        numeratorSign = -1;
    }
    if (denominator < 0) {
        denominatorSign = -1;
        denominator = -denominator;
    }

    resultSign = numeratorSign * denominatorSign;
    remainder = _s32_div_f(numerator, denominator);
    quotient = resultSign * remainder;
    remainder =
        numerator * numeratorSign - quotient * denominator * denominatorSign;

    if (remainder != 0 && resultSign < 0) {
        remainder += denominator * denominatorSign;
    }
    return remainder;
}
