#include "nitro/types.h"

extern int AcquireRecordSlot(int slot, int param);
extern void ReleaseRecordSlot(s32 slot);
extern unsigned int func_0202a9e4(unsigned int range);
extern void func_ov002_0206aaa0(s32 *itemIds);
extern s32 PickRandomAvailableRecord(s32 category, s32 *preferredItemIds);

s32 PickRandomRecordWithBias(s32 category)
{
    s32 preferred[6];
    s32 result;

    AcquireRecordSlot(9, 1);
    if (func_0202a9e4(100) < 70) {
        func_ov002_0206aaa0(preferred);
        result = PickRandomAvailableRecord(category, preferred);
    } else {
        result = PickRandomAvailableRecord(category, NULL);
    }
    ReleaseRecordSlot(9);
    return result;
}
