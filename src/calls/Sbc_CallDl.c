#include "nitro/types.h"

typedef struct NNSG3dRS {
    const u8 *c;
    u32 pad04;
    u32 flag;
} NNSG3dRS;

extern void FlushGeometryCommandBuffer(const void *src, u32 size);

void Sbc_CallDl(NNSG3dRS *rs)
{
    if (!(rs->flag & 0x100)) {
        u32 rel = (u32)(rs->c[1] | (rs->c[2] << 8) | (rs->c[3] << 16) | (rs->c[4] << 24));
        u32 size = (u32)(rs->c[5] | (rs->c[6] << 8) | (rs->c[7] << 16) | (rs->c[8] << 24));

        FlushGeometryCommandBuffer(rs->c + rel, size);
    }
    rs->c += 1 + 4 + 4;
}
