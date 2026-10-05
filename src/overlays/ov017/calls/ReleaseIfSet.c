#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap();

void ReleaseIfSet(void **ptr)
{
    if (*ptr != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *ptr = 0;
    }
}
