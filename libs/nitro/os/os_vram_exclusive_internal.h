#ifndef NITRO_OS_VRAM_EXCLUSIVE_INTERNAL_H
#define NITRO_OS_VRAM_EXCLUSIVE_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

enum {
    OS_VRAM_BANK_KINDS = 9,
    OS_VRAM_BANK_ID_ALL = 0x01ff
};

extern u32 OSi_VramExclusive;
extern u16 OSi_VramLockId[OS_VRAM_BANK_KINDS];

u32 OsCountZeroBits(u32 bitmap);
void OSi_InitVramExclusive(void);
void OSi_UnlockVram(u16 bank, u16 lockId);

#endif
