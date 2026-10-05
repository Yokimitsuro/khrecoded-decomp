#include "nitro/types.h"

extern int data_02060394;
extern void NNS_FndFreeToExpHeap(void *heap, void *block);

void NNSi_FndFreeToExpHeap(void *block, void **heap)
{
    if (heap == 0) {
        heap = *(void ***)((char *)&data_02060394 + 4);
    }
    NNS_FndFreeToExpHeap(*heap, block);
}
