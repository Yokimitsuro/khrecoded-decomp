#include "libs/nns/gfd/gfdi_LinkedListVramMan_Common.h"

BOOL NNSi_GfdAddNewFreeBlock(NNSiGfdLnkVramMan *manager, NNSiGfdLnkVramBlock **blockPoolList, u32 baseAddress, u32 size)
{
    NNSiGfdLnkVramBlock *block = GetNewBlock_(blockPoolList);
    if (block) {
        InitBlockFromParams_(block, baseAddress, size);
        InsertBlock_(&manager->freeList, block);
        return GFD_TRUE;
    } else {
        return GFD_FALSE;
    }
}
