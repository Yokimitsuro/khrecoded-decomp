#include "libs/nitro/os/os_vram_exclusive_internal.h"

void OSi_InitVramExclusive(void)
{
    s32 i;

    OSi_VramExclusive = 0;
    for (i = 0; i < OS_VRAM_BANK_KINDS; i++) {
        OSi_VramLockId[i] = 0;
    }
}
