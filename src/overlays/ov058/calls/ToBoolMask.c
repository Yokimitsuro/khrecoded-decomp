#include "nitro/types.h"

// Converts a nonzero value to an all-bits mask
s32 ToBoolMask(s32 value)
{
    return -(s32)(u32)(value != 0);
}
