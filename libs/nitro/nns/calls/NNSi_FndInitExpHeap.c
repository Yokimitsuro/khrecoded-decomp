typedef struct NNSiFndHeapHead {
    unsigned int signature;
    void *previous;
    void *next;
    unsigned char childList[12];
    void *heapStart;
    void *heapEnd;
    unsigned int attribute;
} NNSiFndHeapHead;

typedef struct NNSiFndExpHeapHead {
    NNSiFndHeapHead common;
    void *freeBlocks;
    void *usedBlocks;
    unsigned int groupId;
} NNSiFndExpHeapHead;

extern void NNSi_FndInitHeapHead(
    NNSiFndHeapHead *head,
    unsigned int signature,
    void *heapStart,
    void *heapEnd,
    int optionFlag);

void *NNSi_FndInitExpHeap(NNSiFndExpHeapHead *head, void *heapEnd, int optionFlag)
{
    NNSi_FndInitHeapHead(
        &head->common,
        0x46524d48,
        (char *)head + sizeof(NNSiFndExpHeapHead),
        heapEnd,
        optionFlag);
    head->freeBlocks = head->common.heapStart;
    head->usedBlocks = head->common.heapEnd;
    head->groupId = 0;
    return head;
}
