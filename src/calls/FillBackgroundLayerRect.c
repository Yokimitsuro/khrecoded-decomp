#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    u16 tile;
    u16 width;
    u16 height;
    u8 pad_32;
    u8 screenKind;
} LayerInfo;

extern void NNS_G2dMapScrToCharText(u16 *dst, int width, int height, int x, int y,
                                                  int mapW, int tile, int palette);

void FillBackgroundLayerRect(LayerInfo *info, u16 *dst, int x, int y, u8 palette)
{
    u32 sel = (u32)info;
    int size;
    volatile u16 buf[8];

    switch (info->screenKind) {
    case 0: { u16 v = *(volatile u16 *)0x04000008; buf[7] = v; sel = v; break; }
    case 1: { u16 v = *(volatile u16 *)0x0400000a; buf[6] = v; sel = v; break; }
    case 2: { u16 v = *(volatile u16 *)0x0400000c; buf[5] = v; sel = v; break; }
    case 3: { u16 v = *(volatile u16 *)0x0400000e; buf[4] = v; sel = v; break; }
    case 4: { u16 v = *(volatile u16 *)0x04001008; buf[3] = v; sel = v; break; }
    case 5: { u16 v = *(volatile u16 *)0x0400100a; buf[2] = v; sel = v; break; }
    case 6: { u16 v = *(volatile u16 *)0x0400100c; buf[1] = v; sel = v; break; }
    case 7: { u16 v = *(volatile u16 *)0x0400100c; buf[0] = v; sel = v; break; }
    default:
        goto skip;
    }
    sel = (u32)(u16)sel >> 0xe;
skip:
    size = (sel == 0 || sel == 2) ? 0x20 : 0x40;

    NNS_G2dMapScrToCharText(dst, info->width, info->height, x, y, size, info->tile, palette);
}
