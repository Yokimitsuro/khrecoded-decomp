typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

typedef struct NNSFndLink {
    void *prevObject;
    void *nextObject;
} NNSFndLink;

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct NNSiFndHeapHead {
    u32 signature;
    NNSFndLink link;
    NNSFndList childList;
    void *heapStart;
    void *heapEnd;
    u32 attribute;
} NNSiFndHeapHead;

typedef NNSiFndHeapHead *NNSFndHeapHandle;

typedef struct NNSiFndFrmHeapState {
    u32 tagName;
    void *headAllocator;
    void *tailAllocator;
    struct NNSiFndFrmHeapState *pPrevState;
} NNSiFndFrmHeapState;

typedef struct NNSiFndFrmHeapHead {
    void *headAllocator;
    void *tailAllocator;
    NNSiFndFrmHeapState *pState;
} NNSiFndFrmHeapHead;

BOOL NNS_FndFreeByStateToFrmHeap(NNSFndHeapHandle heap, u32 tagName)
{
    NNSiFndFrmHeapHead *frame;
    NNSiFndFrmHeapState *state;

    frame = (NNSiFndFrmHeapHead *)((u8 *)heap + sizeof(NNSiFndHeapHead));
    state = frame->pState;

    if (tagName != 0) {
        for (; state; state = state->pPrevState) {
            if (state->tagName == tagName) {
                break;
            }
        }
    }

    if (!state) {
        return 0;
    }

    frame->headAllocator = state->headAllocator;
    frame->tailAllocator = state->tailAllocator;
    frame->pState = state->pPrevState;
    return 1;
}
