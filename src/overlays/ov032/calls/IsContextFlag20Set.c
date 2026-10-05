#include "nitro/types.h"

extern int data_ov032_020c0080[];

u32 IsContextFlag20Set(void)
{
    return *(u16 *)(data_ov032_020c0080[1] + 6) & 0x20;
}
