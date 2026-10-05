#include "nitro/types.h"

extern u32 GetBoundedEntryField();

u16 GetBiasAdjustedField(void)
{
    u32 base;

    base = GetBoundedEntryField();
    return (u16)(*(u16 *)(base + 0x94) - 0x8000);
}
