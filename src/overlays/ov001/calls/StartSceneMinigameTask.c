#include "nitro/types.h"

typedef struct SelectionRecord {
    u8 pad_000[0x130];
    s16 sceneId;
} SelectionRecord;

typedef struct FieldState {
    u8 pad_0000[0x434];
    void *minigameTask;
    u8 pad_0438[0xf08];
    void (*callbacks[6])(void);
} FieldState;

typedef struct FieldGlobals {
    u32 unk_00;
    FieldState *state;
} FieldGlobals;

typedef void *(*FieldStep)(void);

extern FieldGlobals data_ov001_020a04c4;
extern char data_ov001_0209f024[];
extern SelectionRecord *GetOverlaySelectionRecord(int index);
extern void *func_0202a45c(void *descriptor, void *userData);
extern void StartFieldMinigameRound(void);
extern void func_ov001_0207eb04(void);
extern void HandleListMenuConfirm(void);
extern void func_ov001_0207eb98(void);
extern void func_ov001_0207ebb4(void);
extern void func_ov001_0207ebc4(void);
extern void *func_ov001_02070e98(void);

FieldStep StartSceneMinigameTask(void)
{
    FieldState *state = data_ov001_020a04c4.state;
    s16 sceneId = GetOverlaySelectionRecord(0)->sceneId;

    if (state->minigameTask == NULL) {
        switch (sceneId) {
        case 0xc5:
            state->minigameTask = func_0202a45c(data_ov001_0209f024, (void *)1);
            break;
        case 0xc6:
            state->minigameTask = func_0202a45c(data_ov001_0209f024, (void *)2);
            break;
        case 0xca:
            state->minigameTask = func_0202a45c(data_ov001_0209f024, (void *)3);
            break;
        default:
            goto done;
        }
        state->callbacks[0] = StartFieldMinigameRound;
        state->callbacks[1] = func_ov001_0207eb04;
        state->callbacks[2] = HandleListMenuConfirm;
        state->callbacks[3] = func_ov001_0207eb98;
        state->callbacks[4] = func_ov001_0207ebb4;
        state->callbacks[5] = func_ov001_0207ebc4;
    }
done:
    return func_ov001_02070e98;
}
