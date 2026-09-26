typedef unsigned int u32;

extern u32 *data_020603c8[];

void *NNSi_FndGetCurrentRootHeap(void)
{
    return (void *)data_020603c8[1][8];
}
