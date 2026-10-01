#include "libs/nitro/gx/gx_vramcnt_internal.h"

extern void OSi_UnlockVram(u16 banks, u16 lockId);
extern u16 GXi_VRamLockId;

int disableBankForX_(u16 *bankState)
{
    int banks = *bankState;
    *bankState = 0;

    if (banks & GX_VRAM_A)
        reg_GX_VRAMCNT_A = 0;
    if (banks & GX_VRAM_B)
        reg_GX_VRAMCNT_B = 0;
    if (banks & GX_VRAM_C)
        reg_GX_VRAMCNT_C = 0;
    if (banks & GX_VRAM_D)
        reg_GX_VRAMCNT_D = 0;
    if (banks & GX_VRAM_E)
        reg_GX_VRAMCNT_E = 0;
    if (banks & GX_VRAM_F)
        reg_GX_VRAMCNT_F = 0;
    if (banks & GX_VRAM_G)
        reg_GX_VRAMCNT_G = 0;
    if (banks & GX_VRAM_H)
        reg_GX_VRAMCNT_H = 0;
    if (banks & GX_VRAM_I)
        reg_GX_VRAMCNT_I = 0;

    OSi_UnlockVram((u16)banks, GXi_VRamLockId);
    return banks;
}
