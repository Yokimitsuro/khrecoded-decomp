#include "libs/nitro/os/os_arena_internal.h"

typedef unsigned long u32;
extern u32 OS_GetConsoleType(void);

void *OS_GetInitArenaLo(OSArenaId arena)
{
    switch (arena) {
    case 0:
        return (void *)0x020d9c40;
    case 2:
        if (!OSi_ArenaState.mainExArenaEnabled) {
            return (void *)0;
        }
        if ((OS_GetConsoleType() & 0xf) == 1) {
            return (void *)0;
        } else {
            return (void *)0x023e0000;
        }
    case 3:
        return (void *)0x01fffec0;
    case 4:
        return (void *)0x027e0280;
    case 5:
        return (void *)0x02fff000;
    case 6:
        return (void *)0x037f8000;
    }
    return (void *)0;
}