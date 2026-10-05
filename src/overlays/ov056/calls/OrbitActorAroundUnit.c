#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
    fx32 w;
} QuatFx32;

typedef struct {
    u8 pad_00[0xe0];
    QuatFx32 spin;
    fx32 height;
    fx32 accel;
    fx32 minDistanceSq;
} OrbitDef;

typedef struct {
    u8 pad_000[0xd4];
    VecFx32 position;
    u8 pad_0e0[0x150 - 0xe0];
    OrbitDef *def;
} OrbitUnit;

typedef struct {
    OrbitUnit *unit;
    QuatFx32 rotation;
    fx32 speed;
    s32 state;
} OrbitWork;

typedef struct {
    u8 pad_00[0x10];
    s16 actorId;
} OrbitEvent;

typedef struct StageActor StageActor;

extern StageActor *func_ov001_0209c068(int id);
extern VecFx32 *func_ov001_02090f2c(StageActor *actor);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void func_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void MultiplyFixedPointQuaternions(QuatFx32 *dst, QuatFx32 *a, QuatFx32 *b);
extern void func_0202fbbc(VecFx32 *in, QuatFx32 *rotation, VecFx32 *out);
extern void func_ov001_020911bc(StageActor *actor);
extern void func_ov001_020911d0(StageActor *actor);
extern void AddObjectOffsetVector(StageActor *actor, VecFx32 *offset);
extern void func_ov001_0209590c(OrbitEvent *event, int status);

BOOL OrbitActorAroundUnit(OrbitEvent *event, OrbitWork *work)
{
    OrbitUnit *unit;
    OrbitDef *def;
    StageActor *actor;
    VecFx32 pos;
    VecFx32 dir;
    VecFx32 center;

    switch (work->state) {
    default:
        work->state = 0;
    case 0:
        func_ov001_0209590c(event, 9);
        break;
    case 1:
        unit = work->unit;
        def = unit->def;
        actor = func_ov001_0209c068(event->actorId);
        center = unit->position;
        pos = *func_ov001_02090f2c(actor);
        func_01ff9e3c(&pos, &center, &dir);
        MultiplyFixedPointQuaternions(&work->rotation, &work->rotation, &def->spin);
        func_0202fbbc(&dir, &work->rotation, &dir);
        func_01ff9e0c(&center, &dir, &pos);
        pos.y += def->height;
        dir.y = 0;
        if (VEC_DotProduct(&dir, &dir) > def->minDistanceSq) {
            VEC_Normalize(&dir, &dir);
            work->speed += def->accel;
            func_01ffa09c(-work->speed, &dir, &pos, &pos);
        }
        func_ov001_020911bc(actor);
        func_ov001_020911d0(actor);
        func_01ff9e3c(&pos, func_ov001_02090f2c(actor), &dir);
        AddObjectOffsetVector(actor, &dir);
        return TRUE;
    }
    return FALSE;
}
