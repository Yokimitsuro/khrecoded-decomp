#include "nitro/types.h"

typedef struct ScriptRunner {
    u16 targetKind;
    u16 targetId;
} ScriptRunner;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    ScriptRunner runner;
    u8 pad_1d4[0xb6];
    u16 unk_28a_0 : 9;
    u16 scriptBusy : 1;
    u16 unk_28a_10 : 6;
} StageActor;

typedef struct StageTask {
    u8 pad_00[4];
    u16 unk_04_0 : 5;
    u16 cancelOnA : 1;
    u16 unk_04_6 : 2;
    u16 cancelOnB : 1;
    u16 unk_04_9 : 7;
    u8 pad_06[6];
    u8 kind;
    u8 pad_0d[3];
    s16 actorId;
    u16 objectId;
    u8 pad_14[0xa];
    s16 timer;
    u8 pad_20[0x184];
    BOOL pending;
} StageTask;

extern StageActor *GetStageActor(int id);
extern void *GetStageObjectHandle(u16 index);
extern int SelectSequenceTrack(ScriptRunner *runner, int slot);

int WaitStageActorScript(StageTask *task)
{
    StageActor *actor = GetStageActor(task->actorId);

    GetStageObjectHandle(task->objectId);
    if (task->kind == 2 && task->pending && (task->cancelOnB || task->cancelOnA)) {
        task->pending = FALSE;
    }
    if (SelectSequenceTrack(&actor->runner, 6) != 4) {
        return 0;
    }
    if (task->kind == 4) {
        return 0;
    }
    actor->scriptBusy = 0;
    task->timer = 0;
    if (task->kind == 8 && task->pending) {
        if (!task->cancelOnB && !task->cancelOnA) {
            return 4;
        }
        task->pending = FALSE;
    }
    return 3;
}
