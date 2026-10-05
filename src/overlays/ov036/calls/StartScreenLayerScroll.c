#include "nitro/types.h"

typedef struct ScreenLayer {
    u8 pad_00[0x24];
    u16 flags;
    u8 pad_26[0x2];
    s32 activeImageId;
    s32 startX;
    s32 startY;
    s32 scrollX;
    s32 scrollY;
    u8 pad_3C[0x4];
    s32 scrollYOffset;
    s32 scrollFrame;
    u32 scrollDuration;
    u8 pad_4C[0x8];
} ScreenLayer;

typedef struct PanelWork {
    u8 pad_0000[0xc80];
    s32 isBusy;
    u8 pad_0C84[0x414];
    ScreenLayer *layers;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;
extern void func_ov036_020bbfb0(int screen);

void StartScreenLayerScroll(int screen, s32 x, s32 y, s32 duration)
{
    PanelWork *work = data_ov036_020c3940.work;
    ScreenLayer *layer = &work->layers[screen];

    layer->startX = layer->scrollX;
    layer->startY = layer->scrollY;
    layer->scrollX = -x;
    layer->scrollY = y;
    if (work->isBusy != 0) {
        return;
    }
    layer->scrollFrame = duration;
    layer->scrollDuration = duration;
    layer->flags |= 4;
    if (duration == 0) {
        func_ov036_020bbfb0(screen);
    }
}
