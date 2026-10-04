typedef unsigned char u8;
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

extern NNSFndHeapHandle NNS_FndCreateFrmHeapEx(void *startAddress, u32 size, int optFlag);
extern void NNS_FndDestroyFrmHeap(NNSFndHeapHandle heap);
extern BOOL InitHeap(NNSSndHeap *heap, NNSFndHeapHandle handle);

NNSSndHeapHandle NNS_SndHeapCreate(void *startAddress, u32 size)
{
    NNSSndHeap *heap;
    void *endAddress;
    NNSFndHeapHandle handle;

    endAddress = (u8 *)startAddress + size;
    startAddress = (void *)(((u32)startAddress + 3) & ~3);

    if (startAddress > endAddress) return 0;

    size = (u32)((u8 *)endAddress - (u8 *)startAddress);
    if (size < sizeof(NNSSndHeap)) return 0;

    size -= sizeof(NNSSndHeap);
    heap = (NNSSndHeap *)startAddress;
    startAddress = heap + 1;

    handle = NNS_FndCreateFrmHeapEx(startAddress, size, 0);
    if (handle == 0) return 0;

    if (!InitHeap(heap, handle)) {
        NNS_FndDestroyFrmHeap(handle);
        return 0;
    }

    return heap;
}