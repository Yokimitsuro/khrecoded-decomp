#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 data[0xd4];
} HitResult;

typedef struct {
    u8 pad_00[0x18];
    fx32 maxDistance;
    s32 duration;
} EffectParams;

typedef struct {
    u8 pad_00[2];
    s8 state;
    u8 pad_03;
    s32 timer;
    u8 pad_08[0x10];
    VecFx32 origin;
    u8 pad_24[0xb0];
    VecFx32 position;
    u8 pad_e0[0x58];
    EffectParams *params;
} EffectObj;

extern VecFx32 SteerTowardTarget(void *context, EffectObj *obj, int delta);
extern HitResult FindStrongestHit(void *context, EffectObj *obj, VecFx32 *position, const VecFx32 *velocity);
extern BOOL AdvanceOwnerAnimation(EffectObj *obj, int delta);
extern void AdvanceToSecondPhase(EffectObj *obj);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

BOOL UpdateEffectMovePhase(void *context, EffectObj *obj, int delta)
{
    EffectParams *params = obj->params;
    VecFx32 position;
    VecFx32 velocity;
    BOOL finished;
    BOOL hit;

    obj->timer += delta;
    position = obj->position;
    velocity = SteerTowardTarget(context, obj, delta);
    FindStrongestHit(context, obj, &position, &velocity);
    VEC_Add(&position, &velocity, &position);
    obj->position = position;
    if (obj->state == 1) {
        finished = FALSE;
        hit = AdvanceOwnerAnimation(obj, delta);
        if (params->duration >= 0) {
            if (obj->timer >= params->duration) {
                finished = TRUE;
            }
        } else if (hit) {
            finished = TRUE;
        }
        if (params->maxDistance >= 0 && VEC_Distance(&obj->origin, &position) > params->maxDistance) {
            finished = TRUE;
        }
        if (finished) {
            AdvanceToSecondPhase(obj);
        }
    }
    return obj->state == -1;
}
