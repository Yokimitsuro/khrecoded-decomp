#include "libs/nitro/os/os_arena_internal.h"

typedef unsigned long u32;
typedef signed long s32;
extern u32 OS_GetConsoleType(void);
extern u32 SDK_AUTOLOAD_DTCM_START;
extern void SDK_SYS_STACKSIZE(void);
extern void SDK_IRQ_STACKSIZE(void);
extern void SDK_SECTION_ARENA_DTCM_START(void);

void *OS_GetInitArenaHi(OSArenaId arena)
{
    switch (arena) {
    case 0:
        return (void *)0x023e0000;
    case 2:
        if (!OSi_ArenaState.mainExArenaEnabled) {
            return (void *)0;
        }
        if ((OS_GetConsoleType() & 0xf) == 1) {
            return (void *)0;
        } else {
            return (void *)0x02700000;
        }
    case 3:
        return (void *)0x02000000;
    case 4:
    {
        u32 irqStackLo;
        u32 sysStackLo;
        irqStackLo = (u32)&SDK_AUTOLOAD_DTCM_START + 0x3f80 - (u32)SDK_IRQ_STACKSIZE;
        if ((s32)SDK_SYS_STACKSIZE == 0) {
            sysStackLo = (u32)&SDK_AUTOLOAD_DTCM_START;
            if (sysStackLo < (u32)SDK_SECTION_ARENA_DTCM_START) {
                sysStackLo = (u32)SDK_SECTION_ARENA_DTCM_START;
            }
        } else if ((s32)SDK_SYS_STACKSIZE < 0) {
            sysStackLo = (u32)SDK_SECTION_ARENA_DTCM_START - (s32)SDK_SYS_STACKSIZE;
        } else {
            sysStackLo = irqStackLo - (s32)SDK_SYS_STACKSIZE;
        }
        return (void *)sysStackLo;
    }
    case 5:
        return (void *)0x02fff680;
    case 6:
        return (void *)0x037f8000;
    }
    return (void *)0;
}