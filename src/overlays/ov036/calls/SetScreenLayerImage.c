#include "nitro/types.h"

typedef struct ScreenLayer {
    u8 pad_00[0x28];
    s32 activeImageId;
    u8 pad_2C[0x20];
    s32 useWhiteClearColor;
    s32 pendingImageId;
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
extern void func_ov036_020bb9bc(ScreenLayer *layer, int screen);

void SetScreenLayerImage(int screen, s32 imageId)
{
    PanelWork *work = data_ov036_020c3940.work;
    ScreenLayer *layer = &work->layers[screen];
    s32 isBusy = work->isBusy;

    layer->pendingImageId = imageId;
    if (isBusy != 0) {
        return;
    }
    layer->activeImageId = imageId;
    layer->useWhiteClearColor = 0;
    func_ov036_020bb9bc(layer, screen);
}
