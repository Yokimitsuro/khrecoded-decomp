#include "nitro/types.h"

typedef struct BrightnessFade {
    s32 from;
    s32 to;
    s32 duration;
    s32 current;
    s32 timer;
} BrightnessFade;

typedef struct ScreenLayer {
    u8 pad_00[0x24];
    u16 flags;
    u8 pad_26[0x2e];
} ScreenLayer;

typedef struct SceneWork {
    u8 pad_0000[0xc80];
    s32 skipAnimations;
    u8 pad_0C84[0x200];
    BrightnessFade fades[2];
    u8 pad_0EAC[0x1ec];
    ScreenLayer *layers;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

extern SceneContext data_ov036_020c3940;
extern int func_02029f5c(void);
extern int func_02029f6c(void);
extern void SetBrightnessAndSyncMain(int brightness);
extern void SetSecondaryBrightness(int brightness);
extern void GXx_SetMasterBrightness_(u32 reg, int brightness);

void StartScreenBrightnessFade(int screen, int level, s32 duration)
{
    SceneWork *work = data_ov036_020c3940.work;
    ScreenLayer *layer = &work->layers[screen];
    BrightnessFade *fade = &work->fades[screen];
    int brightness;

    fade->to = level - 0x10;
    fade->current = level - 0x10;
    if (work->skipAnimations != 0) {
        return;
    }
    fade->timer = 0;
    fade->duration = duration;
    if (duration > 0) {
        if (screen == 0) {
            brightness = func_02029f5c();
        } else {
            brightness = func_02029f6c();
        }
        fade->current = brightness;
        fade->from = brightness;
        layer->flags |= 0x8;
    } else if (work->skipAnimations != 0 && fade->to == 0) {
        return;
    }
    if (screen == 0) {
        SetBrightnessAndSyncMain(fade->current);
        GXx_SetMasterBrightness_(0x0400006c, fade->current);
    } else {
        SetSecondaryBrightness(fade->current);
        GXx_SetMasterBrightness_(0x0400106c, fade->current);
    }
}
