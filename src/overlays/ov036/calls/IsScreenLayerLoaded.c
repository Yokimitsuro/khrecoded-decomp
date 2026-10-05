#include "nitro/types.h"

typedef struct ScreenLayer {
    u8 pad_00[0x24];
    u16 loadedCount;
    u8 pad_26[0x2e];
} ScreenLayer;

typedef struct PanelWork {
    u8 pad_0000[0x1098];
    ScreenLayer *layers;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;

BOOL IsScreenLayerLoaded(int screen)
{
    return data_ov036_020c3940.work->layers[screen].loadedCount != 0;
}
