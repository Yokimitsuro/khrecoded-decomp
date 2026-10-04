typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef void *NNSFndHeapHandle;

typedef struct NNSSndHeap {
    NNSFndHeapHandle handle;
    NNSFndList sectionList;
} NNSSndHeap;

typedef NNSSndHeap *NNSSndHeapHandle;

extern BOOL NNS_FndRecordStateForFrmHeap(NNSFndHeapHandle heap, u32 tagName);
extern BOOL NNS_FndFreeByStateToFrmHeap(NNSFndHeapHandle heap, u32 tagName);
extern BOOL NewSection(NNSSndHeap *heap);

int NNS_SndHeapSaveState(NNSSndHeapHandle heap)
{
    BOOL result;

    if (!NNS_FndRecordStateForFrmHeap(heap->handle, heap->sectionList.numObjects)) {
        return -1;
    }

    if (!NewSection(heap)) {
        result = NNS_FndFreeByStateToFrmHeap(heap->handle, 0);
        return -1;
    }

    return heap->sectionList.numObjects - 1;
}