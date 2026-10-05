#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    void *objectHeap;
    u8 pad_1c[0x18];
    void *heap;
    void *savedHeap;
} HeapScope;

typedef struct {
    u32 unk_00;
    void *block;
} StageBuffer;

typedef struct {
    u8 pad_00[9];
    u8 unk_09_0 : 4;
    u8 marked : 1;
    u8 unk_09_5 : 3;
    u8 pad_0a[0x28 - 0xa];
} StageLink;

typedef struct {
    u8 pad_000[0x10];
    u16 id;
    u8 pad_012[0x1c8 - 0x12];
} StageEvent;

typedef struct {
    u8 pad_000[0x27c];
    u16 active;
    u8 pad_27e[0x3c8 - 0x27e];
} StageActor;

typedef struct {
    u8 pad_00[0xc];
    u16 active;
    u8 pad_0e[0x1c - 0xe];
} StageSlot;

typedef struct {
    void *model;
    void *buffer;
    u8 pad_08[4];
    u8 resource[0x80 - 0xc];
    void *resourceData;
} StageObjectRecord;

typedef struct {
    u32 flags;
    u8 pad_00004[4];
    StageBuffer buffers[64];
    StageLink *links;
    u32 *linkFlags;
    StageEvent *events;
    u8 pad_00214[0x4b14 - 0x214];
    StageActor actors[64];
    StageSlot slots[64];
    u8 pad_14414[0x18d80 - 0x14414];
    void *pools[8];
    u8 pad_18da0[0x18de4 - 0x18da0];
    u16 eventCount;
    u16 linkCount;
    u16 activeLinks;
    u16 pendingA;
    u16 pendingB;
    u8 pad_18dee[4];
    u16 pendingC;
    u8 pad_18df4[0x18e14 - 0x18df4];
    HeapScope heapScope;
    u8 pad_18e50[0x18e5c - 0x18e50];
    u32 pendingFlags;
} StageManager;

extern StageManager *data_ov001_020a0528;
extern BOOL func_ov001_0206c768(void);
extern void func_ov001_0206c720(void (*callback)(void));
extern void DrawVisibleStageQuads(void);
extern void ReleaseSlotActor(StageSlot *slot);
extern void ReleaseEventResources(StageEvent *event);
extern void ReleaseActorResources(StageActor *actor);
extern StageObjectRecord *GetStageObjectRecord(u16 id);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ReleaseResourceAndDetach(void *resource);
extern void ZeroHalfThenFree(void *model);
extern void *Heap_GetCurrent(void);
extern void *SetDefaultHeap(void *heap);
extern void HandlePool_ReleaseAll(void *pool);

static inline void PushStageHeap(void)
{
    StageManager *manager = data_ov001_020a0528;

    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
        manager->heapScope.savedHeap = Heap_GetCurrent();
        SetDefaultHeap(manager->heapScope.objectHeap);
    }
}

static inline void PopStageHeap(void)
{
    StageManager *manager = data_ov001_020a0528;

    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
        SetDefaultHeap(manager->heapScope.savedHeap);
        manager->heapScope.savedHeap = NULL;
    }
}

void ShutdownStageManager(void)
{
    int i;
    StageObjectRecord *record;

    if (func_ov001_0206c768() && (data_ov001_020a0528->flags & 0x80000000)) {
        func_ov001_0206c720(DrawVisibleStageQuads);
    }
    data_ov001_020a0528->flags &= 0x7fffffff;
    for (i = 0; i < 64; i++) {
        if (data_ov001_020a0528->slots[i].active != 0) {
            ReleaseSlotActor(&data_ov001_020a0528->slots[i]);
        }
    }
    for (i = 0; i < data_ov001_020a0528->eventCount; i++) {
        if (data_ov001_020a0528->events[i].id != 0) {
            ReleaseEventResources(&data_ov001_020a0528->events[i]);
        }
    }
    for (i = 0; i < 64; i++) {
        if (data_ov001_020a0528->actors[i].active != 0) {
            ReleaseActorResources(&data_ov001_020a0528->actors[i]);
        }
    }
    for (i = 0; i < 64; i++) {
        record = GetStageObjectRecord(i + 1);
        if (record != NULL) {
            if (record->buffer != NULL) {
                NNSi_FndFreeFromDefaultHeap(record->buffer);
                record->buffer = NULL;
            }
            if (record->resourceData != NULL) {
                ReleaseResourceAndDetach(record->resource);
            }
            if (record->model != NULL) {
                ZeroHalfThenFree(record->model);
                record->model = NULL;
            }
        }
    }
    data_ov001_020a0528->pendingA = 0;
    PushStageHeap();
    for (i = 0; i < 64; i++) {
        if (data_ov001_020a0528->buffers[i].block != NULL) {
            NNSi_FndFreeFromDefaultHeap(data_ov001_020a0528->buffers[i].block);
            data_ov001_020a0528->buffers[i].block = NULL;
        }
    }
    data_ov001_020a0528->pendingB = 0;
    PopStageHeap();
    data_ov001_020a0528->pendingFlags = 0;
    if (data_ov001_020a0528->links != NULL) {
        for (i = 0; i < data_ov001_020a0528->linkCount; i++) {
            data_ov001_020a0528->links[i].marked = 0;
        }
    }
    data_ov001_020a0528->pendingC = 0;
    PushStageHeap();
    HandlePool_ReleaseAll(data_ov001_020a0528->pools[0]);
    HandlePool_ReleaseAll(data_ov001_020a0528->pools[1]);
    HandlePool_ReleaseAll(data_ov001_020a0528->pools[2]);
    HandlePool_ReleaseAll(data_ov001_020a0528->pools[4]);
    HandlePool_ReleaseAll(data_ov001_020a0528->pools[5]);
    HandlePool_ReleaseAll(data_ov001_020a0528->pools[6]);
    HandlePool_ReleaseAll(data_ov001_020a0528->pools[7]);
    PopStageHeap();
}


