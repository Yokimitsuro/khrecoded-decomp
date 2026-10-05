#include "nitro/types.h"

typedef struct BgGraphics {
    u8 pad_00[0xc];
    s32 windowMask;
    void *bg2Screen;
    void *bg3Screen;
    void *charData;
    void *palette;
} BgGraphics;

#define REG_DISPCNT (*(vu32 *)0x04000000)

extern BgGraphics *data_ov036_020ca204;
extern void DC_FlushAll(void);
extern void ConfigureOverlay036BackgroundControls(void);
extern void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Scr(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void ApplyTextWindowBgOffsets(void);

void UploadAndFreeBgGraphics(void)
{
    BgGraphics *graphics = data_ov036_020ca204;

    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x300;
    DC_FlushAll();
    ConfigureOverlay036BackgroundControls();
    GX_LoadBG2Scr(graphics->bg2Screen, 0, 0x800);
    GX_LoadBG3Scr(graphics->bg3Screen, 0, 0x800);
    GX_LoadBG2Char(graphics->charData, 0, 0x10000);
    GX_LoadBG3Char(graphics->charData, 0, 0x10000);
    GX_LoadBGPltt(graphics->palette, 0, 0x200);
    NNSi_FndFreeFromDefaultHeap(graphics->palette);
    NNSi_FndFreeFromDefaultHeap(graphics->charData);
    NNSi_FndFreeFromDefaultHeap(graphics->bg2Screen);
    NNSi_FndFreeFromDefaultHeap(graphics->bg3Screen);
    graphics->palette = NULL;
    graphics->charData = NULL;
    graphics->bg2Screen = NULL;
    graphics->bg3Screen = NULL;
    REG_DISPCNT = (REG_DISPCNT & ~0xe000) | (graphics->windowMask << 13);
    ApplyTextWindowBgOffsets();
}
