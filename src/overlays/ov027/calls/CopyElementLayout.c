#include "nitro/types.h"

typedef struct ElementLayout {
    u8 pad_00[6];
    u16 width;
    u16 height;
    s16 offsetX;
    s16 offsetY;
    u8 pad_0E[0xA];
    u32 attr;
} ElementLayout;

ElementLayout *CopyElementLayout(void *owner, ElementLayout *dst, const ElementLayout *src)
{
    dst->width = src->width;
    dst->height = src->height;
    dst->offsetX = src->offsetX;
    dst->offsetY = src->offsetY;
    dst->attr = src->attr;
    return dst;
}
