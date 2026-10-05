#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s16 animId;
    u8 pad_02[0x2a];
} QueuedAnim;

typedef struct {
    u8 pad_000[0x5d0];
    QueuedAnim queue[7];
    u8 pad_704[0x114];
    s32 timer;
    s32 timerLimit;
    u8 pad_820[0x4c];
    fx32 moveScale;
    u8 pad_870[0x24];
    u8 rootMotion[0x370];
    u8 anim[0xd8];
    u8 blend[0x2c];
    VecFx32 blendOffset;
    s32 lockHeading;
    u8 pad_D18[0x1e4];
    s32 heading;
} FieldActor;

extern const VecFx32 data_0205344c;
extern const s16 data_02053580[];

extern void ActorAnim_AdvanceAndGetRootDelta(VecFx32 *out, void *rootMotion);
extern void func_01ffafb4(fx32 scale, const VecFx32 *in, VecFx32 *out);
extern void MTX_Identity43_(MtxFx43 *mtx);
extern void MTX_RotY43_(MtxFx43 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec43(const VecFx32 *vec, const MtxFx43 *mtx, VecFx32 *out);
extern void Actor_FireExpiredTrackCues(FieldActor *actor);
extern BOOL func_ov001_020645c8(int bitId);
extern int Anim_GetFrame(void *anim, int track);
extern void WriteSessionPackedBits(int bitId, int value, int arg);
extern u32 BuildSlotMask(void *anim, int flag);
extern void ClearActorFlagBit40(FieldActor *actor);
extern void selectJointAnimationBlend(void *anim, int track, void *blend, int animId);
extern void func_01ffb2f8(void *anim, int track, int frame);

void ApplyActorRootMotion(FieldActor *actor, VecFx32 *out) {
    VecFx32 motion;
    MtxFx43 rotation;
    VecFx32 delta;
    int heading;
    int i;

    ActorAnim_AdvanceAndGetRootDelta(&delta, actor->rootMotion);
    motion = delta;
    heading = actor->heading;
    func_01ffafb4(actor->moveScale, &motion, &motion);
    if (actor->lockHeading == 0) {
        MTX_Identity43_(&rotation);
        heading >>= 4;
        MTX_RotY43_(&rotation, data_02053580[heading], data_02053580[(0x400 - heading) & 0xfff]);
        MTX_MultVec43(&motion, &rotation, out);
    } else {
        *out = motion;
    }
    Actor_FireExpiredTrackCues(actor);
    if (func_ov001_020645c8(0x362a) && actor->queue[1].animId == -1 && Anim_GetFrame(actor->anim, 0) >= 0x8000) {
        if (actor->heading < 0x8000) {
            actor->heading = 0x2000;
        } else {
            actor->heading = 0xe000;
        }
        actor->timerLimit = -1;
        actor->timer = 0x2ab8;
        WriteSessionPackedBits(0x362a, 1, 0);
    }
    if (BuildSlotMask(actor->anim, 0x1000)) {
        if (actor->queue[1].animId != -1) {
            actor->blendOffset = data_0205344c;
            selectJointAnimationBlend(actor->anim, 0, actor->blend, actor->queue[1].animId);
            func_01ffb2f8(actor->anim, 0, 0);
            actor->queue[1].animId = -1;
            for (i = 1; i < 6; i++) {
                s16 next = actor->queue[i + 1].animId;
                if (next == -1) {
                    break;
                }
                actor->queue[i].animId = next;
                actor->queue[i + 1].animId = -1;
            }
        } else {
            ClearActorFlagBit40(actor);
        }
    }
}
