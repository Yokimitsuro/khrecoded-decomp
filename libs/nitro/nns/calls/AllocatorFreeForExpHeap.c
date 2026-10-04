extern void *NNS_FndFreeToExpHeap(void *heap, void *block);

void *AllocatorFreeForExpHeap(void **allocator, void *block)
{
    return NNS_FndFreeToExpHeap(allocator[1], block);
}
