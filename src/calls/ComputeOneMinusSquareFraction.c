#include "nitro/types.h"

extern void FX_Sqrt(u32 value);

void ComputeOneMinusSquareFraction(int value)
{
    s64 squared = (s64)value * (s64)value + 0x800;
    FX_Sqrt(0x1000 - (u32)(squared >> 0xc));
}
