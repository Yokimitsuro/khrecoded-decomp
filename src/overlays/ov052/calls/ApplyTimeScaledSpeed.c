#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 func_ov001_0206db44(void);
extern fx32 FX_Mul(fx32 a, fx32 b);

/* Scales entity speed by global time factor */
void ApplyTimeScaledSpeed(int entity, fx32 targetSpeed)
{
    fx32 speed;

    speed = func_ov001_0206db44();
    speed = FX_Mul(*(fx32 *)(entity + 0x9f0), speed);
    speed = FX_Mul(speed, targetSpeed);
    *(fx32 *)(entity + 0x340) = speed;
    *(fx32 *)(entity + 0x9ec) = speed;
    *(fx32 *)(entity + 0x9f4) = targetSpeed;
}
