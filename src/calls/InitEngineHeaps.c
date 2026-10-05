extern void CreateEngineHeaps(int *specialHeapSize, int *defaultHeapSize);
extern void NNS_FndInitAllocatorForExpHeap(void *allocator, int handle, int align);
extern int data_02060394;
extern int data_020603a0;
extern int data_020603a4;
extern int data_020603b4;
extern int data_020603b8;

void InitEngineHeaps(void)
{
    int specialHeapSize;
    int defaultHeapSize;

    CreateEngineHeaps(&specialHeapSize, &defaultHeapSize);

    NNS_FndInitAllocatorForExpHeap(&data_020603b8, *(int *)((char *)&data_02060394 + 0x20) = specialHeapSize, 4);
    *(int *)&data_02060394 = (int)&data_020603b4;

    NNS_FndInitAllocatorForExpHeap(&data_020603a4, *(int *)((char *)&data_02060394 + 0xc) = defaultHeapSize, 4);
    *(int *)((char *)&data_02060394 + 8) = (int)&data_020603a0;
    *(int *)((char *)&data_02060394 + 4) = (int)&data_020603a0;
}
