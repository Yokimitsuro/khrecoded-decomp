#include "nitro/types.h"

typedef struct ScriptRunner {
    u16 targetKind;
    u16 targetId;
} ScriptRunner;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    ScriptRunner runner;
    u8 pad_1d4[0xa8];
    u16 scriptId;
    u8 pad_27e[0xa];
    u16 motionFlags;
    u8 pad_28a[0xa];
    s32 speed;
    s32 velocityX;
    s32 velocityZ;
    u32 unk_2a0;
    s32 accel;
    u32 unk_2a8;
    s32 turnRate;
} StageActor;

typedef struct StageTask {
    u8 pad_00[4];
    u16 unk_04_0 : 3;
    u16 keepMotion : 1;
    u16 unk_04_4 : 12;
    u8 pad_06[0xa];
    s16 actorId;
    u16 objectId;
} StageTask;

extern StageActor *GetStageActor(int id);
extern void *GetStageObjectHandle(u16 index);
extern u32 func_ov001_0209c5ac(u32 mask);
extern int SelectSequenceTrack(ScriptRunner *runner, int slot);
extern void ReleaseEventResources(StageTask *task);

BOOL StartStageActorScript(StageTask *task)
{
    StageActor *actor = GetStageActor(task->actorId);
    BOOL runScript;

    GetStageObjectHandle(task->objectId);
    runScript = TRUE;
    if (!task->keepMotion) {
        actor->velocityX = 0;
        actor->speed = 0;
        actor->velocityZ = 0;
        actor->turnRate = 0;
        actor->accel = 0;
        actor->motionFlags |= 0x1000;
    }
    if (func_ov001_0209c5ac(2) && !task->keepMotion && (actor->scriptId == 0 || actor->scriptId == 0xffff)) {
        runScript = FALSE;
    }
    if (runScript && SelectSequenceTrack(&actor->runner, 7) != 4) {
        return FALSE;
    }
    ReleaseEventResources(task);
    return TRUE;
}
