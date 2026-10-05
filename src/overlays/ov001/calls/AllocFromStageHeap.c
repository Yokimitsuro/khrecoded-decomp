#include "nitro/types.h"

typedef struct StageHeap {
    u8 pad_00[0x34];
    void *heap;
    void *savedHeap;
} StageHeap;

typedef struct StageData {
    u8 pad_00000[0x18e14];
    StageHeap heapContext;
} StageData;

extern StageData *data_ov001_020a0528;
extern void *Heap_GetCurrent(void);
extern void *SetDefaultHeap(void *heap);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

static inline void PushStageHeap(void)
{
    StageData *stage = data_ov001_020a0528;

    if (stage != NULL && &stage->heapContext != NULL && stage->heapContext.savedHeap == NULL) {
        stage->heapContext.savedHeap = Heap_GetCurrent();
        SetDefaultHeap(stage->heapContext.heap);
    }
}

static inline void PopStageHeap(void)
{
    StageData *stage = data_ov001_020a0528;

    if (stage != NULL && &stage->heapContext != NULL && stage->heapContext.savedHeap != NULL) {
        SetDefaultHeap(stage->heapContext.savedHeap);
        stage->heapContext.savedHeap = NULL;
    }
}

void *AllocFromStageHeap(u32 size)
{
    u32 alignedSize;
    void *block;

    if (size == 0) {
        size = 0x200;
    }
    PushStageHeap();
    alignedSize = size & ~0x1ff;
    if (size & 0x1ff) {
        alignedSize += 0x200;
    }
    block = NNSi_FndAllocFromDefaultHeap(alignedSize);
    PopStageHeap();
    if (block == NULL) {
        return NULL;
    }
    return block;
}
