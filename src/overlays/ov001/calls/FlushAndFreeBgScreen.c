#include "nitro/types.h"

typedef struct LayerList {
    int layers[3];
} LayerList;

typedef struct BgScreen {
    u8 pad_000[0x448];
    void *bg3Char;
    void *bg2Char;
    void *screenBuffers[3];
    void *palette;
} BgScreen;

extern LayerList data_ov001_0209dbd4;
extern int func_ov001_0207123c(void);
extern void DC_FlushAll(void);
extern int func_ov027_020b9e10(int widgets, int layer);
extern void func_ov027_020b9e20(int widgets, int layer);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBGPltt(void *dest, u32 srcOffset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FlushAndFreeBgScreen(BgScreen *screen)
{
    int widgets = func_ov001_0207123c();
    LayerList list = data_ov001_0209dbd4;
    int *layers = list.layers;
    int i;

    DC_FlushAll();
    for (i = 0; i < 3; i++) {
        int layer = layers[i];
        MIi_CpuCopyFast(screen->screenBuffers[i], (void *)func_ov027_020b9e10(widgets, layer), 0x800);
        func_ov027_020b9e20(widgets, layer);
    }
    GX_LoadBG3Char(screen->bg3Char, 0, 0x5b00);
    GX_LoadBG2Char(screen->bg2Char, 0, 0x1000);
    GX_LoadBGPltt(screen->palette, 0, 0x200);
    NNSi_FndFreeFromDefaultHeap(screen->palette);
    NNSi_FndFreeFromDefaultHeap(screen->bg2Char);
    NNSi_FndFreeFromDefaultHeap(screen->bg3Char);
    screen->palette = NULL;
    screen->bg2Char = NULL;
    screen->bg3Char = NULL;
    for (i = 0; i < 3; i++) {
        NNSi_FndFreeFromDefaultHeap(screen->screenBuffers[i]);
        screen->screenBuffers[i] = NULL;
    }
}
