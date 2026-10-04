typedef struct NNSiFndUntHeapMBlockHead {
    struct NNSiFndUntHeapMBlockHead *next;
} NNSiFndUntHeapMBlockHead;

typedef struct NNSiFndUntMBlockList {
    NNSiFndUntHeapMBlockHead *head;
} NNSiFndUntMBlockList;

NNSiFndUntHeapMBlockHead *PopMBlock(NNSiFndUntMBlockList *list)
{
    NNSiFndUntHeapMBlockHead *block = list->head;

    if (block) {
        list->head = block->next;
    }

    return block;
}
