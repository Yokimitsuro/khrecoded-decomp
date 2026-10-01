typedef struct NNSFndLink {
    void *previous;
    void *next;
} NNSFndLink;

typedef struct NNSFndList {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short offset;
} NNSFndList;

typedef struct NNSiFndHeapHead {
    unsigned int signature;
    NNSFndLink link;
    NNSFndList childList;
    void *heapStart;
    void *heapEnd;
    unsigned int attribute;
} NNSiFndHeapHead;

extern int data_0205a8b0;
extern NNSFndList data_0205a8b4;
extern void NNS_FndInitList(NNSFndList *list, int linkOffset);
extern NNSFndList *FindListContainHeap(const void *memoryBlock);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);

void NNSi_FndInitHeapHead(
    NNSiFndHeapHead *head,
    unsigned int signature,
    void *heapStart,
    void *heapEnd,
    unsigned short optionFlag)
{
    head->signature = signature;
    head->heapStart = heapStart;
    head->heapEnd = heapEnd;
    head->attribute = 0;
    head->attribute &= ~0xff;
    head->attribute |= optionFlag & 0xff;
    NNS_FndInitList(&head->childList, 4);
    if (!data_0205a8b0) {
        NNS_FndInitList(&data_0205a8b4, 4);
        data_0205a8b0 = 1;
    }
    NNS_FndAppendListObject(FindListContainHeap(head), head);
}
