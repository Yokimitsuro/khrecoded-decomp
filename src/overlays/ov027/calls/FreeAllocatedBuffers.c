#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *block);

struct Owner {
    void *primary;
    u8 pad_04[0xc];
    void *secondary;
};

void FreeAllocatedBuffers(struct Owner *owner) {
    NNSi_FndFreeFromDefaultHeap(owner->secondary);
    NNSi_FndFreeFromDefaultHeap(owner->primary);
}
