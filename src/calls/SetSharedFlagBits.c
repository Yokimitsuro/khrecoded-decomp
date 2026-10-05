#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 baseAddr;
} SharedContext_0205fe00;

extern SharedContext_0205fe00 data_0205fe00;
extern void AcquireRecordSlot(int a, int b);
extern void ReleaseRecordSlot(int a);
extern s32 TestRecordFlagBit(u32 handle, s32 *outIndex, u8 *outFlags);

s32 SetSharedFlagBits(u32 handle)
{
    s32 index;
    u8 flags[4];
    s32 result;
    u32 base;

    AcquireRecordSlot(9, 1);
    result = TestRecordFlagBit(handle, &index, flags);
    ReleaseRecordSlot(9);

    base = data_0205fe00.baseAddr + 0x2788;
    if (result == 0) {
        *(u8 *)(base + index) |= flags[0];
        base += 0x67;
        *(u8 *)(base + index) |= flags[0];
    }
    return 1;
}
