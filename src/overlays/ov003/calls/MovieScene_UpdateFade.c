#include "nitro/types.h"

#define REG_MASTER_BRIGHT_MAIN ((vu16 *)0x0400006c)
#define REG_MASTER_BRIGHT_SUB ((vu16 *)0x0400106c)

typedef struct MovieScene {
    u8 pad_000[0x8bc];
    BOOL fadeToWhite;
    s32 fadeStep;
    u8 pad_8c4[0x08];
    s32 mainBrightnessLimit;
} MovieScene;

extern int GetSubtitleStreamFrame(void);
extern void GXx_SetMasterBrightness_(vu16 *reg, int brightness);

void MovieScene_UpdateFade(MovieScene *scene)
{
    int level;

    if (scene->fadeStep < 0) {
        if (GetSubtitleStreamFrame() <= 0) {
            return;
        }
        GXx_SetMasterBrightness_(REG_MASTER_BRIGHT_SUB, 0);
        return;
    }
    if (scene->fadeStep >= 16) {
        return;
    }
    level = ++scene->fadeStep;
    if (!scene->fadeToWhite) {
        level = -level;
    }
    GXx_SetMasterBrightness_(REG_MASTER_BRIGHT_SUB, level);
    if (level >= scene->mainBrightnessLimit) {
        level = scene->mainBrightnessLimit;
    }
    GXx_SetMasterBrightness_(REG_MASTER_BRIGHT_MAIN, level);
}
