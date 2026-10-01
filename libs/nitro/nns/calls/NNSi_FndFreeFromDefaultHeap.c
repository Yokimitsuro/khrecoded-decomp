typedef struct DefaultHeapState {
    void *heap;
    void **currentHeap;
} DefaultHeapState;

extern DefaultHeapState data_02060394;
extern void NNS_FndFreeToExpHeap(void *heap, void *memory);

void NNSi_FndFreeFromDefaultHeap(void *memory)
{
    NNS_FndFreeToExpHeap(*data_02060394.currentHeap, memory);
}
