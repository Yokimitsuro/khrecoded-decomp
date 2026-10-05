#include "nitro/types.h"

extern void GetModeDataRegion(u32 *offset, u32 *size);
extern BOOL func_ov001_020645c8(u32 flagIndex);
extern u16 func_ov001_02086994(u32 entryId, u32 slot);

int GetEntryUnlockState(BOOL skipModeCheck, u32 flagOffset, u32 entryId, u32 slot)
{
    u32 regionOffset;
    u32 size;

    if (!skipModeCheck) {
        GetModeDataRegion(&regionOffset, &size);
        if (!func_ov001_020645c8(regionOffset + flagOffset)) {
            return 0;
        }
    }
    if (entryId != 0xFFFF && slot != 0xFF) {
        if (func_ov001_02086994(entryId, slot)) {
            return 2;
        }
        return 1;
    }
    return 2;
}
