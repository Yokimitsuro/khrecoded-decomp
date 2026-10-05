#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x14];
    fx32 duration;
    u8 pad_18[0x50 - 0x18];
    fx32 radius;
} CircleDef;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
    fx32 w;
} QuatFx32;

typedef struct {
    u8 pad_000[0x200];
    QuatFx32 spin;
    fx32 facingOffset;
    fx32 step;
} CircleParams;

typedef struct {
    u8 pad_000[0x18];
    VecFx32 position;
    u8 pad_024[0x138 - 0x24];
    CircleDef *def;
    u8 pad_13c[0x150 - 0x13c];
    CircleParams *params;
} CircleUnit;

typedef struct {
    u8 pad_000[0x18c];
    fx32 tangentScale;
} CircleOwner;

typedef struct {
    VecFx32 target;
    VecFx32 velocity;
    VecFx32 tangent;
    VecFx32 offset;
    fx32 elapsed;
    CircleOwner *owner;
    CircleUnit *unit;
    s32 state;
} CircleWork;

typedef struct {
    u8 pad_00[0x10];
    s16 actorId;
} CircleEvent;

typedef struct StageActor {
    u8 pad_000[0x2e6];
    u16 facing;
} StageActor;

extern const VecFx32 data_ov056_020d7f78;

extern StageActor *func_ov001_0209c068(int id);
extern VecFx32 *func_ov001_02090f2c(StageActor *actor);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void func_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern int FX_Mul(int left, int right);
extern void func_0202fbbc(VecFx32 *in, QuatFx32 *rotation, VecFx32 *out);
extern void func_ov056_020d5368(VecFx32 *out, const VecFx32 *start, const VecFx32 *end, const VecFx32 *startTangent, const VecFx32 *endTangent, fx32 t);
extern void func_ov001_020911bc(StageActor *actor);
extern void func_ov001_020911d0(StageActor *actor);
extern void AddObjectOffsetVector(StageActor *actor, VecFx32 *offset);
extern void func_ov001_02090f64(StageActor *actor, int degrees);
extern void func_ov001_0209590c(CircleEvent *event, int status);

BOOL CircleActorAroundUnit(CircleEvent *event, CircleWork *work)
{
    CircleOwner *owner = work->owner;
    CircleUnit *unit = work->unit;
    CircleParams *params = unit->params;
    StageActor *actor = func_ov001_0209c068(event->actorId);
    fx32 step = params->step;
    fx32 radius;
    fx32 radiusSq;
    fx32 t;
    VecFx32 dir;
    VecFx32 side;
    VecFx32 next;
    VecFx32 pos;
    VecFx32 delta;

    switch (work->state) {
    default:
        work->state = 0;
    case 0:
        func_ov001_0209590c(event, 9);
        break;
    case 1:
        radius = unit->def->radius;
        radiusSq = FX_Mul(radius, radius);
        func_01ff9e3c(func_ov001_02090f2c(actor), &unit->position, &dir);
        if (VEC_DotProduct(&dir, &dir) < radiusSq) {
            dir.x = 0;
            dir.y = 0;
            dir.z = 0x1000;
        }
        func_01ff9ea8(&data_ov056_020d7f78, &dir, &side);
        VEC_Normalize(&side, &side);
        func_01ffa09c(radius, &side, &unit->position, &work->target);
        func_01ff9ea8(&side, &data_ov056_020d7f78, &dir);
        func_01ffafb4(owner->tangentScale, &dir, &work->tangent);
        work->velocity.z = 0;
        work->velocity.y = 0;
        work->velocity.x = 0;
        work->elapsed = 0;
        work->state = 2;
    case 2:
        if (work->elapsed + step <= unit->def->duration) {
            t = FX_Div(step, unit->def->duration - work->elapsed);
            pos = *func_ov001_02090f2c(actor);
            func_ov056_020d5368(&next, &pos, &work->target, &work->velocity, &work->tangent, t);
            func_01ff9e3c(&next, &pos, &work->velocity);
            func_ov001_020911bc(actor);
            func_ov001_020911d0(actor);
            AddObjectOffsetVector(actor, &work->velocity);
            work->elapsed += step;
            break;
        }
        func_01ff9e3c(func_ov001_02090f2c(actor), &unit->position, &work->offset);
        work->state = 3;
    case 3:
        delta = *func_ov001_02090f2c(actor);
        func_0202fbbc(&work->offset, &params->spin, &work->offset);
        func_01ff9e0c(&unit->position, &work->offset, &delta);
        func_ov001_020911bc(actor);
        func_ov001_020911d0(actor);
        func_01ff9e3c(&delta, func_ov001_02090f2c(actor), &delta);
        AddObjectOffsetVector(actor, &delta);
        func_ov001_02090f64(actor, params->facingOffset + (fx32)(((s64)actor->facing * 0x1680000 + 0x80000) >> 20));
        break;
    }
    return FALSE;
}
