#ifndef NITRO_GX_INTERNAL_H
#define NITRO_GX_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef volatile u32 vu32;

typedef enum GXBGMode {
    GX_BGMODE_0 = 0,
    GX_BGMODE_1,
    GX_BGMODE_2,
    GX_BGMODE_3,
    GX_BGMODE_4,
    GX_BGMODE_5,
    GX_BGMODE_6
} GXBGMode;

typedef enum GXBG0As {
    GX_BG0_AS_2D = 0,
    GX_BG0_AS_3D = 1
} GXBG0As;

typedef enum GXDispMode {
    GX_DISPMODE_OFF = 0,
    GX_DISPMODE_GRAPHICS = 1,
    GX_DISPMODE_VRAM_A = 2,
    GX_DISPMODE_MMEM = 3,
    GX_DISPMODE_VRAM_B = 6,
    GX_DISPMODE_VRAM_C = 10,
    GX_DISPMODE_VRAM_D = 14
} GXDispMode;

#define FALSE 0
#define TRUE 1
#define REG_GX_DISPCNT (*(vu32 *)0x04000000)
#define GX_DISPCNT_BG_MODE_MASK 0x00000007
#define GX_DISPCNT_BG0_3D_MASK 0x00000008
#define GX_DISPCNT_DISPLAY_MODE_MASK 0x00030000
#define GX_DISPCNT_VRAM_BLOCK_MASK 0x000c0000

typedef struct GXDataState {
    u16 isDisplayOn;
    u16 padding;
    u32 dmaId;
} GXDataState;

typedef struct GXBssState {
    u16 displayMode;
    volatile u16 vramLockId;
} GXBssState;

extern GXDataState gGXDataState;
extern GXBssState gGXBssState;

BOOL GX_IsDispOn(void);
void GX_DispOff(void);
void GX_DispOn(void);
void GX_SetGraphicsMode(GXDispMode displayMode, GXBGMode bgMode, GXBG0As bg0Mode);

#endif