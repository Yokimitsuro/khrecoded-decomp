#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_ov001_0206a8c8(fx32 rate);
extern void func_ov001_0206a7c0(s32 mode);

s32 EnterState12WithHalfRate_020ba8f0(void)
{
    func_ov001_0206a8c8(FX_Div(0x10000, 0x20000));
    func_ov001_0206a7c0(2);
    return 12;
}
