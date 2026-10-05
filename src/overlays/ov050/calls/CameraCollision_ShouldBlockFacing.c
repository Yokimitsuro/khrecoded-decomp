#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShortVec {
    s16 x;
    s16 y;
    s16 z;
} ShortVec;

typedef struct CollisionShape {
    u8 pad_00[0x14];
    ShortVec normal;
    u8 pad_1a[0x52];
    s32 objectType;
} CollisionShape;

typedef struct CollisionObject {
    CollisionShape *shape;
    s32 category;
} CollisionObject;

typedef struct ContactQuery {
    u8 pad_00[0x20];
    VecFx32 direction;
} ContactQuery;

static inline VecFx32 ToVecFx32(const ShortVec *in)
{
    VecFx32 out;
    out.x = in->x;
    out.y = in->y;
    out.z = in->z;
    return out;
}

extern s32 ContainsMatchingEntry(CollisionObject *object, u32 kind);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

BOOL CameraCollision_ShouldBlockFacing(CollisionObject *object, void *unused, ContactQuery *query)
{
    VecFx32 normal;

    if (ContainsMatchingEntry(object, 4)) {
        return FALSE;
    }
    if (object->category == 4 &&
        (object->shape->objectType == 1 || object->shape->objectType == 0x17)) {
        return FALSE;
    }
    if (object->category != 4) {
        normal = ToVecFx32(&object->shape->normal);
        if (VEC_DotProduct(&query->direction, &normal) > 0) {
            return FALSE;
        }
    }
    return TRUE;
}
