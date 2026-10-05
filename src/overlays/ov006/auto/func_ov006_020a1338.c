#include "nitro/types.h"

void *func_ov006_020a1338(const void *object, s32 index, void *base)
{
    s16 stride = *(const s16 *)((const u8 *)object + 0xe);
    return (u8 *)base + index * stride;
}
