#include "nitro/types.h"

extern u16 func_ov021_020a7564(void *angles);
extern u16 AddQuantizedViewAngle(u16 angle);

u16 QuantizeSummedAngle(void *angles)
{
    return AddQuantizedViewAngle(func_ov021_020a7564(angles) + 0x3fff);
}
