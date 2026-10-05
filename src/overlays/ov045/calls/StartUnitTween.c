#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct Tween Tween;

extern void func_02052528(Tween *tween, int mode, fx32 startValue, fx32 endValue, int duration);
extern void func_02052570(Tween *tween);

void StartUnitTween(Tween *tween, int duration)
{
    func_02052528(tween, 0, 0, FX32_ONE, duration);
    func_02052570(tween);
}
