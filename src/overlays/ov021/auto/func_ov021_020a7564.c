#include "nitro/types.h"

u16 func_ov021_020a7564(const void *object)
{
    const u8 *bytes = object;
    return *(const u16 *)bytes + *(const u16 *)(bytes + 4);
}
