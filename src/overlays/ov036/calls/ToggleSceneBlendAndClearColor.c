#include "nitro/types.h"

typedef struct MosaicLayer {
    u8 pad_00[0x4c];
    s32 whiteClear;
} MosaicLayer;

typedef struct SceneWork {
    u8 pad_0000[0x1098];
    MosaicLayer *layer;
    u8 pad_109C[0x40];
    BOOL toggled;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

#define REG_DISPCNT (*(vu32 *)0x04000000)

extern SceneContext data_ov036_020c3940;
extern void G2x_SetBlendBrightnessExt_(u32 addr, int plane1, int plane2, int ev1, int ev2, int brightness);
extern void G3X_SetClearColor(unsigned color, unsigned alpha, unsigned depth, unsigned polygonID, BOOL fog);
extern void func_ov036_020bad5c(void);

void ToggleSceneBlendAndClearColor(void)
{
    SceneWork *work = data_ov036_020c3940.work;
    int planes = (REG_DISPCNT & 0x1f00) >> 8;

    G2x_SetBlendBrightnessExt_(0x04000050, planes, 0x22, 0, 0x10, -8);
    if (work->layer->whiteClear != 0) {
        G3X_SetClearColor(0x7ffe, 0x1f, 0x7fff, 0x3f, FALSE);
    } else {
        G3X_SetClearColor(0, 1, 0x7fff, 0x3f, FALSE);
    }
    data_ov036_020c3940.work->toggled = !data_ov036_020c3940.work->toggled;
    func_ov036_020bad5c();
}
