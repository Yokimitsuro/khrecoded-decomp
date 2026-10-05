#include "nitro/types.h"

void SetFieldAt0x30(void *obj, u32 value)
{
    *(u32 *)((u8 *)obj + 0x30) = value;
}
