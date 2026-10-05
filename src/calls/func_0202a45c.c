#include "nitro/types.h"

extern int data_02060394;
extern void *NNSi_FndAllocFromExpHeapEx(u32 size, void **heap);
extern void *Obj_Construct(void *buffer, void *descriptor, void *userData, int flag);

void *func_0202a45c(void *descriptor, void *userData)
{
    return Obj_Construct(NNSi_FndAllocFromExpHeapEx(0x2c, *(void **)&data_02060394), descriptor, userData, 0);
}
