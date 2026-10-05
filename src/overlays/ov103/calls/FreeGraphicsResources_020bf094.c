#include "nitro/types.h"

typedef struct {
    void *fileData;
    u8 pad_04[0xc];
} GraphicsResource;

typedef struct {
    u8 pad_000[0x134];
    GraphicsResource resources[4];
} MenuScene;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeGraphicsResources_020bf094(MenuScene *scene)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (scene->resources[i].fileData != NULL) {
            NNSi_FndFreeFromDefaultHeap(scene->resources[i].fileData);
        }
    }
}
