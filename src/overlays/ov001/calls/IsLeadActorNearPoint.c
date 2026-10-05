#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct NearbyPoint {
    u8 pad_00[0x40];
    VecFx32 position;
} NearbyPoint;

extern VecFx32 *func_ov001_0206dc4c(int slot);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

BOOL IsLeadActorNearPoint(NearbyPoint *point)
{
    BOOL isNear = FALSE;

    if (VEC_Distance(&point->position, func_ov001_0206dc4c(0)) <= 0x2000) {
        isNear = TRUE;
    }
    return isNear;
}
