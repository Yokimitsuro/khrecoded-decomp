#include "libs/nitro/card/card_rom_internal.h"

extern int OSi_IsThreadInitialized;
extern int OS_IsAlarmAvailable(void);
extern void OS_Sleep(u32 msec);

void CARDi_RefreshRom(u32 warningMask)
{
    if (CARDi_ReadRomStatusCore() & warningMask) {
        CARDi_RefreshRomCore();
        while (!(CARDi_ReadRomStatusCore() & 0x20)) {
            if (OSi_IsThreadInitialized && OS_IsAlarmAvailable()) {
                OS_Sleep(1);
            }
        }
    }
}
