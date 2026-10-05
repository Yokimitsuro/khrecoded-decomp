#include "nitro/types.h"

typedef struct BgGraphics {
    u8 *screen;
    u16 *character;
    u8 *palette;
} BgGraphics;

typedef struct ScreenLayer {
    u8 pad_00[0x14];
    void *buffer;
    BgGraphics graphics;
    u8 pad_24[0x4];
    u32 imageId;
    u8 pad_2c[0x8];
    s32 scrollX;
    s32 scrollY;
    u8 pad_3c[0x4];
    s32 verticalBias;
} ScreenLayer;

typedef struct SlotScene {
    u8 pad_0000[0x1050];
    u32 imageBase;
    u8 pad_1054[0x10dc - 0x1054];
    int highlight;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3940;
extern void NNSi_FndFreeFromDefaultHeap(void *memory);
extern void *Archive_LoadFile(u32 fileId, u32 kind);
extern void GetBgDataFromArchive(BgGraphics *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern int Bg_LoadPaletteForScreen(int bg, u8 *palette, u8 *screen, int offset, int size);
extern int Gfx_EnqueueTableCmdAt14(int idx, void *p, int arg2, int arg3);
extern int Gfx_EnqueueTableCmdAtC(int idx, void *p, int arg2, int arg3);
extern void DispatchByPartType(int bg, u8 *screen, u16 *character, u8 *palette, int arg4, int arg5);
extern void G3X_SetClearColor(u32 color, u32 alpha, u32 depth, u32 polygonId, BOOL fog);

#define REG_BG1OFS (*(vu32 *)0x04000014)
#define REG_DB_BG0OFS (*(vu32 *)0x04001010)

void LoadScreenLayerImage(ScreenLayer *layer, int screen)
{
    SlotScene *scene = data_ov036_020c3940.scene;

    if (layer->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(layer->buffer);
        layer->buffer = NULL;
    }
    layer->buffer = Archive_LoadFile((((scene->imageBase + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (layer->imageId & 0x1ff), 0xd);
    GetBgDataFromArchive(&layer->graphics, layer->buffer, 0, 0, 0);
    if (screen == 0) {
        Bg_LoadPaletteForScreen(1, layer->graphics.palette, layer->graphics.screen, 0, *(int *)(layer->graphics.palette + 8));
        Gfx_EnqueueTableCmdAt14(1, layer->graphics.character, 0, *(int *)((u8 *)layer->graphics.character + 0x10));
        Gfx_EnqueueTableCmdAtC(1, layer->graphics.screen, 0, *(int *)(layer->graphics.screen + 8));
    } else {
        DispatchByPartType(4, layer->graphics.screen, layer->graphics.character, layer->graphics.palette, 2, 4);
    }
    if (*layer->graphics.character > 24) {
        layer->verticalBias = ((*layer->graphics.character - 24) * 8) / 2;
    } else {
        layer->verticalBias = 0;
    }
    if (screen == 0) {
        REG_BG1OFS = (-layer->scrollX & 0x1ff) | ((-(layer->scrollY - layer->verticalBias) << 16) & 0x1ff0000);
        G3X_SetClearColor(0, scene->highlight, 0x7fff, 0x3f, FALSE);
    } else {
        REG_DB_BG0OFS = (-layer->scrollX & 0x1ff) | ((-(layer->scrollY - layer->verticalBias) << 16) & 0x1ff0000);
    }
}
