#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void *func_ov001_0209c114(u32 id);
extern void func_ov001_0209590c(void *record, u32 state);

void StageRecord_ClearStateIfMatches(u32 id, u32 state)
{
    void *record;

    if (id != 0 && data_ov001_0209f2e8 != -1 && (record = func_ov001_0209c114(id)) != NULL) {
        func_ov001_0209590c(record, state);
    }
}
