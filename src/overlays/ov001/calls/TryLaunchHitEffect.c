#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitQuery {
    u32 kind;
    VecFx32 direction;
    VecFx32 origin;
    fx32 radius;
    u32 unk_20;
    u32 resultFlags;
    u8 pad_28[8];
    u32 unk_30;
    u32 unk_34;
} HitQuery;

typedef struct EffectRequest {
    u8 active;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 flagA;
    u8 flagB;
    u8 pad_26[2];
    u16 soundId;
    u16 mode;
} EffectRequest;

typedef struct HitHandler HitHandler;

struct HitHandler {
    u8 pad_000[0x208];
    int (*query)(HitHandler *handler, HitQuery *query);
};

typedef struct ActorOwner {
    u8 pad_00[4];
    s32 busy;
} ActorOwner;

typedef struct TargetRef {
    ActorOwner *owner;
    s32 type;
} TargetRef;

typedef struct Motion {
    fx32 speed;
    VecFx32 direction;
} Motion;

typedef struct ActorDefData {
    u8 pad_00[0x86];
    s16 effectGroup;
} ActorDefData;

typedef struct LaunchActor {
    u8 pad_00[8];
    ActorDefData *def;
    u8 pad_0c[0x40 - 0x0c];
    VecFx32 position;
    u8 pad_4c[0x58 - 0x4c];
    s32 canLaunch;
} LaunchActor;

extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern HitHandler *GetBoundedEntryField(int index);
extern void ResetAnimationTrackState(EffectRequest *request);
extern VecFx32 *func_ov001_0206dc60(int index);
extern int func_ov021_020a8cc0(EffectRequest *request, int groupId);

int TryLaunchHitEffect(void *unused, TargetRef *target, Motion *motion, LaunchActor *actor)
{
    HitQuery query;
    EffectRequest effect;
    VecFx32 velocity;
    VecFx32 direction;
    HitHandler *handler;
    int hit;
    fx32 speed;

    if (target != NULL && target->type == 2 && target->owner->busy == 0 && actor->canLaunch != 0) {
        hit = 0;
        MIi_CpuClearFast(0, &query, sizeof(query));
        query.radius = 0xa000;
        query.kind = 4;
        speed = motion->speed;
        velocity = motion->direction;
        ScaleVecFx32InPlace(&velocity, speed);
        direction = velocity;
        func_01ffaff4(&direction, &direction);
        ScaleVecFx32InPlace(&direction, 0x800);
        query.direction = direction;
        query.origin = actor->position;
        query.unk_20 = 0;
        query.unk_30 = 0;
        query.unk_34 = 0;
        handler = GetBoundedEntryField(0);
        if (handler->query != NULL) {
            hit = handler->query(handler, &query);
        }
        if (hit != 0 && !(query.resultFlags & 1)) {
            ResetAnimationTrackState(&effect);
            effect.active = 0;
            effect.flagB = 0;
            effect.flagA = 0;
            effect.position = *func_ov001_0206dc60(0);
            effect.soundId = 0x1a1;
            effect.mode = 3;
            func_ov021_020a8cc0(&effect, actor->def->effectGroup);
        }
    }
    return 0;
}
