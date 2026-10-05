#include "nitro/types.h"

extern int data_02060394;
extern void *NNSi_FndAllocFromExpHeapEx(u32 size, void **heap);
extern void *func_0202a4c4(void *object, void *descriptor, void *userData, int useTailAlloc);

void *Obj_CreateWithTailWork(void *descriptor, void *userData)
{
    return func_0202a4c4(NNSi_FndAllocFromExpHeapEx(0x2c, *(void **)&data_02060394), descriptor, userData, 1);
}
