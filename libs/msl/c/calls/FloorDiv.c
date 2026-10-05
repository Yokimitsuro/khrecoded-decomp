#include "nitro/types.h"

typedef struct MSLDivResult {
    int quotient;
    int remainder;
} MSLDivResult;

extern int _s32_div_f(int numerator, int denominator);

MSLDivResult FloorDiv(int numerator, int denominator)
{
    int quotient;
    int remainder;
    int numeratorSign;
    int denominatorSign;
    int resultSign;
    MSLDivResult result;

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
    quotient = resultSign * _s32_div_f(numerator, denominator);
    remainder =
        numerator * numeratorSign - quotient * denominator * denominatorSign;

    if (remainder != 0 && resultSign < 0) {
        remainder += denominator * denominatorSign;
        quotient--;
    }

    result.quotient = quotient;
    result.remainder = remainder;
    return result;
}
