typedef unsigned int u32;

extern u32 *gTaskManager[];

void *NNSi_FndGetCurrentRootHeap(void)
{
    return (void *)gTaskManager[1][8];
}
