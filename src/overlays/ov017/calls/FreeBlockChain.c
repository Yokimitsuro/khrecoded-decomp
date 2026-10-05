#include "nitro/types.h"

typedef struct HeapBlock {
    struct HeapBlock *next;
} HeapBlock;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeBlockChain(HeapBlock **head)
{
    HeapBlock *block = *head;
    while (block != NULL) {
        HeapBlock *current = block;
        block = block->next;
        NNSi_FndFreeFromDefaultHeap(current);
    }
    *head = NULL;
}
