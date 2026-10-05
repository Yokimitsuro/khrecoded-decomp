#include "nitro/types.h"

struct NNSiFndHeapHead;
extern struct NNSiFndHeapHead *NNS_FndCreateExpHeapEx(void *startAddress, u32 size, u16 optionFlag);
extern void *PXI_Init_0201313c(void *heapStart);
extern void NNS_FndInitAllocatorForExpHeap(int *allocator, int a, int b);

void func_0202a104(int *state)
{
    void *start = (void *)state[0];
    int size = *(int *)((char *)start + 0x1c) - (int)start;
    PXI_Init_0201313c(start);
    void *heap = NNS_FndCreateExpHeapEx(start, size, 1);
    state[0] = (int)heap;
    NNS_FndInitAllocatorForExpHeap(state + 1, (int)heap, 4);
}
