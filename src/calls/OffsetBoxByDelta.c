#include "nitro/types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    s32 x, y, z;
} Vec3i;

/* Shifts a box's near side by a delta per axis. */
void OffsetBoxByDelta(const Box *src, Box *dst, const Vec3i *delta) {
    if (delta->x > 0) {
        dst->minX = src->minX + delta->x;
        dst->maxX = src->maxX;
    } else {
        dst->maxX = src->maxX + delta->x;
        dst->minX = src->minX;
    }
    if (delta->y > 0) {
        dst->minY = src->minY + delta->y;
        dst->maxY = src->maxY;
    } else {
        dst->maxY = src->maxY + delta->y;
        dst->minY = src->minY;
    }
    if (delta->z > 0) {
        dst->minZ = src->minZ + delta->z;
        dst->maxZ = src->maxZ;
    } else {
        dst->maxZ = src->maxZ + delta->z;
        dst->minZ = src->minZ;
    }
}
