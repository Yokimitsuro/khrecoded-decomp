#include "nitro/types.h"

void func_ov052_020ccab0(void *record, u16 value)
{
    *(u32 *)record = 0;
    *(u16 *)((u8 *)record + 4) = 0;
    *(u16 *)((u8 *)record + 6) = value;
}
