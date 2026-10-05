#include "nitro/types.h"

extern void FlushGeometryCommandBuffer(const void *src, u32 size);
extern u8 data_ov001_0209f194[0x154];

void FlushActorGeometryBuffer(void) {
    FlushGeometryCommandBuffer(data_ov001_0209f194, 0x154);
}
