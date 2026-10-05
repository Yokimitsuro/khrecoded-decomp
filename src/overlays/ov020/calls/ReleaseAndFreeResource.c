#include "nitro/types.h"

extern void ReleaseResourceAndDetach(void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseAndFreeResource(int self) {
    if (*(void **)(self + 0x48) != NULL) {
        ReleaseResourceAndDetach(*(void **)(self + 0x48));
        NNSi_FndFreeFromDefaultHeap(*(void **)(self + 0x48));
        *(void **)(self + 0x48) = NULL;
    }
}
