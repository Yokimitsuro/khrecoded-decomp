#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PullSource {
    u8 pad_000[0xf4];
    VecFx32 position;
    fx32 strength;
} PullSource;

typedef struct PullWork {
    fx32 speed;
    PullSource *source;
    s32 state;
} PullWork;

typedef struct PullEvent {
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
extern void func_ov001_020911bc(StageActor *actor);
extern void func_ov001_020911d0(StageActor *actor);
extern void AddObjectOffsetVector(StageActor *actor, VecFx32 *offset);
extern void func_ov001_0209590c(PullEvent *event, int status);

BOOL PullActorTowardSource(PullEvent *event, PullWork *work)
{
    PullSource *source;
    StageActor *actor;
    fx32 step;
    fx32 speed;
    VecFx32 pos;
    VecFx32 dir;

    switch (work->state) {
    default:
        work->state = 0;
    case 0:
        func_ov001_0209590c(event, 9);
        break;
    case 1:
        source = work->source;
        actor = GetStageActor(event->actorId);
        step = FX_Mul(0xb2, source->strength);
        pos = *func_ov001_02090f2c(actor);
        VEC_Subtract(&source->position, &pos, &dir);
        if (VEC_DotProduct(&dir, &dir) > FX_Mul(0xccd, 0xccd)) {
            VEC_Normalize(&dir, &dir);
            speed = work->speed + step;
            if (speed >= 0xc00) {
                speed = 0xc00;
            }
            work->speed = speed;
            VEC_MultAdd(speed, &dir, &pos, &pos);
            func_ov001_020911bc(actor);
            func_ov001_020911d0(actor);
            VEC_Subtract(&pos, func_ov001_02090f2c(actor), &dir);
            AddObjectOffsetVector(actor, &dir);
        }
        return TRUE;
    }
    return FALSE;
}
