#include "nitro/types.h"

typedef struct Tween {
    s32 mode;
    s32 duration_ticks;
    s32 from;
    s32 to;
    s64 startTick;
    u32 flags;
} Tween;

typedef struct HudSlide {
    s32 state;
    Tween tween;
} HudSlide;

typedef struct Hud {
    u8 pad_000[0x550];
    HudSlide slide;
} Hud;

typedef struct HudHandle {
    u32 unk_00;
    Hud *hud;
} HudHandle;

extern HudHandle data_ov001_020a04c4;

extern void FlushAndCloseSceneMessage(Hud *hud);
extern void func_02052528(Tween *tween, int mode, int from, int to, int duration);
extern void func_02052570(Tween *tween);

BOOL BeginHudSlideClose(void)
{
    Hud *hud = data_ov001_020a04c4.hud;
    HudSlide *slide = &hud->slide;
    BOOL result = TRUE;

    switch (slide->state) {
    case 1:
        result = FALSE;
        break;
    case 2:
        FlushAndCloseSceneMessage(hud);
    case 3:
        func_02052528(&slide->tween, 4, 0, 0x28000, 500);
        func_02052570(&slide->tween);
        slide->state = 4;
        break;
    case 4:
        break;
    }
    return result;
}
