#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_0000[0xea4];
    s32 displayMode;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;
extern void StartScreenBrightnessFade(int screen, s32 brightness, s32 duration);

void StartScreenBrightnessFade_020bd6dc(int screen, s32 brightness, s32 duration)
{
    PanelWork *work = data_ov036_020c3940.work;

    if (screen == 0 && work->displayMode == 0x10) {
        screen = 2;
    }
    switch (screen) {
    case 0:
    case 1:
        StartScreenBrightnessFade(screen, brightness, duration);
        break;
    case 2:
        StartScreenBrightnessFade(0, brightness, duration);
        StartScreenBrightnessFade(1, brightness, duration);
        break;
    }
}
