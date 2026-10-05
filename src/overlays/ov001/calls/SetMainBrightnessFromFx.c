#include "nitro/types.h"

extern void SetBrightnessAndSyncMain(int value);

void SetMainBrightnessFromFx(s32 value)
{
    SetBrightnessAndSyncMain(value >> 12);
}
