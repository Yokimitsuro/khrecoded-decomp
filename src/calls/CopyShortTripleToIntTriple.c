#include "nitro/types.h"

typedef struct Vec3s16 {
    s16 x;
    s16 y;
    s16 z;
} Vec3s16;

typedef struct Vec3s32 {
    s32 x;
    s32 y;
    s32 z;
} Vec3s32;

void CopyShortTripleToIntTriple(void *unused, volatile Vec3s16 *src, Vec3s32 *dst)
{
    s32 x = src->x;
    s32 y = src->y;
    s32 z = src->z;
    dst->x = x;
    dst->y = y;
    dst->z = z;
}
