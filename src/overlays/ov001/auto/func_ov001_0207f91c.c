#include "nitro/types.h"

u8 func_ov001_0207f91c(const void *object)
{
    const u8 *nested = *(const u8 *const *)((const u8 *)object + 0x8);
    return nested[0x82];
}
