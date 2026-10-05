#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 data[0xd4];
} HitResult;

typedef struct {
    u8 pad_00[2];
    s8 state;
    u8 pad_03;
    s32 timer;
    u8 pad_08[0x28];
    u8 animation[0xa4];
    VecFx32 position;
} EffectObj;

extern const VecFx32 data_0205344c;

extern int func_0202f4cc(void *animation, u16 index);
extern HitResult FindStrongestHit(void *context, EffectObj *obj, VecFx32 *position, const VecFx32 *velocity);
extern BOOL AdvanceOwnerAnimation(EffectObj *obj, int delta);

BOOL UpdateEffectAnimationPhase(void *context, EffectObj *obj, int delta)
{
    VecFx32 position = obj->position;
    VecFx32 velocity = data_0205344c;
    int i;
    int duration;

    for (i = 0; i < 5; i++) {
        duration = func_0202f4cc(obj->animation, i);
        if (duration > 0) {
            break;
        }
    }
    obj->timer += delta;
    if (obj->timer <= duration - 0x9000) {
        FindStrongestHit(context, obj, &position, &velocity);
    }
    if (AdvanceOwnerAnimation(obj, delta)) {
        obj->state = -1;
    }
    return obj->state == -1;
}
