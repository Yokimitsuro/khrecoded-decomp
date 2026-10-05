#include "nitro/types.h"

typedef struct StageResource {
    u16 id;
    u16 pad_02;
    void *data;
} StageResource;

typedef struct {
    u8 pad_00[0x18];
    void *objectHeap;
    u8 pad_1c[0x18];
    void *heap;
    void *savedHeap;
} HeapScope;

typedef struct StageManager {
    u8 pad_00[0x08];
    StageResource resources[64];
    u8 pad_208[0x18dec - 0x208];
    u16 resourceCount;
    u8 pad_18dee[0x12];
    s32 archiveBase;
    u8 pad_18e04[0x10];
    HeapScope heapScope;
} StageManager;

extern StageManager *data_ov001_020a0528;

extern u16 FindStageLinkIndex(u32 id);
extern u32 OpenAndClassifyFile(u32 fileId);
extern void *Heap_GetCurrent(void);
extern void *SetDefaultHeap(void *heap);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern u32 LoadFileIntoBuffer(u32 fileId, void *buffer, u32 size);
extern void RelocateResourceTable(void *table);
extern void *GetStageEntry(int id);

#define STAGE_FILE_ID(index) (0x80000000 | (((data_ov001_020a0528->archiveBase + 0x8000) & 0xfffffc) << 7) | (index))

void *LoadStageResource(u32 id)
{
    u16 slot = FindStageLinkIndex(id);
    StageManager *manager;
    u32 fileIndex;
    u32 size;
    void *buffer;

    if (slot == 0) {
        fileIndex = id & 0x1ff;
        size = OpenAndClassifyFile(STAGE_FILE_ID(fileIndex));
        if (size == 0) {
            return NULL;
        }
        manager = data_ov001_020a0528;
        if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
            manager->heapScope.savedHeap = Heap_GetCurrent();
            SetDefaultHeap(manager->heapScope.objectHeap);
        }
        buffer = NNS_FndAllocFromDefaultExpHeapEx(size, 0x20);
        if (buffer == NULL) {
            return NULL;
        }
        manager = data_ov001_020a0528;
        if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
            SetDefaultHeap(manager->heapScope.savedHeap);
            manager->heapScope.savedHeap = NULL;
        }
        if ((u16)LoadFileIntoBuffer(STAGE_FILE_ID(fileIndex), buffer, size) == 0) {
            return NULL;
        }
        data_ov001_020a0528->resources[data_ov001_020a0528->resourceCount].id = id;
        data_ov001_020a0528->resources[data_ov001_020a0528->resourceCount].data = buffer;
        data_ov001_020a0528->resourceCount++;
        RelocateResourceTable(buffer);
        slot = data_ov001_020a0528->resourceCount;
    }
    return GetStageEntry((s16)slot);
}
