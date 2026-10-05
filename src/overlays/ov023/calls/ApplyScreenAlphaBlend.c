#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x58];
    u8 objManager[1];
} ScreenState;

extern void set_engine_alpha_blend(char *object, int blendAlpha);
extern ScreenState *data_ov023_020b6f84;

void ApplyScreenAlphaBlend(void)
{
    set_engine_alpha_blend((char *)data_ov023_020b6f84->objManager, 8);
}
