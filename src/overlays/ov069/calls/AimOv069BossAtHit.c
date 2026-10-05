#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 mode : 8;
    s32 step : 8;
    s32 count : 16;
} IntroCounter;

typedef struct {
    u8 pad_00[0xe4];
    VecFx32 dir;
    fx32 speed;
    u8 pad_f4[8];
    IntroCounter counter;
} SceneObject;

typedef struct {
    u8 pad_00[4];
    SceneObject *obj;
} HitContext;

typedef struct {
    u8 pad_00[4];
    int phase;
    int kind;
    VecFx32 pos;
} HitEvent;

typedef struct {
    u8 pad_00[0x94];
    u16 angle;
    u8 pad_96[0xbc - 0x96];
    VecFx32 pos;
} Actor;

extern const s16 data_02053580[];
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);

void AimOv069BossAtHit(Actor *actor, HitEvent *event, HitContext *ctx)
{
    SceneObject *obj = ctx->obj;
    VecFx32 diff;
    u16 heading;
    int index;

    if (event->kind == 1 && event->phase != 1) {
        return;
    }
    switch (obj->counter.mode) {
    case 3:
    case 4:
        break;
    case 0:
    case 1:
    case 2:
    default:
        VEC_Subtract(&actor->pos, &event->pos, &diff);
        if (VEC_DotProduct(&diff, &diff) > 4) {
            VEC_Normalize(&diff, &obj->dir);
        } else {
            heading = actor->angle - 0x8000;
            index = (u16)(heading + 0x8000) >> 4;
            obj->dir.x = -data_02053580[index];
            obj->dir.y = 0;
            obj->dir.z = -data_02053580[(0x400 - index) & 0xfff];
        }
        obj->speed = 0xa00;
        obj->counter.mode = 1;
        break;
    }
}
