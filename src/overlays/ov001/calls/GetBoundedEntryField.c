#include "nitro/types.h"

extern u32 data_ov001_020a04bc;

/* Bounds-checked indexed lookup into manager records */
u32 GetBoundedEntryField(int index)
{
    if (index >= *(int *)(data_ov001_020a04bc + 0x7c)) {
        return 0;
    }
    return *(u32 *)(data_ov001_020a04bc + index * 0x28 + 8);
}
