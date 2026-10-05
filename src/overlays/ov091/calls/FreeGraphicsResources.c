#include "nitro/types.h"

typedef struct {
    void *fileData;
    u8 pad_04[0xc];
} GraphicsResource;

typedef struct {
    u8 pad_00[0xa4];
    GraphicsResource resources[5];
} MenuScene;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeGraphicsResources(MenuScene *scene)
{
    int i;

    for (i = 0; i < 5; i++) {
        if (scene->resources[i].fileData != NULL) {
            NNSi_FndFreeFromDefaultHeap(scene->resources[i].fileData);
        }
    }
}
