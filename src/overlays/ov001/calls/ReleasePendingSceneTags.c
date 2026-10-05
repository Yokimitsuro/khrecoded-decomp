#include "nitro/types.h"

typedef struct SceneTagState {
    u8 pad[0x44];
    int tagCount;
    u8 pad48[8];
    u32 releasePending : 1;
    u32 unk50 : 31;
} SceneTagState;

extern SceneTagState *data_ov001_020a04cc;
extern void *GetSceneTagTracker(void);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8288(void *pool, void *record);
extern void func_ov027_020b7f80(void *pool, void *record, int flag);

void ReleasePendingSceneTags(void) {
    SceneTagState *state = data_ov001_020a04cc;
    int i;
    void *tracker = GetSceneTagTracker();
    int pairs;

    if (state->releasePending) {
        state->releasePending = 0;
        func_ov027_020b8288(tracker, FindActiveRecordById(tracker, 0x14));
        pairs = (state->tagCount + 1) / 2;
        for (i = 0; i < pairs; i++) {
            func_ov027_020b7f80(tracker, FindActiveRecordById(tracker, (u16)(i + 50000)), 1);
        }
        state->tagCount = 0;
    }
}
