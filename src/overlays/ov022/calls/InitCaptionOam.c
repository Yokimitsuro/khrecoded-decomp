#include "nitro/types.h"

typedef struct {
    u32 attr01;
    u16 attr2;
    u16 affine;
} OamEntry;

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void DC_FlushRange(void *buffer, u32 size);
extern void GX_LoadOAM(const void *src, u32 offset, u32 size);
extern void GXS_LoadOAM(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_DISPCNT_SUB (*(vu32 *)0x04001000)

void InitCaptionOam(BOOL mainScreen) {
    int count = 0;
    OamEntry *oam = NNS_FndAllocFromDefaultExpHeapEx(0x400, 0x20);
    int i;
    int x;
    int y;

    if (mainScreen) {
        REG_DISPCNT = (REG_DISPCNT & 0xffbfff9f) | 0x20;
    } else {
        REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x60) | 0x20;
    }
    for (i = 0; i < 0x80; i++) {
        oam[i].attr01 = 0xc0;
        *(u32 *)&oam[i].attr2 = 0;
    }
    for (y = 0; y < 0xc0; y += 0x40) {
        for (x = 0; x < 0x100; x += 0x40) {
            oam[count].attr01 = ((y + 0x10) & 0xff) | 0xc0000c00 | ((u32)(x << 23) >> 7);
            oam[count].attr2 = (x / 8 + ((y / 8) << 5)) | 0xfc00;
            count++;
        }
    }
    DC_FlushRange(oam, 0x400);
    if (mainScreen) {
        GX_LoadOAM(oam, 0, 0x400);
    } else {
        GXS_LoadOAM(oam, 0, 0x400);
    }
    NNSi_FndFreeFromDefaultHeap(oam);
}
