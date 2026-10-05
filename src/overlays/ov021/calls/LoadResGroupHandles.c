#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 *flags;
} ResDesc;

typedef struct {
    u32 pad_00;
    s32 resId;
} ResItem;

typedef struct {
    u8 pad_00[0x10];
    ResItem **items;
    s32 itemCount;
    void **handles;
    s32 handleCount;
} ResGroup;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void *AcquirePaletteEntry(void *owner, ResDesc *desc, s32 resId, int arg3);

void LoadResGroupHandles(ResGroup *group, void *owner, ResDesc *desc)
{
    int i;

    if (*desc->flags & 4) {
        group->handles = NNSi_FndAllocFromDefaultHeap(group->itemCount * 4);
        group->handleCount = group->itemCount;
        for (i = 0; i < group->handleCount; i++) {
            group->handles[i] = AcquirePaletteEntry(owner, desc, group->items[i]->resId, 0);
        }
    }
}
