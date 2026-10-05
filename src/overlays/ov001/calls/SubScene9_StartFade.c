#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Tween {
    s32 mode;
    s32 duration;
    fx32 startValue;
    fx32 endValue;
    u8 pad_10[0xc];
} Tween;

typedef struct SubScene9 {
    u8 state;
    u8 requestValue;
    u8 pad_02[6];
    Tween fadeTween;
} SubScene9;

extern SubScene9 *data_ov001_020a0488;
extern void func_02052528(Tween *tween, int mode, fx32 startValue, fx32 endValue, int duration);
extern void func_02052570(Tween *tween);

void SubScene9_StartFade(BOOL fadeIn)
{
    SubScene9 *scene;

    scene = data_ov001_020a0488;
    if (fadeIn) {
        func_02052528(&scene->fadeTween, 1, 0, 0x10000, 400);
        func_02052570(&scene->fadeTween);
        return;
    }
    func_02052528(&scene->fadeTween, 2, 0x10000, 0, 400);
    func_02052570(&scene->fadeTween);
}
