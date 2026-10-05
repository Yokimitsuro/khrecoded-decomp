#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xf4];
    s32 fadeLevel;
} ModeContext;

extern ModeContext *data_ov001_020a04e4;

extern void G2x_SetBlendAlpha_(vu32 *reg, int plane1, int plane2, int ev1, int ev2);

void ApplyModeFadeBlend(void)
{
    int level = data_ov001_020a04e4->fadeLevel;

    if (level > 16) {
        level = 16;
    } else if (level < 0) {
        level = 0;
    }
    G2x_SetBlendAlpha_((vu32 *)0x04000050, 4, 1, level, 16 - level);
}
