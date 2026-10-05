#include "nitro/types.h"

typedef struct {
    void *block;
    u8 pad_04[0xc];
} ResourceSlot;

typedef struct {
    u8 pad_000[0x1b0];
    ResourceSlot resources[5];
} SceneWork;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeResourceBlocks(SceneWork *work)
{
    int i;

    for (i = 0; i < 5; i++) {
        if (work->resources[i].block != NULL) {
            NNSi_FndFreeFromDefaultHeap(work->resources[i].block);
        }
    }
}
