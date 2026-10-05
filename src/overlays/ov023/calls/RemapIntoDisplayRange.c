#include "nitro/types.h"

extern int FX_Mul(int left, int right);
extern int FX_Div(int numer, int denom);

int RemapIntoDisplayRange(int start, int end, int value)
{
    int result = 0x21000;
    result += FX_Div(FX_Mul(0xbe000, value - start), end - start);
    return result;
}
