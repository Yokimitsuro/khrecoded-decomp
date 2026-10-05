#include "nitro/types.h"

typedef struct {
    u32 active;
    u8 modeState[8];
    s32 mode;
} ModeContext;

extern ModeContext *data_ov001_020a04e4;

extern void *GetSceneTagTracker(void);
extern void RefreshWindowHighlight(void *modeState, int value, int layer);
extern void FreeModeResources(void *modeState);
extern void *FindLoadedElementById(void *tracker, u32 id);
extern void SetTagRecordArmed(void *tracker, void *entry, u32 flag);

void CloseActiveMode(void)
{
    ModeContext *context = data_ov001_020a04e4;
    void *tracker = GetSceneTagTracker();

    RefreshWindowHighlight(context->modeState, 0, 9);
    RefreshWindowHighlight(context->modeState, 0, 10);
    RefreshWindowHighlight(context->modeState, 0, 11);
    FreeModeResources(context->modeState);
    *(vu32 *)0x04000000 &= 0xffff1fff;
    SetTagRecordArmed(tracker, FindLoadedElementById(tracker, 5), 0);
    context->active = 0;
    context->mode = 0;
}
