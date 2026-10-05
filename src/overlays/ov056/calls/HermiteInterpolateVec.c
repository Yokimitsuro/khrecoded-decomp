#include "nitro/types.h"
#include "nitro/fx_types.h"

void HermiteInterpolateVec(VecFx32 *out, const VecFx32 *start, const VecFx32 *end, const VecFx32 *startTangent, const VecFx32 *endTangent, fx32 t)
{
    fx32 startX = start->x;
    fx32 startY = start->y;
    fx32 startZ = start->z;
    fx32 endX = end->x;
    fx32 endY = end->y;
    fx32 endZ = end->z;
    fx32 tanX = startTangent->x;
    fx32 tanY = startTangent->y;
    fx32 tanZ = startTangent->z;
    /* Quadratic terms reuse the end tangent X on every axis */
    fx32 endTanX = endTangent->x;
    fx32 cubicY = endTangent->y + (tanY + (startY - endY) * 2);
    fx32 cubicZ = endTangent->z + (tanZ + (startZ - endZ) * 2);
    s64 t1 = t;
    s64 t2 = (t1 * t1) >> 12;
    s64 t3 = (t2 * t1) >> 12;

    out->x = startX + (fx32)((t1 * tanX + (t3 * (endTanX + (tanX + (startX - endX) * 2)) + t2 * ((endX - startX) * 3 - endTanX - tanX * 2))) >> 12);
    out->y = startY + (fx32)((t1 * tanY + (t3 * cubicY + t2 * ((endY - startY) * 3 - endTanX - tanY * 2))) >> 12);
    out->z = startZ + (fx32)((t1 * tanZ + (t3 * cubicZ + t2 * ((endZ - startZ) * 3 - endTanX - tanZ * 2))) >> 12);
}
