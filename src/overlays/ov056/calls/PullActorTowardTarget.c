#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x18c];
    fx32 stopDistanceSq;
    fx32 accel;
    fx32 maxSpeed;
    fx32 accelScale;
} PullDef;

typedef struct {
    u8 pad_00[0x18];
    VecFx32 position;
} PullTarget;

typedef struct {
    fx32 speed;
    PullDef *def;
    PullTarget *target;
    s32 state;
} PullWork;

typedef struct {
    u8 pad_00[0x10];
    s16 actorId;
} PullEvent;

typedef struct StageActor StageActor;

extern StageActor *func_ov001_0209c068(int id);
extern VecFx32 *func_ov001_02090f2c(StageActor *actor);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void func_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern int FX_Mul(int left, int right);
extern void func_ov001_020911bc(StageActor *actor);
extern void func_ov001_020911d0(StageActor *actor);
extern void func_ov001_02091c78(StageActor *actor, VecFx32 *offset);
extern void func_ov001_0209590c(PullEvent *event, int status);

BOOL PullActorTowardTarget(PullEvent *event, PullWork *work)
{
    PullDef *def = work->def;
    PullTarget *target = work->target;
    StageActor *actor;
    VecFx32 pos;
    VecFx32 dir;

    switch (work->state) {
    default:
        work->state = 0;
    case 0:
        func_ov001_0209590c(event, 9);
        break;
    case 1:
        actor = func_ov001_0209c068(event->actorId);
        pos = *func_ov001_02090f2c(actor);
        func_01ff9e3c(&target->position, &pos, &dir);
        if (VEC_DotProduct(&dir, &dir) > def->stopDistanceSq) {
            VEC_Normalize(&dir, &dir);
            work->speed += FX_Mul(def->accel, def->accelScale);
            if (work->speed > def->maxSpeed) {
                work->speed = def->maxSpeed;
            }
            func_01ffa09c(work->speed, &dir, &pos, &pos);
            func_ov001_020911bc(actor);
            func_ov001_020911d0(actor);
            func_01ff9e3c(&pos, func_ov001_02090f2c(actor), &dir);
            func_ov001_02091c78(actor, &dir);
        } else {
            func_ov001_0209590c(event, 9);
            work->state = 0;
        }
        return TRUE;
    }
    return FALSE;
}
