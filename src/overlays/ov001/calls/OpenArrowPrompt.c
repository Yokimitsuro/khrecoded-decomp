#include "nitro/types.h"

typedef struct ArrowPrompt {
    u8 state;
    u8 steps;
    u8 pad_02[0x2];
    s32 visible;
    u8 pad_08[0x4];
    s32 active;
    s32 seed;
    u8 pad_14[0x4];
    s32 elapsed;
    s32 timeLimit;
    u16 directions[2];
    u16 count;
    u16 remaining : 14;
    u32 failed : 1;
    u32 cleared : 1;
    s32 current;
} ArrowPrompt;

typedef struct StepTable {
    s32 values[4];
} StepTable;

extern ArrowPrompt *data_ov001_020a04f0;
extern const StepTable data_ov001_0209e020;
extern const StepTable data_ov001_0209e030;

extern void *GetSceneTagTracker(void);
extern int func_ov001_0207123c(void);
extern s32 GetClampedPaletteSlot(void);
extern int func_0202a7b8(void);
extern void SetupBgBlend(void);
extern void func_ov027_020b9d74(int layers, int layer, int x, int y, int width, int height);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8230(void *tracker, void *record);
extern u16 func_ov001_0207d860(void);
extern void ShowTwoDigitCounters(ArrowPrompt *prompt);
extern void RefreshCounterRecordPositions(ArrowPrompt *prompt);

void OpenArrowPrompt(void) {
    ArrowPrompt *prompt = data_ov001_020a04f0;
    void *tracker = GetSceneTagTracker();
    int layers = func_ov001_0207123c();
    StepTable steps = data_ov001_0209e020;
    StepTable seconds = data_ov001_0209e030;
    int i;

    if (prompt == NULL) {
        return;
    }
    i = 0;
    prompt->state = 0;
    prompt->steps = (steps.values[GetClampedPaletteSlot()] * 10 + 9) / 10;
    prompt->seed = func_0202a7b8();
    prompt->timeLimit = (seconds.values[GetClampedPaletteSlot()] * 10 + 9) / 10 * 1000;
    prompt->elapsed = 0;
    prompt->count = 0;
    prompt->remaining = 4;
    prompt->failed = 0;
    prompt->cleared = 0;
    SetupBgBlend();
    func_ov027_020b9d74(layers, 0xb, 0, 8, 0xb, 0x10);
    func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x12c));
    func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x12e));
    func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x131));
    func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x132));
    func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x133));
    prompt->current = 0;
    do {
        prompt->directions[i] = func_ov001_0207d860();
        i++;
    } while (i < 2);
    ShowTwoDigitCounters(prompt);
    RefreshCounterRecordPositions(prompt);
    prompt->visible = 1;
    prompt->active = 1;
}
