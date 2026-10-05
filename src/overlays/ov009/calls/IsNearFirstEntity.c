#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct NearbyObject {
    u8 pad_00[0x40];
    VecFx32 position;
} NearbyObject;

extern VecFx32 *func_ov001_0206dc4c(int entityIndex);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

BOOL IsNearFirstEntity(NearbyObject *object)
{
    BOOL isNear = FALSE;

    if (VEC_Distance(&object->position, func_ov001_0206dc4c(0)) <= 0x2000) {
        isNear = TRUE;
    }
    return isNear;
}
