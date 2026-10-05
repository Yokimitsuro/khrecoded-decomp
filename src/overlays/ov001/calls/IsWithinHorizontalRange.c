#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RangeObject {
    u8 pad_00[0x18];
    s32 range;
    u8 pad_1c[8];
    VecFx32 position;
} RangeObject;

extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

BOOL IsWithinHorizontalRange(RangeObject *object, const VecFx32 *target)
{
    VecFx32 objectFlat;
    VecFx32 targetFlat;

    if (object->range & 0x80000000) {
        return TRUE;
    }
    objectFlat = object->position;
    targetFlat = *target;
    objectFlat.y = 0;
    targetFlat.y = 0;
    return VEC_Distance(&objectFlat, &targetFlat) <= object->range;
}

