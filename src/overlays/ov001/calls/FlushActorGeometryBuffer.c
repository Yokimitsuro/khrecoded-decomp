#include "nitro/types.h"

extern void func_01ffa204(const void *src, u32 size);
extern u8 data_ov001_0209f194[0x154];

void FlushActorGeometryBuffer(void) {
    func_01ffa204(data_ov001_0209f194, 0x154);
}
