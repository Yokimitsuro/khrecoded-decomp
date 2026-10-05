#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x2c0];
    void *src;
    u32 length;
    void *dst;
    u32 result;
} CardThreadBlock;

typedef struct {
    u8 pad_00[4];
    CardThreadBlock *thread;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void OS_CreateThread(CardThreadBlock *thread, void (*entry)(CardThreadBlock *), CardThreadBlock *arg,
                          void *stack, u32 stackSize, u32 priority);
extern void OS_WakeupThreadDirect(char *thread);
extern void func_02026b6c(CardThreadBlock *arg);

void StartCardTransferThread(void *src, void *dst, u32 length)
{
    data_0205fe00.thread = NNSi_FndAllocFromDefaultHeap(0x2d0);
    data_0205fe00.thread->src = src;
    data_0205fe00.thread->length = length;
    data_0205fe00.thread->dst = dst;
    OS_CreateThread(data_0205fe00.thread, func_02026b6c, data_0205fe00.thread,
                  &data_0205fe00.thread->src, 0x200, 0x11);
    OS_WakeupThreadDirect((char *)data_0205fe00.thread);
}
