#include "nitro/types.h"

typedef struct AnimBase {
    u32 words[10];
} AnimBase;

typedef struct AnimTransform {
    AnimBase base;
    u8 pad28[0xc];
    s32 frame;
    s32 scaleX;
    s32 scaleY;
    u32 enabled : 1;
    u32 flipped : 1;
    u32 looped : 1;
} AnimTransform;

void CopyAnimTransform(const AnimBase *src, AnimTransform *dst)
{
    dst->base = *src;
    dst->enabled = 1;
    dst->flipped = 0;
    dst->frame = 0;
    dst->looped = 0;
    dst->scaleX = 0x1000;
    dst->scaleY = 0x1000;
}
