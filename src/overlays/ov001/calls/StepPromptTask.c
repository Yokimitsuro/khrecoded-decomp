#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x480];
    u32 lowBits : 14;
    u32 promptActive : 1;
    u32 highBits : 17;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

typedef struct PromptTask PromptTask;
typedef void *(*PromptHandler)(void);

struct PromptTask {
    u8 pad_00[0x14];
    PromptHandler handler;
};

extern FieldManagerHandle data_ov001_020a04c4;
extern BOOL UpdatePanelPromptInput(void);
extern PromptTask *func_ov001_0207b604(void);

BOOL StepPromptTask(void)
{
    PromptTask *task;
    PromptHandler next;

    UpdatePanelPromptInput();
    if (data_ov001_020a04c4.manager->promptActive) {
        task = func_ov001_0207b604();
        next = (PromptHandler)task->handler();
        if (next != NULL) {
            task->handler = next;
        }
    }
    return TRUE;
}
