#include "nitro/types.h"

typedef struct StageActorFlags {
    u32 bits : 31;
    u32 top : 1;
} StageActorFlags;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    u8 runner[0x26c - 0x1d0];
    StageActorFlags flags;
    u8 pad_270[0x29c - 0x270];
    int pending;
} StageActor;

typedef struct StageEvent {
    u16 pad_00[2];
    u16 lowFlags : 13;
    u16 resumes : 1;
    u16 highFlags : 2;
    u16 lowState : 10;
    u16 effectPending : 1;
    u16 highState : 5;
    u8 pad_08[8];
    s16 actorId;
    u16 objectId;
    u8 pad_14[0x70 - 0x14];
    int nextState;
    int resumeState;
    u8 pad_78[0x1b8 - 0x78];
    u16 slots[2];
} StageEvent;

extern int func_ov001_02063a24(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void ClearActorMotionState(StageActor *actor);
extern void ClearActorGroupFlagsAndNotify(StageEvent *event);
extern void StartStageEventEffect(StageEvent *event);
extern int ReleaseStageSlotEntry(int index, int slot);
extern StageActor *GetStageActor(int id);
extern void *GetStageObjectHandle(u32 id);
extern int SelectSequenceTrack(void *runner, int slot);

int FinishStageEventStep(StageEvent *event)
{
    StageActor *actor = GetStageActor(event->actorId);
    int i;

    GetStageObjectHandle(event->objectId);
    if (event->effectPending) {
        event->effectPending = 0;
        StartStageEventEffect(event);
    }
    ClearActorGroupFlagsAndNotify(event);
    actor->pending = 0;
    if (!func_ov001_02063a24() || !func_ov001_020645c8(0x379c)) {
        if (SelectSequenceTrack(actor->runner, 8) != 4) {
            return 0;
        }
    }
    ClearActorMotionState(actor);
    for (i = 0; i < 2; i++) {
        if (event->slots[i] != 0) {
            ReleaseStageSlotEntry(4, event->slots[i]);
            event->slots[i] = 0;
        }
    }
    actor->flags.bits &= ~1;
    if (event->resumes) {
        event->nextState = event->resumeState;
        return 3;
    }
    return 8;
}
