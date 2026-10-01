#include "libs/nitro/os/os_types_internal.h"

extern u32 OS_GetConsoleType(void);
extern void *OS_GetInitArenaHi(int arena);
extern void OS_SetArenaHi(int arena, void *high);
extern void *OS_GetInitArenaLo(int arena);
extern void OS_SetArenaLo(int arena, void *low);
extern void OS_SetProtectionRegionEx(u32 region, u32 address, u32 size);

void OS_InitArenaEx(void)
{
    u32 consoleType = OS_GetConsoleType();
    u32 memorySize = consoleType & 3;

    OS_SetArenaHi(2, OS_GetInitArenaHi(2));
    OS_SetArenaLo(2, OS_GetInitArenaLo(2));
    OS_SetProtectionRegionEx(1, 0x02000000, 0x2a);
}
