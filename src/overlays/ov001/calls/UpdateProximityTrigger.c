#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ProximityCommand {
    u8 pad_00[0x4];
    u16 unk_04_0 : 1;
    u16 playerOutOfRange : 1;
    u16 unk_04_2 : 4;
    u16 keepMotion : 1;
    u16 unk_04_7 : 9;
    u8 pad_06[0x9 - 0x6];
    u8 kind;
    u8 pad_0a[0x10 - 0xa];
    s16 groupId;
    u16 targetId;
} ProximityCommand;

typedef struct TriggerTarget {
    u16 paramIndex;
    u8 pad_02[0x18 - 0x2];
    u32 alwaysOutOfRange;
    VecFx32 position;
} TriggerTarget;

typedef struct TriggerParams {
    u8 pad_00[0x14];
    u32 tracksPlayer;
    u8 pad_18[0x28 - 0x18];
    fx32 activationRadius;
    fx32 playerRadius;
} TriggerParams;

typedef struct StageManager {
    u8 pad_00000[0x18e5c];
    fx32 minActivationHeight;
} StageManager;

typedef struct ActorModel {
    u8 pad_00[0x5c];
    s32 currentMotion;
} ActorModel;

typedef struct ScriptRunner {
    u16 targetKind;
    u16 targetId;
} ScriptRunner;

typedef struct TriggerActor {
    u8 pad_000[0x90];
    u16 savedAngle;
    u8 pad_092[0xb8 - 0x92];
    VecFx32 savedPosition;
    u8 pad_0c4[0x1d0 - 0xc4];
    ScriptRunner runner;
    u8 pad_1d4[0x1e0 - 0x1d4];
    ActorModel *model;
    u8 pad_1e4[0x248 - 0x1e4];
    s32 motionId;
    s32 idleMotion;
    u8 pad_250[0x288 - 0x250];
    u16 unk_288_0 : 5;
    u16 resetMotionTimer : 1;
    u16 unk_288_6 : 10;
    u16 moveMode : 2;
    u16 unk_28A_2 : 14;
    u16 unk_28C_0 : 11;
    u16 zone : 3;
    u16 unk_28C_14 : 2;
    u8 pad_28e[0x29c - 0x28e];
    u32 motionTimer;
    u8 pad_2a0[0x2c0 - 0x2a0];
    VecFx32 position;
    u8 pad_2cc[0x2e6 - 0x2cc];
    u16 angle;
    u8 pad_2e8[0x3a4 - 0x2e8];
    u16 unk_3A4;
    u8 pad_3a6[2];
    u16 unk_3A8;
} TriggerActor;

extern TriggerActor *GetStageActor(s16 groupId);
extern TriggerTarget *GetStageObjectHandle(u32 id);
extern TriggerParams *GetLargeTableEntry(u32 index);
extern u32 func_ov001_0209c5ac(u32 mask);
extern void func_ov001_0209c5c4(u32 mask);
extern StageManager *func_ov001_0209c3e8(void);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern u16 FindNearestStageEntry(VecFx32 *position);
extern TriggerActor *GetLinkedStageActor(TriggerActor *member);
extern void SyncStageEntryPosition(int playerIndex, VecFx32 *position);
extern void CopySourceWords(ScriptRunner *runner);
extern void ClearActorMotionState(TriggerActor *actor);
extern u16 RunGroupScriptSlot(TriggerActor *leader, int slot);

int UpdateProximityTrigger(ProximityCommand *command)
{
    TriggerActor *actor = GetStageActor(command->groupId);
    TriggerTarget *target = GetStageObjectHandle(command->targetId);
    TriggerParams *params = GetLargeTableEntry(target->paramIndex);
    u32 wasOutOfRange = command->playerOutOfRange;
    VecFx32 delta;
    TriggerActor *member;
    VecFx32 playerPosition;

    if (func_ov001_0209c5ac(1)) {
        if (!func_ov001_0209c5ac(0x40)) {
            actor->savedPosition = actor->position;
            actor->savedAngle = actor->angle;
            if (command->kind != 4) {
                func_ov001_0209c5c4(0x10);
            } else {
                func_ov001_0209c5c4(0x20);
            }
            return 9;
        }
        return 0;
    }
    if (func_ov001_0209c5ac(1)) {
        return 0;
    }
    if (params->activationRadius != 0) {
        StageManager *manager = func_ov001_0209c3e8();

        if (manager != NULL && manager->minActivationHeight != 0 &&
            manager->minActivationHeight > actor->position.y) {
            return 6;
        }
        VEC_Subtract(&target->position, &actor->position, &delta);
        if (VEC_Mag(&delta) > params->activationRadius) {
            return 6;
        }
    }
    member = actor;
    if (actor->zone == 0) {
        u16 zone = FindNearestStageEntry(&actor->position);

        for (; member != NULL; member = GetLinkedStageActor(member)) {
            member->zone = zone;
        }
    }
    if (actor->motionId != -1 && params->tracksPlayer != 0 &&
        (command->playerOutOfRange || actor->idleMotion == actor->model->currentMotion)) {
        SyncStageEntryPosition(1, &playerPosition);
        VEC_Subtract(&playerPosition, &actor->position, &delta);
        delta.y = 0;
        command->playerOutOfRange = VEC_Mag(&delta) > params->playerRadius;
        if (target->alwaysOutOfRange != 0) {
            command->playerOutOfRange = 1;
        }
        if (command->playerOutOfRange != wasOutOfRange) {
            CopySourceWords(&actor->runner);
            ClearActorMotionState(actor);
            if (command->playerOutOfRange) {
                actor->unk_3A4 = 0;
                actor->unk_3A8 = 0;
            } else if (!command->keepMotion) {
                actor->moveMode = 1;
                actor->unk_3A4 = 0;
                actor->unk_3A8 = 0xffff;
            }
        }
    }
    if (command->playerOutOfRange) {
        if (actor->resetMotionTimer) {
            actor->motionTimer = 0;
        }
        RunGroupScriptSlot(actor, 2);
    } else {
        RunGroupScriptSlot(actor, 3);
    }
    return 0;
}
