#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[2];
    s8 phase;
    u8 pad_03[0x21];
    VecFx32 velocity;
} MovingEffect;

extern BOOL UpdateEffectMovePhase(void *context, MovingEffect *effect, int delta);

BOOL UpdateStoppingEffect(void *context, MovingEffect *effect, int delta)
{
    BOOL result = UpdateEffectMovePhase(context, effect, delta);

    if (effect->phase == 2) {
        effect->velocity.z = 0;
        effect->velocity.y = 0;
        effect->velocity.x = 0;
    }
    return result;
}
