#include "nitro/types.h"

typedef struct ArrowPrompt {
    u8 pad_00[0xc];
    s32 active;
    u32 startTime;
    u32 flashStart;
    u32 finishStart;
    s32 timeLimit;
} ArrowPrompt;

extern void *GetSceneTagTracker(void);
extern int func_ov001_0207123c(void);
extern u32 func_0202a7b8(void);
extern void RunHudExitCallback(void);
extern void func_ov027_020b9d74(int layers, int layer, int x, int y, int width, int height);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b81f8(void *pool, void *record, s16 frame);
extern void func_ov027_020b8230(void *tracker, void *record);
extern void func_ov027_020b8288(void *pool, void *record);

static inline int FramesToMs(u32 frames) {
    return frames * 1000 / 30;
}

void UpdateArrowPromptTimer(ArrowPrompt *prompt) {
    void *tracker = GetSceneTagTracker();
    int layers = func_ov001_0207123c();
    u32 now = func_0202a7b8();
    int elapsed;
    int seconds;
    void *record;

    if (prompt->flashStart != 0 && FramesToMs(now - prompt->flashStart) >= 500) {
        prompt->flashStart = 0;
        func_ov027_020b8288(tracker, FindActiveRecordById(tracker, 0x134));
    }
    if (prompt->finishStart != 0) {
        if (FramesToMs(now - prompt->finishStart) >= 500) {
            RunHudExitCallback();
        }
        return;
    }
    seconds = 0;
    func_ov027_020b9d74(layers, 0xb, 0xe, 0, 4, 2);
    elapsed = FramesToMs(func_0202a7b8() - prompt->startTime);
    if (prompt->timeLimit - elapsed < -500) {
        RunHudExitCallback();
        return;
    }
    if (elapsed >= prompt->timeLimit) {
        prompt->active = 0;
    } else {
        seconds = prompt->timeLimit / 1000 - elapsed / 1000;
    }
    if (seconds / 10 != 0) {
        record = FindActiveRecordById(tracker, seconds / 10 + 0x168);
        func_ov027_020b81f8(tracker, record, 0xe);
        func_ov027_020b8230(tracker, record);
    }
    record = FindActiveRecordById(tracker, seconds % 10 + 0x168);
    func_ov027_020b81f8(tracker, record, seconds >= 10 ? 0x10 : 0xf);
    func_ov027_020b8230(tracker, record);
}
