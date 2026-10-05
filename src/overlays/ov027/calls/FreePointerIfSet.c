#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreePointerIfSet(void **ptr) {
    if (*ptr != 0) {
        NNSi_FndFreeFromDefaultHeap(*ptr);
        *ptr = 0;
    }
}
