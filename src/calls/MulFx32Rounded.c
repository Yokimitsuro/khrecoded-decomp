#include "nitro/types.h"

extern s64 PanelState_NoOpG(s64 value);

s64 MulFx32Rounded(s32 a, s32 b)
{
    return PanelState_NoOpG(((s64)a * b + 0x800) >> 12);
}
