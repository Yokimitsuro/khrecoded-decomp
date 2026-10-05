#include "nitro/types.h"

void *func_ov052_020ceb74(const void *object)
{
    u8 *nested = *(u8 *const *)((const u8 *)object + 0x230);
    return nested + 0xa8;
}
