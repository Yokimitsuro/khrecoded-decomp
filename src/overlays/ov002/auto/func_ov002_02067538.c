#include "nitro/types.h"

extern u32 SetGlobalPackedBit();

u32 func_ov002_02067538(void *object)
{
    return SetGlobalPackedBit((u8 *)object + 0x200);
}
