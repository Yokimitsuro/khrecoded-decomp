#include "libs/nns/gfd/gfdi_LinkedListVramMan_Common.h"

extern BOOL TryToMergeBlockRegion_(NNSiGfdLnkVramMan *, NNSiGfdLnkVramBlock **, NNSiGfdLnkMemRegion *);

void NNSi_GfdMergeAllFreeBlocks(NNSiGfdLnkVramMan *manager, NNSiGfdLnkVramBlock **blockPoolList)
{
    NNSiGfdLnkMemRegion region;
    NNSiGfdLnkVramBlock *cursor = manager->freeList;

    while (cursor) {
        region.start = cursor->address;
        region.end = cursor->address + cursor->size;
        if (TryToMergeBlockRegion_(manager, blockPoolList, &region)) {
            cursor->address = region.start;
            cursor->size = region.end - region.start;
            cursor = manager->freeList;
        } else {
            cursor = cursor->next;
        }
    }
}
