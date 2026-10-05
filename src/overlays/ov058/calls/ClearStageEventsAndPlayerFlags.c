#include "nitro/types.h"

typedef struct {
    u8 mode;
    u8 pad_01[3];
    s32 timer;
} SceneControl;

typedef struct {
    u8 pad_000[0x9ac];
    u64 stateFlags;
} PlayerEntry;

extern s32 ForwardToActiveServiceWithResult(void);
extern s32 func_ov001_0208796c(s32 startIndex);
extern int IsStageEventReady(u32 id);
extern void StageRecord_ClearStateIfMatches(u32 id, u32 state);
extern PlayerEntry *GetBoundedEntryField(int index);
extern BOOL Camera_ReturnFromPathView(void);

void ClearStageEventsAndPlayerFlags(SceneControl *control)
{
    s32 record;
    int i;

    for (record = ForwardToActiveServiceWithResult(); record != 0; record = func_ov001_0208796c(record)) {
        if (IsStageEventReady(record)) {
            StageRecord_ClearStateIfMatches(record, 9);
        }
    }
    control->timer = 0;
    control->mode = 7;
    for (i = 0; i < 3; i++) {
        GetBoundedEntryField(i)->stateFlags &= ~0x20000000ULL;
    }
    Camera_ReturnFromPathView();
}
