#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
} PenetrationResult;

typedef struct {
    fx32 distance;
    VecFx32 normal;
    fx32 fraction;
    u8 contactFlags;
} CollisionContact;

extern void NegateVecFx32(VecFx32 *vec);

void WritePenetrationContact(const PenetrationResult *result, CollisionContact *contact, u32 flags)
{
    s8 axisSign;
    VecFx32 normal;
    u8 contactFlags;

    if (contact == NULL) {
        return;
    }
    contact->distance = result->depth;
    axisSign = result->axisSign;
    normal = result->axis;
    if (axisSign < 0) {
        NegateVecFx32(&normal);
    }
    contact->normal = normal;
    contact->contactFlags = result->featureId;
    if (flags & 1) {
        NegateVecFx32(&contact->normal);
        contactFlags = contact->contactFlags;
        contact->contactFlags = (contactFlags & ~3) | ((contactFlags & 1) << 1) | ((contactFlags & 2) >> 1);
    }
}
