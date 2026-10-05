#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *block);

typedef struct {
    u8 pad_000[0x44];
    void *resource;
} SomeObj;

void FreeResourceAt0x44(SomeObj *obj)
{
    if (obj->resource != 0) {
        NNSi_FndFreeFromDefaultHeap(obj->resource);
    }
}
