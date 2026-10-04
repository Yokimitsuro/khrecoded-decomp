#include "libs/nns/gfd/gfdi_LinkedListVramMan_Common.h"

extern BOOL TryToMergeBlockRegion_(NNSiGfdLnkVramMan *, NNSiGfdLnkVramBlock **, NNSiGfdLnkMemRegion *);

BOOL NNSi_GfdFreeLnkVram(NNSiGfdLnkVramMan *manager, NNSiGfdLnkVramBlock **blockPoolList, u32 address, u32 size)
{
    NNSiGfdLnkMemRegion region;
    region.start = address;
    region.end = address + size;
    (void)TryToMergeBlockRegion_(manager, blockPoolList, &region);

    {
        NNSiGfdLnkVramBlock *newFreeBlock = GetNewBlock_(blockPoolList);
        if (newFreeBlock == GFD_NULL) {
            return GFD_FALSE;
        } else {
            InitBlockFromRegion_(newFreeBlock, &region);
            InsertBlock_(&manager->freeList, newFreeBlock);
        }
    }
    return GFD_TRUE;
}
