typedef struct DefaultHeapState {
    void *heap;
    void *currentHeap;
} DefaultHeapState;

extern DefaultHeapState data_02060394;

void *NNSi_FndGetAllocatorForDefaultHeap(void *heap)
{
    if (heap == 0) {
        heap = data_02060394.currentHeap;
    }
    return (char *)heap + 4;
}