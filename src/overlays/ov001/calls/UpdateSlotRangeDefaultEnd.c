#include "nitro/types.h"

extern void func_ov001_020749c0(int slot, u32 start, u32 limit, u32 end, int arg, int flag);

void UpdateSlotRangeDefaultEnd(int slot, u32 start, u32 limit, u32 end, int arg)
{
    if (end == 0) {
        end = start;
    }
    func_ov001_020749c0(slot, start, limit, end, arg, 0);
}
