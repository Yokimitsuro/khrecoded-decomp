#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 entryCount;
    u8 fndList[0x34];
} ResourceCacheState;

extern void func_ov001_02073030(u32 unused);
extern BOOL DestroyFndObjectList(int container);

void DestroyFndListIfNonEmpty(ResourceCacheState *state)
{
    if (state->entryCount != 0) {
        func_ov001_02073030(0);
        DestroyFndObjectList((int)&state->fndList);
    }
}
