#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s64 PanelState_NoOpF(s64 value);

s64 MulFx32ToFx64(fx32 a, fx32 b)
{
    return PanelState_NoOpF(((s64)a * b + 0x800) >> 12);
}
