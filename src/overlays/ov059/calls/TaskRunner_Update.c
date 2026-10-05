#include "nitro/types.h"

typedef struct ScriptTask {
    u8 pad_000[2];
    s8 handler;
    u8 pad_003[0x150 - 0x3];
    int *status;
} ScriptTask;

typedef struct ScriptTimer {
    int id;
    u8 pad_04[0x14 - 0x4];
} ScriptTimer;

typedef struct ScriptActor {
    u8 pad_0000[0x934];
    s32 mode : 8;
    s32 modeRest : 24;
    u8 pad_0938[0x16d4 - 0x938];
    u8 locked;
} ScriptActor;

typedef struct ScriptRunner ScriptRunner;
typedef BOOL (*ScriptHandler)(ScriptRunner *runner, ScriptTask *task, void *arg);

struct ScriptRunner {
    u8 pad_00[0x8];
    ScriptTask *tasks;
    u8 pad_0c[0x15 - 0xc];
    u8 taskCount;
    u8 pad_16[0x28 - 0x16];
    ScriptHandler handlers[6];
    ScriptTimer *timers;
    ScriptActor *actor;
};

extern void PlayCursor_Advance(ScriptRunner *runner, ScriptTimer *timer, void *arg);

void TaskRunner_Update(ScriptRunner *runner, void *arg) {
    BOOL busy = FALSE;
    int count = runner->taskCount;
    int i;

    for (i = 0; i < count; i++) {
        ScriptTask *task = &runner->tasks[i];
        if (task->handler != -1) {
            if (runner->handlers[task->handler](runner, task, arg)) {
                task->handler = -1;
            } else if (*task->status == 2) {
                busy = TRUE;
            }
        }
    }
    if (!busy) {
        ScriptActor *actor = runner->actor;
        if (actor->mode == 4 && actor->locked == 0) {
            actor->mode = 0;
        }
    }
    for (i = 0; i < 10; i++) {
        if (runner->timers[i].id != -1) {
            PlayCursor_Advance(runner, &runner->timers[i], arg);
        }
    }
}
