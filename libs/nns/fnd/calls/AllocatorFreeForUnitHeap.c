extern void *NNS_FndFreeToUnitHeap(void *heap, void *block);

void *AllocatorFreeForUnitHeap(void **allocator, void *block)
{
    return NNS_FndFreeToUnitHeap(allocator[1], block);
}
