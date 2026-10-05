#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct Actor {
    u8 pad_000[0x340];
    fx32 baseTimeScale;
    u8 pad_344[0x958 - 0x344];
    fx32 timeScale;
} Actor;

extern fx32 FX_Mul(fx32 left, fx32 right);

void Actor_SetTimeScale(Actor *actor, fx32 scale)
{
    fx32 scaled = FX_Mul(FX32_ONE, scale);

    actor->baseTimeScale = scale;
    actor->timeScale = scaled;
}
