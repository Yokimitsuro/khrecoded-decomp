#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ProbeShape {
    u8 pad_00[0x4];
    VecFx32 max;
    VecFx32 min;
    int kind;
} ProbeShape;

typedef struct CollisionOwner {
    u8 pad_00[0x24];
    ProbeShape shape;
    u8 pad_44[0x28];
    int objectType;
} CollisionOwner;

typedef struct ContactRef {
    CollisionOwner *owner;
    int category;
    u8 surfaceType;
} ContactRef;

typedef struct ContactQuery {
    u8 pad_00[0x4];
    VecFx32 direction;
    fx32 speed;
} ContactQuery;

typedef struct CameraSweep {
    BOOL blocked;
    BOOL hit;
    VecFx32 direction;
    u8 pad_14[0x10];
    ProbeShape shape;
    void *contacts;
} CameraSweep;

typedef struct ProbeSource {
    VecFx32 *base;
    u8 pad_04[0x1c];
    VecFx32 offset;
} ProbeSource;

typedef BOOL (*ShapeTestFn)(ProbeShape *self, ProbeShape *other, void *hit, int flags);

extern ShapeTestFn gCollisionTestPairDispatch[][6];
extern BOOL IsFacingContactNormal(ContactRef *ref, const VecFx32 *direction);
extern s8 func_ov001_02068084(void);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void SetShapePosition(ProbeShape *shape, const VecFx32 *position);
extern void PushContact(void *list, CollisionOwner *owner, int category, u8 surfaceType, VecFx32 *normal);

static inline BOOL TestShapeOverlap(ProbeShape *shape, ProbeShape *other)
{
    if (shape->max.x >= other->min.x && shape->min.x <= other->max.x &&
        shape->max.z >= other->min.z && shape->min.z <= other->max.z &&
        shape->max.y >= other->min.y && shape->min.y <= other->max.y) {
        return gCollisionTestPairDispatch[shape->kind][other->kind](shape, other, NULL, 0);
    }
    return FALSE;
}

BOOL CameraSweep_CollectContact(ContactRef *ref, ContactQuery *query, CameraSweep *sweep, ProbeSource *source)
{
    if (!IsFacingContactNormal(ref, &query->direction)) {
        return FALSE;
    }
    if (ref->category == 4 && func_ov001_02068084() != 5) {
        int type = ref->owner->objectType;
        if (type == 0x1e || type == 1 || type == 0x23) {
            if (query->speed > 0) {
                VecFx32 position;
                VecFx32 sum;

                VEC_Add(source->base, &source->offset, &sum);
                position = sum;
                SetShapePosition(&sweep->shape, &position);
                if (!TestShapeOverlap(&sweep->shape, &ref->owner->shape)) {
                    return FALSE;
                }
                sweep->hit = TRUE;
            } else {
                sweep->hit = TRUE;
            }
        }
    }
    if (VEC_DotProduct(&sweep->direction, &query->direction) < 0) {
        sweep->blocked = TRUE;
    }
    PushContact(sweep->contacts, ref->owner, ref->category, ref->surfaceType, &query->direction);
    return FALSE;
}

