#include "libs/nns/gfd/gfdi_LinkedListVramMan_Common.h"

BOOL TryToMergeBlockRegion_(NNSiGfdLnkVramMan *manager, NNSiGfdLnkVramBlock **blockPoolList, NNSiGfdLnkMemRegion *region)
{
    NNSiGfdLnkVramBlock *cursor = manager->freeList;
    NNSiGfdLnkVramBlock *next = GFD_NULL;
    BOOL merged = GFD_FALSE;

    while (cursor) {
        next = cursor->next;
        if (cursor->address == region->end) {
            region->end = GetBlockEndAddress_(cursor);
            RemoveBlock_(&manager->freeList, cursor);
            InsertBlock_(blockPoolList, cursor);
            merged |= GFD_TRUE;
        }
        if (GetBlockEndAddress_(cursor) == region->start) {
            region->start = cursor->address;
            RemoveBlock_(&manager->freeList, cursor);
            InsertBlock_(blockPoolList, cursor);
            merged |= GFD_TRUE;
        }
        cursor = next;
    }
    return merged;
}
