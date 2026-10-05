#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x2cc];
    u32 result;
} CardThreadBlock;

typedef struct {
    u8 pad_00[4];
    CardThreadBlock *thread;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern BOOL OS_IsThreadTerminated(int *thread);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

u32 PollCardTransferThread(void)
{
    u32 result = 0xffffffff;

    if (data_0205fe00.thread != 0 &&
        OS_IsThreadTerminated((int *)data_0205fe00.thread) != 0) {
        result = data_0205fe00.thread->result;
        NNSi_FndFreeFromDefaultHeap(data_0205fe00.thread);
        data_0205fe00.thread = 0;
    }
    return result;
}
