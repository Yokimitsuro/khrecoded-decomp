#include "nitro/types.h"

typedef struct ActorController {
    s32 state;
    s32 nextState;
    u16 flags;
    u16 eventId;
    s16 actorId;
} ActorController;

typedef struct ScriptRunner {
    u16 targetKind;
    u16 targetId;
} ScriptRunner;

typedef struct ControlledActor {
    u8 pad_000[0x1d0];
    ScriptRunner runner;
    u8 pad_1d4[0x26c - 0x1d4];
    u32 statusFlags : 31;
    u32 statusTop : 1;
    u8 pad_270[0x27e - 0x270];
    u16 objectId;
    u8 pad_280[0x28c - 0x280];
    u16 moveLow : 11;
    u16 teamSlot : 3;
    u16 moveHigh : 2;
} ControlledActor;

typedef struct StageEventRecord {
    u8 pad_00[0x10];
    u16 linkedActorId;
} StageEventRecord;

extern ControlledActor *GetStageActor(s16 actorId);
extern void *GetStageObjectRecord(u32 id);
extern StageEventRecord *GetStageEventRecord(u32 id);
extern int SelectSequenceTrack(ScriptRunner *runner, int slot);

s32 ControllerStateActive(ActorController *controller)
{
    ControlledActor *actor = GetStageActor(controller->actorId);
    StageEventRecord *record;
    ControlledActor *linked;

    GetStageObjectRecord(actor->objectId);
    if (actor->teamSlot == 0 && controller->eventId != 0) {
        record = GetStageEventRecord(controller->eventId);
        if (record != NULL && record->linkedActorId != 0) {
            linked = GetStageActor(record->linkedActorId);
            if (linked != NULL) {
                actor->teamSlot = linked->teamSlot;
            }
        }
    }
    SelectSequenceTrack(&actor->runner, 3);
    if (actor->statusFlags & 1) {
        return 4;
    }
    return 0;
}
