#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    void *bufferA;
    void *bufferB;
    void *bufferC;
} DataBuffers;

extern void NNSi_FndFreeFromDefaultHeap(void);

void Obj_FreeDataBuffers(DataBuffers *obj)
{
    if (obj->bufferA != 0) {
        NNSi_FndFreeFromDefaultHeap();
        obj->bufferA = 0;
    }
    if (obj->bufferB != 0) {
        NNSi_FndFreeFromDefaultHeap();
        obj->bufferB = 0;
    }
    if (obj->bufferC == 0) {
        return;
    }
    NNSi_FndFreeFromDefaultHeap();
    obj->bufferC = 0;
}
