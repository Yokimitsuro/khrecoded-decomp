#include "nitro/types.h"

void func_ov001_0206b948(void *record, u16 first, u16 second)
{
    *(u32 *)record = 1;
    *(u16 *)((u8 *)record + 4) = first;
    *(u16 *)((u8 *)record + 6) = second;
}
