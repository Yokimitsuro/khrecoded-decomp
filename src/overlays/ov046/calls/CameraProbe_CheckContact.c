#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactNormal {
    fx16 x;
    fx16 y;
    fx16 z;
} ContactNormal;

typedef struct ProbeShape {
    u8 pad_00[0x4];
    VecFx32 max;
    VecFx32 min;
    int kind;
} ProbeShape;

typedef struct CollisionOwner {
    u8 pad_00[0x14];
    ContactNormal normal;
    u8 pad_1a[0x24 - 0x1a];
    ProbeShape shape;
    u8 pad_44[0x28];
    int objectType;
} CollisionOwner;

typedef struct ContactRef {
    CollisionOwner *owner;
    int category;
} ContactRef;

typedef struct ContactQuery {
    u8 pad_00[0x4];
    VecFx32 direction;
    fx32 distance;
} ContactQuery;

typedef struct CameraProbe {
    u8 pad_00[0x10];
    ProbeShape shape;
    u32 hit : 1;
    s32 slowDown : 1;
    VecFx32 normal;
} CameraProbe;

typedef struct ProbeSource {
    VecFx32 *base;
    u8 pad_04[0x1c];
    VecFx32 offset;
} ProbeSource;

typedef BOOL (*ShapeTestFn)(ProbeShape *self, ProbeShape *other, void *hit, int flags);

extern ShapeTestFn gCollisionTestPairDispatch[][6];
extern BOOL IsFacingContactNormal(ContactRef *ref, const VecFx32 *direction);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern s8 func_ov001_02068084(void);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetShapePosition(ProbeShape *shape, const VecFx32 *position);

static inline VecFx32 GetContactNormal(const ContactNormal *src)
{
    VecFx32 normal;
    normal.x = src->x;
    normal.y = src->y;
    normal.z = src->z;
    return normal;
}

static inline BOOL TestShapeOverlap(ProbeShape *shape, ProbeShape *other)
{
    if (shape->max.x >= other->min.x && shape->min.x <= other->max.x &&
        shape->max.z >= other->min.z && shape->min.z <= other->max.z &&
        shape->max.y >= other->min.y && shape->min.y <= other->max.y) {
        return gCollisionTestPairDispatch[shape->kind][other->kind](shape, other, NULL, 0);
    }
    return FALSE;
}

BOOL CameraProbe_CheckContact(ContactRef *ref, ContactQuery *query, CameraProbe *probe, ProbeSource *source)
{
    VecFx32 forward;
    VecFx32 position;
    VecFx32 normal;
    VecFx32 normalized;
    VecFx32 sum;

    if (!IsFacingContactNormal(ref, &query->direction)) {
        return FALSE;
    }
    func_01ffaff4(&source->offset, &normalized);
    forward = normalized;
    if (VEC_DotProduct(&forward, &query->direction) >= -0x80) {
        return FALSE;
    }
    if (AbsDotProduct(&query->direction, &probe->normal) > 0xffe) {
        return FALSE;
    }
    if (ref->category == 4) {
        if (func_ov001_02068084() != 5) {
            int type = ref->owner->objectType;
            if (type == 0x1e || type == 1 || type == 0x23) {
                VEC_Add(source->base, &source->offset, &sum);
                position = sum;
                SetShapePosition(&probe->shape, &position);
                if (!TestShapeOverlap(&probe->shape, &ref->owner->shape)) {
                    return FALSE;
                }
                probe->hit = TRUE;
            }
        }
    } else {
        normal = GetContactNormal(&ref->owner->normal);
        if (VEC_DotProduct(&normal, &source->offset) >= 0) {
            return FALSE;
        }
    }
    if (probe->slowDown) {
        if ((query->distance -= 0x80000) < 0) {
            query->distance = 0;
        }
    }
    return TRUE;
}


