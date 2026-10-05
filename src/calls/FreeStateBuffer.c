#include "nitro/types.h"

typedef struct StateBuffer {
    void *buffer;
    u8 pad_04[0x18];
    int state;
} StateBuffer;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeStateBuffer(StateBuffer *owner)
{
    switch (owner->state) {
    case 0:
        NNSi_FndFreeFromDefaultHeap(owner->buffer);
        break;
    case 1:
        NNSi_FndFreeFromDefaultHeap(owner->buffer);
        break;
    case 2:
        NNSi_FndFreeFromDefaultHeap(owner->buffer);
        break;
    case 3:
        NNSi_FndFreeFromDefaultHeap(owner->buffer);
        break;
    case 4:
        NNSi_FndFreeFromDefaultHeap(owner->buffer);
        break;
    }
    owner->buffer = NULL;
    owner->state = -1;
}
