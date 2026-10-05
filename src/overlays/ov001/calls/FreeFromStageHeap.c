#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x34];
    void *heap;
    void *savedHeap;
} HeapScope;

typedef struct {
    u8 pad_00[0x18e14];
    HeapScope heapScope;
} StageManager;

extern StageManager *data_ov001_020a0528;
extern void *Heap_GetCurrent(void);
extern void *SetDefaultHeap(void *heap);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeFromStageHeap(void *block)
{
    StageManager *manager;

    manager = data_ov001_020a0528;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
        manager->heapScope.savedHeap = Heap_GetCurrent();
        SetDefaultHeap(manager->heapScope.heap);
    }
    if (block != NULL) {
        NNSi_FndFreeFromDefaultHeap(block);
    }
    manager = data_ov001_020a0528;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
        SetDefaultHeap(manager->heapScope.savedHeap);
        manager->heapScope.savedHeap = NULL;
    }
}
