#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x3c];
    u32 flags;
    u8 pad_40[0xc];
    u16 lowBits : 6;
    u16 keepPose : 1;
    u16 highBits : 9;
    u8 pad_4e[0x42];
} AnimClip;

typedef struct {
    u8 pad_00[0x6c];
    AnimClip *clips;
    u8 pad_70[4];
    void *spawnData;
    s16 *groupId;
    u8 pad_7c[4];
    s8 memberIndex;
} AnimSet;

typedef struct {
    u16 flags;
    u8 pad_02[0x7c];
    u16 yaw;
    u8 pad_80[0x24];
    VecFx32 pos;
} GroupMember;

typedef struct {
    void *callback;
    void *owner;
    u8 pad_08[0x18];
} ClipEventContext;

typedef struct {
    u8 pad_00[8];
    fx32 damping;
    u8 pad_0c[4];
    VecFx32 velocity;
    u8 pad_1c[0x25];
    s8 clipIndex;
} DragMotion;

typedef struct DragActor DragActor;

struct DragActor {
    u8 pad_000[0xbc];
    VecFx32 pos;
    u8 pad_0c8[0x1f8 - 0xc8];
    void (*onRelease)(DragActor *actor, int a, int b);
    u8 pad_1fc[0x224 - 0x1fc];
    VecFx32 *(*getPosition)(DragActor *actor);
    u8 pad_228[0x234 - 0x228];
    u32 moveFlags;
    u8 pad_238[0x760 - 0x238];
    s32 frame;
    u8 pad_764[4];
    s32 motionActive;
    u8 pad_76c[0x9ac - 0x76c];
    u64 flags;
    u8 entryId;
    u8 pad_9b5[0x9c4 - 0x9b5];
    s32 height;
    VecFx32 offset;
    u8 pad_9d4[0xa10 - 0x9d4];
    DragMotion motion;
    u8 pad_a54[0x1030 - 0xa54];
    s32 pendingAction;
    u8 pad_1034[0x1078 - 0x1034];
    AnimSet *anim;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setState)(DragActor *actor, int state);
};

extern const s16 data_02053580[];
extern void *func_ov001_0206db78(int index);
extern BOOL func_ov021_020aa588(AnimClip *clip, s32 frame, int arg);
extern BOOL func_ov052_020d0544(DragActor *actor);
extern BOOL func_ov021_020a7524(void *entry);
extern fx32 ApproachTargetValue(DragMotion *motion);
extern void ComputeFacingAndDirection(DragActor *actor, VecFx32 *dir);
extern u16 func_ov021_020a7564(void *entry);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern GroupMember *GetGroupMemberData(int groupId, int member);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern void func_ov052_020d1a18(ClipEventContext *ctx, AnimClip *clip, int arg, int entryId);
extern void func_ov030_020bbd70(void);
extern BOOL func_ov052_020d014c(DragActor *actor, AnimClip *clip, ClipEventContext *ctx);
extern BOOL func_ov052_020d02b4(DragActor *actor, AnimClip *clip, int arg);
extern BOOL func_ov052_020d03d8(DragActor *actor);

void UpdateDraggedActorMotion(DragActor *actor)
{
    ClipEventContext ctx;
    VecFx32 dir;
    VecFx32 facing;
    VecFx32 diff;
    void *entry = func_ov001_0206db78(actor->entryId);
    DragMotion *motion = &actor->motion;
    AnimSet *anim = actor->anim;
    AnimClip *clip = &anim->clips[motion->clipIndex];
    fx32 speed;
    u16 angle;
    int index;
    GroupMember *member;
    VecFx32 *pos;
    u32 heavy;
    u32 keepPose;

    if (!(actor->flags & 0x100) && func_ov021_020aa588(clip, actor->frame, 0) &&
        func_ov052_020d0544(actor)) {
        actor->pendingAction = 6;
        actor->flags |= 0x100;
    }
    dir.z = 0;
    dir.y = 0;
    dir.x = 0;
    if (func_ov021_020a7524(entry)) {
        speed = ApproachTargetValue(motion);
        ComputeFacingAndDirection(actor, &dir);
        angle = func_ov021_020a7564(entry);
        index = angle >> 4;
        dir.x = -data_02053580[index];
        dir.z = -data_02053580[(0x400 - index) & 0xfff];
        func_01ffaff4(&motion->velocity, &facing);
        VEC_Add(&dir, &facing, &dir);
        func_01ffaff4(&dir, &dir);
    } else {
        dir = motion->velocity;
        speed = 0xe14;
        motion->damping = FX_Mul(motion->damping, speed);
    }
    dir.x = FX_Mul(dir.x, speed);
    dir.z = FX_Mul(dir.z, speed);
    motion->velocity = dir;
    actor->offset.x += dir.x;
    actor->offset.z += dir.z;
    if (actor->height <= 0x3000) {
        member = GetGroupMemberData(*anim->groupId, anim->memberIndex);
        if (actor->getPosition != NULL) {
            pos = actor->getPosition(actor);
        } else {
            pos = &actor->pos;
        }
        VEC_Subtract(pos, &member->pos, &diff);
        func_01ffaff4(&diff, &diff);
        member->yaw = FX_Atan2Idx(-diff.x, diff.y);
        member->flags |= 0x20;
    }
    func_ov052_020d1a18(&ctx, clip, 0, actor->entryId);
    if (anim->spawnData != NULL) {
        ctx.owner = anim;
        ctx.callback = func_ov030_020bbd70;
    }
    if (func_ov052_020d014c(actor, clip, &ctx) || func_ov052_020d02b4(actor, clip, 0) || actor->motionActive == 0) {
        return;
    }
    heavy = actor->moveFlags & 4;
    keepPose = clip->keepPose;
    if (func_ov052_020d03d8(actor)) {
        return;
    }
    if (heavy) {
        if (!(clip->flags & 4)) {
            actor->setState(actor, 1);
            if (actor->onRelease != NULL) {
                actor->onRelease(actor, 0, -1);
            }
            return;
        }
        actor->setState(actor, 5);
        return;
    }
    if (keepPose == 0) {
        actor->flags |= 0x100;
    }
    actor->setState(actor, 4);
}
