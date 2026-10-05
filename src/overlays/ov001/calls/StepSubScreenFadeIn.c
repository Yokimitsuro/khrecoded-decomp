#include "nitro/types.h"

typedef struct FadeTask {
    u8 pad_00[0x30];
    int state;
    u8 pad_34[0x24];
    int step;
    u8 pad_5c[0x84];
    int brightness;
} FadeTask;

extern void SetSecondaryBrightness(int brightness);

void StepSubScreenFadeIn(FadeTask *task)
{
    task->brightness += task->step;
    if (task->brightness >= 0) {
        task->brightness = 0;
        task->state = 6;
    }
    SetSecondaryBrightness(task->brightness);
}
