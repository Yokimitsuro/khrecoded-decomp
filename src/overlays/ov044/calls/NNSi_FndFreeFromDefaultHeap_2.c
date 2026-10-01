typedef unsigned char u8;
typedef struct DefaultHeapState {
    u8 reserved[0x48];
    void *heap;
} DefaultHeapState;
extern DefaultHeapState *data_ov044_020d0ec0;
extern void NNS_FndFreeToExpHeap_2(void *heap, void *block);
void NNSi_FndFreeFromDefaultHeap_2(void *block)
{
    NNS_FndFreeToExpHeap_2(data_ov044_020d0ec0->heap, block);
}