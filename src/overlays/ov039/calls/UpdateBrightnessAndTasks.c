#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov039Task {
    BOOL (*run)(void);
    u8 pad_04[0xc];
    BOOL finished;
} Ov039Task;

typedef struct Ov039State {
    u8 pad_0000[0xc9c8];
    fx32 brightness;
    fx32 subBrightness;
    u8 brightnessTween[0x18];
    u32 unused0 : 2;
    u32 tweenPaused : 1;
    u32 unused3 : 29;
    u8 subBrightnessTween[0x1c];
    int frameFlag;
    BOOL syncSubBrightness;
    u8 pad_ca10[0x30];
    BOOL tasksPaused;
    u8 pad_ca44[0x30];
    u8 taskList[1];
} Ov039State;

typedef struct CPContext {
    u8 data[0x1c];
} CPContext;

extern Ov039State *data_ov039_020bea20;
extern void CP_SaveContext(CPContext *context);
extern void CPi_RestoreContext(CPContext *context);
extern void SampleTweenValue(void *tween, fx32 *value);
extern int GetStateC9C4(void);
extern void SetSecondaryBrightness(int value);
extern void SetBrightnessAndSyncMain(int value);
extern void *NNS_FndGetNextListObject(void *list, void *object);

void UpdateBrightnessAndTasks(void)
{
    Ov039State *state = data_ov039_020bea20;
    Ov039Task *task;
    Ov039Task *next;

    state->frameFlag = 0;
    if (!state->tweenPaused) {
        CPContext context;
        int mainLevel;
        int subLevel;

        CP_SaveContext(&context);
        SampleTweenValue(state->brightnessTween, &state->brightness);
        SampleTweenValue(state->subBrightnessTween, &state->subBrightness);
        CPi_RestoreContext(&context);
        while (*(vu16 *)0x04000280 & 0x8000) {
        }
        mainLevel = state->brightness >> 12;
        subLevel = state->subBrightness >> 12;
        if (GetStateC9C4() == 6 || GetStateC9C4() == 7) {
            SetSecondaryBrightness(subLevel);
        } else {
            if (state->syncSubBrightness) {
                SetSecondaryBrightness(subLevel);
            }
            SetBrightnessAndSyncMain(mainLevel);
        }
    }
    if (state->tasksPaused) {
        return;
    }
    task = NNS_FndGetNextListObject(state->taskList, NULL);
    if (task == NULL) {
        return;
    }
    do {
        next = NNS_FndGetNextListObject(state->taskList, task);
        if (!task->finished && !task->run()) {
            task->finished = TRUE;
        }
        task = next;
    } while (next != NULL);
}
