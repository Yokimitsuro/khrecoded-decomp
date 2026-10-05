#include "nitro/types.h"

typedef struct {
    void *block;
    u8 pad_04[0xc];
} ResourceSlot;

typedef struct {
    u8 pad_000[0x42c];
    ResourceSlot resources[3];
} SceneWork;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeResourceBlocks_020bf5c4(SceneWork *work)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (work->resources[i].block != NULL) {
            NNSi_FndFreeFromDefaultHeap(work->resources[i].block);
        }
    }
}
