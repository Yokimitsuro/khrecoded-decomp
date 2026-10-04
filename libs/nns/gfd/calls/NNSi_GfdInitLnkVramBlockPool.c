#include "libs/nns/gfd/gfdi_LinkedListVramMan_Common.h"

NNSiGfdLnkVramBlock *NNSi_GfdInitLnkVramBlockPool(NNSiGfdLnkVramBlock *blocks, u32 length)
{
    {
        int i;
        for (i = 0; i < length - 1; i++) {
            blocks[i].next = &blocks[i + 1];
            blocks[i + 1].previous = &blocks[i];
        }
        blocks[0].previous = GFD_NULL;
        (blocks + length - 1)->next = GFD_NULL;
    }
    return &blocks[0];
}
