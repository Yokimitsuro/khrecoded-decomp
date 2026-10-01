#include "libs/nitro/os/os_types_internal.h"

#define REG_VRAMCNT_A (*(volatile u8 *)0x04000240)
#define REG_VRAMCNT_B (*(volatile u8 *)0x04000241)
#define REG_VRAMCNT_C (*(volatile u8 *)0x04000242)
#define REG_VRAMCNT_D (*(volatile u8 *)0x04000243)
#define REG_VRAMCNT_E (*(volatile u8 *)0x04000244)
#define REG_VRAMCNT_F (*(volatile u8 *)0x04000245)
#define REG_VRAMCNT_G (*(volatile u8 *)0x04000246)
#define REG_VRAMCNT_H (*(volatile u8 *)0x04000248)
#define REG_VRAMCNT_I (*(volatile u8 *)0x04000249)

void GX_VRAMCNT_SetLCDC_(int banks)
{
    if (banks & (1 << 0))
        REG_VRAMCNT_A = 0x80;
    if (banks & (1 << 1))
        REG_VRAMCNT_B = 0x80;
    if (banks & (1 << 2))
        REG_VRAMCNT_C = 0x80;
    if (banks & (1 << 3))
        REG_VRAMCNT_D = 0x80;
    if (banks & (1 << 4))
        REG_VRAMCNT_E = 0x80;
    if (banks & (1 << 5))
        REG_VRAMCNT_F = 0x80;
    if (banks & (1 << 6))
        REG_VRAMCNT_G = 0x80;
    if (banks & (1 << 7))
        REG_VRAMCNT_H = 0x80;
    if (banks & (1 << 8))
        REG_VRAMCNT_I = 0x80;
}
