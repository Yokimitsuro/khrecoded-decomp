#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x30];
    s32 phase;
    fx32 timer;
    u8 pad_038[0x2a4 - 0x38];
    s32 fadeValue;
} OverlayState;

extern OverlayState data_ov058_020d8a44;

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_ov001_0206e750(int brightness);
extern void func_ov001_0206e7c0(void);
extern void func_ov058_020d7d40(void);
extern void ClearStageEventsAndPlayerFlags(OverlayState *state);

static inline fx32 MulFx(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

void UpdateBlastFadeSequence(fx32 delta)
{
    OverlayState *state = &data_ov058_020d8a44;
    fx32 level;

    switch (state->phase) {
    case 1:
        state->timer += delta;
        level = MulFx(FX_Div(state->timer, 0x9000), 0x10000);
        func_ov001_0206e750((s8)((level + 0xfff) >> 12));
        if (level >= 0x10000) {
            state->phase = 2;
            state->timer = 0;
            state->fadeValue = 0;
        }
        break;
    case 2:
        state->timer += delta;
        func_ov001_0206e750(0x10);
        if (state->timer >= 0x1e000) {
            state->phase = 3;
            state->timer = 0;
            func_ov058_020d7d40();
            ClearStageEventsAndPlayerFlags(state);
        }
        break;
    case 3:
        state->timer += delta;
        level = MulFx(FX_Div(state->timer, 0xf000), 0x10000);
        func_ov001_0206e750((s8)(0x10 - ((level + 0xfff) >> 12)));
        if (level >= 0x10000) {
            func_ov001_0206e7c0();
            state->phase = 0;
            state->timer = 0;
        }
        break;
    }
}
