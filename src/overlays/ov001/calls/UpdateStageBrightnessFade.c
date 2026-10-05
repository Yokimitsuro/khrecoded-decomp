#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageManager {
    u8 pad_00000[0x18f2c];
    s8 fadeStartBrightness;
    s8 fadeTargetBrightness;
    u8 pad_18f2e[2];
    fx32 fadeTime;
    fx32 fadeDuration;
} StageManager;

extern StageManager *data_ov001_020a0528;
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void SetBrightnessAndSyncMain(int value);

void UpdateStageBrightnessFade(void)
{
    StageManager *manager = data_ov001_020a0528;
    s8 delta;

    if (manager->fadeDuration != 0) {
        manager->fadeTime += 0x1000;
        if (manager->fadeTime <= manager->fadeDuration) {
            fx32 progress = FX_Div(manager->fadeTime, manager->fadeDuration);
            delta = manager->fadeTargetBrightness - manager->fadeStartBrightness;
            SetBrightnessAndSyncMain((s8)(manager->fadeStartBrightness + (s8)((delta * progress) >> 12)));
            return;
        }
        manager->fadeDuration = 0;
        SetBrightnessAndSyncMain(manager->fadeTargetBrightness);
        return;
    }
    if (manager->fadeTargetBrightness != 0) {
        SetBrightnessAndSyncMain(manager->fadeTargetBrightness);
    }
}
