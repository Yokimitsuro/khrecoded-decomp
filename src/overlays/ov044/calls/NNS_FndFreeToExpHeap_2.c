typedef struct Ov044HeapFreeRequest {
    unsigned char reserved[0x40];
    void *previousHeap;
    void *heap;
    unsigned char work[0x1c];
    int result;
    void *memoryBlock;
    int active;
} Ov044HeapFreeRequest;

extern Ov044HeapFreeRequest *data_ov044_020d0ec0;
extern void SnapshotPanelPose(
    Ov044HeapFreeRequest *request,
    void *memoryBlock,
    Ov044HeapFreeRequest **requestSlot,
    int active);

void NNS_FndFreeToExpHeap_2(void *heap, void *memoryBlock)
{
    Ov044HeapFreeRequest *request = data_ov044_020d0ec0;

    request->previousHeap = request->heap;
    data_ov044_020d0ec0->heap = heap;
    data_ov044_020d0ec0->result = 0;
    data_ov044_020d0ec0->memoryBlock = memoryBlock;
    request = data_ov044_020d0ec0;
    request->active = 1;
    SnapshotPanelPose(request, memoryBlock, &data_ov044_020d0ec0, 1);
}
