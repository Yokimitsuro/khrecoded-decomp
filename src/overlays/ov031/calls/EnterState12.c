#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_ov001_0206a8c8(fx32 value);
extern void BeginScreenFadeOut(int mode);

u32 EnterState12(void)
{
    func_ov001_0206a8c8(FX_Div(0x10000, 0x20000));
    BeginScreenFadeOut(2);
    return 12;
}
