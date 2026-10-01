typedef struct DefaultHeapState {
    void *reserved;
    void **currentHeap;
} DefaultHeapState;

extern DefaultHeapState data_02060394;
extern void *NNS_FndAllocFromExpHeapEx(void *heap, unsigned int size, int alignment);

void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int size, int alignment)
{
    return NNS_FndAllocFromExpHeapEx(*data_02060394.currentHeap, size, alignment);
}