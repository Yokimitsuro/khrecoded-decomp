#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xd0];
    s32 depth;
} TouchContext;

extern s32 FX_Div(s32 numer, s32 denom);

void ScreenToTouchVector(TouchContext *context, int screenX, int screenY, s32 *out) {
    int dx = screenX - 0x80;
    int dy;

    out[0] = FX_Div(dx > 0 ? (int)(0.5f + (float)(dx << 12)) : (int)((float)(dx << 12) - 0.5f), 0x40000);
    dy = 0x60 - screenY;
    out[1] = FX_Div(dy > 0 ? (int)(0.5f + (float)(dy << 12)) : (int)((float)(dy << 12) - 0.5f), 0x40000);
    out[2] = context->depth;
}
