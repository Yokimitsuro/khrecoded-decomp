extern int NNSi_FndGetAllocatorForDefaultHeap();
extern int NNS_FndAllocFromAllocator();

void *CamAnim_AllocPlayer(void) {
    return NNS_FndAllocFromAllocator(NNSi_FndGetAllocatorForDefaultHeap(0), 0x20);
}
