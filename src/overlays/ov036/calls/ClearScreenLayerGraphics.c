#include "nitro/types.h"

typedef struct ScreenLayer {
    u8 pad_00[0x14];
    void *buffer;
    u8 pad_18[0x34];
    s32 useWhiteClearColor;
} ScreenLayer;

extern void NNSi_FndFreeFromDefaultHeap(void *memory);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG1CharPtr(void);
extern void *G2S_GetBG0ScrPtr(void);
extern void *G2S_GetBG0CharPtr(void);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void G3X_SetClearColor(u32 color, u32 alpha, u32 depth, u32 polygonId, BOOL fog);

void ClearScreenLayerGraphics(ScreenLayer *layer, int screen)
{
    u16 backdropColor = 0;

    if (layer->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(layer->buffer);
        layer->buffer = NULL;
    }
    if (screen == 0) {
        MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
        MIi_CpuClearFast(0, G2_GetBG1CharPtr(), 0x20000);
        GX_LoadBGPltt(&backdropColor, 0, sizeof(backdropColor));
        if (layer->useWhiteClearColor != 0) {
            G3X_SetClearColor(0x7ffe, 0x1f, 0x7fff, 0x3f, FALSE);
            return;
        }
        G3X_SetClearColor(0, 0, 0x7fff, 0x3f, FALSE);
        return;
    }
    MIi_CpuClearFast(0, G2S_GetBG0ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG0CharPtr(), 0x20000);
    GXS_LoadBGPltt(&backdropColor, 0, sizeof(backdropColor));
}
