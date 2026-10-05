#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void *func_ov001_0209c114(u32 id);
extern void func_ov001_020958f8(void *record, u32 callback, u32 userData);

void StageRecord_SetCallback(u32 id, u32 callback, u32 userData)
{
    void *record;

    if (id != 0 && data_ov001_0209f2e8 != -1 && (record = func_ov001_0209c114(id)) != NULL) {
        func_ov001_020958f8(record, callback, userData);
    }
}
