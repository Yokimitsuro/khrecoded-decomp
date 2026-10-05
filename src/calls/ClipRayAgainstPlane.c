#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PlaneClipResult {
    s64 enterT;
    s64 exitT;
    VecFx32 enterNormal;
    s32 depth;
    VecFx32 depthNormal;
    u8 hasDepth;
    u8 depthId;
    u8 pad_2e[2];
    u8 hasEnter;
    u8 touching;
    u8 enterId;
} PlaneClipResult;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern s64 FX_DivFx64c(fx32 numerator, fx32 denominator);

BOOL ClipRayAgainstPlane(fx32 planeDist, fx32 startDist, const VecFx32 *normal, u8 id,
                                  const VecFx32 *direction, PlaneClipResult *result, s64 *outT) {
    s64 limit;
    s64 t;
    fx32 depth;
    fx32 dot = VEC_DotProduct(normal, direction);

    if (dot == 0) {
        if (startDist <= planeDist - 2) {
            t = (s64)0x8000000000000000LL;
            limit = 0x7fffffffffffffffLL;
            if (startDist == planeDist) {
                result->touching = TRUE;
            }
        } else {
            return FALSE;
        }
    } else {
        fx32 distance = startDist - planeDist;
        if ((s64)distance > 0 && dot > 0) {
            return FALSE;
        }
        if (dot < 0) {
            dot = -dot;
        }
        t = FX_DivFx64c(distance, dot);
        if (t > 0x100000000LL) {
            return FALSE;
        }
        limit = 0x100000000LL;
    }
    if (result->enterT < t && t >= 0) {
        result->enterT = t;
        result->enterNormal = *normal;
        result->hasEnter = TRUE;
        result->enterId = id;
    }
    if (limit < result->exitT) {
        result->exitT = limit;
    }
    if (t <= 0 && result->depth > (depth = planeDist - startDist)) {
        result->depth = depth;
        result->depthNormal = *normal;
        result->hasDepth = TRUE;
        result->depthId = id;
    }
    if (outT != NULL) {
        *outT = t;
    }
    return TRUE;
}
