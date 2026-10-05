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

extern StageActor *GetStageActor(int id);
extern VecFx32 *func_ov001_02090f2c(StageActor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern int FX_Mul(int left, int right);
extern void ClearActorMotionState(StageActor *actor);
extern void ClearActorMotionSpeed(StageActor *actor);
extern void AddObjectOffsetVector(StageActor *actor, VecFx32 *offset);
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
        actor = GetStageActor(event->actorId);
        pos = *func_ov001_02090f2c(actor);
        VEC_Subtract(&target->position, &pos, &dir);
        if (VEC_DotProduct(&dir, &dir) > def->stopDistanceSq) {
            VEC_Normalize(&dir, &dir);
            work->speed += FX_Mul(def->accel, def->accelScale);
            if (work->speed > def->maxSpeed) {
                work->speed = def->maxSpeed;
            }
            VEC_MultAdd(work->speed, &dir, &pos, &pos);
            ClearActorMotionState(actor);
            ClearActorMotionSpeed(actor);
            VEC_Subtract(&pos, func_ov001_02090f2c(actor), &dir);
            AddObjectOffsetVector(actor, &dir);
        } else {
            func_ov001_0209590c(event, 9);
            work->state = 0;
        }
        return TRUE;
    }
    return FALSE;
}
