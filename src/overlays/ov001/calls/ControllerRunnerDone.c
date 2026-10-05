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
} ControlledActor;

extern ControlledActor *GetStageActor(s16 actorId);
extern void *GetStageObjectRecord(u32 id);
extern int func_ov021_020b4bfc(ScriptRunner *runner, int slot);

s32 ControllerRunnerDone(ActorController *controller)
{
    ControlledActor *actor = GetStageActor(controller->actorId);

    GetStageObjectRecord(actor->objectId);
    if ((u16)func_ov021_020b4bfc(&actor->runner, 8) == 4) {
        return 4;
    }
    if (actor->statusFlags & 1) {
        return 4;
    }
    return 0;
}
