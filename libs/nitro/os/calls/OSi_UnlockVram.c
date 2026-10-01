#include "libs/nitro/os/os_vram_exclusive_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);

void OSi_UnlockVram(u16 bank, u16 lockId)
{
    u32 workMap;
    s32 zeroBits;
    OSIntrMode enabled = OS_DisableInterrupts();

    workMap = bank & OSi_VramExclusive & OS_VRAM_BANK_ID_ALL;
    while (1) {
        zeroBits = 31 - (s32)OsCountZeroBits(workMap);
        if (zeroBits < 0) {
            break;
        }

        workMap &= ~(1 << zeroBits);
        if (OSi_VramLockId[zeroBits] == lockId) {
            OSi_VramLockId[zeroBits] = 0;
            OSi_VramExclusive &= ~(1 << zeroBits);
        }
    }

    OS_RestoreInterrupts(enabled);
}
